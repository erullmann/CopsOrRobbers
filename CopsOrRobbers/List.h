//List.h
//Implementation of a linked list for pointers
//NOTE: GIVE THE TYPE OF POINTER YOU WANT, NOT THE POINTER ITSELF
//EX: use int not int*
#pragma once
#include <SFML\Graphics.hpp>
#include "Button.h"
#include "PhysicsComponent.h"
#include "Contact.h"

struct listItem{
	void* p;
	listItem* n;
};

template <typename T> 
class List{
public:

	List();

	List(T* item);

	~List();

	//add an item to the end of the list
	void pushBack(T* item);

	//removes the last item from the list and returns the value
	//returns NULL if list is empty
	T* popBack();

	//removes all items from the list
	void clearList();

	//returns the last item in the list
	//returns NULL for empty lists
	T* last();

	//returns the length of the list 
	//0 for empty lists
	int getLength();

	//removes all instances of a specific item (O(n) operation)
	void removeItem(T* item);

	//returns true if particle present
	//false otherwise
	bool isMember(T* item);

	//attach a list of the same type to the end of this one (O(1) operation)
	//this list will have all of its items and then the new items will come afterwards
	//does not effect attached list (is a copy operation)
	void concat(List<T>* list);

	//returns true if the list is empty
	bool isEmpty();

	listItem* _head;
	listItem* _tail;
	listItem* _sentinal;

	bool _empty();

	int _length;

};