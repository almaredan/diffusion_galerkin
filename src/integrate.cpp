/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   integrate.cpp
 * Author: almaredan
 * 
 * Created on 11 апреля 2017 г., 11:11
 */

#include "integrate.h"

integrate::integrate() {
}

integrate::integrate(const integrate& orig) {
}

integrate::~integrate() {
}

double integrate::operator()(std::function< double (double) > f, double x0, double h) {
     return f(x0)*h  + ( f(x0+h/2) + f(x0-h/2) - 2*f(x0) )*h/6;
}



