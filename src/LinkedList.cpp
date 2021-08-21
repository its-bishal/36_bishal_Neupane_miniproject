#include <iostream>
#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList()
{
    HEAD = nullptr;
    TAIL = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    delete HEAD, TAIL;
}

template <typename T>
bool LinkedList<T>::isEmpty()
{
    return (HEAD == nullptr && TAIL == nullptr);
}

template <typename T>
Node<T> *LinkedList<T>::getHeadPointer()
{
    return HEAD;
}

template <typename T>
void LinkedList<T>::addToHead(T data)
{
    Node<T> *newNode = new Node<T>();
    newNode->data = data;
    newNode->next = HEAD;
    HEAD = newNode;

    if (TAIL == nullptr)
    {
        TAIL = HEAD;
    }
}

template <typename T>
void LinkedList<T>::addToTail(T data)
{
    Node<T> *newNode = new Node<T>();

    if (isEmpty())
    {
        newNode->data = data;
        newNode->next = nullptr;
        TAIL = newNode;
        HEAD = TAIL;
    }
    else
    {
        newNode->data = data;
        newNode->next = nullptr;
        TAIL->next = newNode;
        TAIL = newNode;
    }
}

template <typename T>
void LinkedList<T>::add(T data, Node<T> *predecessor)
{
    Node<T> *newNode = new Node<T>();
    newNode->data = data;
    newNode->next = predecessor->next;
    predecessor->next = newNode;
}

template <typename T>
T LinkedList<T>::removeFromHead()
{
    if (isEmpty())
    {
        throw "Empty list";
    }

    Node<T> *nodeToDelete = HEAD;
    HEAD = nodeToDelete->next;
    T removedData = nodeToDelete->data;
    delete nodeToDelete;

    if (isEmpty())
    {
        TAIL = nullptr;
    }

    return removedData;
}

template <typename T>
T LinkedList<T>::removeFromTail()
{
    if (isEmpty())
    {
        throw "Empty list";
    }

    Node<T> *nodeToDelete = TAIL;
    T removedData = nodeToDelete->data;

    if (HEAD == nullptr)
    {
        HEAD = TAIL = nullptr;
    }
    else
    {
        Node<T> *_predecessor = HEAD;
        while (_predecessor->next != TAIL)
        {
            _predecessor = _predecessor->next;
        }
        TAIL = _predecessor;
        _predecessor->next = nullptr;
        delete nodeToDelete;
    }

    return removedData;
}

template <typename T>
void LinkedList<T>::remove(T data)
{
    if (isEmpty())
    {
        throw "Empty list";
    }

    if (HEAD->data == data)
    {
        removeFromHead();
    }

    else
    {
        Node<T> *temp = HEAD->next;
        Node<T> *prev = HEAD;

        while (temp != nullptr)
        {
            if (temp->data == data)
            {
                break;
            }

            else
            {
                prev = prev->next;
                temp = temp->next;
            }
        }

        if (temp != NULL)
        {
            prev->next = temp->next;
            delete temp;
        }
    }
}

template <typename T>
bool LinkedList<T>::search(T data)
{
    if (isEmpty())
    {
        return false;
    }

    Node<T> *temp = HEAD;
    while (temp != nullptr)
    {
        if (temp->data == data)
        {
            return true;
        }

        temp = temp->next;
    }

    return false;
}

template <typename T>
Node<T> *LinkedList<T>::retrieve(T data)
{
    if (isEmpty())
    {
        throw "Empty list";
    }

    if (HEAD->data == data)
    {
        return HEAD;
    }

    Node<T> *node = HEAD->next;
    while (node != nullptr)
    {
        if (node->data == data)
        {
            return node;
        }
        node = node->next;
    }

    return nullptr;
}

template <typename T>
void LinkedList<T>::traverse(char delimiter)
{
    if (isEmpty())
    {
        throw "Empty list";
    }

    Node<T> *node = HEAD;
    while (node != nullptr)
    {
        std::cout << node->data << delimiter;
        node = node->next;
    }

    std::cout << std::endl;
}

template <typename T>
T LinkedList<T>::getFirstElement()
{
    if (isEmpty())
    {
        throw "Empty list";
    }

    return HEAD->data;
}

template <typename T>
T LinkedList<T>::getLastElement()
{
    if (isEmpty())
    {
        throw "Empty list";
    }

    return TAIL->data;
}
