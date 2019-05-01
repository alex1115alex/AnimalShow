//REPRESENTS AN ANIMAL
// Author: Alexander Israelov
// Recitation: 107 – Andrew Altomare
// Cloud9 Workspace Editor Link: https://ide.c9.io/alexisraelov/csci1300
// Animal.cpp

#include "Animal.h"
#include "RandomChance.cpp"
#include <iostream>
#include <iomanip>
using namespace std;

Animal::Animal() //default constructor
{ 
    name = "Quacker";
    species = "Duck";
    sound = "QUACK QUACK";
    skill = generateRandomNumber(1, 10); //should be randomly generated 1-10
    health = 10;
    food = 10;
    age = 0;
    daysHungry = 0;
    idealTemperature = generateRandomNumber(1, 100); //should be randomly generated 1-100;
    isSick = false;
    animalShowsWon = 0;
}

Animal::Animal(string myName, string mySpecies, string mySound) //parameterized constructor
{
    name = myName;
    species = mySpecies;
    sound = mySound;
    skill = generateRandomNumber(1, 10); //should be randomly generated
    health = 10;
    food = 10;
    age = 0;
    daysHungry = 0;
    idealTemperature = generateRandomNumber(1, 100); //should be randomly generated 1-100;
    isSick = false;
    animalShowsWon = 0;
}

Animal::Animal(string myName, string mySpecies, string mySound, int mySkill) //parameterized constructor with option for skill
{
    name = myName;
    species = mySpecies;
    sound = mySound;
    skill = mySkill;
    health = 10;
    food = 10;
    age = 0;
    daysHungry = 0;
    idealTemperature = generateRandomNumber(1, 100); //should be randomly generated 1-100;
    isSick = false;
    animalShowsWon = 0;
}

Animal::Animal(string myName, string mySpecies, string mySound, int mySkill, int myHealth, int myFood, int myAge, int myDaysHungry, int myIdealTemperature, bool myIsSick, int myAnimalShowsWon) //parameterized constructor with parameters for everything
{
    name = myName;
    species = mySpecies;
    sound = mySound;
    skill = mySkill;
    health = myHealth;
    food = myFood;
    age = myAge;
    daysHungry = myDaysHungry;
    idealTemperature = myIdealTemperature; //should be randomly generated 1-100;
    isSick = myIsSick;
    animalShowsWon = myAnimalShowsWon;
}

string Animal::getName()
{
    return name;
}

string Animal::getSpecies()
{
    return species;
}

string Animal::getSound()
{
    return sound;
}

int Animal::getSkill()
{
    return skill;
}

int Animal::getHealth()
{
    return health;    
}

int Animal::getFood()
{
    return food;    
}

int Animal::getAge()
{
    return age;
}

bool Animal::getIsSick()
{
    return isSick;
}

int Animal::getDaysHungry()
{
    return daysHungry;
}

int Animal::getAnimalShowsWon()
{
    return animalShowsWon;
}

void Animal::raiseSkill(int amtSkill)
{
    if(skill + amtSkill > 10)
        skill = 10;
    else
        skill += amtSkill;
}

void Animal::loseSkill(int amtSkill)
{
    cout << name << " lost " << amtSkill << " skill points!" << endl;
    if(skill - amtSkill < 0)
        skill = 0;
    else
        skill -= amtSkill;
}

int Animal::getTemperature()
{
    return idealTemperature;
}

void Animal::die()
{
    health = 0; //this is for edge cases in which health drops below 0
    cout << sound << "!\n" << name << " has died!" << endl; //rip
}

void Animal::overheat()
{
    cout << name << " is overheating!" << endl;
    getSick();
}

void Animal::starve()
{
    cout << name << " is starving!" << endl;
    food = 0; //set food to 0
    loseHealth(3);
}

void Animal::loseHealth(int amtHealth)
{
    cout << name << " lost " << amtHealth << " health points!" << endl;
    if(health - amtHealth <= 0) //If their health drops all the way down, it dies
    {
        die();
    }
    else //otherwise just subtract health by amtHealth
    {
        health -= amtHealth;
    }
}

void Animal::loseFood(int amtFood)
{
    cout << name << " lost " << amtFood << " food!" << endl;
    if(amtFood > food)
        food = 0;
    else
        food -= amtFood;
}

void Animal::incrementDaysHungry() //increments daysHungry
{
    daysHungry++;
    cout << name << " is hungry!" << endl;
}

