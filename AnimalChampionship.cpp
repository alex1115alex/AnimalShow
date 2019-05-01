//represents an animal championship
//stores an array of animal shows, and the day
// Author: Alexander Israelov
// Recitation: 107 – Andrew Altomare
// Cloud9 Workspace Editor Link: https://ide.c9.io/alexisraelov/csci1300
// AnimalChampionship.cpp

#include "AnimalChampionship.h"
#include <iostream>
#include <iomanip>
using namespace std;

AnimalChampionship::AnimalChampionship(string fileName)
{
    animalsSold = 0;
    file = fileName;
    numShows = readShows(fileName);
    day = 0;
}

int split (string str, char c, string array[], int size)
 {
    if (str.length() == 0) {
         return 0;
     }
    string word = "";
    int count = 0;
    str = str + c;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == c)
        {
            if (word.length() == 0)
                continue;
            array[count++] = word;
            word = "";
        } else {
            word = word + str[i];
        }
    }
    return count ;
}

int AnimalChampionship::getAnimalsSold()
{
    return animalsSold;
}

int AnimalChampionship::readShows(string fileName)
{
     if(fileName.length() == 0) //fileName is an empty string
        fileName = "Shows.txt"; //default to "Shows.txt"
        
    int index = 0;
    ifstream myfilestream; //create a new ifstream object
    myfilestream.open(fileName); //open the file
    if (myfilestream.is_open()) //if the file is open,
    {
        string line = ""; //create a new string called line, this will temporarily store each line pulled from Shows.txt
        while (getline(myfilestream, line)) //while there's another line in Shows.txt
        {
            if(line.length() != 0 && line[0] != '/') //if the line is not empty or commented out
            {
                string animalShowInfo[9]; //make an array of 10 strings (one for each data member of an AnimalShow)
                split(line, ',', animalShowInfo, 9); //fill the new array with the ratings
                
                //Copy all the data into their own variables to make this more readable
                string myName = animalShowInfo[0];
                int myDay = stoi(animalShowInfo[1]);
                int myDifficulty = stoi(animalShowInfo[2]);
                int myTemperature = stoi(animalShowInfo[3]);
                string bossName = animalShowInfo[4];
                string bossSpecies = animalShowInfo[5];
                string bossSound = animalShowInfo[6];
                int bossSkill = stoi(animalShowInfo[7]);
                
                //I was originally planning on storing these all in the Shows.txt file, but I think that having these variables be random is more fun
                int bossHealth = generateRandomNumber(7, 10); //boss's health is between 7 and 10
                int bossFood = generateRandomNumber(7, 10); //boss's food is between 8 and 10
                int bossAge = generateRandomNumber(1, 365); //boss's age is between 1 and 365
                int bossDaysHungry = 0; //boss's days hungry always starts at zero
                int bossIdealTemperature = generateRandomNumber(0, 100); //boss's ideal temperture is random between 0 and 100
                bool bossIsSick = chancesOf(10); //15% chance of boss being sick
                int bossNumShowsWon = generateRandomNumber(0, (myDifficulty / 2)); //bossNumShowsWon is between 0 and the difficuluty / 2  
                
                int myPrize = stoi(animalShowInfo[8]);
                
                animalShows.push_back(AnimalShow(myName, myDay, myDifficulty, myTemperature, bossName, bossSpecies, bossSound, bossSkill, bossHealth, bossFood, bossAge, bossDaysHungry, bossIdealTemperature, bossIsSick, bossNumShowsWon, myPrize)); //push back a new AnimalShow object with these parameters
                
                index++; //increment index
            }
        }
    }
    else //file cannot be opened
    {
        return -1; //return -1
    }
    myfilestream.close(); //close the file stream
    return index; //return the total number of books in the system, which conveniently happens to be equal to index
}

int AnimalChampionship::readHallOfFame(string fileName)
{
     if(fileName.length() == 0) //fileName is an empty string
        fileName = "HallOfFame.txt"; //default to "HallOfFame.txt"
        
    int index = 0;
    ifstream myfilestream; //create a new ifstream object
    myfilestream.open(fileName); //open the file
    if (myfilestream.is_open()) //if the file is open,
    {
        string line = ""; //create a new string called line, this will temporarily store each line pulled from Shows.txt
        while (getline(myfilestream, line)) //while there's another line in Shows.txt
        {
            if(line.length() != 0 && line[0] != '/') //if the line is not empty or commented out
            {
                string animalInfo[11]; //make an array of 10 strings (one for each data member of an Animal)
                split(line, ',', animalInfo, 11); //fill the new array with the ratings
                
                //Copy all the data into their own variables to make this more readable
            
                string name = animalInfo[0];
                string species = animalInfo[1];
                string sound = animalInfo[2];
                int skill = stoi(animalInfo[3]);
                int health = stoi(animalInfo[4]);
                int food = stoi(animalInfo[5]);
                int age = stoi(animalInfo[6]);
                int daysHungry = stoi(animalInfo[7]);
                int idealTemperature = stoi(animalInfo[8]);
                bool isSick = false;
                if(animalInfo[9] == "true")
                    isSick = true;
                int animalShowsWon = stoi(animalInfo[10]);
                famousAnimals.push_back(Animal(name, species, sound, skill, health, food, age, daysHungry, idealTemperature, isSick, animalShowsWon));
                index++; //increment index
            }
        }
    }
    else //file cannot be opened
    {
        return -1; //return -1
    }
    myfilestream.close(); //close the file stream
    return index; //return the total number of famous animals in the system, which conveniently happens to be equal to index
}

