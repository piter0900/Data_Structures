/*****************************************
 * UW User ID:  y22Lai
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#define nullptr 0

#include "ece250.h"
#include "Double_node.h"
#include "Exception.h"

#define nullptr 0

template <typename Type>
class Double_list {
	private:
		Double_node<Type> *list_head;
		Double_node<Type> *list_tail;
		int list_size; 

	public:
		Double_list();

		Double_list( Double_list const & );
		~Double_list();

		// Accessors

		int size() const;
		
		bool empty()const;
		
		Type front()const;
		
		Type back() const;
		

		Double_node<Type> *head() const;
		
		Double_node<Type> *tail() const;
	

		int count( Type const & ) const;


		// Mutators

		void swap( Double_list & );
		Double_list &operator=( Double_list const & );

		void push_front( Type const & );
		void push_back( Type const & );

		Type pop_front();
		Type pop_back();

		int erase( Type const & );

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_list<T> const & );
};

template <typename Type>
Double_list<Type>::Double_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// empty constructor
}

template <typename Type>
Double_list<Type>::Double_list( Double_list<Type> const &list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	for(Double_node<Type> *ptr = list.head() ;ptr != nullptr; ptr = ptr -> next())
	{
			push_back(ptr->retrieve()); 
	}
}

template <typename Type>
Double_list<Type>::~Double_list() 
{
	//for(Double_node<Type> *ptr = list_head ;ptr != nullptr; ptr = ptr -> next())
//	{
		while(!empty())
		{
		pop_front();
		}
 //}
}

template <typename Type>
int Double_list<Type>::size() const {

		return list_size;
}

template <typename Type>
bool Double_list<Type>::empty() const {
	return (list_size == 0);
}

template <typename Type>
Type Double_list<Type>::front() const {
	{
			if(empty())
			throw underflow();
			else
			return list_head->retrieve();		//return the vale of List_head
		} 
							
}

template <typename Type>
Type Double_list<Type>::back() const {
	{
			if(empty())
			throw underflow();
			else
			return list_tail->retrieve(); 			//return the vale of list_tail
		}

} 

template <typename Type>
Double_node<Type> *Double_list<Type>::head() const {
	return list_head;
}

template <typename Type>
Double_node<Type> *Double_list<Type>::tail() const {
	return list_tail;
}

template <typename Type>
int Double_list<Type>::count( Type const &obj ) const 
{
	int i = 0;
	for(Double_node<Type> *ptr = list_head;ptr != nullptr; ptr = ptr -> next())
	{
		if(ptr->retrieve() == obj)			//while the value of ptr = the parameter 
		{i++;}								// counter ++
	}
	return i;
}

template <typename Type>
void Double_list<Type>::swap( Double_list<Type> &list ) {
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Double_list<Type> &Double_list<Type>::operator=( Double_list<Type> const &rhs ) {
	Double_list<Type> copy( rhs );

	swap( copy ); 					
	
	return *this;
}

template <typename Type>
void Double_list<Type>::push_front( Type const &obj ) 
{

	if (empty()) 
	{
		Double_node<Type> *new_node = new Double_node<Type>(obj, nullptr, nullptr);
		list_head = new_node;
		list_tail = list_head;
		list_size++; 
	}
	else
	{
	Double_node<Type> *new_node = new Double_node<Type>(obj, nullptr, list_head);     //point the current node to the list head 
	list_head->previous_node = new_node;
	new_node->next_node = list_head;
	
	list_head = new_node;            // swap the list tail with the ADDRESS of the list head 
	list_size++;        
	
	}
}

template <typename Type>
void Double_list<Type>::push_back( Type const &obj ) 
{
	if (empty()) 
	{
		Double_node<Type> *new_node = new Double_node<Type>(obj, nullptr, nullptr);
		list_head = new_node;
		list_tail = list_head;
		list_size++; 
	}
	else
	{
	Double_node<Type> *new_node = new Double_node<Type>(obj, list_tail, nullptr);     //point the current node to the list head 
	list_tail->next_node = new_node;
	new_node->previous_node = list_tail;
	list_tail = new_node;            // swap the list tail with the ADDRESS of the list head 
	list_size++;
	}
}

template <typename Type>
Type Double_list<Type>::pop_front() 
{
	Type s = front();
	if (list_size==1)
	{
		
		Double_node<Type> *Temp = list_head;
		list_head = nullptr;
		//change list head 
		list_size--;
		delete Temp;
	}
	else{
	Double_node<Type> *Temp = list_head;
	
	list_head = list_head->next() ;
	list_head->previous_node = nullptr;
	//change list head 
	list_size--;
	delete Temp; 
	}		// cant find the destructor
	
	return s;			
}

template <typename Type>
Type Double_list<Type>::pop_back() 
{
	Double_node<Type> *Temp = list_tail;
	Type s = list_tail->retrieve();
	list_tail == list_tail->previous();
	list_tail->next_node = nullptr;
	;//change list head 
	list_size--;
	delete Temp;               

	return s;	
}

template <typename Type>
int Double_list<Type>::erase( Type const &obj ) {
				//only destro one node 
	if (obj == head() -> retrieve()) //if element we want to delete is the head
	{
		pop_front(); 
		return 1;
	}
	if (obj == tail() -> retrieve()) //if element we want to delete is the tail
	{
		pop_back();
		return 1;
	}	
	for(Double_node<Type> *ptr = list_head; ptr != nullptr; ptr = ptr -> next())
	{
		if (ptr->retrieve() == obj)
		{
			ptr->next()->previous_node = ptr->previous();
			ptr->previous()->next_node = ptr->next();
			delete ptr; 
			list_size--;
		}
	}		//trversy though 
				//if find node
				//swap the previous and next 
				//delete the current node 
				//special casese for head, tail
	return 1; //	
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_list<T> const &list ) {
	out << "head";

	for ( Double_node<T> *ptr = list.head(); ptr != nullptr; ptr = ptr->next() ) {
		out << "->" << ptr->retrieve();
	}

	out << "->0" << std::endl << "tail";

	for ( Double_node<T> *ptr = list.tail(); ptr != nullptr; ptr = ptr->previous() ) {
		out << "->" << ptr->retrieve();
	}

	out << "->0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
