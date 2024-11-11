
// Quản lý việc đăng nhập của người dùng
// File này định nghĩa lớp User, bao gồm các thuộc tính và phương thức
// để quản lý thông tin đăng nhập của người dùng như tên đăng nhập và mật khẩu.
// Nó cung cấp các phương thức để thiết lập và lấy thông tin người dùng,
#pragma once
#ifndef USER_H
#define USER_H
#include "Person.h"
#include <iostream>
#include <string>
using namespace std;

class User{
private:
    int _ID; // Added id member variable
    string username;
    string password;

public:
    // Constructor
    User(const string& username, const string& password, int id);
    ~User(){}
    // Getters
    int getID() const; // Added getter for id
    string getUsername() const;
    string getPassword() const;

    // Setters
    void setID(int id); // Added setter for id
    void setUsername(const string& username);
    void setPassword(const string& password);

};

#endif // USER_H
