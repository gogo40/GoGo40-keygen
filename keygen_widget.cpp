/// @file: keygen_widget.cpp
/*
 Copyright 2016 Péricles Lopes Machado

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include "keygen_widget.h"
#include "ui_keygen_widget.h"

#include <QDebug>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <thread>
#include <sstream>

KeyGen::KeyGen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KeyGen)
{
    pub_key_is_loaded = false;
    ui->setupUi(this);

    QObject::connect(this, SIGNAL(message(QString)),
                     ui->log,
                     SLOT(append(QString)),
                     Qt::QueuedConnection
                     );
    QObject::connect(this,
                     SIGNAL(enableGenKeys(bool)),
                     ui->generate_pub_key,
                     SLOT(setEnabled(bool)),
                     Qt::QueuedConnection);
}

KeyGen::~KeyGen()
{
    delete ui;
}

bool KeyGen::read_all_data(std::string& buffer, const QString& file_name)
{
    QFile file(file_name);

    file.open(QIODevice::ReadOnly);

    if (file.isOpen()) {
        QByteArray data = std::move(file.readAll());
        buffer = std::move(data.toStdString());
        file.close();
        return true;
    }


    return false;
}

bool KeyGen::load_pub_key(const QString& pub_key_file)
{
    ui->pub_key_file->setText(pub_key_file);

    pub_key_is_loaded = false;

    ui->log->clear();

    try {
        std::string buffer;

        if (read_all_data(buffer, pub_key_file)) {

            std::stringstream pub_in(buffer, std::ios_base::in);

            ui->log->append("[key-gen-widget] Carregando chave pública: " + pub_key_file);
            gogo40_keygen::KeyGen::load_public_key(pub_in, pub_key);
            pub_key_is_loaded = true;
        } else {
            ui->log->append("[key-gen-widget] Não foi possivel abrir arquivo: " + pub_key_file);
        }
    } catch( CryptoPP::Exception& e ) {
        ui->log->append("[key-gen] Um erro ocorreu: ");
        ui->log->append(e.what());
    }
    return pub_key_is_loaded;
}

void KeyGen::on_get_pub_key_clicked()
{
    QString pub_key_file = QFileDialog::getOpenFileName(this, "Selecione arquivo com a chave pública",
                                                        QDir::currentPath(),
                                                        "*.pub");

    if (pub_key_file == "") return;

    load_pub_key(pub_key_file);
}

void KeyGen::save_stream(std::ostringstream& out, const QString& message_file)
{
    QFile file_out(message_file);
    file_out.open(QIODevice::WriteOnly);
    std::string buffer = std::move(out.str());
    file_out.write(buffer.c_str(), buffer.size());
    file_out.close();
}

void KeyGen::on_generate_license_clicked()
{
    if (!pub_key_is_loaded) {
        if (!load_pub_key(ui->pub_key_file->text())) return;
    }

    QString message_file = QFileDialog::getSaveFileName(this,
                                                        "Salvar arquivo de licença",
                                                        QDir::currentPath(),
                                                        "*.crt");

    if (message_file == "") return;

    QStringList l = message_file.split(".");
    int s = l.size() - 1;
    if (l[s] != "crt") {
        message_file += ".crt";
    }

    ui->log->clear();

    if (!pub_key_is_loaded) {
        ui->log->append("Por favor, selecione um arquivo com uma chave pública válida...\n");
        return;
    }

    QString name = ui->name->text();
    QString group = ui->group->text();
    QString mac = ui->mac->text();
    QDate date = ui->expiration_date->selectedDate();
    int year = date.year();
    int month = date.month();
    int day = date.day();

    ui->log->append("[key-gen-widget] Gerando licença...");
    ui->log->append("[key-gen-widget] Proprietário: " + name);
    ui->log->append("[key-gen-widget] Empresa: " + group);
    ui->log->append("[key-gen-widget] MAC: " + mac);
    ui->log->append("[key-gen-widget] Data de expiração: " + QString::number(day) +
                    "/" + QString::number(month) + "/" + QString::number(year));


    QJsonObject license;

    license.insert("name", name);
    license.insert("group", group);
    license.insert("MAC", mac);
    license.insert("expiration", date.toString());

    QJsonDocument doc(license);
    QByteArray json = std::move(doc.toJson());
    std::string std_json = std::move(json.toStdString());
    std::string cipher;

    gogo40_keygen::KeyGen key_gen;

    key_gen.encrypt(pub_key, std_json, cipher);

    {
        std::ostringstream out(std::ios_base::binary | std::ios_base::out);
        gogo40_keygen::save_message(out, cipher);

        save_stream(out, message_file);
    }

    std::string output = "";
    if (!read_all_data(output, message_file)) {
        ui->log->append("[key-gen-widget] Certificado foi corrompido!");
    } else {
        ui->log->append("[key-gen-widget] Licença:\n" + doc.toJson());
        ui->log->append("[key-gen-widget] Licença encriptada:\n" + QString(output.c_str()));
        ui->log->append("[key-gen-widget] O arquivo de licença foi salvo em: " + message_file);

        ui->license_file->setText(message_file);
    }
}

void KeyGen::on_generate_pub_key_clicked()
{
    QString base_name = QFileDialog::getSaveFileName(this, "Nome base para salvar as chaves",
                                                     QDir::currentPath());

    if (base_name == "") return;

    QString pub_key_file = base_name + ".pub";
    QString pri_key_file = base_name + ".pri";

    ui->log->clear();

    ui->log->append("[key-gen-widget] Gerando chaves...");

    int key_size = ui->key_size->value();

    ui->generate_pub_key->setEnabled(false);

    auto job = [=](){
        gogo40_keygen::KeyGen key_gen;
        std::ostringstream pub_out(std::ios_base::binary | std::ios_base::trunc);
        std::ostringstream pri_out(std::ios_base::binary | std::ios_base::trunc);

        key_gen.generate_keys(pub_out, pri_out, key_size);

        save_stream(pub_out, pub_key_file);
        save_stream(pri_out, pri_key_file);

        emit message("[key-gen-widget] Chaves gravadas nos arquivos:" +
                     pub_key_file + " e " + pri_key_file);
        emit enableGenKeys(true);
    };

    (new StdWorker(job))->start();

    ui->pub_key_file->setText(pub_key_file);
    ui->private_key->setText(pri_key_file);
}

void KeyGen::on_get_license_file_clicked()
{
    QString license_file = QFileDialog::getOpenFileName(this, "Carregar arquivo de licença",
                                                        QDir::currentPath(),
                                                        "*.crt");
    if (license_file == "") return;

    ui->license_file->setText(license_file);

}

void KeyGen::on_get_private_key_clicked()
{
    QString pri_key_file = QFileDialog::getOpenFileName(this, "Carregar chave privada",
                                                        QDir::currentPath(),
                                                        "*.pri");

    if (pri_key_file == "") return;

    ui->private_key->setText(pri_key_file);
}

void KeyGen::on_test_license_clicked()
{
    ui->test_license_log->clear();
    QString license_file = ui->license_file->text();
    QString private_key_file = ui->private_key->text();

    gogo40_keygen::KeyGen key_gen;
    CryptoPP::RSA::PrivateKey pri_key;



    try {

        std::string cipher = "";
        std::string message = "";

        {
            std::string input = "";
            bool ok = read_all_data(input, license_file);

            if (!ok) {
                ui->test_license_log->append("[key-gen-widget] Arquivo de licença " +
                                             license_file +
                                             " não é válido.");
                return;
            }

            std::istringstream lic_in(input, std::ios_base::binary | std::ios_base::in);
            gogo40_keygen::load_message(lic_in, cipher);
        }

        {
            std::string input = "";
            bool ok = read_all_data(input, private_key_file);

            if (!ok) {
                ui->test_license_log->append("[key-gen-widget] Arquivo de chave privada " +
                                             private_key_file +
                                             " não é válido.");
                return;
            }

            std::istringstream pri_in(input, std::ios_base::binary | std::ios_base::in);
            key_gen.load_private_key(pri_in, pri_key);
        }

        key_gen.decrypt(pri_key, cipher, message);

        ui->test_license_log->append("[key-gen-widget] Licença desencriptada: " + QString(message.c_str()));
    } catch( CryptoPP::Exception& e ) {
        ui->test_license_log->append("[key-gen] Um erro ocorreu: ");
        ui->test_license_log->append(e.what());
    }
}
