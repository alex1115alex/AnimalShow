// Author: Alexander Israelov
// Recitation: 107 – Andrew Altomare
// Cloud9 Workspace Editor Link: https://ide.c9.io/alexisraelov/csci1300
// Player.h

#ifndef PLAYER_H
#define PLAYER_H
#include "Animal.h"
#include "AnimalChampionship.h"
#include "RandomChance.h"
#include <vector>
#include <iostream>
using namespace std;

class Player
{
    private:
        string name;
        int money; //money (dollars)
        int food; //food (pounds)
        int medicine; //number of medicinal items the player owns
        int rareCandy; //amount of rare candy the player has
        int numAnimals; //number of animals
        int day; //current day
        int fenceDurability; //The player needs to keep his fence in good condition (1 - 100), or its animals might get eaten!
        int fencePieces;
          
    public:
        vector<Animal> animals; //vector array of animals
        vector<AnimalChampionship> championship; //every player stores a vector array of AnimalChampionships, which will hold one AnimalChampionship, which is responsible for keeping track of the day, a vector of AnimalShow obects, and managing the hall of fame
        
        //Player(); //default constructor
        Player(string myName, string fileName);
        
        int getDay(); //returns the day
        void nextDay(); //increments the day
        
        string getName(); //returns the player's name
        
        int getMoney(); //returns the amount of money the player has
        bool payMoney(int amtMoney); //returns true if the transaction is possible, and then subtracts money
        void addMoney(int amtMoney); //add money
        
        int getFood(); //returns the amount of food the player has
        bool loseFood(int amtFood); //returns true if it's possible to lose that much food, and subtracts that amount
        void addFood(int amtFood); //adds the specified amount of food to the user's food variable
        
        int getMedicine(); //returns the amount of medicine the player has
        void addMedicine(int amtMedicine); //adds the specified amount of medicine to he user's medicine variable
        bool useMedicine(); //if the medicine variable is 1 or more, decrement it, and return true. False if otherwise.
        
        int getRareCandy(); //returns the amount of Rare Candy the player has
        void addRareCandy(int amtRareCandy); //adds the specified amount of candy to the user's rareCandy variable
        bool useRareCandy(int amtRareCandy); //removes the specified amount of rare candy 
        
        int getFenceDurability(); //returns fenceDurability
        void repairFence(int amtRepair); //repair the fence's durability by amtRepair
        void damageFence(int amtDamage); //reduce the fence's durability by amtDamage and return true. False if amtDamage > fenceDurability.
        
        int getFencePieces();
        void addFencePieces(int amtPieces);
        bool useFencePieces(int amtPieces);
        
        void addAnimal(string myName, string mySpecies, string mySound); //adds an animal to the Player's list of animals
        void addAnimal(); //adds a default animal
        int getNumAnimals();
        int getNumLivingAnimals();
        Animal getAnimalAtIndex(int index);
        bool isValidAnimal(int index); //returns true if animals[index] contains a valid animal
        
        int getPriceOfNewAnimal(); // returns the price the player will have to pay to purchase a new animal
        
        void train(); //train for the animal show - increases the age of all Animals and the AnimalChampionship
        
        void viewAllAnimals(); //prints each animal's info (whether they be dead or alive)
        void viewAllLivingAnimals(); //prints each living animal's info
        
        void addChampionship(string fileName); //add a new AnimalChampionship
        AnimalChampionship getChampionship(); //returns the current championship
};

#endif
