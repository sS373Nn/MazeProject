#pragma once
#pragma once

class Node {
public:
    Node();
    Node(int val);
    Node* FindRoot();
    void Insert(Node* add);

private:
    int value;
    int group;
    bool right;
    bool down;
    bool route;
    Node* parent;
    Node* leftC;
    Node* rightC;
    friend class Maze;
    friend class NodeMatrix;
};

Node::Node() {
    value = 0;
    group = 0;
    right = false;
    down = false;
    route = false;
    parent = nullptr;
    leftC = nullptr;
    rightC = nullptr;
}

Node::Node(int val) {
    value = val;
    group = val;
    right = false;
    down = false;
    route = false;
    parent = nullptr;
    leftC = nullptr;
    rightC = nullptr;
}

Node* Node::FindRoot() {
    Node* temp;
    temp = this;
    while (temp->parent != nullptr) {
        temp = temp->parent;
    }

    return temp;
}

void Node::Insert(Node* add) {
    //could make more complex to find parent of add first***
    if (this->value < add->value) { //insert to the right
        if (this->rightC == nullptr) {
            this->rightC = add;
            add->parent = this;
            return;
        }
        else {
            Node* temp;
            temp = this->rightC;
            temp->Insert(add);
        }
    }
    else { //insert to the left
        if (this->leftC == nullptr) {
            this->leftC = add;
            add->parent = this;
            return;
        }
        else {
            Node* temp;
            temp = this->leftC;
            temp->Insert(add);
        }
    }
}