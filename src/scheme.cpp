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
#define tol12 1.e-12

scheme::scheme() {
    
}

scheme::scheme(double _x0, double _x1, double _T, double _cu, right_part& _f, int _N) {
    x0 = _x0;
    x1 = _x1;
    num_of_nods = _N;
    h = (x1 - x0)/num_of_nods;
    
    double M1_arr [] = {tol12, 1., tol12,
                        tol12, tol12, 1./6.,
                        tol12, 1./12., tol12};
    double inv_M_arr [] = { 9./4., tol12, -15.,
                            tol12, 12., tol12,
                            -15., tol12, 180.};
    M1.set_elements(M1_arr);
    inv_M.set_elements(inv_M_arr);
    inv_M /= h;
    
    T = _T;
    cu = _cu;
    f = _f;
    uL = f(x0);
    uR = f(x1);
    for (int i = 0; i < num_of_nods; ++i) {
        mesh.emplace_back(i*h + h/2.);
        velocity.emplace_back(f.fact(mesh.at(i), h) * inv_M);
    }
    double tau = cu * h;
    num_of_iter = (int) (T/tau);
    
    flow.resize(num_of_nods);
}


scheme::scheme(const scheme& orig) {
}

scheme::~scheme() {
}

std::vector<Vector3D> scheme::getVelocity() const {
    return velocity;
}

std::vector<double> scheme::getMesh() const {
    return mesh;
}

void scheme::test_flow() {
    step_one();
    std::cout << "Calculated    Real" << std::endl;
    for (int i = 0; i < num_of_nods; ++i) {
        std::cout << flow[i][0] <<
                " " << std::cos( mesh.at(i) ) <<
                " " << flow[i][0]/std::cos( mesh.at(i) ) << std::endl;
    }
}


void scheme::step_one() {
    Vector3D phi(1., .0, .0), phiPlus(1., 1./2., 1./4.);
    flow[0] = inv_M*(velocity.at(0)*phiPlus - uL)*phi - 
            inv_M*M1*velocity.at(0);
    for (int i = 1; i < num_of_nods-1; ++i) {
        flow[i] = inv_M*(velocity.at(i)*phiPlus - velocity.at(i-1)*phiPlus)*phi - 
            inv_M*velocity.at(i)*M1;
    }
    flow[num_of_nods-1] = inv_M*(uR - velocity.at(num_of_nods - 2)*phiPlus)*phi - 
            inv_M*M1*velocity.at(num_of_nods-1);
}

void scheme::step_two() {
    Vector3D phi(1., .0, .0), phiMinus(1, -0.5, 0.25);
    for (int i = 0; i < num_of_nods-1; ++i) {
        velocity.at(i) = velocity.at(i) - tau*inv_M * ( flow.at(i)*M1 - 
                (flow.at(i+1)*phiMinus - flow.at(i)*phiMinus)*phi );
    }
    velocity.at(num_of_nods-1) = velocity.at(num_of_nods-1) - tau*inv_M * 
            ( flow.at(num_of_nods-1)*M1 - (.0 - flow.at(num_of_nods-1)*phiMinus)*phi );
}

std::vector<double> scheme::solve() {
    for (int i; i < num_of_iter; i++) {
        step_one();
        step_two();
    }
    std::vector<double> ret_vec;
    for (Vector3D _vel : velocity) {
        ret_vec.push_back(_vel.x);
    }
    return ret_vec;
}

int scheme::getN() const {
    return num_of_nods;
}

double scheme::getT() const {
    return T;
}
