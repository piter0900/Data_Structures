
/*****************************************
 * UW User ID:  d8mitche
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2014
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

//class definition
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
		bool empty() const;

		Type front() const;
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

// empty constructor
template <typename Type>
Double_list<Type>::Double_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {}
	

// copy constructor
template <typename Type>
Double_list<Type>::Double_list( Double_list<Type> const &list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) 
{	//traverse the list
	for(Double_node<Type> *ptr = list.head();ptr != nullptr; ptr = ptr -> next())
		{
			this -> push_back(ptr -> retrieve()); //copy nodes from front of the list to the back of the new list
		}
}

//Destructor 
template <typename Type>
Double_list<Type>::~Double_list() //traverse the list, popping the front node off one by one
{ 
	while(!empty())
	{
		pop_front();
	}
}


template <typename Type>
int Double_list<Type>::size() const //returns the amount of elements in the list , aka the list size
{
	return list_size;
}

template <typename Type>
bool Double_list<Type>::empty() const //Checks if the list is empty. If the list_head is nullptr then yes, else no
{ 
	return (list_head == nullptr);
}

template <typename Type>
Type Double_list<Type>::front() const // returns value at head 
{ 
	if (empty())
	{
		throw underflow(); // if list is empty, throw underflow exception
	}
	else
	{
		return head() -> retrieve(); //retrieves value
	}
}

template <typename Type>
Type Double_list<Type>::back() const //returns the value at tail
{
	if (empty())
	{
		throw underflow(); // if list is empty, throw underflow exception
	}
	else
	{
		return tail() -> retrieve(); //retrieves value
	}
}

template <typename Type>
Double_node<Type> *Double_list<Type>::head() const 
{ 
	return list_head;
}

template <typename Type>
Double_node<Type> *Double_list<Type>::tail() const 
{ 
	return list_tail;
}

template <typename Type>
int Double_list<Type>::count( Type const &obj ) const //counts how many times an element appears in the list
{ 
	int match_count = 0;
	for (Double_node <Type> *ptr = head(); ptr != nullptr; ptr = ptr -> next()) //traverse the list
	{
		if (ptr -> retrieve() == obj) //if element is found
		{
			match_count++; //increment the number of times it appears by 1
		}
	}
	
	return match_count;
}

template <typename Type>
void Double_list<Type>::swap( Double_list<Type> &list ) //transfers contents from the list you call the function on to another list
{ 
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Double_list<Type> &Double_list<Type>::operator=( Double_list<Type> const &rhs ) //creates a copy and swaps the copy
{  
	Double_list<Type> copy( rhs );
	swap( copy );
	
	return *this;
}

template <typename Type>
void Double_list<Type>::push_front( Type const &obj ) //adds an element to the front of the list
{ 
	if (empty()) 
	{
		list_head = new Double_node <Type> (obj, nullptr, nullptr); //added element becomes head
		list_tail = list_head;  //added element becomes tail
	}
	else
	{
		list_head = new Double_node <Type> (obj, nullptr, head()); //assigns head to added element
		head() -> next() -> previous_node = head(); // redirects previous pointer of the previous head to the new head
	}
		
	list_size++; 
}

template <typename Type>
void Double_list<Type>::push_back( Type const &obj ) //add an element to the end of the list
{
	if (empty())
	{
		list_head = new Double_node <Type> (obj, nullptr, nullptr); //added element becomes head
		list_tail = list_head; //added element becomes tail
	}
	else
	{
		list_tail = new Double_node <Type> (obj,tail(), nullptr); //assigns tail to added element
		tail() -> previous() -> next_node = tail(); //assigns the next pointer of the old tail to the new tail
	}
		
	list_size++; 
}

template <typename Type>
Type Double_list <Type> ::pop_front() //removes the first element of the list
{ 	
	Type e = front(); //assigns the value at head to local variable e. front() also ensures that if the list is empty,
					  //underflow exception is thrown
	Double_node <Type> *ptr = head(); //creates a pointer and assigns is to head
	if (list_size == 1)
	{
		list_head = nullptr; //list is now empty, therefore, assign head to null;
		list_tail = nullptr; //list is now empty, therefore, assign tail to null;
	}
	else
	{
		list_head = head() -> next(); //reassign head to the second element in the list
	}
		
	list_size--; 

	delete ptr; //deallocate the memory used by the pointer
				//also sets the previous pointer of the new head to null

	return e; // returns the value that was popped  
}

template <typename Type>
Type Double_list<Type>::pop_back() //removes the last element in the list
{ 
	Type e = back(); //assigns the value at tail to local variable e.
					 //back() ensures underflow is thrown if list is empty

	Double_node <Type> *ptr = tail(); //creates a pointer and assigns is to head
	if (list_size == 1)
	{
		list_head = nullptr; //list is now empty, therefore, assign head to null;
		list_tail = nullptr; //list is now empty, therefore, assign tail to null;
	}
	else
	{
		list_tail = tail() -> previous(); //assigns tail to second last element in the list
	}
	delete ptr; //deallocate the memory used by the pointer
				//also sets the next pointer of the new tail to null

	list_size--; 
	
	return e; //returns popped value
}

template <typename Type>
int Double_list<Type>::erase( Type const &obj ) //deletes passed-in element
{ 	
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
	for(Double_node <Type> *ptr = head();ptr != nullptr;ptr = ptr -> next()) //else, traverse the list
	{
		if (ptr -> retrieve() == obj) //if the element is found
		{
			ptr -> previous() -> next_node = ptr -> next(); //reassigns the next pointer of the previous node to the next ptr 
															//of the node to be deleted
			ptr -> next() -> previous_node = ptr -> previous(); // reassigns the previous pointer of the next node to the 
																// previous ptr of the node to be deleted
			delete ptr; // deletes desired node and deallocates the memory
			list_size--; 
			return 1;
		}
	}
		
	return 0; //returns 1 if the desired element was found and zero otherwise
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








template <typename Type>
Double_list<Type>::Double_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// empty constructor
}