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

bool KeyGen::load_pub_key(QString pub_key_file)
{
    ui->pub_key_file->setText(pub_key_file);

    pub_key_is_loaded = false;

    ui->log->clear();

    try {
        std::string file_name = pub_key_file.toStdString();
        std::ifstream pub_in(file_name.c_str(), std::ios_base::binary);

        if (pub_in.is_open()) {
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
        std::string file_name = message_file.toStdString();
        std::ofstream out(file_name.c_str(), std::ios_base::binary);
        gogo40_keygen::save_message(out, cipher);
    }

    std::string output;
    {
        std::string file_name = message_file.toStdString();
        std::ifstream in(file_name.c_str());
        std::string line;
        while (in >> line) {
            output += line;
        }
    }

    ui->log->append("[key-gen-widget] Licença:\n" + doc.toJson());
    ui->log->append("[key-gen-widget] Licença encriptada:\n" + QString(output.c_str()));
    ui->log->append("[key-gen-widget] O arquivo de licença foi salvo em: " + message_file);
}

void KeyGen::on_generate_pub_key_clicked()
{
    QString base_name = QFileDialog::getSaveFileName(this, "Nome base para salvar as chaves",
                                                     QDir::currentPath());

    if (base_name == "") return;

    QString qpub_key = base_name + ".pub";
    QString qpri_key = base_name + ".pri";

    std::string pub_key_file = qpub_key.toStdString();
    std::string pri_key_file = qpri_key.toStdString();

    ui->log->clear();

    ui->log->append("[key-gen-widget] Gerando chaves...");

    int key_size = ui->key_size->value();

    ui->generate_pub_key->setEnabled(false);
    auto job = [=](){
        gogo40_keygen::KeyGen key_gen;
        std::ofstream pub_out(pub_key_file, std::ios_base::binary | std::ios_base::trunc);
        std::ofstream pri_out(pri_key_file, std::ios_base::binary | std::ios_base::trunc);

        key_gen.generate_keys(pub_out, pri_out, key_size);


        emit message("[key-gen-widget] Chaves gravadas nos arquivos:" +
                     qpub_key + " e " + qpri_key);
        emit enableGenKeys(true);
    };

    (new StdWorker(job))->start();
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
    QString qlic_file = ui->license_file->text();
    QString qpri_file = ui->private_key->text();

    std::string license_file = qlic_file.toStdString();
    std::string pri_key_file = qpri_file.toStdString();

    gogo40_keygen::KeyGen key_gen;
    CryptoPP::RSA::PrivateKey pri_key;

    std::string cipher = "";
    std::string message = "";

    try {
        std::string input = "";
        std::string line = "";

        {
            std::ifstream lic_in(license_file.c_str());
            if (!lic_in.is_open()) {
                ui->test_license_log->append("[key-gen-widget] Arquivo de licença " + qlic_file + " não é válido.");
                return;
            }
            gogo40_keygen::load_message(lic_in, cipher);
        }

        {
            std::ifstream pri_in(pri_key_file.c_str(), std::ios_base::binary);
            if (!pri_in.is_open()) {
                ui->test_license_log->append("[key-gen-widget] Arquivo de chave privada " + qpri_file + " não é válido.");
                return;
            }

            key_gen.load_private_key(pri_in, pri_key);
        }

        key_gen.decrypt(pri_key, cipher, message);

        ui->test_license_log->append("[key-gen-widget] Licença desencriptada: " + QString(message.c_str()));
    } catch( CryptoPP::Exception& e ) {
        ui->test_license_log->append("[key-gen] Um erro ocorreu: ");
        ui->test_license_log->append(e.what());
    }
}
