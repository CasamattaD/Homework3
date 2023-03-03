#include <iostream>
#include <fstream>
#include <iomanip>
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

// Recursively used for Add
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

// Insert a Person passed into the Binary Search Phone Book
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

// Recursively searches the search tree for a specific Person
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

// Searches through the binary search tree for Person
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
        Find(root, str); // Recursive function to search to the right of the current node 
    }
    Find(root, str); // Recursive function to search to the left of the current node

}

// Change persons phone number
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

// Deletes the deepest node in the BST
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

// Deletes a node from the BST
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
    queue<node*> nodes; // Put nodes into a queue for easy use
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

// Save the People from BST into the file
void Book::saveBST(ofstream& outFile, node* root) {
    if (root == NULL)
    {
        return;
    }

    // recursively find order using self function
    saveBST(outFile, root->left);
    outFile << setw(15) << root->person.getFirstName() + "\t" << setw(15) << root->person.getLastName() + "\t" << setw(12) << root->person.getPhoneName() + "\n";
    saveBST(outFile, root->right);
    
    return;
}

// Save's the file itself
void Book::saveFile(ofstream& outFile) {
    outFile << setw(15) << "FirstName\t" << setw(15) << "LastName\t" << setw(12) << "PhoneNumber\n";
    saveBST(outFile, root);
}