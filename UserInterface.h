#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Person.h"
#include "PhoneBook.h"

using namespace std;

// Function to convert a string to lowercase
string toLowercase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Class for user interface
class UserInterface {
public:
    void run() {
        cout << "Welcome to the phone book!" << endl;
        loadFromFile();
        char choice;
        do {
            cout << "\nMenu:\n"
                << "1. Add a person\n"
                << "2. Delete a person\n"
                << "3. Find a person\n"
                << "4. Change a person's phone number\n"
                << "5. Display phone book\n"
                << "6. Quit\n"
                << "Enter your choice (1-6): ";
            cin >> choice;
            switch (choice) {
            case '1':
                addPerson();
                break;
            case '2':
                deletePerson();
                break;
            case '3':
                findPerson();
                break;
            case '4':
                changePhoneNumber();
                break;
            case '5':
                displayPhoneBook();
                break;
            case '6':
                saveToFile();
                cout << "Have a nice life!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        } while (choice != '6');
    }

private:
    Book phoneBook;

    // Function to load phone book data from file
    void loadFromFile() {
        ifstream inFile("phonebook.txt");
        if (inFile.is_open()) {
            string firstName, lastName, phoneNumber;
            while (inFile >> firstName >> lastName >> phoneNumber) {
                Person person(firstName, lastName, phoneNumber);
                phoneBook.Add(person);
            }
            inFile.close();
            cout << "Phone book data loaded from file." << endl;
        }
        else {
            cout << "Could not open file 'phonebook.txt'. Starting with empty phone book." << endl;
        }
    }

    // Function to save phone book data to file
    void saveToFile() {
        ofstream outFile("phonebook.txt");
        if (outFile.is_open()) {
            phoneBook.displayPhoneBook(); // insert outFile
            outFile.close();
            cout << "Phone book data saved to file." << endl;
        }
        else {
            cout << "Could not open file 'phonebook.txt' for writing." << endl;
        }
    }

    // Function to add a person to the phone book
    void addPerson() {
        string firstName, lastName, phoneNumber;
        cout << "Enter first name: " << endl;
        cin >> firstName;
        cout << "Enter last name: " << endl;
        cin >> lastName;
        cout << "Enter phone number: " << endl;
        cin >> phoneNumber;
        Person person(firstName, lastName, phoneNumber);
        phoneBook.Add(person);
        cout << person.getFirstName() + " " + person.getLastName() + " has been added";
    }

    // Function to delete a person from the phone book
    void deletePerson() {
        string firstName, lastName;
        cout << "Enter first name: ";
        cin >> firstName;
        cout << "Enter last name: ";
        cin >> lastName;
        phoneBook.deleteNode(lastName);
        cout << firstName + " " + lastName + " has been deleted";
    }

    void findPerson() {
        string firstName, lastName;
        cout << "Enter first name: ";
        cin >> firstName;
        cout << "Enter last name: ";
        cin >> lastName;
        phoneBook.findPerson(lastName);
        // cout << found.getFirstName() + " " + found.getLastName() + " - " + found.getPhoneName();

    }

    void changePhoneNumber() {
        string firstName, lastName, phoneNumber;
        cout << "Enter first name: ";
        cin >> firstName;
        cout << "Enter last name: ";
        cin >> lastName;
        cout << "Enter new phone number: ";
        cin >> phoneNumber;
        phoneBook.changeNumber(lastName, phoneNumber);
    }

    void displayPhoneBook() {
        phoneBook.displayPhoneBook();
    }

};

