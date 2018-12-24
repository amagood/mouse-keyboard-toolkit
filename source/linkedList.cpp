#include <stdlib.h>
#include "myNamespace.hpp"

void freeAll(dataStructure::NODE *a)  //free the whole linked list
{
    if(a->next!=nullptr)
    {
        freeAll(a->next);
    }
    free(a->next);
}

dataStructure::NODE* allocateNode()    //create a new node of linked list and return its pointer
{
    dataStructure::NODE *ptr;
    ptr=(dataStructure::NODE *)malloc(sizeof(dataStructure::NODE));
    ptr->data=0;
    ptr->next=nullptr;
    return ptr;
}

bool pushBackAtEnd(dataStructure::NODE *a) //insert a node behind a (a->next=newNode)
{
    if(a->next!=nullptr)
        return false;//not the end node

    //else
    dataStructure::NODE *newNode=allocateNode();
    a->next=newNode;
    return true;
    //endelse

}
