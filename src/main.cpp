#include <iostream>
#include "LinkedList.h"
#include "Matrix.h"

int main()
{
    bool isDirected = true; //set true for directed, false for undirected matrix

    Matrix<int> matrix(isDirected);

    std::cout << (matrix.isEmpty() ? "matrix is empty.\n" : "matrix is not empty.\n") << std::endl;

    matrix.addVertex(1);
    matrix.addVertex(2);
    matrix.addVertex(6);
    matrix.addVertex(0);

    std::cout << (matrix.isEmpty() ? "matrix is empty.\n" : "matrix is not empty.\n") << std::endl;

    matrix.getVerticesNum();

    std::cout << "The vertices are : " << std::endl;
    matrix.display();

    matrix.addEdge(1, 6);
    matrix.addEdge(1, 2);
    matrix.addEdge(1, 0);

    matrix.addEdge(2, 6);
    matrix.addEdge(2, 1);
    matrix.addEdge(2, 0);

    matrix.addEdge(6, 1);
    matrix.addEdge(6, 2);
    matrix.addEdge(6, 0);

    matrix.addEdge(0, 2);
    matrix.addEdge(0, 1);
    matrix.addEdge(0, 6);

    matrix.display();

    matrix.removeVertex(1);

    std::cout << "After removing some vertices :" << std::endl;

    matrix.display();

    matrix.removeEdge(2, 0);
    matrix.removeEdge(6, 2);

    std::cout << "After removing some edges : " << std::endl;
    matrix.display();

    matrix.getNeighboursOf(1);
    matrix.getNeighboursOf(0);
}