#pragma once

#include "Node.hpp"

// NODETYPE has to have a copy constructor
template <typename NODETYPE>
class LinkedList
{
public:
    // Default Constructor
    LinkedList();

    // Destructor
    ~LinkedList();

    // Checks if the list is empty
    // Returns a bool
    bool isEmpty();

    // Inserts a node at the back of the list
    // Takes a piece of data, must have a copy constructor
    void insertBack(NODETYPE nData);

    // Removes a node at the specified index
    // Takes an int, returns true if something was deleted
    bool removeAt(int index);

    // Returns the size of the list
    int size();

    // Gets the node at the specified index
    // Takes an integer, returns the data located inside of the node
    NODETYPE getData(int index);

private:
    // Pointer to the front of the list
    Node<NODETYPE>* pHead;
};

// --------Template Function Definitions---------

// Constructor
template <typename NODETYPE>
LinkedList<NODETYPE>::LinkedList()
{
    pHead = nullptr;
}

// Destructor
template <typename NODETYPE>
LinkedList<NODETYPE>::~LinkedList()
{
    // Delete every node in the list
    while (pHead != nullptr)
    {
        // Delete itself if it is the last node
        if (pHead->getNextPtr() == nullptr)
        {
            delete pHead;
            pHead = nullptr;
            break;
        }
        
        // Delete all subnodes
        pHead = pHead->getNextPtr();
        delete pHead->getPrevPtr();
    }
}

// Checks if the list is empty
// Returns a bool
template <typename NODETYPE>
bool LinkedList<NODETYPE>::isEmpty()
{
    return pHead == nullptr;
}

// Inserts a node at the back of the list
// Takes a piece of data, must have a copy constructor
template <typename NODETYPE>
void LinkedList<NODETYPE>::insertBack(NODETYPE nData)
{
    // Allocate memory to the heap
    Node<NODETYPE>* mPTemp = new Node<NODETYPE>(nData);

    // If the list is empty, assign the new node as the head node
    if (isEmpty())
        pHead = mPTemp;
    
    // Otherwise, move through the list and insert at back
    else
    {
        // Traversal pointer
        Node<NODETYPE>* pTraversal = pHead;

        // While we are not at the end of the list, update the traversal pointer
        while(pTraversal->getNextPtr() != nullptr)
            pTraversal = pTraversal->getNextPtr();
        
        // Set the new node's pPrev to the traversal pointer
        mPTemp->setPrevPtr(pTraversal);
        // Set the traversal pointer's pNext to the new node
        pTraversal->setNextPtr(mPTemp);
    }
}

// Removes a node at the specified index
// Takes an int, returns true if something was deleted
template <typename NODETYPE>
bool LinkedList<NODETYPE>::removeAt(int index)
{
    // Traversal pointer
    Node<NODETYPE>* pTraversal = pHead;

    // Step through the list up until the specified index
    for (int i = 0; i < index; i++)
    {
        // Return false if index was out of bounds
        if (pTraversal->getNextPtr() == nullptr)
            return false;

        // Move through the list
        pTraversal = pTraversal->getNextPtr();
    }

    // If this is the only node in the list, set pHead to null
    if (pTraversal->getNextPtr() == nullptr && pTraversal == pHead)
    {
        delete pTraversal;
        pHead = nullptr;
        return true;
    }

    // Set the pPrev and pNext nodes to reference eachother
    if (pTraversal->getPrevPtr() != nullptr)
        pTraversal->getPrevPtr()->setNextPtr(pTraversal->getNextPtr());
    
    if (pTraversal->getNextPtr() != nullptr)
        pTraversal->getNextPtr()->setPrevPtr(pTraversal->getPrevPtr());
    
    // Set the head pointer to the next node if head node is deleted
    if (pTraversal == pHead)
        pHead = pTraversal->getNextPtr();
    
    // Remove the target node
    delete pTraversal;
    return true;
}

// Returns the size of the list
template <typename NODETYPE>
int LinkedList<NODETYPE>::size()
{
    // Size of the list
    int size = 0;

    // Traversal pointer
    Node<NODETYPE>* pTraversal = pHead;
    
    // Count the nodes
    while (pTraversal != nullptr)
    {
        size++;
        pTraversal = pTraversal->getNextPtr();
    }

    // Return the counter
    return size;
}

// Gets the node at the specified index
// Takes an integer, returns the data located inside of the node
template <typename NODETYPE>
NODETYPE LinkedList<NODETYPE>::getData(int index)
{
    // Traversal pointer
    Node<NODETYPE>* pTraversal = pHead;

    // Step through the LinkedList for the specified index
    for (int i = 0; i < index; i++)
    {
        pTraversal = pTraversal->getNextPtr();
    }

    return pTraversal->getData();
}