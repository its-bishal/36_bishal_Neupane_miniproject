#include <iostream>

#include "Matrix.h"

template <typename T>
Matrix<T>::Matrix(bool _isDirected) : verticesNum(0), edgesNum(0), _isDirected(_isDirected)
{
    std::cout << (this->_isDirected ? "Directed" : "Undirected") << " Matrix is created." << std::endl;
    if (_isDirected)
    {
        edgeArrow = "   ";
        openBracket = "< ";
        closeBracket = " >";
    }
    else
    {
        edgeArrow = "   ";
        openBracket = "{ ";
        closeBracket = " }";
    }
}

template <typename T>
bool Matrix<T>::isEmpty()
{
    return adjList.empty();
}

template <typename T>
bool Matrix<T>::isDirected()
{
    return _isDirected;
}

template <typename T>
void Matrix<T>::addVertex(T newVertex)
{
    std::cout << "Adding a new vertex : " << newVertex
              << std::endl;

    bool vertexExists = false;
    for (auto rowPointer : adjList)
    {
        T mainVertex = rowPointer->getFirstElement();
        if (mainVertex == newVertex)
            vertexExists = true;
    }

    if (vertexExists)
    {
        std::cout << "The vertex " << newVertex << " already exists.\n"
                  << std::endl;
    }
    else
    {
        LinkedList<T> *list = new LinkedList<T>();
        list->addToTail(newVertex);
        adjList.emplace_back(list);
        this->verticesNum++;

        std::cout << "Vertex " << newVertex << " is added.\n"
                  << std::endl;
    }
}

template <typename T>
void Matrix<T>::removeVertex(T vertexToRemove)
{
    std::cout << "Removing a vertex " << vertexToRemove
              << std::endl;

    if (!isEmpty())
    {
        bool vertexExists = false;
        for (auto rowPointer : adjList)
        {
            T mainVertex = rowPointer->getFirstElement();
            if (mainVertex == vertexToRemove)
                vertexExists = true;
        }

        if (!vertexExists)
        {
            std::cout << "The vertex " << vertexToRemove << " does not exist.\n"
                      << std::endl;
        }
        else
        {
            int neighboursCount = 0;
            typename std::vector<LinkedList<T> *>::iterator rowPointer;
            for (rowPointer = adjList.begin(); rowPointer != adjList.end(); rowPointer++)
            {
                T mainVertex = (*rowPointer)->getFirstElement();

                if (mainVertex == vertexToRemove)
                {
                    Node<T> *node = (*rowPointer)->getHeadPointer()->next;
                    while (node != NULL)
                    {
                        neighboursCount++;
                        node = node->next;
                    }

                    adjList.erase(rowPointer);
                    verticesNum--;
                }
            }

            for (auto rowPointer : adjList)
            {
                Node<T> *node = rowPointer->getHeadPointer()->next;
                while (node != NULL)
                {
                    if (vertexToRemove == node->data)
                    {
                        rowPointer->remove(vertexToRemove);
                        break;
                    }
                    node = node->next;
                }
            }

            if (isDirected())
                edgesNum = neighboursCount;
            else
                edgesNum = neighboursCount / 2 + 1;

            std::cout
                << std::endl;
        }
    }
    else
    {
        std::cout << "The Matrix is empty." << std::endl;
    }
}

template <typename T>
void Matrix<T>::getVerticesNum()
{
    std::cout << "Number of vertices : " << verticesNum << "\n"
              << std::endl;
}

