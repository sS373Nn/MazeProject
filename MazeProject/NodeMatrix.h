#pragma once
#pragma once
#include <iostream>
#include <iomanip>
#include "Node.h"

class NodeMatrix {
public:
    NodeMatrix(int s);
    ~NodeMatrix();
    void Print();

private:
    unsigned int size;
    Node** matrix;
    friend class Maze;

};

NodeMatrix::NodeMatrix(int s) {
    size = s;
    int count = 0;
    matrix = new Node * [size];
    for (unsigned int i = 0; i < size; i++) {
        matrix[i] = new Node[size];
        for (unsigned int j = 0; j < size; j++) {
            matrix[i][j].value = count;
            matrix[i][j].group = 3;
            matrix[i][j].right = false;
            matrix[i][j].down = false;
            matrix[i][j].route = false;
            matrix[i][j].parent = nullptr;
            matrix[i][j].leftC = nullptr;
            matrix[i][j].rightC = nullptr;
            count++;
        }
    }
}

void NodeMatrix::Print() {
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            std::cout << std::setw(3) << matrix[i][j].value << " ";
        }
        std::cout << std::endl;
    }
}

NodeMatrix::~NodeMatrix() {
    for (unsigned int i = 0; i < size; i++) {
        delete matrix[i];
    }
    delete[] matrix;
}