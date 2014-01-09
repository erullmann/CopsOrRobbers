#include "ListIter.h"

template <typename T>
ListIter<T>::ListIter(List<T>* list){
	currList = list;
	currItem = currList->_head;
}

template <typename T>
void ListIter<T>::reset(){
	currItem = currList->_head;
}

template <typename T>
void ListIter<T>::set(listItem* item){
	currItem = item;
}

template <typename T>
listItem* ListIter<T>::getPlace(){
	return currItem;
}

template <typename T>
T* ListIter<T>::curr(){
	return (T*) currItem->p;
}

template <typename T>
T* ListIter<T>::next(){
	currItem = currItem->n;
	return (T*) currItem->p;
}

template <typename T>
T* ListIter<T>::peek(){
	return (T*) currItem->n->p;
}

template <typename T>
void ListIter<T>::assignList(List<T>* list){
	currList = list;
	currItem = currList->_head;
}

template <typename T>
bool ListIter<T>::atEnd(){
	return currItem == currList->_sentinal;
}

template class ListIter<Button>;
template class ListIter<PhysicsComponent>;
template class ListIter<Contact>;