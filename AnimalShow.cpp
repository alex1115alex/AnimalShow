//Represents an animal show
//stores a title, day, difficulty, temperature, and a Boss Animal
//REPRESENTS A PLAYER
// Author: Alexander Israelov
// Recitation: 107 – Andrew Altomare
// Cloud9 Workspace Editor Link: https://ide.c9.io/alexisraelov/csci1300
// AnimalShow.cpp

#include "AnimalShow.h"
#include <iostream>
#include <iomanip>
using namespace std;

AnimalShow::AnimalShow(string myName, int myDay, int myDifficulty, int myTemperature, string bossName, string bossSpecies, string bossSound, int bossSkill, int bossHealth, int bossFood, int bossAge, int bossDaysHungry, int bossIdealTemperature, int bossIsSick, int bossNumShowsWon, int myPrize) //parameterized constructor
{
    name = myName;
    day = myDay;
    difficulty = myDifficulty;
    temperature = myTemperature;
    boss = Animal(bossName, bossSpecies, bossSound, bossSkill, bossHealth, bossFood, bossAge, bossDaysHungry, bossIdealTemperature, bossIsSick, bossNumShowsWon);
    prize = myPrize;
}
        
string AnimalShow::getName() //returns this AnimalShow's name
{
    return name;
}

int AnimalShow::getDay() //returns the day this AnimalShow takes place
{
    return day;
}

int AnimalShow::getPrize()
{
    return prize;
}

int AnimalShow::getDifficulty() //returns this object's difficulty
{
    return difficulty;
}

int AnimalShow::getTemperature() //returns the temperature
{
    return temperature;    
}   

Animal AnimalShow::getBoss() //returns this AnimalShow object's boss
{
    return boss;
}

bool AnimalShow::compete(Animal competetor) 
{
    cout << "Welcome to the " << name << " Animal Show!\nToday's contestents are " << competetor.getName() << " and " << boss.getName() << "!\n" << endl;
    string line;
    int chance = 50; //chance always starts at 50 for even odds. We will compare each animal's stats, and add the modifiers to it before deciding the winner
    
    //SKILL MODIFIER
    int skillModifier = 10 * (competetor.getSkill() - boss.getSkill());
    if(skillModifier > 0) //competetor has a higher skill
        cout << competetor.getSound() << "! Competetor " << competetor.getName() << " did a cool trick!\n" << endl;
    else if(skillModifier < 0) //the boss has a higher skill
    {
        skillModifier *= (1 + (double(difficulty) / 10.0));
        cout << boss.getSound() << "! Boss " << boss.getName() << " did a cool trick!\n" << endl;
    }
    else //it's a tie
        cout << competetor.getSound() << "! " << boss.getSound() << "! Both animals did cool tricks!\n" << endl;
        
    //FOOD MODIFIER
    int foodModifier = 10 * (competetor.getFood() - boss.getFood());
    if(foodModifier > 0) //competetor has more food
        cout << "Competetor " << competetor.getName() << " seems to be better-fed than Boss " << boss.getName() << "\n" << endl;
    else if(foodModifier < 0) //boss has more food
    {
        foodModifier *= (1 + (double(difficulty) / 10.0));
        cout << "Boss " << boss.getName() << " seems to be better-fed than Competetor " << competetor.getName() << "\n" << endl;
    }
    
    //SICK MODIFIER
    int sickModifier;
    if(competetor.getIsSick() && !boss.getIsSick()) //the competetor is sick, but not the boss
    {
        cout << "Competetor " << boss.getName() << " appears to be sick!\n" << endl;
        sickModifier = -10;
    }
    else if(!competetor.getIsSick() && boss.getIsSick()) //if the competetor is not sick, but the boss is sick
    {
        cout << "Boss " << boss.getName() << " appears to be sick!\n" << endl;
        sickModifier = 10;
    }
    else //they're both sick or not sick
    {
        if(competetor.getIsSick())
            cout << "Both animals are sick!\n" << endl;
        else
            cout << "Both animals are in happy healthy condition!\n" << endl;
        sickModifier = 0;
    }
    
    //TEMPERATURE MODIFIER
    line = "";
    int temperatureModifier = abs(boss.getTemperature() - temperature) - abs(competetor.getTemperature() - temperature);
    if(temperatureModifier > 0) //the competetor has a better temperatureModifier
    {   
        line += "Boss " + boss.getName() + " is ";
        if(boss.getTemperature() > temperature) //The animal is cold
            line += "freezing, it can't handle the cold!\n";
        else //the animal is too hot
            line += "sweating! It can't take the heat!\n";
    }
    else if(temperatureModifier < 0) //the boss has a better modifier
    {
        temperatureModifier *= (1 + (double(difficulty) / 10.0));
        line += "Competetor " + competetor.getName() + " is ";
        if(competetor.getTemperature() > temperature) //The animal is too cold
            line += "freezing, it can't handle the cold!";
        else //the animal is too hot
            line += "sweating! It can't take the heat!";
    }
    else
    {
        line += "Both animals are holding well in the ";
        if(temperature > 80)
            line += "hot sun.";
        else if(temperature > 60)
            line += "warm.";
        else if(temperature > 35)
            line += "chillly weather.";
        else
            line += "freezing weather.";
    }
    line += "\n";
    
    //FINAL RESULTS
    line += "\n===FINAL RESULTS===\n";
    line += "Skill: ";
    if(skillModifier > 0)
        line += competetor.getName();
    else if(skillModifier < 0)
        line += boss.getName();
    else
        line += "Tie";
    line += "\n";
    
    line += "Food: ";
    if(foodModifier > 0)
        line += competetor.getName();
    else if(foodModifier < 0)
        line += boss.getName();
    else
        line += "Tie";
    line += "\n";
    
    line += "Wellness: ";
    if(sickModifier > 0)
        line += competetor.getName();
    else if(sickModifier < 0)
        line += boss.getName();
    else
        line += "Tie";
    line += "\n";
    
    line += "Temperature: ";
    if(temperatureModifier > 0)
        line += competetor.getName();
    else if(temperatureModifier < 0)
        line += boss.getName();
    else
        line += "Tie";
    
    line += "\nChance: " + to_string(chance + skillModifier + foodModifier + sickModifier + temperatureModifier) + "\n\n";
    
    bool competetorWon = chancesOf(chance + skillModifier + foodModifier + sickModifier + temperatureModifier);
    if(competetorWon)
        line += "Congratulations! Your " + competetor.getName() + " won the Animal Show!";
    else
        line += "Dang! Your " + competetor.getName() + " lost the AnimalShow...";
        
    cout << line << endl; //print line

    return competetorWon;
}

void AnimalShow::printInfo()
{
    string line = "";
    line += "\nName: " + name;
    line += "\nDay: " + to_string(day);
    line += "\nDifficulty: " + to_string(difficulty);
    line += "\nTemperature: " + to_string(temperature) + "*F";
    line += "\nPrize: $" + to_string(prize);
    line += "\nBOSS:";
    cout << line << endl;
    boss.printStats();
}