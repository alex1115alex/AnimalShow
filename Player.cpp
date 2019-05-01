//REPRESENTS A PLAYER
// Author: Alexander Israelov
// Recitation: 107 – Andrew Altomare
// Cloud9 Workspace Editor Link: https://ide.c9.io/alexisraelov/csci1300
// Player.cpp

#include "Player.h"
#include "AnimalChampionship.h"
#include <iostream>
#include <iomanip>
using namespace std;

/*
Player::Player()
{
    name = "Jeff";
    money = 150;
    food = 0; 
    day = 0;
    medicine = 0;
    numAnimals = 0;
}
*/

Player::Player(string myName, string fileName)
{
    name = myName;
    money = 150;
    food = 0; 
    day = 0;
    medicine = 0;
    rareCandy = 0;
    fenceDurability = 100;
    fencePieces = 0;
    numAnimals = 0;
    addChampionship("Shows.txt");
}

string Player::getName()
{
    return name;
}

int Player::getMoney()
{
    return money;
}

int Player::getMedicine()
{
    return medicine;
}

int Player::getNumAnimals()
{
    return numAnimals;
}

int Player::getNumLivingAnimals()
{
    int count = 0;
    for(int i = 0; i < numAnimals; i++)
        if(animals[i].getHealth() != 0)
            count++;
    return count;
}

int Player::getDay()
{
    return day;
}
        
int Player::getRareCandy()
{
    return rareCandy;
}

void Player::addRareCandy(int amtRareCandy)
{
    rareCandy += amtRareCandy;
}

bool Player::useRareCandy(int amtRareCandy)
{
    if(rareCandy - amtRareCandy < 0)
        return false;
    rareCandy -= amtRareCandy;
    return true;
}

int Player::getFenceDurability()
{
    return fenceDurability;
}

void Player::repairFence(int amtRepair)
{
    fenceDurability += amtRepair * 5;
    cout << "You used " << amtRepair << " fence pieces.\nYour fence now has " << fenceDurability << "%" << " durability." << endl;
}

void Player::damageFence(int amtDamage)
{
    if(amtDamage > fenceDurability)
        fenceDurability = 0;
    else
        fenceDurability -= amtDamage;
}

int Player::getFencePieces()
{
    return fencePieces;
}

void Player::addFencePieces(int amtPieces)
{
    fencePieces += amtPieces;
}

bool Player::useFencePieces(int amtPieces)
{
    if(amtPieces > fencePieces)
        return false;
    fencePieces -= amtPieces;
    return true;
}

void Player::addMedicine(int amtMedicine)
{
    medicine += amtMedicine;
}

void Player::nextDay()
{
    day++; //increment the day
    
    if(fenceDurability < 70 && !chancesOf(fenceDurability / 2)) //if the fenceDurability has decayed below 70%, decide whether an animal gets eaten (100 - fenceDurability/2)% chance
        animals[generateRandomNumber(0, numAnimals - 1)].getEaten(); //a random animal gets eaten
        
    if(fenceDurability > 100)
        fenceDurability -= 10; //reduce the durability by 10% each turn it's above 100%
    else
        fenceDurability -= 5; //otherwise, just reduce it by 5% each turn
}

bool Player::useMedicine()
{
    if(medicine > 0)
    {
        medicine--;
        return true;
    }
    return false;
}

bool Player::payMoney(int amtMoney)
{
    if(money - amtMoney >= 0)
    {
        money -= amtMoney;
        return true;
    }
    return false;
}

void Player::addMoney(int amtMoney)
{
    money += amtMoney;
}

int Player::getFood()
{
    return food;
}

bool Player::loseFood(int amtFood)
{
    if(food - amtFood >= 0)
    {
        food -= amtFood;
        return true;
    }
    return false;
}

void Player::addFood(int amtFood)
{
    food += amtFood;
}

void Player::addAnimal() //add a default animal
{
    animals.push_back(Animal());
    numAnimals++;
}

int Player::getPriceOfNewAnimal()
{
    return int(50 * (1 + (double(numAnimals) / 10.0)));
}

void Player::train() //train for the animal show (starts next day)
{
    championship[0].incrementDay(); //increments the day of the championship
    nextDay(); //increments the day
    for(int i = 0; i < numAnimals; i++) //increase the age of all animals
        animals[i].increaseAge();
}

void Player::addAnimal(string myName, string mySpecies, string mySound) //add a parameterized animal
{
    animals.push_back(Animal(myName, mySpecies, mySound));
    numAnimals++;
}

void Player::addChampionship(string fileName) //add a parameterized AnimalChampionship
{
    championship.push_back(AnimalChampionship(fileName));
}

Animal Player::getAnimalAtIndex(int index)
{
    return animals[index];
}

AnimalChampionship Player::getChampionship()
{
    return championship[0];
}

void Player::viewAllAnimals()
{
    if(numAnimals != 0)
    {
        for(int i = 0; i < numAnimals; i++)
        {
            cout << "\nAnimal #" << i << ":" << endl;
            animals[i].printStats();
        }
    }
    else
    {
        cout << "You don't have any animals..." << endl;
    }
}

bool Player::isValidAnimal(int index)
{
    return (index < numAnimals && animals[index].getHealth() > 0); //return whether the index is less than numAnimals and, if it is, if that animal is alive
}

void Player::viewAllLivingAnimals()
{
    if(numAnimals != 0)
    {
        for(int i = 0; i < numAnimals; i++)
        {
            if(animals[i].getHealth() != 0)
            {
                cout << "\nAnimal #" << i << ":" << endl;
                animals[i].printStats();
            }
        }
    }
    else
    {
        cout << "You don't have any animals..." << endl;
    }
            
}
