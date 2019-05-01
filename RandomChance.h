#include <stdlib.h>
#include <iostream>
#include <iomanip>
using namespace std;

#ifndef RANDOMCHANCE_H
#define RANDOMCHANCE_H
    /*
        chancesOf(int) - returns a boolean based on how the inptut compares to a randomly generated number 1-100
        ie:
        chancesOf(0) always returns false
        chancesOf(50) returns true 50% of the time, returns false 50% of the time
        chancesOf(100) always returns true
    */
    bool chancesOf(int probability); //returns true based on the input percent chance (ie. input of 100 will ALWAYS return true, input of 0 ALWAYS returns false) 
    
    /*
        generateRandomNumber(int min, int max)
        returns a random integer between min and max
    */
    int generateRandomNumber(int min, int max);
#endif