bool AnimalChampionship::appendHallOfFame(string fileName, Animal famousAnimal) //appends an animal's info to the hall of fame
{
    if(fileName.length() == 0) //fileName is an empty string
        fileName = "HallOfFame.txt"; //default to "Shows.txt"
    
    ofstream myfilestream;
    myfilestream.open(fileName, ios::app);
    if (myfilestream.is_open())
    {
        string line = ""; //create a string 
        line += famousAnimal.getName() + ",";
        line += famousAnimal.getSpecies() + ",";
        line += famousAnimal.getSound() + ",";
        line += to_string(famousAnimal.getSkill()) + ",";
        line += to_string(famousAnimal.getHealth()) + ",";
        line += to_string(famousAnimal.getFood()) + ",";
        line += to_string(famousAnimal.getAge()) + ",";
        line += to_string(famousAnimal.getDaysHungry()) + ",";
        line += to_string(famousAnimal.getTemperature()) + ",";
        if(famousAnimal.getIsSick())
            line += "true,";
        else
            line += "false,";
        line += to_string(famousAnimal.getAnimalShowsWon());
        cout << "Line to be appended:\n" << line << endl;
        myfilestream << line << endl;
        return true;
    }
    else
    {
        cout << "file open failed" << endl;
        return false;
    }
    return false;
}

int AnimalChampionship::getDaysUntilNextShow() //returns the number of days until the next show
{
    for(int i = 0; i < numShows; i++) //for each show
    {
        if(animalShows[i].getDay() >= day && (i == 0 || animalShows[i - 1].getDay() < day)) //if the show is later than today, AND the previous show is before today (or it's the first show)
        {
            return animalShows[i].getDay() - day; 
        }
    }
    return -1; //no more shows
}


AnimalShow AnimalChampionship::getNextShow() //returns the next upcoming AnimalShow. Precondition: getDaysUntilNextShow() != 0;
{
    for(int i = 0; i < numShows; i++)
    {
        if(animalShows[i].getDay() >= day && (i == 0 || animalShows[i - 1].getDay() < day)) //if the show is later than today, AND the previous show is before today (or it's the first show)
        {
            return animalShows[i]; 
        }
    }
    return animalShows[0]; //We need to return SOMETHING, so we'll default to the first show
}

bool AnimalChampionship::createShow(Animal famousAnimal, string fileName, string myName, int myDay, int myDifficulty, int myTemperature, int myPrize)
{
    if(fileName.length() == 0) //fileName is an empty string
        fileName = "Shows.txt"; //default to "Shows.txt"
    
    ofstream myfilestream;
    myfilestream.open(fileName, ios::app);
    if (myfilestream.is_open())
    {
        string line = ""; //create a string  /string myName, int myDay, int myDifficulty, int myTemperature, string bossName, string bossSpecies, string bossSound, int bossSkill, int myPrize
        line += myName + ",";
        line += myDay + ",";
        line += myDifficulty + ",";
        line += myTemperature + ",";
        line += famousAnimal.getName() + ",";
        line += famousAnimal.getSpecies() + ",";
        line += famousAnimal.getSound() + ",";
        line += to_string(famousAnimal.getSkill()) + ",";
        line += myPrize;
        cout << "Line to be appended:\n" << line << endl;
        myfilestream << line << endl;
        
        if(myDay > day)
            animalShows.push_back(AnimalShow(myName, myDay, myDifficulty, myTemperature, famousAnimal.getName(), famousAnimal.getSpecies(), famousAnimal.getSound(), famousAnimal.getSkill(), famousAnimal.getHealth(), famousAnimal.getFood(), famousAnimal.getAge(), famousAnimal.getDaysHungry(),famousAnimal.getTemperature(), famousAnimal.getIsSick(), famousAnimal.getAnimalShowsWon(),- myPrize));
        
        return true;
    }
    else
    {
        cout << "file open failed" << endl;
        return false;
    }
    return false;
}

int AnimalChampionship::getCurrentDay()
{
    return day;
}

void AnimalChampionship::incrementDay()
{
    day++;
}


void AnimalChampionship::printAllShows()
{
    for(int i = 0; i < numShows; i++)
        animalShows[i].printInfo();
}

void AnimalChampionship::printAllFamousAnimals()
{
    for(int i = 0; i < famousAnimals.size(); i++)
    {
        famousAnimals[i].printStats(); 
        cout << "\n" << endl;
    }
}

