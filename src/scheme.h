/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   scheme.h
 * Author: almaredan
 *
 * Created on 13 апреля 2017 г., 17:17
 */

#ifndef SCHEME_H
#define SCHEME_H

#include <vector>

#include "right_part.h"


class scheme {
public:
    scheme();
    scheme(double _x0, double _x1, double _T, double _cu, right_part& _f, int _N);
    scheme(const scheme& orig);
    void test_flow();
    virtual ~scheme();
    std::vector<Vector3D> getVelocity() const;
    std::vector<double> getMesh() const;
    std::vector<double> solve();
    int getN() const;
    double getT() const;
private:
    void step_one();
    void step_two();
    
    double x0, x1, h, T, cu, tau;
    int num_of_nods, num_of_iter;
    std::vector<double> mesh;
    std::vector<Vector3D> velocity, flow;
    right_part f;
    double uL;
    double uR;
    tensor3D M1, inv_M;
};

#endif /* SCHEME_H */

