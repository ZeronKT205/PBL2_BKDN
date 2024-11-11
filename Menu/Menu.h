#pragma once
#include <iostream>
#include "Patient.h"
#include "Doctor.h"
using namespace std;
#ifndef MENU_H
#define MENU_H
class Home {
public:
    static void welcome(); //ham in ra chu welcome
    static int printTask(); // ham in ra cac option
    static void menu();
};

class PatientMenu {
public:
    static int printTask();                    // In ra console các chức năng
    static void menu(User&);               // Thực hiện các chức năng menu, switchcase
    static void login();
    static void signUp();
    static void Main();

    //cac chuc nang
    static void viewAppointment(User& user);
    static void makeAppointment(User& user);
    static void cancelAppointment(User& user);
    static void viewMyInfornation(User& user);
    static void updateInformation(User& user);
    static void changePassword(User& user);
};

class DoctorMenu {
public:
    static int printTask();
    static void menu(User&);                  // Thực hiện các chức năng menu, switchcase
    static void login();
    static void Main();

    //cac chuc nang
    static void viewAppointment(User& user);
    static void SetStatusAppointment(User& user);
    static void viewPatientAppointment(User& user);
    static void ChangePassword(User& usern);
    static void CancleAppointment(User& user);
    static void viewMyInformation(User& user);
    static void updateInformation(User& user);
    static void UpdateWorkSchedule(User& user);
};

#endif
