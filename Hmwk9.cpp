/*
sources:

1.
A couple of my CAs helped me figure out a why certain variables weren't updating.
Our solution was to make the Player's vectors of Animals and AnimalChampionship public, so I could access them directly.

2.
The functions within AnimalChampionship.cpp for reading/writing from a file, as well as the split function, were taken taken previous recitation writeups

3.
I learned how to use a do loop from cppreference.com

4.
I brainstormed with some friends about what some random events should be. Jordan came up with the idea of having a fence that you need to keep out wild animals.  
*/

#include <iostream> 
#include <iomanip> 
#include "Player.cpp"
#include "Animal.cpp"
#include "AnimalShow.cpp"
#include "AnimalChampionship.cpp"
#include <fstream>
  using namespace std;

void clearScreen() //prints a bunch of empty lines to the console
{
  cout << "\n\n\n\n\n" << endl;
}

void displayMenu(Player myP) { //displays the main menu
  //HEADER
  cout << "\nDay: " << myP.getDay() << ", Money: $" << myP.getMoney() << ", Food: " << myP.getFood() << " lbs, Medicine: " << myP.getMedicine() << " vials\nRare Candy: " << myP.getRareCandy() << " pieces, Fence: " << myP.getFenceDurability() << "%\n" << endl;

  //AnimalShow info
  if (myP.getChampionship().getDaysUntilNextShow() > 0) //if there's an upcoming animal show
    cout << "There are " << myP.getChampionship().getDaysUntilNextShow() << " days until the next Animal Show." << endl; //print how many days until the show
  else if (myP.getChampionship().getDaysUntilNextShow() == 0) //if the show is today
    cout << "The Animal Show is today!" << endl; //tell the user the show is today
  else //daysUntilNextShow() returns -1, meaning there are no more shows
    cout << "Congratulations, you've won the Animal Championship!\nBe sure to check out the Hall of Fame!" << endl; //tell the user they've won, and that they should enter the hall of fame

  //Main menu
  cout << "======Main Menu=====" << endl;
  cout << "1. View Animals" << endl;
  cout << "2. Visit the shop" << endl;
  cout << "3. Train for the Animal Show" << endl;
  cout << "4. Use item" << endl;
  cout << "5. View Animal Shows" << endl;
  cout << "6. Go to the Animal Show!" << endl;
  cout << "7. Forfeit the Animal Championship" << endl;
  if (myP.getChampionship().getDaysUntilNextShow() == -1)
    cout << "8. Enter the hall of fame!" << endl;
}

void displayShop() //displays the shop screen
{
  cout << "\nWelcome to the shop!" << endl;
  cout << "======SHOP=====" << endl;
  cout << "1. Buy animals" << endl;
  cout << "2. Buy animal food" << endl;
  cout << "3. Buy medicine" << endl;
  cout << "4. Buy rare candy" << endl;
  cout << "5. Buy fencing" << endl;
  cout << "6. Exit" << endl;
}

void displayInventory(Player myPlayer) //displays the inventory screen
{
  cout << "\n===INVENTORY===" << endl;
  cout << "1. Give food (" << myPlayer.getFood() << ")" << endl;
  cout << "2. Give medicine (" << myPlayer.getMedicine() << ")" << endl;
  cout << "3. Give Rare Candy (" << myPlayer.getRareCandy() << ")" << endl;
  cout << "4. Repair fence (" << myPlayer.getFencePieces() << ", " << myPlayer.getFenceDurability() << "%)" << endl;
  cout << "5. Exit" << endl;
}

void displayHallOfFame() //displays the inventory screen
{
  cout << "\n===Hall Of Fame===" << endl;
  cout << "1. View Animals" << endl;
  cout << "2. Add Animal" << endl;
  cout << "3. Create Animal Show" << endl;
  cout << "4. Exit" << endl;
}

