// Specification file for the HashNode class
// Written By: Paing Hein Kyaw, Aye Thwe Tun

#ifndef _HASH_NODE
#define _HASH_NODE

#include "Game.h"
#include "LinkedList.h"

using std::string;

class HashNode
{
private:
    LinkedList item;
    int occupied;

public:
    // constructors
    HashNode() {occupied = 0;}
    HashNode(Game anItem) {item.insertNode(anItem); occupied = 1;}
    HashNode(Game anItem, int ocp)
             {item.insertNode(anItem); occupied = ocp;}
    // setters
    void addItem(const Game &anItem) {item.insertNode(anItem);}
    void setOccupied(int ocp) {occupied = ocp;}
    bool removeItem(Game &anItem, string key) {return item.removeNode(anItem, key);}

    // getters
    LinkedList getList() const {return item;}
    int getOccupied() const {return occupied;}
};

#endif
