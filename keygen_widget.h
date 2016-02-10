/// @file: keygen_widget.h
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

#ifndef KEYGEN_WIDGET_H
#define KEYGEN_WIDGET_H

#include <QMainWindow>
#include <QThread>
#include <functional>
#include <QFile>
#include <QDebug>
#include "keygen.h"

namespace Ui {
class KeyGen;
}

class StdWorker : public QObject {
    Q_OBJECT
public:
    using StdJob = std::function<void()>;

    StdWorker(StdJob _job) : QObject(0), job(_job), thread() {
        connect(&thread, SIGNAL(started()), this, SLOT(process()));
        connect(&thread, SIGNAL(finished()), this, SLOT(deleteLater()));

        this->moveToThread(&thread);
    }

    virtual ~StdWorker() {
        qDebug() << "delete stdWorker...\n";
    }

    void start() {
        thread.start();
    }


private slots:
    void process() {
        job();
    }


signals:
    void finished();
    void error(QString err);
private:
    StdJob job;
    QThread thread;
};

class KeyGen : public QMainWindow
{
    Q_OBJECT

public:
    explicit KeyGen(QWidget *parent = 0);
    ~KeyGen();

private slots:
    void on_get_pub_key_clicked();

    void on_generate_license_clicked();

    void on_generate_pub_key_clicked();

    void on_get_license_file_clicked();

    void on_get_private_key_clicked();

    void on_test_license_clicked();

signals:
    void message(QString);
    void enableGenKeys(bool);

private:
    Ui::KeyGen *ui;

    CryptoPP::RSA::PublicKey pub_key;

    bool pub_key_is_loaded;
    bool load_pub_key(const QString& pub_key_file);
    bool read_all_data(std::string& buffer, const QString& file_name);
    void save_stream(std::ostringstream& out, const QString& message_file);
};

#endif // KEYGEN_WIDGET_H
