// Inspired from https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/data_structures/rb_tree.cpp

#include "redblack.h"

void RBtree::insert(int data)
{
    node* temp1, * temp2;
    node* temp = new node;
    temp->key = data;
    temp->m_left = nullptr;
    temp->m_right = nullptr;
    temp->color = 'r';
    temp1 = m_root;
    temp2 = nullptr;
    if (m_root == nullptr){
        m_root = temp;
        temp->parent = nullptr;
    }
    else
    {
        while (temp1 != nullptr)
        {
            temp2 = temp1;
            if (temp1->key < temp->key)
                temp1 = temp1->m_right;
            else
                temp1 = temp1->m_left;
        }
        temp->parent = temp2;
        if (temp2->key < temp->key)
            temp2->m_right = temp;
        else
            temp2->m_left = temp;
    }
    insertNode(temp);
}
void RBtree::insertNode(node* temp)
{
    node* temp2;
    if (m_root == temp){
        temp->color = 'b';
        return;
    }
    while (temp->parent != nullptr && temp->parent->color == 'r') {
        node* temp1 = temp->parent->parent;
        if (temp1->m_left == temp->parent)
        {
            if (temp1->m_right != nullptr)
            {
                temp2 = temp1->m_right;
                if (temp2->color == 'r'){
                    temp->parent->color = 'b';
                    temp2->color = 'b';
                    temp1->color = 'r';
                    temp = temp1;
                }
            }
            else {
                if (temp->parent->m_right == temp){
                    temp = temp->parent;
                    leftRotation(temp);
                }
                temp->parent->color = 'b';
                temp1->color = 'r';
                rightRotation(temp1);
            }
        }
        else {
            if (temp1->m_left != nullptr) {
                temp2 = temp1->m_left;
                if (temp2->color == 'r') {
                    temp->parent->color = 'b';
                    temp2->color = 'b';
                    temp1->color = 'r';
                    temp = temp1;
                }
            }
            else {
                if (temp->parent->m_left == temp) {
                    temp = temp->parent;
                    rightRotation(temp);
                }
                temp->parent->color = 'b';
                temp1->color = 'r';
                leftRotation(temp1);
            }
        }
        m_root->color = 'b';
    }
}

void RBtree::deleteData(int data)
{
    if (m_root == nullptr) {
        cout << "\nTree is empty.";
        return;
    }
    node* p;
    p = m_root;
    node* y = nullptr;
    node* q = nullptr;
    int found = 0;
    while (p != nullptr && found == 0) {
        if (p->key == data)
            found = 1;
        if (found == 0){
            if (p->key < data)
                p = p->m_right;
            else
                p = p->m_left;
        }
    }
    if (found == 0){
        cout << "\nElement Not Found.";
        return;
    }
    else{
        cout << "\nDeleted Element: " << p->key;
        cout << "\nColour: ";
        if (p->color == 'b')
            cout << "Black\n";
        else
            cout << "Red\n";

        if (p->parent != nullptr)
            cout << "\nParent: " << p->parent->key;
        else
            cout << "\nThere is no parent of the node.  ";
        if (p->m_right != nullptr)
            cout << "\nRight Child: " << p->m_right->key;
        else
            cout << "\nThere is no right child of the node.  ";
        if (p->m_left != nullptr)
            cout << "\nLeft Child: " << p->m_left->key;
        else
            cout << "\nThere is no left child of the node.  ";
        cout << "\nNode Deleted.";
        if (p->m_left == nullptr || p->m_right == nullptr)
            y = p;
        else
            y = nextNode(p);
        if (y->m_left != nullptr)
            q = y->m_left;
        else
        {
            if (y->m_right != nullptr)
                q = y->m_right;
            else
                q = nullptr;
        }
        if (q != nullptr)
            q->parent = y->parent;
        if (y->parent == nullptr)
            m_root = q;
        else
        {
            if (y == y->parent->m_left)
                y->parent->m_left = q;
            else
                y->parent->m_right = q;
        }
        if (y != p)
        {
            p->color = y->color;
            p->key = y->key;
        }
        if (y->color == 'b')
            deleteNode(q);
    }
}

void RBtree::deleteNode(node* p)
{
    node* s;
    while (p != m_root && p->color == 'b')
    {
        if (p->parent->m_left == p)
        {
            s = p->parent->m_right;
            if (s->color == 'r')
            {
                s->color = 'b';
                p->parent->color = 'r';
                leftRotation(p->parent);
                s = p->parent->m_right;
            }
            if (s->m_right->color == 'b' && s->m_left->color == 'b')
            {
                s->color = 'r';
                p = p->parent;
            }
            else {
                if (s->m_right->color == 'b'){
                    s->m_left->color == 'b';
                    s->color = 'r';
                    rightRotation(s);
                    s = p->parent->m_right;
                }
                s->color = p->parent->color;
                p->parent->color = 'b';
                s->m_right->color = 'b';
                leftRotation(p->parent);
                p = m_root;
            }
        }
        else {
            s = p->parent->m_left;
            if (s->color == 'r'){
                s->color = 'b';
                p->parent->color = 'r';
                rightRotation(p->parent);
                s = p->parent->m_left;
            }
            if (s->m_left->color == 'b' && s->m_right->color == 'b'){
                s->color = 'r';
                p = p->parent;
            }
            else {
                if (s->m_left->color == 'b'){
                    s->m_right->color = 'b';
                    s->color = 'r';
                    leftRotation(s);
                    s = p->parent->m_left;
                }
                s->color = p->parent->color;
                p->parent->color = 'b';
                s->m_left->color = 'b';
                rightRotation(p->parent);
                p = m_root;
            }
        }
        p->color = 'b';
        m_root->color = 'b';
    }
}

