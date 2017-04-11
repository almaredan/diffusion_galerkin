/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   right_part.cpp
 * Author: almaredan
 * 
 * Created on 11 апреля 2017 г., 11:08
 */

#include "right_part.h"

right_part::right_part() {
}

right_part::right_part(std::function<double (double)>& _f) {
    f = _f;
    f2 = [&](double x, double x0, double h) -> double {
        return f(x)*(x - x0)/h;
    };
    f3 = [&](double x, double x0, double h) -> double {
        return f(x)*(x - x0)*(x - x0)/(h * h);
    };
}

right_part::right_part(const right_part& orig) {
}

right_part::~right_part() {
}

Vector3D right_part::fact(double x0, double h) {
    integrate integral;
    std::function< double (double) > _f2 = [&](double x) -> double {
        return f2(x, x0, h);
    };
    std::function< double (double) > _f3 = [&](double x) -> double {
        return f3(x, x0, h);
    };
    Vector3D ret_vec(integral(f, x0, h), integral(_f2, x0, h),
            integral(_f3, x0, h));
    return ret_vec;
}

double right_part::operator()(double x) {
    return f(x);
}
