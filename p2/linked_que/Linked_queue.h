/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
// Replace: 'Single_list' (two changes) with whatever linked-list structure you used in Project 1
//          'Single_node' (two changes) with 'Double_node' if your Project 1 involved doubly linked lists
#include "Double_list.h"
#include "Exception.h"
#include <iostream>

template <typename Type>
class Linked_queue {
	private:
		static int const ARRAY_CAPACITY = 8;

		Double_list<Type *> list;
		int ifront;
		int iback;
		int queue_size;

	public:
		Linked_queue();
		Linked_queue( Linked_queue const & );
		~Linked_queue();

		bool empty() const;
		int size() const;
		int list_size() const;

		Type front() const;

		void swap( Linked_queue & );
		Linked_queue &operator=( Linked_queue );
		void push( Type const &obj );
		Type pop();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Linked_queue<T> const & );
};

template <typename Type>
Linked_queue<Type>::Linked_queue():
queue_size( 0 ) {
	// Empty constructor
}

template <typename Type>
Linked_queue<Type>::Linked_queue( Linked_queue const &queue ):
/*ifront( queue.ifront ),
iback( queue.iback ),
queue_size( queue.queue_size ) {*/

	ifront(0),
		iback(0),
		queue_size(0) {
	/*
	list1 = list;
	delete list;
	ifront = queue.ifront;
	iback = queue.ifront;
	queue_size = queue.ifront;
	list = list1;
	
	
	
	for (Double_node<Type > *ptr = list.front(); ptr != nullptr; ptr = ptr->next())
	{
		push_back(ptr->retrieve());
	}
	Double_list<Type *> list1;

	while (!list.empty())
	{
		list1.push(list.pop());
	}*/

	for (Double_node <Type *> *ptr = queue.list.head(); ptr != nullptr; ptr = ptr->next())
	{
		//std::cout << "enterloop      ";
		//std::cout << queue.list.size()<<   "           ";
		Type *Array = new Type[8];
		
		for (int a = 0; a < 8; a++)
		{
			

			//std
			this->push(ptr->retrieve()[a]);

		}

	}
	ifront = queue.ifront; 
	iback = queue.iback;
	queue_size = queue.queue_size; 



	/*std::cout << list << "         ";
	std::cout << list1 << "         ";
	list = list1;
	std::cout << list << "         ";*/

}

template <typename Type>
Linked_queue<Type>::~Linked_queue() {
	// 
}

template <typename Type>
bool Linked_queue<Type>::empty() const {
	while (queue_size == 0)
	{
		return true; //if the queue has no items, its empty
	}
	return false;
}

template <typename Type>
int Linked_queue<Type>::size() const {
	// enter your implementation here
	return queue_size;
}

// Do not change this implementation

template <typename Type>
int Linked_queue<Type>::list_size() const {
	return list.size();
}

template <typename Type>
Type Linked_queue<Type>::front() const {

	return list.front()[ifront];;
}

template <typename Type>
void Linked_queue<Type>::swap( Linked_queue<Type> &queue ) {
	std::swap( list, queue.list );
	std::swap( queue_size, queue.queue_size );
	std::swap( ifront, queue.ifront );
	std::swap( iback, queue.iback );
}

template <typename Type>
Linked_queue<Type> &Linked_queue<Type>::operator=( Linked_queue<Type> rhs ) {
	swap( rhs );

	return *this;
}

template <typename Type>
void Linked_queue<Type>::push( Type const &obj ) {
	if (empty())
	{
		Type *Array = new Type[8];
		Array[0] = obj;
		//list = new Double_list<Type *>(nullptr, nullptr, 1);
		list.push_back(Array);
		queue_size = 1;
		ifront = 0;
		iback = 0;

	}

	else if (iback == 7 )
	{
		Type *Array = new Type[8];
		Array[0] = obj;
		list.push_back(Array);
		iback = 0;
		queue_size++;

	}

	else
	{	
		iback++;
		list.back()[iback] = obj;
		queue_size++;
	}
	b





}

template <typename Type>
Type Linked_queue<Type>::pop() {
	Type a;
	if (empty())
	{
		throw underflow();

	}

	else if (ifront == 7) // if at the last item 
	{
		
		a = list.front()[ifront];
		list.pop_front();
		ifront = 0;
		queue_size--;

	}

	else
	{
		
		a = list.front()[ifront];
		ifront++;
		queue_size--;
	}

	return a;
}

// Do not modify this function

template <typename T>
std::ostream &operator<<( std::ostream &out, Linked_queue<T> const &queue ) {
	if ( queue.list.size() == 0 ) {
		out << "->0";
	} else if ( queue.list.size() == 1 ) {
		out << "->[ ";

		for ( int i = queue.ifront; i <= queue.iback; ++i ) {
			out << queue.list.front()[i] << " ";
		}

		out << "]->0";
	} else {
		out << "->";

		for ( Double_node<T *> *ptr = queue.list.head(); ptr != nullptr; ptr = ptr->next() ) {
			out << "[ ";

			if ( ptr == queue.list.head() ) {
				for ( int i = queue.ifront; i <= Linked_queue<T>::ARRAY_CAPACITY - 1; ++i ) {
					out << ptr->retrieve()[i] << " ";
				}
			} else if ( ptr == queue.list.tail() ) {
				for ( int i = 0; i <= queue.iback; ++i ) {
					out << ptr->retrieve()[i] << " ";
				}
			} else {
				for ( int i = 0; i <= Linked_queue<T>::ARRAY_CAPACITY - 1; ++i ) {
					out << ptr->retrieve()[i] << " ";
				}
			}

			out << "]->";
		}

		out << "0";
	}

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
