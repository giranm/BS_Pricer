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
#include "bscalc.h"
#include <cmath>
#include <math.h>

// Standard normal probability density function
double norm_pdf(const double& x) {
    return (1.0 / (pow(2 * M_PI, 0.5)))*exp(-0.5*x*x);
}

// An approximation to the cumulative distribution function
// for the standard normal distribution
// Note: This is a recursive function
double norm_cdf(const double& x) {
    double k = 1.0 / (1.0 + 0.2316419*x);
    double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));

    if (x >= 0.0) {
        return (1.0 - (1.0 / (pow(2 * M_PI, 0.5)))*exp(-0.5*x*x) * k_sum);
    }
    else {
        return 1.0 - norm_cdf(-x);
    }
}

// This calculates d_j, for j in {1,2}. This term appears in the closed
// form solution for the European call or put price
double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T, const double& div) {
    return (log(S / K) + ((r - div) + (pow(-1, j - 1))*0.5*v*v)*T) / (v*(pow(T, 0.5)));
}

// Calculate the European vanilla call price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double call_price(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div) {

    // Debugging call_price()
    qDebug("Call Inputs:\n");
    qDebug("S: %f", S);
    qDebug("K: %f", K);
    qDebug("r: %f", r);
    qDebug("v: %f", v);
    qDebug("T: %f", T);
    qDebug("Div: %f", div);

    qDebug("\nCalc Breakdown:\n");
    qDebug("d1: %f", d_j(1, S, K, r, v, T, div));
    qDebug("N(d1): %f", norm_cdf(d_j(1, S, K, r, v, T, div)));
    qDebug("-Ke^(-(r-div)T): %f", -K*exp(-(r - div)*T));
    qDebug("d2: %f", d_j(2, S, K, r, v, T, div));
    qDebug("N(d2): %f", norm_cdf(d_j(2, S, K, r, v, T, div)));
    qDebug("\n");

    return S * norm_cdf(d_j(1, S, K, r, v, T, div)) - K*exp(-(r - div)*T) * norm_cdf(d_j(2, S, K, r, v, T, div));
}

// Calculate the European vanilla put price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double put_price(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div) {

    // Debugging put_price()
    qDebug("Put Inputs:\n");
    qDebug("S: %f", S);
    qDebug("K: %f", K);
    qDebug("r: %f", r);
    qDebug("v: %f", v);
    qDebug("T: %f", T);
    qDebug("Div: %f", div);

    qDebug("\nCalc Breakdown:\n");
    qDebug("d1: %f", d_j(1, S, K, r, v, T, div));
    qDebug("N(-d1): %f", norm_cdf(-d_j(1, S, K, r, v, T, div)));
    qDebug("Ke^(-(r-div)T): %f", K*exp(-(r - div)*T));
    qDebug("d2: %f", d_j(2, S, K, r, v, T, div));
    qDebug("N(-d2): %f", norm_cdf(-d_j(2, S, K, r, v, T, div)));
    qDebug("\n");

    return -S*norm_cdf(-d_j(1, S, K, r, v, T, div)) + K*exp(-(r - div)*T) * norm_cdf(-d_j(2, S, K, r, v, T, div));
}

// Greek Calculations

// Delta
double call_delta(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div) {
    return norm_cdf(d_j(1, S, K, r, v, T, div));
}

double put_delta(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div) {
    return norm_cdf(d_j(1, S, K, r, v, T, div)) - 1;
}

// Gamma
double gamma(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div) {
    return norm_pdf(d_j(1, S, K, r, v, T, div)) / (S * v * pow(T, 0.5));
}

// Vega
double vega(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div) {
    return S * norm_pdf(d_j(1, S, K, r, v, T, div)) * pow(T, 0.5);
}

// Theta
double call_theta(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div) {
    return -((S * norm_pdf(d_j(1, S, K, r, v, T, div)) * v) / 2 * pow(T, 0.5)) - ((r - div) * K * exp(-(r - div) * T) * norm_cdf(d_j(2, S, K, r, v, T, div)));
}

double put_theta(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div) {
    return -((S * norm_pdf(d_j(1, S, K, r, v, T, div)) * v) / 2 * pow(T, 0.5)) + ((r - div) * K * exp(-(r - div) * T) * norm_cdf(-d_j(2, S, K, r, v, T, div)));
}

// Dv01 / Rho
double call_rho(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div) {
    return K * T * exp(-(r - div) * T) * norm_cdf(d_j(2, S, K, r, v, T, div));
}

double put_rho(const double& S, const double& K, const double& r, const double& v, const double& T, const double& div) {
    return -K * T * exp(-(r - div) * T) * norm_cdf(-d_j(2, S, K, r, v, T, div));
}