template <typename T>
void Matrix<T>::display()
{
    if (isEmpty())
    {
        std::cout << "Matrix is empty." << std::endl;
    }
    else
    {
        std::cout << "The matrix in adjacency list representation is: " << std::endl;
        for (auto rowPointer : adjList)
        {
            std::cout << rowPointer->getFirstElement();
            Node<T> *node = rowPointer->getHeadPointer()->next;
            if (node != NULL)
            {
                std::cout << edgeArrow;
            }

            while (node != NULL)
            {
                std::cout << node->data;
                node = node->next;
                if (node != NULL)
                {
                    std::cout << edgeArrow;
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

template <typename T>
void Matrix<T>::addEdge(T vertex1, T vertex2)
{
    std::cout << "Adding edge " << openBracket << vertex1 << ", " << vertex2 << closeBracket << "." << std::endl;
    bool vertex1Exists = false;
    bool vertex2Exists = false;
    for (auto rowPointer : adjList)
    {
        T mainVertex = rowPointer->getFirstElement();
        if (mainVertex == vertex1)
            vertex1Exists = true;
        if (mainVertex == vertex2)
            vertex2Exists = true;
    }

    if (vertex1Exists && vertex2Exists)
    {
        for (auto rowPointer : adjList)
        {
            T mainVertex = rowPointer->getFirstElement();
            if (mainVertex == vertex1)
                if (!(rowPointer->search(vertex2)))
                {
                    rowPointer->addToTail(vertex2);
                    edgesNum++;
                }

            if (!isDirected())
                if (!(rowPointer->search(vertex1)))
                    if (mainVertex == vertex2)
                        rowPointer->addToTail(vertex1);
        }
        std::cout << "Edge " << openBracket << vertex1 << ", " << vertex2 << closeBracket
                  << " added.\n"
                  << std::endl;
    }
    else
    {
        if (!vertex1Exists)
        {
            std::cout << "Vertex " << vertex1 << " does not exist.\n"
                      << std::endl;
        }
        else if (!vertex2Exists)
        {
            std::cout << "Vertex " << vertex2 << " does not exist.\n"
                      << std::endl;
        }
    }
}

template <typename T>
bool Matrix<T>::removeVertexFromEdge(T vertex1, T vertex2)
{
    bool hasEdgeWith = false;
    typename std::vector<LinkedList<T> *>::iterator rowPointer;
    for (rowPointer = adjList.begin(); rowPointer != adjList.end(); rowPointer++)
    {
        T mainVertex = (*rowPointer)->getFirstElement();

        if (mainVertex == vertex1)
        {
            Node<T> *node = (*rowPointer)->getHeadPointer()->next;
            while (node != NULL)
            {
                if (vertex2 == node->data)
                {
                    hasEdgeWith = true;
                    (*rowPointer)->remove(vertex2);
                    break;
                }

                node = node->next;
            }
        }
    }

    return hasEdgeWith;
}

template <typename T>
void Matrix<T>::removeEdge(T vertex1, T vertex2)
{
    if (isEmpty())
    {
        std::cout << "The matrix is empty." << std::endl;
    }
    else
    {
        std::cout << "Removing edge " << openBracket << vertex1 << ", " << vertex2 << closeBracket << "." << std::endl;

        bool vertex1Exists = false;
        bool vertex2Exists = false;
        for (auto rowPointer : adjList)
        {
            T mainVertex = rowPointer->getFirstElement();
            if (mainVertex == vertex1)
                vertex1Exists = true;
            if (mainVertex == vertex2)
                vertex2Exists = true;
        }

        if (vertex1Exists && vertex2Exists)
        {
            bool removeEdgeOf12 = removeVertexFromEdge(vertex1, vertex2);
            bool removeEdgeOf21 = false;

            if (!isDirected())
            {
                removeEdgeOf21 = removeVertexFromEdge(vertex2, vertex1);
            }

            if (removeEdgeOf12 || removeEdgeOf21)
            {
                edgesNum--;

                std::cout << "Edge " << openBracket << vertex1 << ", " << vertex2 << closeBracket << " removed." << std::endl;
            }

            else
            {
                std::cout << "Edge " << openBracket << vertex1 << ", " << vertex2 << closeBracket << " does not exist." << std::endl;
            }

            std::cout << std::endl;
        }
        else
        {
            if (!vertex1Exists)
            {
                std::cout << "Vertex " << vertex1 << " does not exist.\n"
                          << std::endl;
            }
            else if (!vertex2Exists)
            {
                std::cout << "Vertex " << vertex2 << " does not exist.\n"
                          << std::endl;
            }
        }
    }
}

template <typename T>
void Matrix<T>::getEdgesNum()
{
    std::cout << "Number of edges : " << edgesNum << "\n"
              << std::endl;
}

template <typename T>
int Matrix<T>::getInDegreeOf(T vertex)
{
    std::cout << "Finding in-degree of vertex " << vertex << std::endl;

    if (!isEmpty())
    {
        bool vertexExists = false;
        for (auto rowPointer : adjList)
        {
            T mainVertex = rowPointer->getFirstElement();
            if (mainVertex == vertex)
                vertexExists = true;
        }

        if (vertexExists)
        {
            if (isDirected())
            {
                int inDegree = 0;
                for (auto rowPointer : adjList)
                {
                    Node<T> *node = rowPointer->getHeadPointer()->next;

                    while (node != NULL)
                    {
                        if (node->data == vertex) //check if the vertex, vertex is a neighbour of another vertex
                        {
                            inDegree++;
                        }
                        node = node->next;
                    }
                }
                std::cout << "The in-degree of the vertex  " << vertex << " is : " << inDegree << "\n"
                          << std::endl;

                return inDegree;
            }

            else
            {
                std::cout << "The Matrix is undirected.\n"
                          << std::endl;

                return -1;
            }
        }
        else
        {
            std::cout << "Vertex " << vertex << " does not exist.\n"
                      << std::endl;
            return -1;
        }
    }
    else
    {
        std::cout << "The Matrix is empty." << std::endl;
        return -1;
    }
}

template <typename T>
int Matrix<T>::getOutDegreeOf(T vertex)
{
    std::cout << "Finding out-degree of vertex " << vertex << std::endl;

    if (!isEmpty())
    {

        bool vertexExists = false;
        for (auto rowPointer : adjList)
        {
            T mainVertex = rowPointer->getFirstElement();
            if (mainVertex == vertex)
                vertexExists = true;
        }

        if (vertexExists)
        {
            if (isDirected())
            {
                int outDegree = 0;
                for (auto rowPointer : adjList)
                {
                    T mainVertex = rowPointer->getFirstElement();

                    if (mainVertex = vertex)
                    {
                        Node<T> *node = rowPointer->getHeadPointer()->next;
                        while (node != NULL)
                        {
                            outDegree++;
                            node = node->next;
                        }
                        break;
                    }
                }
                std::cout << "The out-degree of the vertex  " << vertex << " is : " << outDegree << "\n"
                          << std::endl;
                return outDegree;
            }

            else
            {
                std::cout << "The Matrix is undirected.\n"
                          << std::endl;

                return -1;
            }
        }
        else
        {
            std::cout << "Vertex " << vertex << " does not exist.\n"
                      << std::endl;
            return -1;
        }
    }
    else
    {
        std::cout << "The Matrix is empty." << std::endl;
        return -1;
    }
}

template <typename T>
void Matrix<T>::getDegreeOf(T vertex)
{
    std::cout << "Finding degree of vertex " << vertex << std::endl;

    if (!isEmpty())
    {

        bool vertexExists = false;
        for (auto rowPointer : adjList)
        {
            T mainVertex = rowPointer->getFirstElement();
            if (mainVertex == vertex)
                vertexExists = true;
        }

        if (vertexExists)
        {
            if (isDirected())
            {
                std::cout << "________________________" << std::endl;
                int degree = getInDegreeOf(vertex) + getOutDegreeOf(vertex);
                std::cout << "The degree of the vertex " << vertex << " is " << degree
                          << std::endl;
                std::cout << "_________________________\n"
                          << std::endl;
            }

            else
            {
                int degree = 0;
                for (auto rowPointer : adjList)
                {
                    T mainVertex = rowPointer->getFirstElement();

                    if (mainVertex = vertex)
                    {
                        Node<T> *node = rowPointer->getHeadPointer()->next;
                        while (node != NULL)
                        {
                            degree++;
                            node = node->next;
                        }
                        break;
                    }
                }
                std::cout << "The degree of the vertex " << vertex << " is " << degree << std::endl;
                std::cout
                    << std::endl;
            }
        }
        else
        {
            std::cout << "Vertex " << vertex << " does not exist.\n"
                      << std::endl;
        }
    }
    else
    {
        std::cout << "The row is empty." << std::endl;
    }
}

template <typename T>
void Matrix<T>::getNeighboursOf(T vertex)
{
    std::cout << "vertex in the rows are : " << vertex << "." << std::endl;

    if (!isEmpty())
    {
        bool vertexExists = false;
        for (auto rowPointer : adjList)
        {
            T mainVertex = rowPointer->getFirstElement();
            if (mainVertex == vertex)
                vertexExists = true;
        }

        if (vertexExists)
        {
            for (auto rowPointer : adjList)
            {
                T mainVertex = rowPointer->getFirstElement();
                if (mainVertex == vertex)
                {
                    Node<T> *node = rowPointer->getHeadPointer()->next;

                    if (node == NULL)
                    {
                        std::cout << "Vertex " << vertex << " has no row members. " << std::endl;
                    }
                    else
                    {
                        std::cout << "Rows of the vertex " << vertex << " are :" << std::endl;
                        while (node != NULL)
                        {
                            std::cout << node->data << " ";
                            node = node->next;
                        }
                        std::cout << "\n"
                                  << std::endl;
                    }
                    break;
                }
            }
        }
        else
        {
            std::cout << "Vertex " << vertex << " doesn't exist.\n"
                      << std::endl;
        }
    }
    else
    {
        std::cout << "The row is empty." << std::endl;
    }
}
