
#ifndef GRAPH_H 
#define GRAPH_H 

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stdio.h>
#include <unistd.h>
#include <list>
#include <string>



using namespace std;


template <class T >
class Graph{
    private:
        /* will map an int to a list of its neighbors */
        map <T, vector<T> > vertices;
        void colorGraph(T);
        // void printColor(int index);

    public:
        Graph();
        void addVertex(T vertex);
        void addEdge(T , T);
        void colorGraph(); // greedy algorithm to color graph 
        void findChromatic();

        void print();


};


#endif
#include "Graph.cpp"





