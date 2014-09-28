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

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cctype>
#include "ece250.h"

class Trie;

class Trie_node {
	private:
		Trie_node **children;
		bool is_terminal;
		static int const CHARACTERS = 26;


	public:
		Trie_node();
		Trie_node *child( int ) const;

		bool member( std::string const &, int ) const;

		bool insert(std::string const &, int);
		bool erase( std::string const &, int, Trie_node *& );
		void clear();

		friend class Trie;

		// if ptr is a pointer to a Trie_node object
		// in one of the friendly classes, you should:
		//    use   ptr->next_   to modify it
		//    use   ptr->next()      to access it
};

Trie_node::Trie_node():
children( nullptr ),
is_terminal( false ) {
	// empty constructor
}


Trie_node *Trie_node::child( int n ) const {
	if ( children == nullptr ) {
		return nullptr;
	} 
	else {
		return children[n];
	}
}

bool Trie_node::member( std::string const &str, int depth ) const {
	char c = str[depth];
	//char letter = ;
	int index = std::tolower(c) - 'a';

	/*if (this == nullptr)
	{
		return false; 
	}
	//if (children != nullptr)
		if (children[index] != nullptr)
		{
			if (depth == str.length())
			{
				return true;
			}
			
			return children[index]->member(str, depth + 1);
		}*/

/*
			
		}*/


	if (depth == str.length())
	{
		//std::cout<< is_terminal;
		return is_terminal;
	}
	if (children == nullptr || children[index] == nullptr)
	{
		return false;
	}
	return children[index]->member(str, depth + 1);
}

bool Trie_node::insert( std::string const &str, int depth ) 
{
	//return false;
	

		char c = str[depth];
		char letter = 'a';
		int index = std::tolower(c) - letter;
		if (depth == str.length())
		{
			is_terminal = true;
			return true;
		}
		if (children == nullptr)
		{
			children = new Trie_node*[CHARACTERS] ;
			for (int i = 0; i < CHARACTERS; i++)
			{
				children[i] = nullptr;
			}
			
		}	
		
		if (children[index] == nullptr)
		{
			children[index] = new Trie_node() ;
		
			
		}

		return	children[index]->insert(str, depth + 1);
			

}


bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ) {
	
	/*if (end of tree but not end of word)
	{
		return false;
	}*/
	char c = str[depth];
	char letter = 'a';
	int index = std::tolower(c) - letter;
	
	
	if (depth == str.length() && is_terminal)
	{
		if (children == nullptr) // if leaf node, delete
		{
			delete this;
			return true;

		}
		else
		{
			bool has_children = false;
			for (int i = 0; i < CHARACTERS; i++)
			{
				if (children[i] != nullptr)
				{
					has_children = true;
				}
			}
			if (has_children)// not leaf but terminal, its not terminal anymore
			{

				is_terminal = false;
				return true;
			}
			else // if children[] has nothing, delete children[] 
			{
				delete this;
				return true;
				delete [] children;

			}
		}
		return false;
	}

	

	if (children[index]->erase(str, depth + 1, children[index]))
	{

		if (!is_terminal)
		{
			if (children == nullptr)
			{
				
				delete [] children;
				delete this;
				ptr_to_this = nullptr;

			}
		}
		return true;
	}
	return false;
	
	/*find terminal to the string 
	delete this node if leaf 

	*/

}

void Trie_node::clear() {
	if (children != nullptr) 
	{
		for (int i = 0; i < CHARACTERS; i++) 
		{
			if (children[i] != nullptr)
			{

				children[i]->clear();
			}
		}

		delete[] children; 

	}
	delete this; 



	
}


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
