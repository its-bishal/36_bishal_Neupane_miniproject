#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include "LinkedList.h"
template <typename T>
class Matrix
{
private:
    std::vector<LinkedList<T> *> adjList;
    int verticesNum, edgesNum;
    bool _isDirected; //0 for undirected, 1 for directed
    std::string edgeArrow, openBracket, closeBracket;

public:
    Matrix(bool _isDirected);
    bool isEmpty();
    bool isDirected();
    void addVertex(T newVertex);
    void addEdge(T vertex1, T vertex2);
    void removeVertex(T vertexToRemove);
    bool removeVertexFromEdge(T vertex1, T vertex2);
    void removeEdge(T vertex1, T vertex2);
    void getVerticesNum();
    void getEdgesNum();
    int getInDegreeOf(T vertex);
    int getOutDegreeOf(T vertex);
    void getDegreeOf(T vertex);
    void getNeighboursOf(T vertex);
    //void areNeighbours(T vertex1, T vertex2);
    void display();
};

#include "../src/Matrix.cpp"

#endif