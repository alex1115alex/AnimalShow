// Author: Alexander Israelov
// Recitation: 107 – Andrew Altomare
// Cloud9 Workspace Editor Link: https://ide.c9.io/alexisraelov/csci1300
// Book.h

#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
using namespace std;

class Animal
{
    string name;
    string species;
    string sound;
    int skill; //should be randomly generated 1-10
    int health; //max of 10. If it hits zero, the animal dies
    int food; //max of 10. If it hits zero, or stays below 4 for too long, the animal will starve
    int age; //age in days
    int daysHungry; //how many days the animal has gone hungry
    int idealTemperature; //the Animal object's ideal tempterature
    bool isSick; //default to false
    int animalShowsWon;
    
    public:
        Animal(); //default constructor
        Animal(string myName, string mySpecies, string mySound); //parameterized constructor
        Animal(string myName, string mySpecies, string mySound, int mySkill); //parameterized constructor with input for skill
        Animal(string myName, string mySpecies, string mySound, int mySkill, int myHealth, int myFood, int myAge, int myDaysHungry, int myIdealTemperature, bool myIsSick, int myAnimalShowsWon); //parameterized constructor with inputs for everything. To be used for saving/loading animals from the hall of fame.
        
        //GETTERS
        string getName(); //returns the animal's name
        string getSpecies(); //returns the animal's species
        string getSound(); //returns the animal's sound
        int getSkill(); //returns the animal's skill
        int getHealth(); //returns the animal's health
        int getFood(); //returns the amount of food the animal has
        int getAge(); //returns age
        int getTemperature(); //returns the animal's ideal temperature
        int getDaysHungry();
        bool getIsSick(); //returns true if the animal is sick
        int getAnimalShowsWon();
        
        void feedAnimal(int amtFood); //change this function's name to eat(int amtFood)
        void loseFood(int amtFood); //lose food by amtFood
        
        void loseHealth(int amtHealth); //lose health by amtHealth
        
        //Skill stuff
        void raiseSkill(int amtSkill); //raises the skill stat by amtSkill
        void loseSkill(int amtSkill); //reduces the skill stat by amtSkill
        
        //Bad things that can happen to an animal
        void getHypothermia();
        void getSick();
        void overheat();
        void vomit(); //vomit - lose food and health
        void starve();
        void incrementDaysHungry(); //increment daysHungry
        void getEaten();
        void die();

        void incrementAnimalShowsWon(); //increments animalShowsWon
        void increaseAge();
        bool getCured(); //Returns true if the animal was successfully cured, false if not
        
        void printStats(); //print this animal's stats
};

#endif
