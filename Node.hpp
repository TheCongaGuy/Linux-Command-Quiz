#pragma once

template <typename NODETYPE>
class Node
{
public:
    // Constructor
    // Requires Data
    Node(NODETYPE nData);

    // Getters
    NODETYPE getData() const;
    Node<NODETYPE>* getPrevPtr();
    Node<NODETYPE>* getNextPtr();

    // Setters
    void setPrevPtr(Node<NODETYPE>* nPPrev);
    void setNextPtr(Node<NODETYPE>* nPNext);
private:
    // Data stored in the node
    NODETYPE data;

    // Pointers to previous and next nodes
    Node<NODETYPE>* pPrev;
    Node<NODETYPE>* pNext;
};

// --------Template Function Definitions--------

// Constructor
template <typename NODETYPE>
Node<NODETYPE>::Node(NODETYPE nData)
{
    // Store the new data
    data = nData;

    // Set pPrev and pNext to null
    pPrev = nullptr;
    pNext = nullptr;
}

// Getters
template <typename NODETYPE>
NODETYPE Node<NODETYPE>::getData() const { return data; }
template <typename NODETYPE>
Node<NODETYPE>* Node<NODETYPE>::getPrevPtr() { return pPrev; }
template <typename NODETYPE>
Node<NODETYPE>* Node<NODETYPE>::getNextPtr() { return pNext; }

// Setters
template <typename NODETYPE>
void Node<NODETYPE>::setPrevPtr(Node<NODETYPE>* nPPrev) { pPrev = nPPrev; }
template <typename NODETYPE>
void Node<NODETYPE>::setNextPtr(Node<NODETYPE>* nPNext) { pNext = nPNext; }