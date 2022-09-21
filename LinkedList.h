// Specification file for the LinkedList class
// Written By: Paing Hein Kyaw, Aye Thwe Tun

#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "Game.h"

class LinkedList
{
private:
  struct Node
  {
    Game game;
    Node *next;
  };

  Node *head;
  int length;

public:
  LinkedList();   // constructor

  // Linked list operations
  int getLength() const {return length;}
  void insertNode(Game);
  bool removeNode(Game&, string);
  bool searchList(string, Game &) const;
  bool printGame(int index, Game& itemOut);
};

#endif
