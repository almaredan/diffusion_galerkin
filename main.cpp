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
    scheme bassi_rebay(0, M_PI, 1, 1, sin, 10);
    bassi_rebay.test_flow();
    
    return 0;
}

