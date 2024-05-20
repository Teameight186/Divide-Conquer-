#include "Node.hpp"

Node::Node(): m_next{this}, m_prev{this}
{
}

Node::~Node()
{
}

Node* Node::next()
{
    return m_next;
}

Node* Node::prev()
{
    return m_prev;
}

Node* Node::insert(Node* b)
{
    Node* c = m_next;
    b->m_next = c; 
    b->m_prev = this;
    m_next = b;
    c->m_prev = b;
    return b;
}

Node* Node::remove()
{
    m_prev->m_next = m_next;
    m_next->m_prev = m_prev;
    m_next = m_prev = this; 
    return this;
}

void Node::splice(Node* b)
{
    Node* a = this;
    Node* an = a->m_next;
    Node* bn = b->m_next;
    a->m_next = bn;
    b->m_next = an;
    an->m_prev = b;
    bn->m_prev = a;
}
