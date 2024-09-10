#ifndef CIRCULAR__H_
#define CIRCULAR__H_
#include"circular.h"
class NoMem{
public:
	NoMem(){}
};
void my_new_handler()
{
	throw NoMem();
}
new_handler Old_Handler_ = set_new_handler(my_new_handler);
class OutOfBounds{
public:
	OutOfBounds(){}
};
template<class T>
circhain<T>::~circhain()
{
	circhainNode<T> *next;
	circhainNode<T> *fnode = first;
	first = first->link;
	while( first != fnode){
		next = first->link;
		delete first;
		first = next;
	}

	delete first;
}
template<class T>