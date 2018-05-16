#include "../include/List.hpp"

List::List(int c)
{
    capacity = c;
    arr = new HeapNode*[capacity];
    inUse = 0;
}
List::~List()
{
    delete [] arr;
}

HeapNode* List::getMin()
{
    return arr[0];
}
void List::update(int index, double time)
{
    int i = 0;
    for(i = 0; i < inUse; i++)
    {
        if(arr[i]->getIndex()==index)
            break;
    }
    if(i < inUse)
        arr[i]->setTime(time);
    sort();
}
void List::insertKey(int index, double time)
{
    if(inUse < capacity)
    {
        inUse++;
        arr[inUse-1] = new HeapNode(index, time);
        sort();
    }
}
void List::swap(int i, int j)
{
    int index = arr[i]->getIndex();
    double time = arr[i]->getTime();
    arr[i]->setIndex( arr[j]->getIndex());
    arr[i]->setTime(arr[j]->getTime());
    arr[j]->setIndex(index);
    arr[j]->setTime(time);
}
void List::sort()
{
    int i, j, minIndex;
    for(i = 0; i < inUse-1; i++)
    {
        minIndex = i;
        for(j = i+1; j < inUse; j++)
        {
            if(arr[j]->getTime() < arr[minIndex]->getTime())
                minIndex = j;
        }
        swap(minIndex, i);
    }
}
void List::print()
{
    for(int i = 0; i < inUse; i++)
    {
        cout << arr[i]->getIndex() << " : " << arr[i]->getTime() << endl;
    }
}

HeapNode* List::getNode(int index)
{
    for(int i =0; i < inUse; i++)
    {
        if(arr[i]->getIndex() == index)
            return arr[i];
    }
    return nullptr;
}