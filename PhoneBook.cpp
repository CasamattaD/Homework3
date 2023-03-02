#include <iostream>
#include <vector>
#include <string>
#include "PhoneBook.h"
#include <queue>

using namespace std;

Book::Book()
{
    root = nullptr;
}

Book::~Book()
{

}

// Used as a crutch for Add function.
node* Book::addPerson(node* root, Person per) {
    if (root == NULL) {
        root = new node(per);
        root->right = nullptr;
        root->left = nullptr;
        return root;
    }

    // Recursively call itself based on the value compared to root it is at
    if (per.getLastName() < root->person.getLastName()) {
        root->left = addPerson(root->left, per);
    }
    else {
        root->right = addPerson(root->right, per);
    }

    return root;
}

// Insert a string passed through into the Binary Search Book
node* Book::Add(Person per)
{
    if (root == NULL) {
        root = new node(per);
        root->right = nullptr;
        root->left = nullptr;
        return root;
    }

    return addPerson(root, per); // Recursively add value
}

/* Given a non-empty binary search tree,
return the node with minimum key value
found in that tree. Note that the entire
tree does not need to be searched. */
node* minValueNode(node* Node)
{
    node* current = Node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}


node* Book::Delete(node* root, Person person)
{
    if (root == nullptr) return root;

    if (person.getLastName() < root->person.getLastName())
        Delete(root->left, person);

    else if (person.getLastName() > root->person.getLastName())
        Delete(root->right, person);

    else
    {
        // node with only one child or no child
        if (root->left == nullptr)
        {
            node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            node* temp = root->left;
            delete root;
            return temp;
        }

        node* temp = minValueNode(root->right);

        root->person = temp->person;

        // Delete the inorder successor
        Delete(root->right, temp->person);
    }
    return root;
}

void Book::deletePerson(string p) {
    /*
    node* per = Find(root, lastName);
    Person person = per->person;
    Delete(root, person);
    */
    //Locate the element
    bool found = false;

    node* curr;
    node* parent;
    curr = root;
    parent = curr;
    while (curr != NULL)
    {
        if (curr->person.getLastName() == p)
        {
            found = true;
            break;
        }
        else
        {
            parent = curr;
            if (p > curr->person.getLastName()) curr = curr->right;
            else curr = curr->left;
        }
    }
    if (!found)
    {
        cout << " Data not found! " << endl;
        return;
    }
    // 3 cases :
// 1. We're removing a leaf node
// 2. We're removing a node with a single child
// 3. we're removing a node with 2 children
// Node with single child
    if ((curr->left == NULL && curr->right != NULL) || (curr->left != NULL
        && curr->right == NULL))
    {
        if (curr->left == NULL && curr->right != NULL)
        {
            if (parent->left == curr)
            {
                parent->left = curr->right;
                delete curr;
            }
            else
            {
                parent->right = curr->right;
                delete curr;
            }
        }
        else // left child present, no right child
        {
            if (parent->left == curr)
            {
                parent->left = curr->left;
                delete curr;
            }
            else
            {
                parent->right = curr->left;
                delete curr;
            }
        }
        return;
    }
    //We're looking at a leaf node
    if (curr->left == NULL && curr->right == NULL)
    {
        if (parent->left == curr) parent->left = NULL;
        else parent->right = NULL;
        delete curr;
        return;
    }
    //Node with 2 children
    // replace node with smallest value in right subtree
    if (curr->left != NULL && curr->right != NULL)
    {
        node* chkr;
        chkr = curr->right;
        if ((chkr->left == NULL) && (chkr->right == NULL))
        {
            curr = chkr;
            delete chkr;
            curr->right = NULL;
        }
        else // right child has children
        {
            //if the node's right child has a left child
            // Move all the way down left to locate smallest element
            if ((curr->right)->left != NULL)
            {
                node* lcurr;
                node* lcurrp;
                lcurrp = curr->right;
                lcurr = (curr->right)->left;
                while (lcurr->left != NULL)
                {
                    lcurrp = lcurr;
                    lcurr = lcurr->left;
                }
                curr->person = lcurr->person;
                delete lcurr;
                lcurrp->left = NULL;
            }
            else
            {
                node* tmp;
                tmp = curr->right;
                curr->person = tmp->person;
                curr->right = tmp->right;
                delete tmp;
            }
        }
        return;
    }
}

