#ifndef DEPENDENCYGRAPH_HPP
#define DEPENDENCYGRAPH_HPP

#include <iostream>
#include "../include/DGVertex.hpp"
using namespace std;
class DependencyGraph
{
  public:
    DependencyGraph();
    DependencyGraph(int numReactions, int **reactants, int **products, int numSpecies);
    virtual int *getDependencies(int id);
    virtual void insertDependency(int id, int val);
    virtual void printGraph();
    virtual void createGraph(int numReactions, int **reactants, int **products, int numSpecies);
    virtual int getDependenciesSize(int id);
    virtual ~DependencyGraph();

  protected:
    int numReactions; //size of the vector
    int numSpecies;
    DGVertex **vertex;
    virtual int *unionSet(int *a, int *b);
    virtual int *intersectionSet(int *a, int *b);
};

#endif // DEPENDENCYGRAPH_H
