#include "Authentication.h"
#include <string>
#include <sstream>
#include <fstream>
#include <sstream>

// Constructor
Authentication::Authentication() {}

// Lưu danh sách User từ file
void Authentication::saveUsers(const string& filename, const LinkedList<User>& users) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int i = 0; i < users.length(); i++) {
            User user = users.get(i);
            if (i != users.length() - 1) {
                outFile << user.getID() << "|" << user.getUsername() << "|" << user.getPassword() << endl;
            }
            else {
                outFile << user.getID() << "|" << user.getUsername() << "|" << user.getPassword();
            }
        }
        outFile.close();
    }
    else {
        cerr << "Could not open file for loading Users : " << filename << endl;
    }
}

//Đọc danh sách User từ file
void Authentication::loadUsers(const string& filename, LinkedList<User>& users) {
    users.clear();
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string id, username, password;
            getline(ss, id, '|');
            getline(ss, username, '|');
            getline(ss, password);

            User newUser(username, password, stoi(id));
            users.addLast(newUser);
        }
    }
}





bool Authentication::login(const string& username, const string& password, const string& filename,bool compare(int,int)) {
    LinkedList<User> users;
    loadUsers(filename, users);
    for (int i = 0; i < users.length(); i++) {
        User& user = users.get(i);
        if (user.getUsername() == username && user.getPassword() == password && compare(user.getID(),1000)) {
            cout << "Login successful! Welcome, " << username << endl;
            return true;  
        }
    }
    cout << "Login failed! Invalid username or password." << endl;
    return false;  
}

bool Authentication::signUp(const User& newUser, const string& filename, LinkedList<User>& users) {
    loadUsers(filename, users);
    //check User
    if (!CheckUser(newUser)) {
        return false;
    }
   
    // Kiểm tra xem username có tồn tại không
    for (int i = 0; i < users.length(); i++) {
        if (users.get(i).getUsername() == newUser.getUsername()) {
            return false;
        }
    }

    // Thêm người dùng mới vào danh sách và lưu vào file
    users.addLast(newUser);
    saveUsers(filename, users);

    return true;
}


//Check User
bool Authentication::CheckUser(const User& newUser) {
    string username = newUser.getUsername();
    string password = newUser.getPassword();
    if (username.length() < 6) {
        cout << "Username must be more than 6 characters!" << endl;
        return false;
    }
    if (username.length() > 15) {
        cout << "Username is not allowed more than 15 character!" << endl;
        return false;
    }

    for (int i = 0; i < username.length(); i++) {
        if (username[i] == ' ') {
            cout << "Username is not allowed to contain spaces!" << endl;
            return false;
        }
    }
    if (password.length() < 6) {
        cout << "Password must be more than 6 characters!" << endl;
        return false;
    }
    if (password.length() > 15) {
        cout << "Password is not allowed more than 15 character!" << endl;
        return false;
    }

    for (int i = 0; i < password.length(); i++) {
        if (password[i] == ' ') {
            cout << "Password are not allowed to contain spaces!" << endl;
            return false;
        }
    }

    return true;

}
bool Authentication::CheckPassword(const string& password) {
    if (password.length() < 6) {
        cout << "Password must be more than 6 characters!" << endl;
        return false;
    }
    if (password.length() > 15) {
        cout << "Password is not allowed more than 15 character!" << endl;
        return false;
    }

    for (int i = 0; i < password.length(); i++) {
        if (password[i] == ' ') {
            cout << "Password are not allowed to contain spaces!" << endl;
            return false;
        }
    }
    return true;
}

