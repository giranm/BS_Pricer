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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bscalc.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage(QString::fromStdString("Copyright (c) 2017, Giran Moodley"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_calc_clicked()
{

    // Extract inputs from form.
    double S = ui->inp_spot->value();
    double K = ui->inp_strike->value();
    double T = ui->inp_maturity->value();
    double r = ui->inp_intrate->value() / 100;
    double v = ui->inp_vol->value() / 100;
    double div = ui->inp_div->value() / 100;
    string type = ui->inp_type->currentText().toStdString();

    // Verify if div, r and v are zero. If so, throw an error.
    if (div == 0.0 && r == 0.0 && v == 0.0) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Must specify at least one non-zero parameter for volatility, dividend or interest rate!");
        msgBox.exec();
        return;
    }

    // Initialise output variables.
    double fair = 0.0;
    double delta = 0.0;
    double gammaVal = 0.0;
    double vegaVal = 0.0;
    double theta = 0.0;
    double rho = 0.0;
    string statusStr = "";

    // Given type, calculate fair and greeks accordingly.
    gammaVal = gamma(S, K, r, v, T, div);
    vegaVal = vega(S, K, r, v, T, div);
    if (type == "Call") {

        fair = call_price(S, K, r, v, T, div);
        delta = call_delta(S, K, r, v, T, div);
        theta = call_theta(S, K, r, v, T, div);
        rho = call_rho(S, K, r, v, T, div);
        statusStr = "Call Calculated";

    } else {

        fair = put_price(S, K, r, v, T, div);
        delta = put_delta(S, K, r, v, T, div);
        theta = put_theta(S, K, r, v, T, div);
        rho = put_rho(S, K, r, v, T, div);
        statusStr = "Put Calculated";

    }

    // Write data to output fields.
    ui->out_fair->setText(QString::number(fair));
    ui->out_delta->setText(QString::number(delta * 100));
    ui->out_gamma->setText(QString::number(gammaVal * 100));
    ui->out_vega->setText(QString::number(vegaVal / 100));
    ui->out_theta->setText(QString::number(theta / 365));
    ui->out_rho->setText(QString::number(rho / 100));
    ui->out_status->setText(QString::fromStdString(statusStr));

}
