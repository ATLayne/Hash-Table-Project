//Austin Layne
//Nathaniel Moreno

//This file defines the person class. This class contains only
//basic information that would be relevent to any individual
//such as name and age. From this class, other classes containing
//objects of different types of people can be derived.

#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Person
{
protected:
    string personName;
    int personAge;

public:
    Person();
    ~Person();

    void SetName(const string nameInput);
    string GetName() const;
    void SetAge(int ageInput);
    int GetAge();
    void display();
};

Person::Person()
{
    SetName("First Last");
    SetAge(0);
}

Person::~Person()
{
}

void Person::SetName(const string nameInput) {
    personName = nameInput;
}
string Person::GetName() const {
    return personName;
}
void Person::SetAge(int ageInput) {
    personAge = ageInput;
}
int Person::GetAge() {
    return personAge;
}
void Person::display() {
    cout << left;
    cout << setw(23) << (*this).personName << (*this).personAge << endl;
}

#endif
