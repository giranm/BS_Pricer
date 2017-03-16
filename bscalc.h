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
#ifndef BSCALC_H_INCLUDED
#define BSCALC_H_INCLUDED
#include <QDebug>

// Prototype function declaration.
double norm_pdf(const double& x);
double norm_cdf(const double& x);
double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T, const double& div);
double call_price(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div);
double put_price(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div);
double call_delta(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div);
double put_delta(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div);
double gamma(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div);
double vega(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div);
double call_theta(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div);
double put_theta(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div);
double call_rho(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div);
double put_rho(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div);

#endif // BSCALC_H
