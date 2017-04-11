/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   integrate.h
 * Author: almaredan
 *
 * Created on 11 апреля 2017 г., 11:11
 */

#include <cstdlib>
#include <functional>

#ifndef INTEGRATE_H
#define INTEGRATE_H

class integrate{
public:
    integrate();
    integrate(const integrate& orig);
    double operator() (std::function<double(double)> f,
                        double x0, double h);
    virtual ~integrate();
private:

};

#endif /* INTEGRATE_H */

