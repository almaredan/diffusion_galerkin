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
#include"src/right_part.h"

//using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    std::function<double (double)> f = [](double x) -> double {
        return std::sin(x);
    };
    
    right_part sin(f);
    Vector3D tmp_vec;
    tmp_vec = sin.fact(M_PI_2, M_PI);
    std::cout << tmp_vec[0] << " " << tmp_vec[1] << " " << tmp_vec[2] << std::endl;
    
    return 0;
}