void RBtree::leftRotation(node* temp)
{
    if (temp->m_right == nullptr)
        return;
    else
    {
        node* y = temp->m_right;
        if (y->m_left != nullptr) {
            temp->m_right = y->m_left;
            y->m_left->parent = temp;
        }
        else
            temp->m_right = nullptr;
        if (temp->parent != nullptr)
            y->parent = temp->parent;
        if (temp->parent == nullptr)
            m_root = y;
        else {
            if (temp == temp->parent->m_left)
                temp->parent->m_left = y;
            else
                temp->parent->m_right = y;
        }
        y->m_left = temp;
        temp->parent = y;
    }
}
void RBtree::rightRotation(node* temp)
{
    if (temp->m_left == nullptr)
        return;
    else
    {
        node* y = temp->m_left;
        if (y->m_right != nullptr) {
            temp->m_left = y->m_right;
            y->m_right->parent = temp;
        }
        else
            temp->m_left = nullptr;
        if (temp->parent != nullptr)
            y->parent = temp->parent;
        if (temp->parent == nullptr)
            m_root = y;
        else {
            if (temp == temp->parent->m_left)
                temp->parent->m_left = y;
            else
                temp->parent->m_right = y;
        }
        y->m_right = temp;
        temp->parent = y;
    }
}

node* RBtree::nextNode(node* temp)
{
    node* y = nullptr;
    if (temp->m_left != nullptr) {
        y = temp->m_left;
        while (y->m_right != nullptr)
            y = y->m_right;
    }
    else {
        y = temp->m_right;
        while (y->m_left != nullptr)
            y = y->m_left;
    }
    return y;
}

void RBtree::dump()
{
    dumpList(m_root);
}
void RBtree::dumpList(node* temp)
{
    if (m_root == nullptr) {
        cout << "\nTree is empty.";
        return;
    }
    if (temp != nullptr)
    {
        cout << "\n\t NODE: ";
        cout << "\n Key: " << temp->key;
        cout << "\n Colour: ";
        if (temp->color == 'b')
            cout << "Black";
        else
            cout << "Red";
        if (temp->parent != nullptr)
            cout << "\n Parent: " << temp->parent->key;
        else
            cout << "\n There is no parent of the node.  ";
        if (temp->m_right != nullptr)
            cout << "\n Right Child: " << temp->m_right->key;
        else
            cout << "\n There is no right child of the node.  ";
        if (temp->m_left != nullptr)
            cout << "\n Left Child: " << temp->m_left->key;
        else
            cout << "\n There is no left child of the node.  ";
        cout << endl;
        if (temp->m_left) {
            cout << "\n\nLeft:\n";
            dumpList(temp->m_left);
        }
        if (temp->m_right) {
            cout << "\n\nRight:\n";
            dumpList(temp->m_right);
        }
    }
}
void RBtree::searchNode(int data)
{
    if (m_root == nullptr) {
        cout << "\nTree is empty\n";
        return;
    }
    node* temp = m_root;
    int found = 0;
    while (temp != nullptr && found == 0) {
        if (temp->key == data)
            found = 1;
        if (found == 0) {
            if (temp->key < data)
                temp = temp->m_right;
            else
                temp = temp->m_left;
        }
    }
    if (found == 0)
        cout << "\nElement Not Found.";
    else {
        cout << "\n\t FOUND NODE: ";
        cout << "\n Key: " << temp->key;
        cout << "\n Colour: ";
        if (temp->color == 'b')
            cout << "Black";
        else
            cout << "Red";
        if (temp->parent != nullptr)
            cout << "\n Parent: " << temp->parent->key;
        else
            cout << "\n There is no parent of the node.  ";
        if (temp->m_right != nullptr)
            cout << "\n Right Child: " << temp->m_right->key;
        else
            cout << "\n There is no right child of the node.  ";
        if (temp->m_left != nullptr)
            cout << "\n Left Child: " << temp->m_left->key;
        else
            cout << "\n There is no left child of the node.  ";
        cout << endl;

    }
}

// Test Red Black Tree
int main()
{
    int ch, y = 0;
    RBtree obj;
    cout << "TESTING INSERTION...\n";
    obj.insert(7);
    obj.insert(17);
    obj.insert(4);
    obj.insert(14);
    obj.insert(16);
    obj.insert(12);   
    obj.dump();

    cout << "\nTESTING DELETION...\n";
    cout << "\nDeleting node 16...\n";
    obj.deleteData(16);
    obj.dump();

    cout << "\n\nTESTING SEARCH...\n";
    cout << "\nSearching node 16...\n";
    obj.searchNode(16);
    obj.dump();
    
    return 1;
}