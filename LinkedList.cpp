// Implementation file for the LinkedList class
// Written By: Paing Hein Kyaw, Aye Thwe Tun

#include <iostream>
#include "LinkedList.h"

using namespace std;

/**
  Default Constructor
*/
LinkedList::LinkedList()
{
    head = new Node; // head points to the sentinel node
    head->next = NULL;
    length = 0;
}

/**
  Insert the given data into the linked list with a new node
*/
void LinkedList::insertNode(Game dataIn)
{
  Node *newNode;  // A new node
  Node *pCur;     // To traverse the list
  Node *pPre;     // The previous node

  // Allocate a new node and store num there.
  newNode = new Node;
  newNode->game = dataIn;

  // Initialize pointers
  pPre = head;
  pCur = head->next;

  // Find location: skip all nodes whose code is less than dataIn's code
  while (pCur && newNode->game.getName() > pCur->game.getName())
  {
    pPre = pCur;
    pCur = pCur->next;
  }

  // Insert the new node between pPre and pCur
  pPre->next = newNode;
  newNode->next = pCur;

  //Update collision no.
  newNode->game.setCol(length);

  // Update the counter
  length++;
}

/**
  Removes the target node and returns the deleted item through the reference parameter and returns true or false
*/
bool LinkedList::removeNode(Game& itemOut, string target)
{
  Node *pCur;       // To traverse the list
  Node *pPre;       // To point to the previous node
  bool deleted = false;

  if(length == 0)
    return deleted;
  // Initialize pointers
  pPre = head;
  pCur = head->next;


  // Find node containing the target: Skip all nodes whose name is less than the target
  while (pCur != NULL && pCur->game.getName() < target)
  {
    pPre = pCur;
    pCur = pCur->next;
  }

  // If found, delte the node
  if (pCur && pCur->game.getName() == target)
  {
    itemOut = pCur->game;
    pPre->next = pCur->next;
    delete pCur;
    deleted = true;
    length--;
  }
  return deleted;
}

/**
  Searches the list for the given target and returns it through the reference game parameter and returns true or false
*/
bool LinkedList::searchList(string target, Game &dataOut) const
{
  bool found = false; // assume target not found
  Node *pCur;         // To move through the list

  if(length == 0)
    return found;
  pCur = head->next;

  while(pCur)
  {
    if(pCur->game.getName() == target) {
      dataOut = pCur->game;
      found = true;

      return found;
    }
    pCur = pCur->next;
  }

  return found;
}

/**
  Returns the data of the game with given index through the reference parameter and returns true or false
*/
bool LinkedList::printGame(int index, Game& itemOut)
{
  Node* pCur = head->next;

  int count = 0;
  while(pCur != NULL)
  {
    if(count == index){
      itemOut = pCur->game;
      return true;
    }
    pCur = pCur->next;
    count++;
  }
  return false;
}