int main(int argc, char
  const * argv[]) {
  string choice; //empty strings used for taking user input
  string c1; //c1 will be used most often
  string c2;
  string c3;
  cout << "Player, what's your name? " << endl;
  do
    getline(cin, choice); //take in input
  while (choice.length() == 0); //take a new input if the input is empty
  Player myPlayer(choice, "Shows.txt");

  cout << "Alrighty then, " << choice << ". You're off to prove your family's farm's glory by winning the annual Animal Championship!" << endl;

  while (choice != "7" && !(myPlayer.getNumLivingAnimals() == 0 && myPlayer.getPriceOfNewAnimal() > myPlayer.getMoney())) {
    displayMenu(myPlayer);

    do
      getline(cin, choice); //ask the user for input
    while (choice.length() != 1 || !isdigit(choice[0])); //if the input is not 1, or the first charactar is not a digit, repeat

    switch (stoi(choice)) {
    case 1:
      //View all animals
      clearScreen();
      myPlayer.viewAllLivingAnimals();
      break;
    case 2:
      //Visit the shop
      while (choice != "6") {
        clearScreen();
        displayShop();
        do
          getline(cin, choice); //ask the user for input
        while (choice.length() != 1 || !isdigit(choice[0])); //if the input is shorter/longer than 1 charactar, or if it is not a digit, repeat
        switch (stoi(choice)) {
        case 1:
          //Buy animals
          cout << "An animal costs $" << to_string(int(50 * (1 + (double(myPlayer.getNumAnimals()) / 10.0)))) << "\nWould you like to buy an animal? (Y/N)" << endl;
          do
            getline(cin, c1); //ask the user for input
          while (c1 != "Y" && c1 != "N"); //if the input has more/less than 1 charactar, or if is not Y and not N, repeat
          if (c1 == "N") {
            cout << "Goodbye!" << endl;
          } else if (c1 == "Y" && myPlayer.payMoney(int(50 * (1 + (double(myPlayer.getNumAnimals()) / 10.0))))) //c1 == "Y"
          {
            cout << "What type of animal would you like?" << endl;
            getline(cin, c2);
            cout << "What kind of sound do " << c2 << "s make?" << endl;
            getline(cin, c3);
            cout << "What's your " << c2 << "'s name?" << endl;
            getline(cin, c1);
            myPlayer.addAnimal(c1, c2, c3); //name, species, sound
            cout << "Congrats! Check out your new animal!\n" << endl;
            myPlayer.animals[myPlayer.getNumAnimals() - 1].printStats();
          } else //c1 == "Y", but player doesn't have enough money
          {
            cout << myPlayer.getName() << " doesn't have enough money..." << endl;
          }
          break;
        case 2:
          //Buy food
          cout << "Food is $5/lb, how many pounds would you like? (Have " << myPlayer.getFood() << ")" << endl;
          do
            getline(cin, c1); //ask the user for input
          while (c1.length() == 0 || !isdigit(c1[0])); //if the input is zero length, or if it is not a digit, repeat
          if (myPlayer.payMoney(stoi(c1) * 5)) //if the transaction is valid
          {
            myPlayer.addFood(stoi(c1));
            cout << "Thank you for your purchase!\nYou now have $" << myPlayer.getMoney() << "." << endl;
          } else //transaction could not be completed
          {
            cout << myPlayer.getName() << " doesn't have enough money..." << endl;
          }
          break;
        case 3:
          //Buy Medicine
          cout << "Medicine is $15/vial, how many vials would you like? (Have " << myPlayer.getMedicine() << ")" << endl;
          do
            getline(cin, c1); //ask the user for input
          while (c1.length() == 0 || !isdigit(c1[0])); //if the input is shorter/longer than 1 charactar, or if it is not a digit, repeat
          if (myPlayer.payMoney(stoi(c1) * 15)) //if the transaction is valid
          {
            myPlayer.addMedicine(stoi(c1));
            cout << "Thank you for your purchase!\nYou now have $" << myPlayer.getMoney() << "." << endl;
          } else //transaction could not be completed
          {
            cout << myPlayer.getName() << " doesn't have enough money..." << endl;
          }
          break;

        case 4:
          //buy Rare Candy
          cout << "Rare Candy is $25 each, how many would you like? (Have " << myPlayer.getRareCandy() << ")" << endl;
          do
            getline(cin, c1); //ask the user for input
          while (c1.length() == 0 || !isdigit(c1[0])); //if the input is shorter/longer than 1 charactar, or if it is not a digit, repeat
          if (myPlayer.payMoney(stoi(c1) * 25)) //if the transaction is valid
          {
            myPlayer.addRareCandy(stoi(c1));
            cout << "Thank you for your purchase!\nYou now have $" << myPlayer.getMoney() << "." << endl;
          } else //transaction could not be completed
          {
            cout << myPlayer.getName() << " doesn't have enough money..." << endl;
          }
          break;

        case 5:
          //buy fencing
          cout << "Fencing is $5/piece, how many pieces would you like? (Have " << myPlayer.getFencePieces() << " pieces)" << endl;
          do
            getline(cin, c1); //ask the user for input
          while (c1.length() == 0 || !isdigit(c1[0])); //if the input is shorter/longer than 1 charactar, or if it is not a digit, repeat
          if (myPlayer.payMoney(stoi(c1) * 5)) //if the transaction is valid
          {
            myPlayer.addFencePieces(stoi(c1));
            cout << "Thank you for your purchase!\nYou now have $" << myPlayer.getMoney() << "." << endl;
          } else //transaction could not be completed
          {
            cout << "Sorry, you don't have enough money..." << endl;
          }
          break;
          
        case 6:
          //Exit shop
          cout << "Thanks for your business!" << endl;
          break;

        default:
          cout << "invalid input" << endl;
        }
      }
      break;
    case 3:
      //Train for the animal show, advances the day
      clearScreen();
      if (myPlayer.getChampionship().getDaysUntilNextShow() == 0) //Don't let the player skip the animal show
        cout << "You must participate in the Animal Show!" << endl;
      else if (myPlayer.getDay() == 0 && myPlayer.getNumAnimals() == 0) //if it's the first day and the player has no animals
        cout << "You must buy an animal first!" << endl;
      else //otherwise, let the player train
      {
        myPlayer.train();
      }
      break;
    case 4:
      //Open inventory
      while (choice != "5") {
        clearScreen();
        displayInventory(myPlayer);
        do
          getline(cin, choice); //ask the user for input
        while (choice.length() != 1 || !isdigit(choice[0])); //if the input's length is not 1, or the first charactar is not a digit, repeat
        switch (stoi(choice)) {
        case 1:
          //Give food
          cout << "Feed which animal? (enter the number)" << endl;
          myPlayer.viewAllLivingAnimals();
          do
            getline(cin, c1); //ask for input
          while (c1.length() == 0 || (isdigit(c1[0]) && !myPlayer.isValidAnimal(stoi(c1)))); //if the length is zero, or if the first charactar is a digit and it's not a valid animal, repeat
          cout << "How much food do you want to feed to " << myPlayer.animals[stoi(c1)].getName() << "?" << endl;
          do
            getline(cin, c2); //ask the user for input
          while (c2.length() == 0 || !isdigit(c2[0])); //if the input is empty, or if it is not a digit, repeat
          if (myPlayer.loseFood(stoi(c2))) //loseFood() returns true
          {
            myPlayer.animals[stoi(c1)].feedAnimal(stoi(c2));
          } else
            cout << myPlayer.getName() << " doesn't have enough food..." << endl;
          break;
        case 2:
          //Give medicine
          cout << "Heal which animal?" << endl;
          myPlayer.viewAllLivingAnimals(); //SHORT VERSION?
          do
            getline(cin, c1); //ask for input
          while (c1.length() == 0 || (isdigit(c1[0]) && !myPlayer.isValidAnimal(stoi(c1)))); //if the length is zero, or if the first charactar is a digit and it's not a valid animal, repeat
          if (myPlayer.useMedicine()) //useMedicine() returns true
            myPlayer.animals[stoi(c1)].getCured();
          else
            cout << myPlayer.getName() << " doesn't have any medicine..." << endl;
          break;
        case 3:
          //Give rare candy
          cout << "Which animal would you like to give a Rare Candy? (enter the number)" << endl;
          myPlayer.viewAllLivingAnimals(); //SHORT VERSION?
          do
            getline(cin, c1); //ask for input
          while (c1.length() == 0 || (isdigit(c1[0]) && !myPlayer.isValidAnimal(stoi(c1)))); //if the length is zero, or if the first charactar is a digit and it's not a valid animal, repeat
          if (myPlayer.useRareCandy(1)) //useRareCandy(1) returns true
          {
            myPlayer.animals[stoi(c1)].raiseSkill(1); //raise the skill by 1
          } else
            cout << myPlayer.getName() << " doesn't have any Rare Candy..." << endl;
          break;

        case 4:
          //Repair fence
          cout << "How many fence pieces do you want to repair? (enter the number)" << endl;
          do
            getline(cin, c1); //ask the user for input
          while (c1.length() == 0 || !isdigit(c1[0])); //if the input is empty, or if it is not a digit, repeat
          if (myPlayer.useFencePieces(stoi(c1))) //if there are enough fence pieces
          {
            myPlayer.repairFence(stoi(c1)); //repair the fence by stoi(c1)
          } else
            cout << myPlayer.getName() << " doesn't have enough fencing to do that..." << endl;
          break;

        case 5:
          //Exit inventory menu

        default:
          cout << "invalid input" << endl;
        }
      }
      break;

    case 5:
      //Print shows
      myPlayer.getChampionship().printAllShows();
      break;

    case 6:
      //Go to the animal show!
      clearScreen();
      if (myPlayer.getChampionship().getDaysUntilNextShow() != 0) //if there isn't an animal show today
      {
        cout << "There isn't an Animal Show today.\nThe next Animal Show is in " << myPlayer.getChampionship().getDaysUntilNextShow() << " days." << endl;
      } else //there IS an animal show!
      {
        cout << "Here's some info about the next Animal Show, would you like to continue? (Y/N)" << endl; //prompt the user
        myPlayer.getChampionship().getNextShow().printInfo();
        do
          getline(cin, c1); //ask the user for input
        while (c1 != "Y" && c1 != "N"); //if the input has more/less than 1 charactar, or if is not Y and not N, repeat
        if (c1 == "N") {
          cout << "Goodbye!" << endl;
        } else //c1 == "Y"
        {
          cout << "\nWhich Animal would you like to compete with? (enter the number)" << endl;
          myPlayer.viewAllLivingAnimals(); //SHORT VERSION?
          do
            getline(cin, c1); //ask for input
          while (c1.length() == 0 || (isdigit(c1[0]) && !myPlayer.isValidAnimal(stoi(c1)))); //if the length is zero, or if the first charactar is a digit and it's not a valid animal, repeat
          if (myPlayer.getChampionship().getNextShow().compete(myPlayer.animals[stoi(c1)])) //if the player wins
          {
            cout << myPlayer.getName() << " won $" << to_string(myPlayer.getChampionship().getNextShow().getPrize()) << "!" << endl; //inform the player they won the prize
            myPlayer.addMoney(myPlayer.getChampionship().getNextShow().getPrize()); //add prize money 

            myPlayer.animals[stoi(c1)].incrementAnimalShowsWon();

            if (chancesOf(60)) //60% chance to raise skill by 1
              myPlayer.animals[stoi(c1)].raiseSkill(1);
            else //40% chance to raise skill by 2
              myPlayer.animals[stoi(c1)].raiseSkill(2);

            if (chancesOf(35)) //35% chance to lose 1-2 health
              myPlayer.animals[stoi(c1)].loseHealth(generateRandomNumber(1, 2));
          } else //player lost :(
          {
            myPlayer.animals[stoi(c1)].die(); //the animal dies if it loses
            int randomPityMoney = generateRandomNumber(0, 40);
            cout << myPlayer.getName() << " collected $" << randomPityMoney << " in pity money." << endl;
            myPlayer.addMoney(randomPityMoney);
          }
          myPlayer.train();
        }
      }
      break;

    case 7:
      //Quit
      cout << myPlayer.getName() << " forfeit the Animal Championship..." << endl;
      break;

    case 8:
      //Enter the hall of fame, but only if the player has won the AnimalChampionship. Otherwise, act like 8 is an invalid menu option

      if (myPlayer.getChampionship().getDaysUntilNextShow() == -1) //the player has not won the AnimalChampionship
      {
        cout << "invalid input" << endl;
      } 
      else //PLAYER HAS COMPLETED THE CHAMPIONSHIP
      {
        clearScreen();
        cout << "Congratulations on winning the Annual Animal Championship!" << endl;
        while(choice != "4")
        {
            displayHallOfFame(); //MAKE THE MENU REPEAT
            do
              getline(cin, choice); //ask the user for input
            while (choice.length() != 1 || !isdigit(choice[0])); //if the input's length is not 1, or the first charactar is not a digit, repeat
            switch (stoi(choice)) {
            case 1:
              //View famous animals
              if (myPlayer.championship[0].readHallOfFame("HallOfFame.txt") != 0) //if there are animals in the hall of fame, (this is the only time I use championship[0] instead of getChampionship(). This is because I need to write to the AnimalChampionship's vector)
              {
                cout << "Here are the animals in the hall of fame:\n" << endl;
                myPlayer.getChampionship().printAllFamousAnimals();
              }
              break;
    
            case 2:
              //Add animal to hall of fame
              cout << "Would you like to enter an animal to the hall of fame? (Y/N)" << endl;
              do
                getline(cin, c1); //ask the user for input
              while (c1 != "Y" && c1 != "N"); //if the input has more/less than 1 charactar, or if is not Y and not N, repeat
              if (c1 == "N") //player does not want to add an animal
              {
                cout << "Come back again later to save your favorite Animal in the hall of fame!" << endl;
              } else //player wants to add an animal!!!
              {
                cout << "Which animal would you like to add? (enter the number)" << endl;
                myPlayer.viewAllAnimals();
                do
                  getline(cin, c1); //ask for input
                while (c1.length() == 0 || (isdigit(c1[0]) && !myPlayer.isValidAnimal(stoi(c1))));
                if (myPlayer.getChampionship().appendHallOfFame("HallOfFame.txt", myPlayer.animals[stoi(c1)]))
                  cout << myPlayer.animals[stoi(c1)].getName() << " was successfully added to the hall of fame!" << endl;
                else
                  cout << "Error adding animal to the hall of fame..." << endl;
              }
              break;
    
            case 3:
              //Create new AnimalShow
              cout << "Would you like to create a new Animal Show? (Y/N)" << endl;
              do
                getline(cin, c1); //ask the user for input
              while (c1 != "Y" && c1 != "N"); //if the input has more/less than 1 charactar, or if is not Y and not N, repeat
              if (c1 == "N") //player does not want to add an animal
              {
                cout << "Come again!" << endl;
              } else //player wants to add an animal!!!
              {
                string myName;
                string myDay;
                string myDifficulty;
                string myTemperature;
                string myPrize;
    
                cout << "Which animal would you like to be the AnimalShow boss? (enter the number)" << endl;
                myPlayer.viewAllAnimals();
                do
                  getline(cin, c1); //ask for input
                while (c1.length() == 0 || (isdigit(c1[0]) && !myPlayer.isValidAnimal(stoi(c1))));
    
                cout << "What would you like to name this Animal Show?" << endl;
                getline(cin, myName);
    
                cout << "What day does is this Animal Show on? If the day is later than the current day (" << myPlayer.getDay() << "), you'll be able to play it!" << endl;
                do
                  getline(cin, myDay); //ask the user for input
                while (myDay.length() == 0 || !isdigit(myDay[0])); //if the input is empty, or if it is not a digit, repeat
    
                cout << "What is the difficulty of this Animal Show?" << endl;
                do
                  getline(cin, myDifficulty); //ask the user for input
                while (myDifficulty.length() == 0 || !isdigit(myDifficulty[0])); //if the input is empty, or if it is not a digit, repeat
    
                cout << "What is the temperature of this Animal Show?" << endl;
                do
                  getline(cin, myTemperature);
                while (myTemperature.length() == 0 || !isdigit(myTemperature[0])); //if the input is empty, or if it is not a digit, repeat
    
                cout << "What is this Animal Show's prize?" << endl;
                do
                  getline(cin, myPrize);
                while (myPrize.length() == 0 || !isdigit(myPrize[0])); //if the input is empty, or if it is not a digit, repeat
    
                myPlayer.championship[0].createShow(myPlayer.animals[stoi(c1)], "Shows.txt", myName, stoi(myDay), stoi(myDifficulty), stoi(myTemperature), stoi(myPrize));
              }
              break;
    
            case 4:
              //Exit
              break;
    
            default:
              cout << "invalid input" << endl;
              break;
            }
            break;
    
            default:
            clearScreen();
            cout << "invalid input" << endl;
            break;
        }
      }
    }
  }
  clearScreen();
  cout << "\n\n\n\nYour last animal has died, and you're too broken to afford a new one.\nHaving to forfeit the Animal Competition, you return back to your home,\nvowing you'll return to the Animal Competetion once again and take better care of your animals." << endl;
  return 0;
}