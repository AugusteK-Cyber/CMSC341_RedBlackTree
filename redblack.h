#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

struct node
{
    int key;
    node* parent;
    char color;
    node* m_left;
    node* m_right;
};
class RBtree
{
    node* m_root;
    node* temp;
public:
    RBtree()
    {
        temp = nullptr;
        m_root = nullptr;
    }
    void insert(int);
    void insertNode(node*);
    void leftRotation(node*);
    void rightRotation(node*);
    void deleteData(int);
    node* nextNode(node*);
    void deleteNode(node*);
    void dump();
    void dumpList(node*);
    void searchNode(int);
};