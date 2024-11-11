#pragma once
#include "Patient.h"
#include "box.h"
#include "DoctorSchedule.h"
#include "Setcolor.h"
#include "Linked_List.cpp"
#include <iostream>
using namespace std;

//ve bang cho patient
void Patient :: drawTablePatient(int startX, int startY, int numRows) {
    Setcolor(11);
    string title = "APPOINTMENT LIST";
    int titlePos = (startX) + (static_cast<long long>(15) * 7 + 5) / 2 - 8;
    gotoxy(titlePos, startY - 2);
    cout << title;
    Setcolor(14);
    gotoxy(startX, startY);
    cout << "+";
    for (int i = 0; i < 7; i++) {
        if (i == 2) // Nếu là cột Doctor (cột thứ 3) thì dùng độ rộng 22
            cout << string(20, '-') << "+";
        else
            cout << string(15, '-') << "+";
    }

    gotoxy(startX, startY + 1);
    cout << "|     Date      |     Time      |       Doctor       |   Specialty   |     Room      |     RoomID    |     Status    |";

    gotoxy(startX, startY + 2);
    cout << "+";
    for (int i = 0; i < 7; i++) {
        if (i == 2) // Nếu là cột Doctor thì dùng độ rộng 22
            cout << string(20, '-') << "+";
        else
            cout << string(15, '-') << "+";
    }
    Setcolor(15);
    for (int row = 0; row < numRows; row++) {
        gotoxy(startX, startY + 3 + (row * 2));
        cout << "|               |               |                    |               |               |               |               |";

        gotoxy(startX, startY + 4 + (row * 2));
        cout << "+";
        for (int i = 0; i < 7; i++) {
            if (i == 2)
                cout << string(20, '-') << "+";
            else
                cout << string(15, '-') << "+";
        }
    }
}
void Patient :: fillAppointmentDetailsForPatient(LinkedList<Appointment>& appointments, int startX, int startY) {
    for (int i = 0; i < appointments.length(); i++) {
        gotoxy(startX + 2, startY + 3 + (i * 2)); // Điền thông tin vào cột Date
        cout << appointments.get(i).getDate(); // Date
        gotoxy(startX + 17, startY + 3 + (i * 2)); // Điền thông tin vào cột Time
        cout << appointments.get(i).getTime(); // Time
        gotoxy(startX + 33, startY + 3 + (i * 2)); // Điền thông tin vào cột Doctor
        cout << appointments.get(i).getDoctorName(); // Doctor
        gotoxy(startX + 56, startY + 3 + (i * 2)); // Điền thông tin vào cột Room
        Schedule* schedule = new Schedule();
        Doctor* doctor = schedule->findDoctorByID(appointments.get(i).getDoctor_ID());
        cout << doctor->getSpecialty(); 
        gotoxy(startX + 72, startY + 3 + (i * 2)); 
        cout << appointments.get(i).getClinicRoom(); // Room
        gotoxy(startX + 89, startY + 3 + (i * 2)); // Điền thông tin vào cột RoomID
        cout << appointments.get(i).getClinic_Room_ID(); // RoomID
        gotoxy(startX + 103, startY + 3 + (i * 2));
        cout << appointments.get(i).getStatus();
    }
}
//ve bang chon Doctor
void Patient::drawTableChooseDoctor(int startX, int startY, int numRows) {
    Setcolor(11);
    string title = "DOCTOR INFORMATION";
    int titlePos = (startX) + (static_cast < long long>(15)*4 + 3) / 2 - 9; // Đặt tiêu đề vào giữa bảng
    gotoxy(titlePos, startY - 2);
    cout << title;
    Setcolor(14);
    // Vẽ tiêu đề bảng
    gotoxy(startX, startY);
    cout << "+";
    for (int i = 0; i < 4; i++) {
        if (i == 0) // Cột Name có độ rộng lớn hơn (20 ký tự)
            cout << string(20, '-') << "+";
        else if (i == 1) // Cột Specialty có độ rộng 20 ký tự
            cout << string(20, '-') << "+";
        else if (i == 2||i == 3) // Cột Years of Experience có độ rộng 15 ký tự
            cout << string(15, '-') << "+";
    }

    gotoxy(startX, startY + 1);
    cout << "|    Doctor Name     |      Specialty     |   Experience  |   Time work   |";

    // Vẽ đường kẻ sau tiêu đề
    gotoxy(startX, startY + 2);
    cout << "+";
    for (int i = 0; i < 4; i++) {
        if (i == 0) // Cột Name
            cout << string(20, '-') << "+";
        else if (i == 1) // Cột Specialty
            cout << string(20, '-') << "+";
        else if (i == 2) // Cột Years of Experience
            cout << string(15, '-') << "+";
        else if (i == 3) // Cột Years of Experience
            cout << string(15, '-') << "+";
    }

    // Vẽ các dòng của bảng
    for (int row = 0; row < numRows; row++) {
        gotoxy(startX, startY + 3 + (row * 2));
        cout << "|                    |                    |               |               |";

        // Vẽ đường kẻ ngang sau mỗi dòng
        gotoxy(startX, startY + 4 + (row * 2));
        cout << "+";
        for (int i = 0; i < 4; i++) {
            if (i == 0) // Cột Name
                cout << string(20, '-') << "+";
            else if (i == 1) // Cột Specialty
                cout << string(20, '-') << "+";
            else if (i == 2) // Cột Years of Experience
                cout << string(15, '-') << "+";
            else if (i == 3) // Cột Years of Experience
                cout << string(15, '-') << "+";
        }
    }
    Setcolor(15);
}
void Patient::fillDoctorDetails(LinkedList<Doctor>& doctors,LinkedList<Doctor_Schedule>& Infor , int startX, int startY) {
    Schedule* Check = new Schedule();

    for (int i = 0; i < doctors.length(); i++) {
        gotoxy(startX + 2, startY + 3 + (i * 2)); // Điền thông tin Name
        cout << doctors.get(i).getName(); // Name

        gotoxy(startX + 23, startY + 3 + (i * 2)); // Điền thông tin Specialty
        cout << doctors.get(i).getSpecialty(); // Specialty

        gotoxy(startX + 44, startY + 3 + (i * 2)); // Điền thông tin Years of Experience

    
        Doctor_Schedule* newInf = Check->findScheduleDoctor(doctors.get(i).getID(), Infor);
        if (newInf != nullptr) {
            cout << newInf->getExperienceYears() << " Years"; 
        }
        else {
            cout << "N/A";
        }
        if (newInf != nullptr) {
            gotoxy(startX + 60, startY + 3 + (i * 2)); 
            cout << newInf->getTime_Start() << " - " << newInf->getTime_End();
        }
    }

    delete Check;
}




