/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   scheme.cpp
 * Author: almaredan
 * 
 * Created on 13 апреля 2017 г., 17:17
 */

#include "scheme.h"

scheme::scheme() {
    
}

scheme::scheme(double _x0, double _x1, double _T, double _cu, right_part& _f, int _N) {
    M1(1, 0) = 1;
    M1(1, 2) = 1/12;
    M1(2, 1) = 1/6;
    inv_M(0, 0) = 9/4;
    inv_M(0, 2) = -15;
    inv_M(1, 1) = 12;
    inv_M(2, 0) = -15;
    inv_M(2, 2) = 180;
    x0 = _x0;
    x1 = _x1;
    T = _T;
    double cu = _cu;
    f = _f;
    N = _N;
    uL = f(x0);
    uR = f(x1);
    h = (x1 - x0)/N;
    inv_M *= (1/h);
    for (int i = 0; i < N; ++i) {
        mesh.emplace_back(i + h/2);
        velocity.emplace_back(inv_M * f.fact(mesh.at(i), h));
    }
    double tau = cu * h;
    num_of_iter = (int) (T/tau);
    
    flow.resize(N);
}


scheme::scheme(const scheme& orig) {
}

scheme::~scheme() {
}

