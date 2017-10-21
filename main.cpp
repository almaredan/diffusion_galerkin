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
    scheme medium(0, 2*M_PI, 1, 1.e-5, sin, 50, "medium");

    std::vector<double> medium_ans = medium.solve();
    std::vector<double> medium_mesh = medium.getMesh();
    std::vector<double> medium_ansAdd = medium.getVelocityAdded();
    std::vector<double> medium_meshAdd = medium.getMeshAdded();
    
    std::cout << "X;Vel;Exact" << std::endl;
    for (int i = 0; i < medium_ans.size(); i++) {
        std::cout << medium_mesh[i] << ";" << medium_ans[i] << ";"
                << std::exp(-1)*sin(medium_mesh[i]) << std::endl;
        std::cout << medium_meshAdd[i] << ";" << medium_ansAdd[i] << ";"
                << std::exp(-1)*sin(medium_meshAdd[i]) << std::endl;
    }
    
    
    return 0;
}

