//This implementation uses a sentinal end value
#include "List.h"

template<typename T> List<T>::List(){
	_length = 0;

	_sentinal = new listItem;
	_sentinal->n = NULL;
	_sentinal->p = NULL;

	_head = _sentinal;
	_tail = _sentinal;
}

template<typename T> List<T>::List(T* item){
	_length = 0;

	_sentinal = new listItem;
	_sentinal->n = NULL;
	_sentinal->p = NULL;

	_head = _sentinal;
	_tail = _sentinal;

	pushBack(item);
}

template <typename T>
List<T>::~List(){
	clearList();
}

template <typename T>
void List<T>::pushBack(T* item){
	_length++;

	if(_empty()){
		_head = new listItem;
		_head->n = _sentinal;
		_head->p = (void*) item;

		_tail = _head;

	} else {
		_tail->n = new listItem;
		_tail = _tail->n;
		_tail->n = _sentinal;
		_tail->p = (void*) item;
	}
}

template <typename T>
T* List<T>::popBack(){
	if(_empty()){
		return NULL;
	} else {
		_length--;

		listItem* curr = _head;
		listItem* prev = NULL;
		T* p = NULL;

		while(curr != _tail){
			prev = curr;
			curr = curr->n;
		}

		if(prev == NULL){
			p = (T*) _tail->p;
			delete _tail;
			_tail = _sentinal;
			_head = _sentinal;

		} else {
			prev->n = _sentinal;
			p = (T*) _tail->p;
			delete _tail;
			_tail = prev;
		}

		return p;
	}
}

template <typename T>
void List<T>::clearList(){
	listItem* prev = _head;

	while(_head != _sentinal){
		popBack();
	}

	_length = 0;
}

template <typename T>
T* List<T>::last(){
	return (T*) _tail->p;
}

template <typename T>
int List<T>::getLength(){
	return _length;
}

template <typename T>
void List<T>::removeItem(T* item){
	listItem* curr = _head;
	listItem* prev = NULL;

	while(curr != _sentinal){
		if((T*) curr->p == item){

			if(prev == NULL){
				_head = curr->n;
				prev = _head;
				delete curr;
			} else {
				prev->n = curr->n;
				delete curr;
			}

			if(_tail == curr){
				_tail = _sentinal;
			}

			curr = prev->n;
		} else {
			curr = curr->n;
		}
	}
}

template <typename T>
bool List<T>::isMember(T* item){
	listItem* curr = _head;
	while(curr != _sentinal){
		if((T*) curr->p == item)
			return true;
		else 
			curr = curr->n;
	}
	return false;
}

template <typename T>
void List<T>::concat(List<T> *list){
	listItem* curr = list->_head;
	while(curr != list->_sentinal){
		pushBack((T*) curr);
		curr = curr->n;
	}
}

template <typename T>
bool List<T>::isEmpty(){
	return _head == _sentinal;
}

template <typename T>
bool List<T>::_empty(){
	return _head == _sentinal;
}

template class List<Button>;
template class List<PhysicsComponent>;
template class List<Contact>;
