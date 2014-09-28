/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 *  the provided code.
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "ece250.h"

// include whatever classes you want
class Weighted_graph {
	private:
		static const double INF;
		int Edge_count;
		int Graph_size;
		double **Graph;
		bool Dikstra_initialized;
		bool *Visited;
		double *Distance;
		int *Previous;
		bool *Existing;
		int recurs_counter;



		// your implementation here
		//  you can add both private member variables and private member functions



	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();
		
		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int ) ;
		int location(int, int) ; 

		void insert( int, int, double );
		void initialize();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};
// constructor, creates the graph 

Weighted_graph::Weighted_graph(int m) :
Graph_size(m), Edge_count(0),
Dikstra_initialized(false),
recurs_counter(0),
Graph(new double*[m]),
Visited(new bool[m]),
Existing(new bool[m]),
Distance(new double[m]),
Previous(new int[m]){
	Graph[0] = nullptr;
	int a = m*(m-1) / 2;
	Graph[1] = new double[a];

	for (int i = 2; i < m; ++i) {
		Graph[i] = Graph[i - 1] + i - 1;

	}
	for (int i = 2; i < m; ++i)
	{
		for (int a = 0; a < i; a++)
		{
			Graph[i][a] = INF; 
		}
	}
	//for (int i = 1; i < m; i++)
	//{
	//	Existing[m] = false;//std::cout<<
	//}
	

	//initialize all to inf
}
//destructor 

Weighted_graph::~Weighted_graph()
{

	delete[] Graph[1]; 
//	std::cout << "1";
	delete[] Graph;
	//std::cout << "2";
	
	delete[] Previous;
	//std::cout << "4";
	delete[] Visited;
	//std::cout << "5";
	delete[] Distance;
	//std::cout << "3";
	delete[] Existing;

	// need to destruct the memory as well, but how 
}

//template <typename Type>
/*Weighted_graph<Type>::int location(int m, int n)  // finds the location of the desired weight 
{
	int a = 0;
	for (int i = 1; i < m; i++)
	{
		a = a + i;
	}
	return (a + n + 1); 
}*/



int Weighted_graph::degree(int m) const//Returns the degree of the vertex n
{
	int degree = 0;
	for (int i = 0; i < m; i++)//record all distance from this point  : this.distance + this to all unvisited;
	{
		if (Graph[m][i] != INF )
		{

			degree++;
		}

	}

	for (int i = m + 1; i < Graph_size; i++)//record all distance from other points : this.distance + this to all unvisited;
	{
		if (Graph[i][m] != INF)
		{

			degree++;

		}
	}
	return degree; //throw an illegal argument exception if the argument does not correspond to an Existinging vertex
}



int Weighted_graph::edge_count() const//Returns the number of edges in the graph
{
	return Edge_count;
}

double Weighted_graph::adjacent(int m, int n) const
{
	//Returns the weight of the edge connecting vertices m and n.
	
	if(m == n)//If the vertices are the same, return 0. 
	{
		return 0;
	}	
	if (m > Graph_size || n > Graph_size)//Throw an illegal argument exception if the arguments do not correspond to Existinging vertices.
	{
		throw illegal_argument(); 
	}
	if(m > n)
	{
		return Graph[m][n]; //If the vertices are not adjacent, return infinity.
	}
	if(m < n)
	{
		return Graph[n][m];
	}
	
}


