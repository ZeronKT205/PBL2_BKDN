#pragma once
#include "Person.h"
#include <iostream>
using namespace std;

// Constructor
Person::Person(const string& name, const string& dateOfBirth, const string& gender, const string& address, const string& phoneNumber) : name(name), dateOfBirth(dateOfBirth), gender(gender), address(address), phoneNumber(phoneNumber) {}


// Getters
string Person::getName() const {
    return name;
}

string Person::getDateOfBirth() const {
    return dateOfBirth;
}

string Person::getGender() const {
    return gender;
}

string Person::getAddress() const {
    return address;
}

string Person::getPhoneNumber() const {
    return phoneNumber;
}
// Setters
void Person::setName(const string& name) {
    this->name = name;
}

void Person::setDateOfBirth(const string& dateOfBirth) {
    this->dateOfBirth = dateOfBirth;
}

void Person::setGender(const string& gender) {
    this->gender = gender;
}

void Person::setAddress(const string& address) {
    this->address = address;
}
void Person::setPhoneNumber(const string& phoneNumber) {
    this->phoneNumber = phoneNumber;
}

// Phương thức hiển thị thông tin cá nhân
void Person::displayInfo() const {
    cout << "Name: " << name << endl;
    cout << "Date of Birth: " << dateOfBirth << endl;
    cout << "Gender: " << gender << endl;
    cout << "Address: " << address << endl;
}