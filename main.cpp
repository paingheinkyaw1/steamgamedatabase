/**
                          CIS 22C Team 11
This is a steam game database that can be used to store any games that you want.
The inital inputFile.txt is taken with reference to the games from the steam library.
You may add or delete any games that you wish and also search them accordingly.
The database is created using a Binary Search Tree and a Hash Table (Chaining).
The program is written by Paing Hein Kyaw, Aye Thwe Tun
===========================================
    S T E A M  G A M E  D A T A B A S E
===========================================
                Menu Options
'A' to add games.
'D' to delete games.
'N' to search according to the game name.
'G' to search according to the game genre.
'P' to print the database sorted by the genre.
'S' to print the statistics.
'H' to show the help menu.
'Q' to quit the program.
============================================
Hidden Options.
'T' to print the BST as an indented list.
'I' to print the creator's info.
**/
//Main Class
#include "Game.h"
#include "HashTable.h"
#include "BinarySearchTree.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iomanip>

using namespace std;

void printTitle();
void printTable(Game&);
void printMenu();
void printToFile(string fileName, HashTable& gameTable);
int elementCounter(string fileName);
void insertManager(HashTable& gameTable, BinarySearchTree& gameTree);
void searchManager(HashTable &gameTable);
void searchManager(BinarySearchTree &gameTree);
void deleteManager(HashTable& gameTable, BinarySearchTree& gameTree);
void statsManager(HashTable& gameTable);
void creatorInfo();

void printByGenre(const BinarySearchTree &gameTree);
int findPrime(int num);
void iDisplay(Game &item, int level);

int main()
{
  string fileName;
  char option;
  BinarySearchTree gameTree;

  cout << "What is the input file's name? ";
  cin >> fileName;

  int numElements = elementCounter(fileName);

  ifstream inFile(fileName);

  if(!inFile) {
    cout << "File failed to open." << endl;
    exit(EXIT_FAILURE);
  }

  int i = 0, hashSize;
  Game gameList[numElements];
  hashSize = numElements * 2;
  hashSize = findPrime(hashSize);
  HashTable gameTable(hashSize);
  string name;

  while(getline(inFile,name, ';'))
  {
    string genre, dev, date;
    double price;
    inFile.ignore();
    getline(inFile, genre, ';');
    inFile.ignore();
    getline(inFile, dev, ';');
    inFile.ignore();
    getline(inFile, date, ';');
    inFile.ignore();
    inFile >> price;
    inFile.ignore();
    Game aGame(name, genre, dev, date, price);
    gameList[i] = aGame;
    i++;
  }

  inFile.close();

  for(int i = 0; i < numElements; i++)
  {
    gameTable.insert(gameList[i]);
    gameTree.insert(gameList[i]);
  }

  printMenu();

  do {
    cout << "\nEnter an option(H - for help): ";
    cin >> option;
    cin.ignore();

    option = toupper(option);

    if(option == 'A')
    {
      insertManager(gameTable, gameTree);
    }
    else if(option == 'D')
    {
      deleteManager(gameTable, gameTree);
    }
    else if(option == 'N')
    {
      searchManager(gameTable);
    }
    else if(option == 'H')
    {
      printMenu();
    }
    else if(option == 'P')
    {
      printByGenre(gameTree);
    }
    else if(option == 'G')
    {
      searchManager(gameTree);
    }
    else if(option == 'S')
    {
      statsManager(gameTable);
    }
    else if(option == 'T')
    {
      gameTree.printIndentedTree(iDisplay);
    }
    else if(option == 'I')
    {
      creatorInfo();
    }
  } while(option != 'Q');

  string outputFile;

  cout << "\nEnter the name of the output file: ";
  cin >> outputFile;

  printToFile(outputFile, gameTable);

  cout << "\nThank you for using this program!" << endl;

  return 0;
}

/**
  Prints the menu onto the screen.
**/
void printMenu(){
    cout << "===========================================" << endl;
    cout << "    S T E A M  G A M E  D A T A B A S E" << endl;
    cout << "===========================================" << endl;
    cout << "                Menu Options               " << endl;
    cout << "'A' to add games." << endl;
    cout << "'D' to delete games." << endl;
    cout << "'N' to search according to the game name." << endl;
    cout << "'G' to search according to the game genre." << endl;
    cout << "'P' to print the database sorted by the genre." << endl;
    cout << "'S' to print the statistics." << endl;
    cout << "'H' to show the help menu." << endl;
    cout << "'Q' to quit the program." << endl;

}

/**
  Prints the title of the data onto the screen.
**/
void printTitle()
{
  cout << "========================================   ==============================    =====================     ====================     =======" << endl;
  cout << "                  Name                                 Genre                       Developer                   Date              Price" << endl;
  cout << "========================================   ==============================    =====================     ====================     =======" << endl;

}

/**
  Prints all the data of game in a formatted manner onto the screen.
  Input parameter: Game
**/
void printTable(Game &aGame)
{
    cout << left << setw(44) << aGame.getName() << setw(34) << aGame.getGenre() << setw(28)<< aGame.getDev() << setw(22) << aGame.getDate() << aGame.getPrice() << endl;
}

