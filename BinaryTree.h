// Binary tree abstract base class
// Created by: Aye Thwe Tun, Paing Hein Kyaw

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"

class BinaryTree
{
protected:
	BinaryNode* rootPtr;		// ptr to root node
	int count;							          // number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree & tree){ }
  virtual ~BinaryTree() { destroyTree(rootPtr); }

	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int getCount() const {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
  void inOrder(void visit(Game &)) const  {_inorder(visit, rootPtr);}
  void printIndentedTree(void visit(Game&, int)) const{_printIndentedTree(visit, rootPtr, 1);}
  void printTree(void visit(Game &)) const{_printTree(visit, rootPtr);}
  bool printGenre(void visit(Game &), string genre) const;

	// abstract functions to be implemented by derived class
	virtual bool insert(const Game &newData) = 0;
	//virtual bool remove(const ItemType &data) = 0;
	virtual bool search(const Game &target, Game & returnedItem) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode* nodePtr);

	// internal traverse
	void _inorder(void visit(Game &), BinaryNode* nodePtr) const;
  void _printIndentedTree(void visit(Game&, int), BinaryNode* nodePtr, int level) const;
  void _printTree(void visit(Game &), BinaryNode* nodePtr) const;
  void _printGenre(void visit(Game &), BinaryNode* nodePtr, string genre, bool& success) const;


};

//Prints tree by genre
bool BinaryTree::printGenre(void visit(Game&), string genre) const
{
  bool success = false;
  _printGenre(visit, rootPtr, genre, success);
  return success;
}

//Destroy the entire tree
void BinaryTree::destroyTree(BinaryNode* nodePtr)
{
    if(nodePtr) // != NULL
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        //cout << "DEBUG - Destructor: Now deleting " << nodePtr->getItem().getName() << endl;
        delete nodePtr;
    }
}

///////////////////////////////////////Private Functions/////////////////////////////////////////

//Inorder Traversal
void BinaryTree::_inorder(void visit(Game &), BinaryNode* nodePtr) const
{
    if (nodePtr) // != NULL
    {
        Game item = nodePtr->getItem();
        _inorder(visit, nodePtr->getLeftPtr());
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());
    }
}

//Prints tree as an indented list
void BinaryTree::_printIndentedTree(void visit(Game&, int), BinaryNode* nodePtr, int level) const
{
  if(!nodePtr){
    return;
	}
  Game item = nodePtr->getItem();
	visit(item, level);
	_printIndentedTree(visit, nodePtr->getRightPtr(), level + 1);
	_printIndentedTree(visit, nodePtr->getLeftPtr(), level + 1);

}

//Prints tree as a list
void BinaryTree::_printTree(void visit(Game &), BinaryNode* nodePtr) const
{
     if (nodePtr)
     {
        _printTree(visit, nodePtr->getLeftPtr());
        Game item = nodePtr->getItem();

        visit(item);

        _printTree(visit, nodePtr->getRightPtr());
   }
}

//Prints tree by genre
void BinaryTree::_printGenre(void visit(Game &), BinaryNode* nodePtr, string genre, bool& success) const
{
     if (nodePtr)
     {
        _printGenre(visit, nodePtr->getLeftPtr(), genre, success);
        Game item = nodePtr->getItem();
        if(item.getGenre() == genre)
        {
          visit(item);
          success = true;
        }

        _printGenre(visit, nodePtr->getRightPtr(), genre, success);
   }
}

#endif