// Recursively searches the search tree for a specific element
node* Book::Find(node* root, string str)
{
    if (root == nullptr)
    {
        cout << "Person could not be found" << endl;
        return nullptr;
    }

    if (str == root->person.getLastName())
    {
        cout << root->person.getFirstName() + " " + root->person.getLastName() + "-" + root->person.getPhoneName() << endl;
        return root;
    }

    // Moves to the right in the search tree if search item is greater than the root value
    if (root->person.getLastName() < str)
    {
        return Find(root->right, str);
    }

    return Find(root->left, str); // Recursively calls itself to search to the left
}

// Searches through the binary search tree for the value specified
void Book::findPerson(string str)
{
    if (root == NULL)
    {
        cout << "Person could not be found" << endl;
    }

    if (str == root->person.getLastName())
    {
        cout << root->person.getFirstName() + " " + root->person.getLastName() + "-" + root->person.getPhoneName() << endl;
        return;
    }
    if (root->person.getLastName() < str)
    {
        Find(root, str); // Recursively calls itself to search to the right of the current node 
    }
    Find(root, str); // Recursively calls itself to search to the left of the current node

}

void Book::changeNumber(string lastName, string number)
{
    node* per = Find(root, lastName);
    per->person.changePhoneNumber(number);
    cout << per->person.getFirstName() + " " + per->person.getLastName() + "'s number has been changed to " + per->person.getPhoneName() << endl;
}

// Put elements in the binary search tree in order into a vector
vector<node*> Book::getOrder(node* root, vector<node*> book) {
    if (root == NULL)
    {
        return book;
    }

    // recursively find order using self function
    getOrder(root->left, book);
    book.push_back(root);
    cout << root->person.getFirstName() + "\t" + root->person.getLastName() + "\t" + root->person.getPhoneName() << endl;
    getOrder(root->right, book);

    return book;
}

// Get all the elements from the search tree in order and put into a vector
void Book::displayPhoneBook() {

    if (root == NULL)
    {
        cout << "Phonebook is empty" << endl;
    }

    cout << "First \t Last \t Number" << endl;
    // recursive function to aide process
    getOrder(root, book);

}

void deleteDeepestNode(node* root, node* deleting_node) {
    queue<node*> nodes;
    nodes.push(root);
    node* temp;
    while (!nodes.empty()) {
        temp = nodes.front();
        nodes.pop();
        if (temp == deleting_node) {
            temp = NULL;
            delete (deleting_node);
            return;
        }
        if (temp->right) {
            if (temp->right == deleting_node) {
                temp->right = NULL;
                delete deleting_node;
                return;
            }
            else {
                nodes.push(temp->right);
            }
        }
        if (temp->left) {
            if (temp->left == deleting_node) {
                temp->left = NULL;
                delete deleting_node;
                return;
            }
            else {
                nodes.push(temp->left);
            }
        }
    }
}

node* Book::deleteNode(string lastName) {
    node* per = Find(root, lastName);
    if (root == NULL) {
        return NULL;
    }
    if (root->left == NULL && root->right == NULL) {
        if (root->person.getLastName() == lastName) {
            return NULL;
        }
        else {
            return root;
        }
    }
    queue<node*> nodes;
    nodes.push(root);
    node* temp = nodes.front();
    node* key_node = NULL;
    while (!nodes.empty()) {
        temp = nodes.front();
        nodes.pop();
        if (temp->person.getLastName() == lastName) {
            key_node = temp;
        }
        if (temp->left) {
            nodes.push(temp->left);
        }
        if (temp->right) {
            nodes.push(temp->right);
        }
    }
    if (key_node != NULL) {
        Person deepest_node_data = temp->person;
        deleteDeepestNode(root, temp);
        key_node->person = deepest_node_data;
    }
    return root;
}