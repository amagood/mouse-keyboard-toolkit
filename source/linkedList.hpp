#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "myNamespace.hpp"
void freeAll(dataStructure::NODE *a);
dataStructure::NODE* allocateNode();
bool pushBackAtEnd(dataStructure::NODE *a); //insert a node behind a (a->next=newNode)


#endif // LINKEDLIST_HPP
