/*************************************************
 * Trie_tester
 * A class for testing tries.
 *
 * Author:  Douglas Wilhelm Harder
 * Copyright (c) 2014 by Douglas Wilhelm Harder.  All rights reserved.
 *
 * DO NOT EDIT THIS FILE
 *************************************************/

#ifndef TRIE_TESTER_H
#define TRIE_TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "Tester.h"
#include "Trie.h"
#include "Trie_node.h"
#include "Trie_node_tester.h"

#include <iostream>

class Trie_tester:public Tester< Trie > {
	using Tester< Trie >::object;
	using Tester< Trie >::command;

	public:
		Trie_tester( Trie *obj = nullptr ):Tester< Trie >( obj ) {
			// empty
		}

		void process();
};

/****************************************************
 * void process()
 *
 * Process the current command.  For trie, these include:
 *
 *  Accessors
 *
 *   size n          size            the size equals n
 *   empty b         empty           the result is the Boolean value b
 *   root            root            the root is not 'nullptr' and starts a Trie_node_tester on that
 *                                   node until the 'exit' command is typed
 *   root0           root            the root is 'nullptr'
 *   member str b    member          a call to member( str ) returns the Boolean value b
 *
 *  Mutators
 *
 *   insert str b    insert          attempting to add the word str to the trie returns b
 *   insert! str     insert          attempting to add the word str results in an exception
 *   erase str b     erase           attempting to remove the word str from the trie returns b
 *   clear           clear           clears the trie (always succeeds)
 *
 *  Others
 *   cout            cout << trie    print the trie (for testing only)
 *   summary                         prints the amount of memory allocated
 *                                   minus the memory deallocated
 *   details                         prints a detailed description of which
 *                                   memory was allocated with details
 *   !!                              use the previous command, e.g.  5 push_front 3
 *                                                                   6 !! 7         // same as push_front 7
 *   !n                              use the command used in line n  7 front 7
 *                                                                   8 !7 9         // same as push_front 9
 *
 ****************************************************/

void Trie_tester::process() {
	if ( command == "new" ) {
		object = new Trie();
		std::cout << "Okay" << std::endl;
	} else if ( command == "size" ) {
		// check if the size equals the next integer read

		int expected_size;

		std::cin >> expected_size;

		int actual_size = object->size();

		if ( actual_size == expected_size ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in size(): expecting the word '" << expected_size << "' but got '" << actual_size << "'" << std::endl;
		}
	} else if ( command == "empty" ) {
		// check if the empty status equals the next Boolean read

		bool expected_empty;

		std::cin >> expected_empty;

		bool actual_empty = object->empty();

		if ( actual_empty == expected_empty ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in empty(): expecting the word '" << expected_empty << "' but got '" << actual_empty << "'" << std::endl;
		}
	} else if ( command == "root" ) {
		// checks that the root is not 'nullptr', and if it is not,
		// the next object gives the number of commands which should
		// be tested by the Trie_node_tester

		Trie_node *actual_root = object->root();

		if ( actual_root == nullptr ) {
			std::cout << "Failure in root(): expecting a non-zero root pointer" << std::endl;
		} else {
			std::cout << "Okay" << std::endl;

			Trie_node_tester tester( actual_root );

			tester.run();
		}
	} else if ( command == "root0" ) {
		// check that the root pointer is 'nullptr'

		if ( object->root() == nullptr ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in root(): expecting a nullptr root pointer" << std::endl;
		}
	} else if ( command == "member" ) {
		// check if the next object read in is in the trie

		std::string str;
		bool expected_member;

		std::cin >> str;
		std::cin >> expected_member;

		if ( object->member( str ) == expected_member ) {
			std::cout << "Okay" << std::endl;
		} else {
			if ( expected_member ) {
				std::cout << "Failure in member( \"" << str << "\" ): expecting the word \"" << str << "\" to be in the trie" << std::endl;
			} else {
				std::cout << "Failure in member( \"" << str << "\" ): not expecting the word \"" << str << "\" to be in the trie" << std::endl;
			}
		}
	} else if ( command == "member!" ) {
		// checking membership on an invalid string should result in an illegal argument exception

		std::string str;
		bool actual_member;

		std::cin >> str;

		try {
			actual_member = object->member( str );
			std::cout << "Failure in member( \"" << str << "\" ): expecting to catch an exception but got \"" << actual_member << "\"" << std::endl;
		} catch( illegal_argument ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in member( \"" << str << "\" ): expecting an illegal argument exception but caught a different exception" << std::endl;
		}
	} else if ( command == "insert" ) {
		// insert the word into the trie

		std::string str;
		bool expected_insert;

		std::cin >> str;
		std::cin >> expected_insert;

		if ( object->insert( str ) == expected_insert ) {
			std::cout << "Okay" << std::endl;
		} else {
			if ( expected_insert ) {
				std::cout << "Failure in insert( " << str << " ): expecting the word \"" << str << "\" to be inserted into the trie" << std::endl;
			} else {
				std::cout << "Failure in insert( " << str << " ): not expecting the word \"" << str << "\" to be inserted into the trie" << std::endl;
			}
		}
	} else if ( command == "insert!" ) {
		// inserting an invalid string should result in an illegal argument exception

		std::string str;
		bool actual_insert;

		std::cin >> str;

		try {
			actual_insert = object->insert( str );
			std::cout << "Failure in insert( \"" << str << "\" ): expecting to catch an exception but got \"" << actual_insert << "\"" << std::endl;
		} catch( illegal_argument ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in insert( \"" << str << "\" ): expecting an illegal argument exception but caught a different exception" << std::endl;
		}
	} else if ( command == "erase" ) {
		std::string str;
		int expected_erase;

		std::cin >> str;
		std::cin >> expected_erase;

		int actual_erase = object->erase( str );

		if ( actual_erase == expected_erase ) {
			std::cout << "Okay" << std::endl;
		} else {
			if ( expected_erase ) {
				std::cout << "Failure in erase( " << str << " ): expecting the word \"" << str << "\" to be removed from the trie" << std::endl;
			} else {
				std::cout << "Failure in erase( " << str << " ): not expecting the word \"" << str << "\" to be removed from the trie" << std::endl;
			}
		}
	} else if ( command == "erase!" ) {
		// calling erase on an invalid string should result in an illegal argument exception

		std::string str;
		bool actual_erase;

		std::cin >> str;

		try {
			actual_erase = object->erase( str );
			std::cout << "Failure in erase( \"" << str << "\" ): expecting to catch an exception but got \"" << actual_erase << "\"" << std::endl;
		} catch( illegal_argument ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in erase( \"" << str << "\" ): expecting an illegal argument exception but caught a different exception" << std::endl;
		}
	} else if ( command == "clear" ) {
		object->clear();
		std::cout << "Okay" << std::endl;
	} else if ( command == "cout" ) {
		std::cout << *object << std::endl;
	} else {
		std::cout << command << "Command not found." << std::endl;
	}
}

#endif
