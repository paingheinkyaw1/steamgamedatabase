// Specification file for the Hash class
// Written By: Paing Hein Kyaw, Aye Thwe Tun

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "HashNode.h"

using std::string;

class HashTable
{
private:
	HashNode* hashAry;
	int hashSize;
  int count;
  int totalCol;
  int longestList;

public:
	HashTable() { count = 0; hashSize = 60; totalCol = 0; longestList = 0; hashAry = new HashNode[hashSize]; }
	HashTable(int n)	{ count = 0; hashSize = n;	totalCol = 0; longestList = 0; hashAry = new HashNode[hashSize]; }
	~HashTable(){ delete [] hashAry; }

	int getCount() const	{ return count; }
  int getSize() const { return hashSize; }
  int getNumLongestList();
  int getLenghtOfLongestList() { return longestList; }
  int getTotalNumCollisions() { return totalCol; }
  double getLoadFactor() const {return 100.0 * count / hashSize; }
  bool isEmpty() const	{ return count == 0; }
  bool isFull()  const	{ return count == hashSize; }

  void insert( Game &itemIn );
  bool remove( Game &itemOut, string key);
  bool search( Game &target, string key);

  void printToFile(string fileName);

private:
    int _hash(string key) const;
};

#endif // HASHTABLE_H_
