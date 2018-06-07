#ifndef NEXTREACTIONMETHODCOMPACT_HPP
#define NEXTREACTIONMETHODCOMPACT_HPP
#include <iostream>
#include <climits>
#include "../include/SSA.hpp"
#include "../include/HeapNode.hpp"
#include "../include/IndexedPrioQueue.hpp"
#include "../include/List.hpp"
#include "../include/DependencyGraphNRM.hpp"

#define inf INT_MAX

using namespace std;

class NextReactionMethodCompact : public SSA
{
public:
    virtual void perform(string filename, double simulTime, double beginTime);
    virtual ~NextReactionMethodCompact();

protected:
    virtual void initialization(string filename, double simulTime);
    virtual void calcPropensity();
    virtual void calcPropOne(int index);
    virtual void reacTimeGeneration();
    virtual void reacSelection();
    virtual void reacExecution();
    IndexedPrioQueue* queue; //priority queue used to store the absolute time of each reaction
    double* timePropZero;
    double* propNonZero;
    double* delta;
    HeapNode* selectedNode; //used to store the selected reaction index and time

};
#endif