/*
 *   Copyright (c) 2017, Giran Moodley
 *
 *   This file is part of BS_Pricer.
 *
 *   BS_Pricer is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Foobar is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with BS_Pricer. If not, see <http://www.gnu.org/licenses/>.
 *
 *   Date       Name        Revision
 *   20170316   GiranM      Initial Commit.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_calc_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
