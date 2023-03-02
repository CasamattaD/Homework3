#include <string>
#include <vector>
#include "Person.h"

using namespace std;

class node { // Set up node class as well as node constructor
public:
    Person person;
    node* left;
    node* right;
    node(Person p) : person(p), left(nullptr), right(nullptr) {}
};

class Book { // Book class to hold functions for Binary Search Tree
public:
    Book(); // Constructor and Destructor for Book
    ~Book();

    node* addPerson(node* root, Person per);
    node* Add(Person per); // Find place to insert node

    node* Delete(string str); // Delete Person

    node* Find(node* root, string str); // Return Node *, if no value, return NULL *
    void findPerson(string str);
    string getValue(node* root);

    // node* changePerson(node* root, string str);

    vector<node*> getOrder(node* root, vector<node*> book);
    void displayPhoneBook(); // Organize the contents of the binary search tree in order in a vector

private:
    vector<node*> book;
    node* root;
};
