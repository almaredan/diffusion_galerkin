/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: almaredan
 *
 * Created on 11 апреля 2017 г., 10:34
 */

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <complex>
#include"src/right_part.h"
#include "src/scheme.h"

//using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {
    
    std::function<double (double)> f = [](double x) -> double {
        return std::sin(x);
    };
    
    right_part sin(f);
<<<<<<< HEAD
    scheme medium(0, 2*M_PI, 1, 1.e-5, sin, 50, "medium");
    scheme corse(0, 2*M_PI, 1, 1.e-5, sin, 25, "corse");

    std::vector<double> medium_ans = medium.solve();
    std::vector<double> medium_mesh = medium.getMesh();
    std::vector<double> corse_ans = corse.solve();
    std::vector<double> corse_mesh = corse.getMesh();
    
    int i = 0;
    double max_err_medium = 0;
    for (double ans : medium_ans) {
        if (max_err_medium < std::abs(ans - medium_mesh[i])) 
                max_err_medium = std::abs(ans - std::exp(-1.)*sin(medium_mesh[i]));
        ++i;
    }
    
    i = 0;
    double max_err_corse = 0;
    for (double ans : corse_ans) {
        if (max_err_corse < std::abs(ans - corse_mesh[i])) 
                max_err_corse = std::abs(ans - std::exp(-1.)*sin(corse_mesh[i]));
        ++i;
    }
    
    double p = log(max_err_corse/max_err_medium) / 
               log(corse.getH() / medium.getH());
    
    std::cout << p << std::endl;
=======
    scheme fine(0, M_PI, 1, 0.01, sin, 10);
    fine.test_flow();
//    std::vector<double> out_vel = fine.solve();
//    std::vector<double> mesh = fine.getMesh();
//    for (int i = 0; i < fine.getN(); ++i) {
//        std::cout << out_vel.at(i) << " " << (fine.getT() / M_E) * sin(mesh.at(i)) <<
//                " " << abs(out_vel.at(i) - (fine.getT() / M_E) * sin(mesh.at(i)))
//                << std::endl;
//    }
>>>>>>> test
    
    return 0;
}

