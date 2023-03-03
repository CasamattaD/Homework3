#pragma once
#include <string>
#include <memory>

using namespace std;


// Person class representing Person firstName, lastName, and phoneNumber
class Person {
public:
    Person(string firstName, string lastName, string phoneNumber) :
        m_firstName(firstName), m_lastName(lastName), m_phoneNumber(phoneNumber) {}

    string getFirstName() const { return m_firstName; }
    string getLastName() const { return m_lastName; }
    string getPhoneName() const { return m_phoneNumber; }
    void changePhoneNumber(string number);

private:
    string m_firstName;
    string m_lastName;
    string m_phoneNumber;
};