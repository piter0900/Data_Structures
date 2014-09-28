/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template <typename Type>
class Double_hash_table {
	private:
		int count;
		int power;
		int array_size;
		int mask;
		Type *array;
		state *occupied;

		int h1( Type const & ) const;
		int h2( Type const & ) const;

	public:
		Double_hash_table( int = 5 );
		~Double_hash_table();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( Type const & ) const;
		Type bin( int ) const;

		void print() const;

		void insert( Type const & );
		bool erase( Type const & );
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_hash_table<T> const & );
};

template <typename Type>
Double_hash_table<Type>::Double_hash_table( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
mask( array_size - 1 ),
array( new Type[array_size] ),
occupied( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = EMPTY;

		
	}
}
template <typename Type>
Double_hash_table<Type>::~Double_hash_table()
{
	delete[] array;
	delete[] occupied;
}

template <typename Type>
int Double_hash_table<Type>::h1(Type const &obj) const
{
	int para = static_cast<int>(obj);
	int bin = para % array_size;
	//std::cout << bin << std::endl;
	if (bin < 0)
	{
		bin = bin + array_size;
	}
	return bin;


}

template <typename Type>
int Double_hash_table<Type>::h2(Type const &obj) const
{
	int para = static_cast<int>(obj);
	int bin = para / array_size;
	int jump = (bin % array_size); 
	if (jump < 0)
	{
		jump = jump + array_size;
	}

	return jump|1;

	}


template <typename Type>
int Double_hash_table<Type>::size() const{
	return count;
}
//Returns the number of elements currently stored in the hash table. (成(1))

template <typename Type>
int Double_hash_table<Type>::capacity() const
{
	return array_size;
}
//Returns the number of bins in the hash table. (成(1))

template <typename Type>
double Double_hash_table<Type>::load_factor() const
{
	return (count / array_size); 
}
//Returns the load factor of hash table(see static_cast<double>(...)).This should be the ratio of occupied bins over the total number of bins. (成(1))

template <typename Type>
bool Double_hash_table<Type>::empty() const
{
	return (count == 0);
}
//Returns true if the hash table is empty, false otherwise. (成(1))

template <typename Type>
bool Double_hash_table<Type>::member(Type const &obj) const
{	
	for (int i = 0; i < array_size; i++)
	{
		if (occupied[i] == OCCUPIED)
		{
			if (array[i] == obj)
			{
				return true;
			}
		}
	}
	return false; 

}
//Returns true if object obj is in the hash table and false otherwise. (成(1) under our assumptions)


template <typename Type>
Type Double_hash_table<Type>::bin(int n) const
{
	//std::cout << static_cast<int>(array[n]);
	return array[n]; 
}
//Return the entry in bin n.The behaviour of this function is undefined if the bin is not filled.It will only be used to test locations that are expected to be filled by specific values. (成(1))


template <typename Type>
void Double_hash_table<Type>::print() const
{
	for (int i = 0; i < array_size; i++)
	{
		std::cout << array[i];
	}
}



template <typename Type>
void Double_hash_table<Type>::insert(Type const &obj)
{
	if (!member(obj))
	{
		int h_1 = h1(obj);
		int h_2 = h2(obj);

		for (int i = 0; i < array_size; i++)
		{

			if (occupied[h_1] != OCCUPIED)
			{
				array[h_1] = obj;
				occupied[h_1] = OCCUPIED;
				count++;
				return;
				//	std::cout << array[h_1]<<std::endl;
			}
			int binNum = ((h_1 + h_2 * i) % array_size);
			//std::cout << "h1 =" << h_1 << std::endl;
			//std::cout << "binNum =" << binNum << std::endl;

			if (occupied[binNum] != OCCUPIED)
			{
				
				array[binNum] = obj;
				occupied[binNum] = OCCUPIED;
				count++; 
				return; 

			}
		}
	}
}


//Insert the argument into the hash table in the appropriate bin as determined by the two aforementioned hash functions and the rules of double hashing.If the table is full, thrown an overflow exception.If the argument is already in the hash table, do nothing.An object can be placed either into an empty or deleted bin. (成(1) under our assumptions)
template <typename Type>
bool Double_hash_table<Type>::erase(Type const &obj)
{
	if (member(obj))
	{
		for (int i = 0; i < array_size; i++)
		{
			if (array[i] == obj)
			{
				//delete.array[i];
				occupied[i] = DELETED;
				count--;
				return true;
			}
		}
	}

	return false; 
}
//Remove the argument from the hash table if it is in the hash table(returning false if it is not) by setting the corresponding flag of the bin to deleted. (成(1) under our assumptions)
template <typename Type>
void Double_hash_table<Type>::clear()
{
	for (int i = 0; i < array_size; ++i) {
		occupied[i] = EMPTY;


	}
	count = 0; 
}
//Removes all the elements in the hash table. (成(M))

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_hash_table<T> const &hash ) {
	for ( int i = 0; i < hash.capacity(); ++i ) {
		if ( hash.occupied[i] == EMPTY ) {
			out << "- ";
		} else if ( hash.occupied[i] == DELETED ) {
			out << "x ";
		} else {
			out << hash.array[i] << ' ';
		}
	}

	return out;
}

#endif
