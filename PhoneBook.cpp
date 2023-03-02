#include <iostream>
#include <vector>
#include <string>
#include "PhoneBook.h"

using namespace std;

Book::Book()
{
    root = NULL;
}

Book::~Book()
{

}

// Used as a crutch for Add function.
node* Book::addPerson(node* root, Person per) {
    if (root == NULL) {
        root = new node(per);
        root->right = NULL;
        root->left = NULL;
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
        root->right = NULL;
        root->left = NULL;
        return root;
    }

    return addPerson(root, per); // Recursively add value
}

// TODO DELETE PERSON

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
    if (root == nullptr)
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

// Put elements in the binary search tree in order into a vector
vector<node*> Book::getOrder(node* root, vector<node*> book) {
    if (root == NULL)
    {
        return book;
    }

    // recursively find order using self function
    getOrder(root->left, book);
    book.push_back(root);
    cout << root->person.getFirstName() + " " + root->person.getLastName() + " - " + root->person.getPhoneName() << endl;
    getOrder(root->right, book);

    return book;
}

// Get all the elements from the search tree in order and put into a vector
void Book::displayPhoneBook() {

    if (root == NULL)
    {
        cout << "Phonebook is empty" << endl;
    }

    // recursive function to aide process
    getOrder(root, book);

}