bool Animal::getCured() //animal in question gets cured
{
    if(chancesOf(50)) //50% chance of being cured
    {
        cout << name << " has been cured!\nIt's no longer sick!" << endl;
        isSick = false;
    }
    else //animal is not cured
    {
        cout << name << " was not cured." << endl;
    }
}

void Animal::vomit()
{
    cout << name << " has vomitted!\nIt puked out 3 food, and lost 2 health!" << endl;
    loseFood(3);
    loseHealth(2);
}

void Animal::getSick() //the animal in question gets sick
{
    if(!isSick) //animal is currently not sick
    {
        cout << name << " got sick!\nGive it some medicine!" << endl;
        isSick = true;
    }
    else //if the animal is currently sick
    {
        cout << name << " is still sick!" << endl;
    }
}

void Animal::getHypothermia()
{
    cout << name << " caught hypothermia!" << endl;
    loseSkill(2);
    loseHealth(3);    
}

void Animal::getEaten()
{
    if(health != 0) //if alive
    {
        cout << name << " was eaten by a wild animal!" << endl;
        die();
    }
}

void Animal::feedAnimal(int amtFood) 
{
    cout << name << " has gained " << amtFood << " pounds of food." << endl;
    if(food + amtFood > 10) //if you've overfed the animal
        vomit(); //it vomits
    else
        food = food + amtFood; //add to food by amtFood
}

void Animal::increaseAge() //age by 1 day. Call this for each animal at the start of each day
{
    if(health != 0)
    {
        age++;
        
        if(food != 0) //if the animal has food
            loseFood(1);
        else //if the animal does not have food,
            starve(); //starve
            
        if(food <= 3 && food > 0) //if food = 1, 2 or 3
            incrementDaysHungry(); //increment daysHungry
        else if(food > 3) //if it's decently fed, reset daysHungry
            daysHungry = 0;
            
        if(daysHungry > 4 && food != 0) //if you've been keeping the animal on low food for over 4 days, it will starve
            starve();
            
        if(chancesOf(7 * animalShowsWon)) //(7 * animalShowsWon)% chance something bad will happen to the animal every day. This is to discourage the player from repeatedly winning shows with the same animal.
        {
            switch(generateRandomNumber(1, 3)) //generate a random number 1 - 4 to decide what happens
            {
                case 1: //temperature related debuff
                    if(idealTemperature > 50) //if the animal prefers a warm climate
                        getHypothermia(); //get hypothermia
                    else //otherwise, if the animal prefers a colder climate
                        overheat();  //overheat
                break;
                
                case 2:
                    getSick(); //get sick
                break;
                
                case 3:
                    vomit(); //vomit
                break;
            }
        }
    }
}

void Animal::incrementAnimalShowsWon()
{
    animalShowsWon++;
}

void Animal::printStats() //prints a list of this animal's stats
{
    string line = ""; //we're gonna print this out at the end.
    
    line += "====" + name + "====";
    
    if(health == 0)
        line += "\n[Deceased]";
    if(isSick)
        line += "\n[Sick]";
    if(food == 0)
        line += "\n[Starving]";
        
    line += "\n";
    
    line += "Species: " + species + "\n";
    
    line += "Sound: " + sound + "\n";
    
    if(health == 0) //animal is dead
    {
        line += "Lived for " + to_string(age);
        line += " days\n";
    }
    else //health != 0, animal is alive
    {
        line += "Age: " + to_string(age);
        line += " days old\n";
    }
    
    line += "Ideal climate: " + to_string(idealTemperature) + "*F\n";
    
    line += "Shows won: " + to_string(animalShowsWon) + "\n";

    //PRINT HEALTH INFORMATION      
    line += "Health: [";
    for(int i = 0; i < 10; i++)
        if(i < health)
            line += "\u25A0";
        else
            line += " ";
            
    //PRINT FOOD INFORMATION
    line += "]\nFood:   [";
    for(int i = 0; i < 10; i++)
        if(i < food)
            line += "\u25A0";
        else
            line += " ";
            
    //PRINT SKILL INFORMATION
    line += "]\nSkill:  [";
    for(int i = 0; i < 10; i++)
        if(i < skill)
            line += "\u25A0"; // \u25A0 is the block charactar
        else
            line += " ";
    line += "]";
    
    cout << line << endl;
}