#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "Menu.h"
#include "Box.h"
#include "Setcolor.h"
using namespace std;

void Home::welcome() {
    ifstream inFile("../PBL2_BKDN/Welcome.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
    system("pause");
    system("cls");
}

int Home::printTask() {
    Setcolor(14);
    ifstream inFile("../PBL2_BKDN/MainPage.txt");
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();
    Setcolor(15);

    //Tao content
    vector <string> HOME;
    HOME.push_back("Doctor");
    HOME.push_back("Patient");
    HOME.push_back("Exit");

    vector<string> BOSS;
    BOSS.push_back("                   GIAM DOC: DOAN KIM TAI");
    //Ve bang dong
    MenuBox HOMEBOX(45, 19, 2, 20, 11, 1, 203, HOME);
    HOMEBOX.boxesArr(45, 14, 2, 62, 11, 1, BOSS);
    int choose = HOMEBOX.menu2();
    return choose; // xuat ra lua chon

}

void Home::menu() {
    int choose = Home::printTask();
    switch (choose) {
    case 1:

        DoctorMenu::Main();
        system("pause");
        break;

    case 2:
        PatientMenu::Main();
        system("pause");
        break;

    case 3:
        exit(0);
        break;
    }
}