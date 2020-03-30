//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Josef Kotoun <xkotou06@stud.fit.vutbr.cz>
// $Date:       $2020-02-16
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Josef Kotoun
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    head = NULL;
}

PriorityQueue::~PriorityQueue()
{
    Element_t *current = GetHead();
    Element_t *toRemove;
    while(current!=NULL)
    {
        toRemove = current;
        current = current->pNext;
        delete toRemove;
    }
    head = NULL;
}
void PriorityQueue::Insert(int value)
{
    Element_t *newElement = new Element_t();
    newElement->value = value;
    if(GetHead() == NULL)
    {
        newElement->pPrev = NULL;
        newElement->pNext = NULL;
        head = newElement;
        return;
    }
    else
    {
        Element_t *current = GetHead();
        while(current != NULL)
        {
            //mensi nez prvni prvek
            if(current->value>= value && current->pPrev == NULL)
            {
                newElement->pNext = current;
                newElement->pPrev = NULL;
                current->pPrev = newElement;
                head = newElement;
                return;
            }
            //posledni prvek
            else if(current->pNext == NULL)
            {
                current->pNext = newElement;
                newElement->pPrev = current;
                newElement->pNext = NULL;
                return;
            }
            //mezi 2 prvky (odpovida hodnota)
            else if(current->value<value && current->pNext->value >= value)
            {
                newElement->pPrev = current;
                newElement->pNext = current->pNext;
                newElement->pNext->pPrev = newElement;
                current->pNext = newElement;
                return;
            }
            current = current->pNext; 
        }
    }
}
bool PriorityQueue::Remove(int value)
{
    Element_t *elementToRemove = Find(value);
        if(elementToRemove != NULL)
        {   
            //mezi prvky
            if(elementToRemove->pPrev != NULL && elementToRemove->pNext != NULL)
            {
                elementToRemove->pPrev->pNext = elementToRemove->pNext;
                elementToRemove->pNext->pPrev = elementToRemove->pPrev;
            }
            //je prvni a za nim jsou dalsi
            else if(elementToRemove->pPrev == NULL && elementToRemove->pNext!=NULL)
            {
                head = elementToRemove->pNext;
                elementToRemove->pNext->pPrev = NULL;
            }
            //je posledni
            else if(elementToRemove->pPrev != NULL && elementToRemove->pNext == NULL)
            {
                elementToRemove->pPrev->pNext = NULL;
            }
            //jediny prvek ve fronte
            else
            {
                head = NULL;
            }
            delete elementToRemove;     
            return true;
        }
    return false;
}
PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    Element_t *current = GetHead();
    while(current!=NULL)
    {
        if(current->value == value)
            return current;
        current = current->pNext;
    }
    return NULL;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return head;
}

/*** Konec souboru tdd_code.cpp ***/
