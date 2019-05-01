#include "RandomChance.h"
#include <iostream>
#include <iomanip>
using namespace std;

bool chancesOf(int probability)
{
    return ((rand() % 100 + 1) <= probability); // returns whether a random number 1-100 is less than the input number
}

int generateRandomNumber(int min, int max) //generates a random number between min and max
{
    return (rand() % (max - min + 1) + (min));
}