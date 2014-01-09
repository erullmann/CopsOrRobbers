#pragma once

#include "List.h"

template <typename A> class ListIter{
public:
	ListIter(List<A>* list);

	//sets the head to the begining of the current list
	void reset();

	void set(listItem* item);

	listItem* getPlace();

	//Returns the current particle the iterator is looking at
	//Returns NULL if list is empty or if at end of list
	A* curr();

	//Moves head to next item in list and returns new item
	//Returns NULL if list is empty or if at end of list
	A* next();

	//returns next item in list
	//Returns NULL if list is empty or if at end of list
	A* peek();

	//Assigns the iterator to a new list and sets the head to the begining of the list
	void assignList(List<A>* list);

	//returns true if the iterator is at the end of the list or if the list it empty
	//returns false otherwise
	bool atEnd();

private:
	listItem* currItem;
	List<A>* currList;
};