//Functions to use in game.cpp and main.cpp
#pragma once

#include <raylib.h>
#include <math.h>
//#include "structures.hpp"

namespace glogal_functions{

char* unconstchar(const char* s) {
    if(!s)
      return NULL;
    int i;
    char* res = NULL;
    res = (char*) malloc(strlen(s)+1);
    if(!res){
        fprintf(stderr, "Memory Allocation Failed! Exiting...\n");
        exit(EXIT_FAILURE);
    } else{
        for (i = 0; s[i] != '\0'; i++) {
            res[i] = s[i];
        }
        res[i] = '\0';
        return res;
    }
}

double torad(double x){
    double rad = (x * M_PI) / 180;
    return rad;
} 

}
