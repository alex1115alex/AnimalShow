// Author: Alexander Israelov
// Recitation: 107 – Andrew Altomare
// Cloud9 Workspace Editor Link: https://ide.c9.io/alexisraelov/csci1300
// AnimalChampionship.h

#ifndef ANIMALCHAMPIONSHIP_H
#define ANIMALCHAMPIONSHIP_H
#include "AnimalShow.h"
#include "Animal.h"
#include "Player.h"
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class AnimalChampionship
{
    string name;
    int animalsSold;
    int numShows;
    int day;
    string file;
    vector<AnimalShow> animalShows; //vector array of AnimalShow objects
    vector<Animal> famousAnimals; //vector array of Animals. It holds the animals from the hall of fame.
    public:
        AnimalChampionship(string fileName); //paramerized constructor
        
        int readShows(string fileName); //reads a list of shows
        int getDaysUntilNextShow(); //returns the number of days until the next show. If there are no more shows, return -1;
        AnimalShow getNextShow(); //returns the next upcoming AnimalShow
        void printAllShows();
        
        int getAnimalsSold(); //returns the number of animals sold to the player
        int getCurrentDay(); //returns the current day
        void incrementDay(); //increments the day
        
        bool createShow(Animal famousAnimal, string fileName, string myName, int myDay, int myDifficulty, int myTemperature, int myPrize); //allows the user to design their own AnimalShows to compete in! Returns true if successful.
        int readHallOfFame(string fileName); //reads animals from the hall of fame
        bool appendHallOfFame(string fileName, Animal famousAnimal);
        void printAllFamousAnimals();
};

#endif
