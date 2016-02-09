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

namespace Ui {
class KeyGen;
}

class KeyGen : public QMainWindow
{
    Q_OBJECT

public:
    explicit KeyGen(QWidget *parent = 0);
    ~KeyGen();

private:
    Ui::KeyGen *ui;
};

#endif // KEYGEN_WIDGET_H
