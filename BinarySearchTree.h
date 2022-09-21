// Binary Search Tree ADT
// Created by: Aye Thwe Tun, Paing Hein Kyaw

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

class BinarySearchTree : public BinaryTree
{
public:
    // insert a node at the correct location
    bool insert(const Game &item);
    // remove a node if found
    bool remove(const Game &item);
    // find a target node
    bool search(const Game &target, Game &returnedItem) const;

private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode* _insert(BinaryNode* nodePtr, BinaryNode* newNode);

	// search for target node
	BinaryNode* _search(BinaryNode* treePtr, const Game &target) const;

  // internal remove node: locate and delete target node
  BinaryNode* _remove(BinaryNode* nodePtr, const Game target);

  BinaryNode* _delete(BinaryNode* nodePtr, Game target);

  BinaryNode* FindMin(BinaryNode* nodePtr);
};


///////////////////////// public function definitions ///////////////////////////
//Wrapper for _insert - Inserting items within a tree
bool BinarySearchTree::insert(const Game & newEntry)
{
	BinaryNode* newNodePtr = new BinaryNode(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	return true;
}

//Wrapper for _search
// - it calls the private _search function that returns a Node pointer or NULL
// - if found, it copies data from that node and sends it back to the caller
//   via the output parameter, and returns true, otherwise it returns false.
bool BinarySearchTree::search(const Game& anEntry, Game & returnedItem) const
{
    BinaryNode* temp = nullptr;

    temp = _search(this->rootPtr, anEntry);
    if(temp)
    {
       returnedItem = temp->getItem();
       return true;
    }
    return false;
}

//Remove the target item from the BST
bool BinarySearchTree::remove(const Game &item)
{
  BinaryNode* temp = nullptr;
  Game target = item;

  temp = _delete(this->rootPtr, target);
  if(temp)
  {
    return true;
  }
  return false;
}

//////////////////////////// private functions ////////////////////////////////////////////

//Implementation of the insert operation
BinaryNode* BinarySearchTree::_insert(BinaryNode* nodePtr, BinaryNode* newNodePtr)
{
     if( !nodePtr) // == NULL
    {
        nodePtr = newNodePtr;
        return nodePtr;
    }

    Game item = newNodePtr->getItem();

    if (item < nodePtr->getItem())
        nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
    if (item >= nodePtr->getItem())
        nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));

    return nodePtr;
}

//Implementation for the search operation
// - return NULL if target not found, otherwise
BinaryNode* BinarySearchTree::_search(BinaryNode* nodePtr, const Game &target) const
{
    BinaryNode* found = nullptr;

    if(!nodePtr)
    {
        return found;
    }

    Game item = target;

    if(item.getGenre() == nodePtr->getItem().getGenre())
    {
        found = nodePtr;
        return found;
    }
    else if(item > nodePtr->getItem())
    {
        return _search(nodePtr->getRightPtr(), target);
    }
    else
    {
        return _search(nodePtr->getLeftPtr(), target);
    }
    return found;
}

/**
 Find the minimum root of the BST
*/
BinaryNode* BinarySearchTree::FindMin(BinaryNode* root)
{
	while(root->getLeftPtr() != NULL) root = root->getLeftPtr();
	return root;
}

// Function to search a delete a value from tree.
BinaryNode* BinarySearchTree::_delete(BinaryNode *root, Game data) {
	if(root == NULL) return root;
	else if(data < root->getItem()) root->setLeftPtr(_delete(root->getLeftPtr(),data));
	else if (data > root->getItem()) root->setRightPtr(_delete(root->getRightPtr(),data));

	if(root->getItem().getName() == data.getName()){
		// Case 1:  No child
		if(root->getLeftPtr() == NULL && root->getRightPtr() == NULL) {
			delete root;
			root = NULL;
		}
		//Case 2: One child
		else if(root->getLeftPtr() == NULL) {
			BinaryNode *temp = root;
			root = root->getRightPtr();
			delete temp;
		}
		else if(root->getRightPtr() == NULL) {
			BinaryNode *temp = root;
			root = root->getLeftPtr();
			delete temp;
		}
		// case 3: 2 children
		else {
			BinaryNode *temp = FindMin(root->getRightPtr());
			root->setItem(temp->getItem());
			root->setRightPtr(_delete(root->getRightPtr(),temp->getItem()));
		}
  }
  else{
      root->setRightPtr(_delete(root->getRightPtr(), data));
    }
	return root;
}
#endif