// Constructor
Patient::Patient(const string& name, const string& dateOfBirth, const string& gender, const string& address, const string& phoneNumber, const string& username, const string& password, int id) : Person(name, dateOfBirth, gender, address, phoneNumber), User(username, password, id) {}


//Them cuoc hen moi
void Patient::addAppointment(const Appointment& appointment) {
    appointments.addLast(appointment);
}

//Huy cuoc hen dua tren ngay hen

void Patient::cancelAppointment(const string& date, const int& appointment_ID) {
    if (appointments.empty()) {
        cout << "No appointment found on " << endl;
        return;
    }
    bool found = false;
    for (int i = 0; i < appointments.length(); i++) {
        if (appointments.get(i).getDate() == date && appointments.get(i).getAppointment_ID() == appointment_ID) {
            appointments.removeAtIndex(i);
            cout << "Appointment on " << date << " has been cancelled." << endl;
        }
    }
}


// Thêm lịch sử y tế mới
void Patient::addMedicalRecord(const string& record) {
    medicalHistory.addLast(record);
}


// Hiển thị lịch sử y tế
void Patient::viewMedicalHistory() {
    if (medicalHistory.empty()) {
        cout << "No medical history available." << endl;
        return;
    }
    cout << "Medical history:" << endl;
    for (int i = 0; i < medicalHistory.length(); i++) {
        cout << "- " << medicalHistory.get(i) << endl;
    }
}
