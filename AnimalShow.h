// Author: Alexander Israelov
// Recitation: 107 – Andrew Altomare
// Cloud9 Workspace Editor Link: https://ide.c9.io/alexisraelov/csci1300
// AnimalShow.h

#ifndef ANIMALSHOW_H
#define ANIMALSHOW_H
#include <iostream>
#include "Animal.h"
using namespace std;

class AnimalShow
{
    string name; //represents the name of this AnimalShow object
    int day; //represents the day this AnimalShow object takes place on
    int difficulty; //the difficulty (1-10) of this particular AnimalShow object
    int temperature; //represets the climate (in Fahrenheit) of this AnimalShow object
    int prize;
    Animal boss; //each AnimalShow object has a "Boss" that the player competes against
    public:
        AnimalShow(string myName, int myDay, int myDifficulty, int myTemperature, string bossName, string bossSpecies, string bossSound, int bossSkill, int bossHealth, int bossFood, int bossAge, int bossDaysHungry, int bossIdealTemperature, int bossIsSick, int bossNumShowsWon, int myPrize); //parameterized constructor
        
        string getName(); //returns this AnimalShow's name
        int getDay(); //returns the day this AnimalShow takes place
        int getDifficulty(); //returns this object's difficulty
        int getTemperature(); //returns the temperature
        int getPrize();
        
        Animal getBoss(); //returns this AnimalShow object's boss
        
        bool compete(Animal competetor); //compete against the boss with the provided Animal. Returns true if the argument Animal wins.
        
        void printInfo();
};

#endif