/**
  insertManager: Asks the user for the details of the game and inputs it in BST and Hash table.
  Input Parameter: Hash Table, Binary Search Tree
**/
void insertManager(HashTable& gameTable, BinarySearchTree& gameTree)
{
  string name, genre, developer, releaseDate;
  double price;

  cout << "\nInsert\n";
  cout <<   "=======\n";

  cout << "Enter the game name: ";
  getline(cin, name);
  cout << "Enter the game genre: ";
  getline(cin, genre);
  cout << "Enter the game developer: ";
  getline(cin, developer);
  cout << "Enter the release date: ";
  getline(cin, releaseDate);
  cout << "Enter the price: ";
  cin >> price;
  cin.ignore();

  Game temp(name, genre, developer, releaseDate, price);
  Game insertedItem;

  if(gameTable.search(insertedItem, name))
  {
    cout << endl << name << " is already in the Steam Database!" << endl;
  }
  else
  {
    gameTable.insert(temp);
    gameTree.insert(temp);
    cout << endl << name << " has been added to the Steam Database!" << endl;
  }

  cout << "\n___________________END INSERT SECTION___________________\n";
}

/*
 Search manager: search the list for the desired target name
 Input Parameter: Hash Table
 */
void searchManager(HashTable &gameTable)
{
    string target = "";

    cout << "\nSearch\n";
    cout <<   "=======\n";

    Game temp;
    cout << "Enter the game name to search: ";
    getline(cin, target);
    if(gameTable.search(temp, target))
    {
      printTitle();
      printTable(temp);
    }
    else
    {
      cout << "\nGame not found!" << endl;
    }

    cout << "\n___________________END SEARCH SECTION___________________\n";
}

/*
 Search manager: search the list for the desired target genre
 Input Parameter: list
 */
void searchManager(BinarySearchTree &gameTree)
{
  string target = "";

  cout << "\nSearch\n";
  cout <<   "=======\n";

  cout << "Enter the game genre to search: ";
  getline(cin, target);

  printTitle();
  gameTree.printGenre(printTable, target);

  cout << "\n___________________END SEARCH SECTION___________________\n";
}

/**
  deleteManager: Asks the user for the game name that they want to delete.
  Deletes the data if it exists. Return false if not false.
  Input Parameter: Hash Table, Binary Search Tree
**/
void deleteManager(HashTable& gameTable, BinarySearchTree& gameTree)
{
  string target = "";

  cout << "\nDelete\n";
  cout <<   "=======\n";

  cout << "Enter the game name to delete: ";
  getline(cin, target);
  Game temp;
  if(gameTable.remove(temp, target))
  {
    if(gameTree.remove(temp))
      cout << endl << temp.getName() << " has been deleted!" << endl;
      else
      cout << "\nGame not found!" << endl;
  }
  else
  {
    cout << "\nGame not found!" << endl;
  }

  cout << "\n___________________END DELETE SECTION___________________\n";
}

/**
  prints the BST which is sorted by genre
  Input Parameter: Binary Search Tree
**/
void printByGenre(const BinarySearchTree &gameTree)
{
  printTitle();
  gameTree.printTree(printTable);
}

/**
  outputs the list of games in hash table onto a file in the order of the hash table
  Input parameter: file name, Hash table
**/
void printToFile(string fileName, HashTable &gameTable)
{
  gameTable.printToFile(fileName);
}


/*
  Check whether num is a prime number.
  If not, find the next prime number after num
  Input parameter: int num
*/
int findPrime(int num)
{
  bool notPrime = true;
	while(notPrime == true)
	{
      notPrime = false;

    	for (int j = 2; j < num/2 && !notPrime; j++)
    	{
        	if (num % j == 0){
            	notPrime = true;
          }
    	}

    	if (!notPrime)
        	return num;

      num++;
	}
  return num;
}

/*
  Counts the number of elements in a given input file.
*/
int elementCounter(string fileName)
{
  int numElements = 0;

  ifstream countFileSize(fileName);

  if(!countFileSize) {
    cout << "File failed to open." << endl;
    exit(EXIT_FAILURE);
  }

  string tempCounter;

  while(getline(countFileSize, tempCounter)) {
    numElements++;
  }

  countFileSize.close();

  return numElements;
}

/**
  Display the game item indented according to the value of level
  Input parameter: item, level
**/
void iDisplay(Game &item, int level)
{
  for (int i = 1; i < level; i++)
    cout << "..";
  cout << level << "). " << item << endl;
}

/**
  Outputs the statisics of the hash table such as load factor, total num of collisions, length of longest list and
  num of longest list
  Input parameter: Hash Table
**/
void statsManager(HashTable& gameTable)
{
  cout << "\nStatistics\n";
  cout <<   "==========\n";

  cout << "\nLoad Factor: " << gameTable.getLoadFactor();
  cout << "\nTotal number of collisions: " << gameTable.getTotalNumCollisions();
  cout << "\nLength of the longest linked list: " << gameTable.getLenghtOfLongestList();
  cout << "\nNumber of longest linked lists: " << gameTable.getNumLongestList() << endl;
    cout << "\n___________________END OF STATS___________________\n";

}

/**
  Outputs the programmer's info
**/
void creatorInfo()
{
  cout << "=============================================" << endl;
  cout << "Programmed by: Aye Thwe Tun & Paing Hein Kyaw" << endl;
  cout << "            Steam Game Database              " << endl;
  cout << "             CIS 22C - Team 11               " << endl;
  cout << "=============================================" << endl;
}
