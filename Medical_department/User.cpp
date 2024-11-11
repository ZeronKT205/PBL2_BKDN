#pragma once
#include "User.h"
#include <iostream>
using namespace std;

// Constructor
User::User(const string& username, const string& password, int id) :username(username), password(password), _ID(id) {}

// Getters
int User::getID() const {
	return this->_ID;
}
string User::getUsername() const {
	return this->username;
}
string User::getPassword() const {
	return this->password;
}

// Setters
void User::setID(int id) {
	this->_ID = id;
}
void User::setUsername(const string& username) {
	this->username = username;
}
void User::setPassword(const string& password) {
	this->password = password;
}
