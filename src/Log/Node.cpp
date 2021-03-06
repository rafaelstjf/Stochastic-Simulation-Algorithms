#include "Node.hpp"

Node::Node()
{
}
Node::~Node()
{
    dict.clear();
}

void Node::setNext(Node *next)
{
    this->next = next;
}
void Node::setPrevious(Node *previous)
{
    this->previous = previous;
}
void Node::setTime(long double time)
{
    this->time = time;
}
Node *Node::getNext()
{
    return next;
}
Node *Node::getPrevious()
{
    return previous;
}
long double Node::getTime()
{
    return time;
}
map<int, double> Node::getDict()
{
    return dict;
}
double Node::getValIndex(int index)
{
    map<int, double>::iterator it = dict.find(index);
    if (it == dict.end())
        return -1 * INT_MAX;
    else
        return it->second;
}
bool Node::checkExists(int index)
{
    if(dict.find(index) != dict.end())
        return true;
    else
        return false;
}
double Node::getValIndexFather(int index)
{
    //checks if there is an element in the desirable index then returns it
    //if there isn't an element then check on the previous node
    Node* it = previous;
    if(checkExists(index))
        return getValIndex(index);
    else
    {
        while(it!= nullptr && !it->checkExists(index))
        {
            it = it->getPrevious();
        }
        if(it!= nullptr)
            return it->getValIndex(index);
    }
    return -1;
}
void Node::insertSpecie(int index, double value, double* array)
{
    Node *it = previous;
    if(previous==nullptr)
    {
        dict.insert(pair<int, double>(index, value));
        array[index] = value;
    }
    else
    {
        if(array[index] != value)
        {
            dict.insert(pair<int, double>(index, value));
            array[index] = value;
        }

    }
}
