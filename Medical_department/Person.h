#pragma once 
#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    string dateOfBirth;
    string gender;
    string address;
    string phoneNumber;
public:
    // Constructor
    Person(){}
    Person(const string& name, const string& dateOfBirth, const string& gender, const string& address, const string& phoneNumber);
    ~Person() {}

    // Getters
    string getName() const;
    string getDateOfBirth() const;
    string getGender() const;
    string getAddress() const;
    string getPhoneNumber() const;

    // Setters
    void setName(const string& name);
    void setDateOfBirth(const string& dateOfBirth);
    void setGender(const string& gender);
    void setAddress(const string& address);
    void setPhoneNumber(const string& phoneNumber);
    // Phương thức hiển thị thông tin cá nhân
    virtual void displayInfo() const;
};

#endif