double Weighted_graph::distance(int m, int n)
{

	//std::cout << "enter distance" << Distance[n] << std::endl;

	if (m== n)//If the vertices are the same, return 0. 
	{
		return 0;
	}

	if(!Dikstra_initialized)
	{
		//std::cout << "initializing dikstra" << Distance[n] << std::endl;
		for (int i = 0; i < Graph_size; i++)
		{
			Visited[i] = false;
			Previous[i] = -1;
			Distance[i] = INF;
			

		}
		Distance[m] = 0;
		Dikstra_initialized = true;
	}
	//Return the shortest distance between vertices m and n.
	//Throw an illegal argument exception if the arguments do not correspond to Existinging vertices.
	//The distance between a vertex and itself is 0.0.
	//The distance between vertices that are not connected is infinity.
	//THIS IS DIKSTRA
	if (m > Graph_size || n > Graph_size)//Throw an illegal argument exception if the arguments do not correspond to Existinging vertices.
	{
		throw illegal_argument();
	}

	//bool Visited[] = new bool[Graph_size];
	//double Distance[] = new double[Graph_size];
	//int Previous[] = new int[Graph_size];
	//Distance[m] = 0;
	//std::cout << "enter distance evaluation" << Distance[n] << std::endl;
	Visited[m] = true;

		
		
	for (int i = 0; i < m; i++)//record all distance from this point  : this.distance + this to all unvisited;
	{
		//std::cout << "Graph[m][i] = "<<Graph[m][i] << std::endl;
		//std::cout << "distance[1] = " << Distance[i] << std::endl;
		//std::cout << "Graph[m][i] + Distance[m] = " << Graph[m][i] + Distance[m] << std::endl;

		if (Graph[m][i] != INF &&  Distance[i] > Graph[m][i]+Distance[m])// if two V are adjacent and new value is smaller than Existinging
		{

				Distance[i] = Graph[m][i] + Distance[m];
				Previous[i] = m;
				//std::cout << "enter case 1" << " i = "<< i << Distance[i] << std::endl;
		}

	}
		
	for (int i = m + 1; i < Graph_size; i++)//record all distance from other points : this.distance + this to all unvisited;
	{
		if (Graph[i][m] != INF && Distance[i] > Graph[i][m] + Distance[m])
		{

				Distance[i] = Graph[i][m] + Distance[m];
				Previous[i] = m;
				//std::cout << "enter case 2"<<"m = "<< m << std::endl;

		}
	}
		
	int next;
	int min = 10000;
	bool not_finished = false;

	for (int i = 0; i < Graph_size; i++)
	{
		if (Existing[i] ==true && Visited[i] == false && Distance[i] < min)
		{
			//std::cout << "enter Eval" << Distance[n] << std::endl;
			not_finished = true;
			next = i;
			min = Distance[i];//wanna recursive call 
		}
	}
	if (not_finished)
	{
		
		recurs_counter++; 
		//std::cout << "calling recurs" << recurs_counter<< std::endl;
		distance(next, n);
	}
	//std::cout << "returning" << Distance[n] << std::endl;
	recurs_counter--;
	if (recurs_counter == 0)
	{
		Dikstra_initialized = false;
	}
	
	return Distance[n];// break out somewhere 



		//community 
		//find 
		//if no path 
		//

	
		


	/*
	dikstra
	start with self
	all adjacent V stay unvisited but record distance
	visit the shortest
	this V is now visited
	record all distance : this.distance + this to all unvisited ;
	check if its larger than its current distance, if not, record
	go to the V with shortest distance that is marked an F
	if no unvisited nabour, make it visited and move on
	if all are visited, done
	if unvisited has distance inf, leave as it may
	

	need :
	visited
	vertex
	distance
	previous
	*/



}

void Weighted_graph::insert(int m, int n, double w)
{
	//std::cout << "w > 0" << (w > 0) << std::endl;
	if ((m > Graph_size) || n > Graph_size || (m == n) || !(w > 0))//If the vertices do not Existing or are equal, throw an illegal argument exception.
	{
		throw illegal_argument();

	}
	else
	{
		if (m > n)
		{
			Graph[m][n] = w; 
			Existing[m] = true;
			Existing[n] = true;
		}
		if (m < n)
		{
			Graph[n][m] = w;
			Existing[m] = true;
			Existing[n] = true;
		}
	}//If the weight w > 0, add an edge between vertices m and n. 


}
//template <typename Type>
/*Weighted_graph<Type>::double destroy()
{


}*/

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Your implementation here

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif



