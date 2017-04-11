/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   right_part.h
 * Author: almaredan
 *
 * Created on 11 апреля 2017 г., 11:08
 */

#include <functional>
#include "integrate.h"
#include "../vector3d.h"

#ifndef RIGHT_PART_H
#define RIGHT_PART_H

class right_part {
public:
    right_part();
    right_part(std::function<double (double)>& _f);
    right_part(const right_part& orig);
    double operator() (double x);
    Vector3D fact (double x, double h);
    virtual ~right_part();
private:
    std::function<double (double)> f;
    std::function<double (double, double, double)> f2;
    std::function<double (double, double, double)> f3;
};

#endif /* RIGHT_PART_H */

