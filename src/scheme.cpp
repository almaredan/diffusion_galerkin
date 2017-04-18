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

#include <complex>
#include <iostream>

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
    inv_M /= h;
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

void scheme::test_flow() {
    step_one();
    for (int i = 0; i < N; ++i) {
        std::cout << "Calculated: " << flow[i][0] <<
                " Real: " << std::cos( mesh.at(i) ) << std::endl;
    }
}


void scheme::step_one() {
    Vector3D phi(1., .0, .0);
    
    flow[0] = inv_M*(velocity.at(1)[0] - uL)*phi - 
            inv_M*M1*velocity.at(0);
    for (int i = 1; i < N-1; ++i) {
        flow[i] = inv_M*(velocity.at(i+1)[0] - velocity.at(i-1)[0])*phi - 
            inv_M*M1*velocity.at(i);
    }
    flow[N-1] = inv_M*(uR - velocity.at(N - 2)[0])*phi - 
            inv_M*M1*velocity.at(N-1);
}


