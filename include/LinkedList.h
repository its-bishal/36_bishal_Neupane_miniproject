#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

template <typename T>
class Node
{
public:
    T data;
    Node *next;

    Node() : next(nullptr){};
    Node(T data, Node *next) : data(data), next(next) {}
};

template <typename T>
class LinkedList
{
private:
    Node<T> *HEAD;
    Node<T> *TAIL;

public:
    LinkedList();
    ~LinkedList();
    bool isEmpty();
    Node<T> *getHeadPointer();
    void addToHead(T data);
    void addToTail(T data);
    void add(T data, Node<T> *predecessor);
    T removeFromHead();
    T removeFromTail();
    void remove(T data);
    bool search(T data);
    Node<T> *retrieve(T data);
    void traverse(char delimiter = ' ');
    T getFirstElement();
    T getLastElement();
};

#include "../src/LinkedList.cpp"

#endif