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

#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;

	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const; 
		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():
root_node( nullptr ),
trie_size( 0 ) {
	// empty constructor
}

Trie::~Trie() {
	if (root_node == nullptr)
	{
		return;
	}
	clear();
}

int Trie::size() const {
	return trie_size;
}

bool Trie::empty() const {
	return (trie_size == 0);
}

Trie_node *Trie::root() const {
	return root_node;
}

bool Trie::member( std::string const &str ) const {
	for (int i = 0; i < str.length(); i++)
	{
		if (tolower(str[i]) < 'a' || tolower(str[i]) > 'z')
		{
			throw illegal_argument();
		}
	}
		
	
	return root_node->member(str, 0);
	
		
		

}

bool Trie::insert(std::string const &str) {
	for (int i = 0; i < str.length(); i++)
	{
		if (tolower(str[i]) < 'a' || tolower(str[i]) > 'z')
		{
			throw illegal_argument();
		}
	}
	
	if (root_node == nullptr)
	{
		root_node = new Trie_node();
	}
	
	if (!(root_node->member(str, 0)))
	{
		
		trie_size++;
		std::cout << trie_size;
		return (root_node->insert(str, 0));
		
	}

	return false;
	
}

bool Trie::erase( std::string const &str ) {
	for (int i = 0; i < str.length(); i++)
	{
		if (tolower(str[i]) < 'a' || tolower(str[i]) > 'z')
		{
			throw illegal_argument();
		}
	}
	if ((member(str)))
	{

		trie_size--;
		std::cout << trie_size; 
		return (root_node->erase(str,0,root_node));

	}
	else
	{
		return false;
	}

}

void Trie::clear() {
	if (!empty())
	{
		root_node->clear();
		trie_size = 0;
		root_node = nullptr;
		return;
	}
	else
	{
		root_node = nullptr;
		return;
	}
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {
/*	for ( Trie_node *ptr = trie.head(); ptr != nullptr; ptr = ptr->next() ) {
		out << "->" << ptr->value();
	} */

	out << "->0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
