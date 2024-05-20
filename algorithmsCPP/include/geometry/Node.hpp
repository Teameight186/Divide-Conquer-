#pragma once

class Node{
protected:
    Node* m_next;
    Node* m_prev;
public:
    Node();
    virtual ~Node();
    Node* next();
    Node* prev();
    Node* insert(Node*);
    Node* remove();
    void splice(Node*);
};