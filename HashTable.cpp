// Implementation file for the Hash class
// Written By: Paing Hein Kyaw, Aye Thwe Tun

#include <string>
#include <fstream>
#include <iostream>

#include "HashTable.h"

using namespace std;

/*~*~*~*
  A simple hash function
*~**/
int HashTable::_hash(string key) const
{
    int sum = 0;
    for (int i = 0; key[i]; i++)
        sum += key[i];
    return sum % hashSize;
};

/**
  Insert the given game data into the hash table
*/
void HashTable::insert( Game &itemIn )
{
  // Hash function determines initial bucket
  int bucket = _hash(itemIn.getName());
  // Insert item in next empty bucket
  hashAry[bucket].addItem(itemIn);
  hashAry[bucket].setOccupied(1);
  count++;
  if(hashAry[bucket].getList().getLength() > 1){
    totalCol++;
  }
  if(hashAry[bucket].getList().getLength() > longestList){
    longestList = hashAry[bucket].getList().getLength();
  }
}

/**
  Remove the target data from the hash table and return it with the given reference parameter and returns true or false
*/
bool HashTable::remove( Game &itemOut, string key)
{
  // Hash function determines initial bucket
  int bucket = _hash(key);

  if(hashAry[bucket].getList().removeNode(itemOut, key)) {
    hashAry[bucket].setOccupied(2);
    count--;
    return true;
  }
  return false;
}

/**
  Searches the hashTable for the target data and returns it with the given reference parameter and returns true or false
*/
bool HashTable::search( Game &itemOut, string key)
{
   // Hash function determines initial bucket
   int bucket = _hash(key);

  if(hashAry[bucket].getList().searchList(key, itemOut)) {
    return true;
  }

  return false;  // Item not found
}

/**
  Prints the data from the hashTable into a file
*/
void HashTable::printToFile(string fileName)
{
  ofstream outputFile(fileName);

  if(!outputFile) {
    cout << "Error opening the file!" << endl;
  }

  int length = 0;
  for(int i = 0; i < hashSize; i++) {
      length = hashAry[i].getList().getLength();
      for(int j = 0; j < length; j++)
      {
        Game aGame;
        if(hashAry[i].getList().printGame(j, aGame)){
          outputFile << aGame << endl;
        }
      }
  }

  outputFile.close();
}

/**
  Returns the number of longest lists
*/
int HashTable::getNumLongestList()
{
  int numLongestList = 0;
  for(int i = 0; i < hashSize; i++)
  {
    if(hashAry[i].getList().getLength() == longestList) {
      numLongestList++;
    }
  }
  return numLongestList;
}
