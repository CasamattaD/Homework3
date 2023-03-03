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

    node* addPerson(node* root, Person per); // Recursive help for Add
    node* Add(Person per); // Find place to insert Person

    node* deleteNode(string lastName); // Delete Person from BST
    
    node* Find(node* root, string str); // Recusrive help for findPerson
    void findPerson(string str); // Find person in BST

    void changeNumber(string lastName, string number); // Change Persons phone number

    vector<node*> getOrder(node* root, vector<node*> book); // Alphabetize BST
    void displayPhoneBook(); // Organize the contents of the binary search tree in order in a vector

    void saveBST(ofstream &outFile, node* root); // Write BST to outFile
    void saveFile(ofstream& outFile); // save outFile

private:
    vector<node*> book;
    node* root;
};
