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
    x0 = _x0;
    x1 = _x1;
    N = _N;
    h = (x1 - x0)/N;
    
    double M1_arr [] = {0, 1., 0,
                        0, 0, 1./6.,
                        0, 1./12., 0};
    double inv_M_arr [] = { 9./4., 0, -15,
                            0, 12, 0,
                            -15, 0, 180};
    M1.set_elements(M1_arr);
    inv_M.set_elements(inv_M_arr);
    inv_M /= h;
    
    T = _T;
    double cu = _cu;
    f = _f;
    uL = f(x0);
    uR = f(x1);
    for (int i = 0; i < N; ++i) {
        mesh.emplace_back(i*h + h/2);
        velocity.emplace_back(f.fact(mesh.at(i), h) * inv_M);
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
    std::cout << "Calculated    Real" << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << flow[i][0] <<
                " " << std::cos( mesh.at(i) ) <<
                " " << flow[i][0]/std::cos( mesh.at(i) ) << std::endl;
    }
}


void scheme::step_one() {
    Vector3D phi(1., .0, .0), phiPlus(1., 1./2., 1./4.),
                              phiMinus(1, -0.5, 0.25);
    flow.erase(flow.begin(), flow.end());
    flow[0] = inv_M*(velocity.at(1)*phiMinus - uL)*phi - 
            inv_M*M1*velocity.at(0);
    for (int i = 1; i < N-1; ++i) {
        flow[i] = inv_M*(velocity.at(i+1)*phiMinus - velocity.at(i-1)*phiPlus)*phi - 
            inv_M*M1*velocity.at(i);
    }
    flow[N-1] = inv_M*(uR - velocity.at(N - 2)*phiPlus)*phi - 
            inv_M*M1*velocity.at(N-1);
}


