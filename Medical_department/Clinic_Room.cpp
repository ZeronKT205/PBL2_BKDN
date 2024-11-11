#pragma once
#include "Clinic_Room.h"
#include <iostream>
using namespace std;

// Constructor
Clinic_Room::Clinic_Room(const int& roomID, const string& roomType, const string& status)
    : roomID(roomID), roomType(roomType), status(status) {}

Clinic_Room::Clinic_Room(const Clinic_Room& other) {
    this->roomID = other.getRoomID();
    this->roomType = other.getRoomType();
    this->status = other.getStatus();
}


// Getters
int Clinic_Room::getRoomID() const {
    return roomID;
}

string Clinic_Room::getRoomType() const {
    return roomType;
}

string Clinic_Room::getStatus() const {
    return status;
}

// Setter cho trạng thái phòng
void Clinic_Room::setStatus(const string& newStatus) {
    status = newStatus;
}

// Kiểm tra phòng trống
bool Clinic_Room::checkAvailability(const string& date, const string& time) const {
    for (int i = 0; i < schedule.length(); i++) {
        Appointment& appt = schedule.get(i);
        if (appt.getDate() == date && appt.getTime() == time) {
            return false;  // Phòng đã có lịch hẹn vào thời gian này
        }
    }
    return true;  // Phòng trống
}

// Thêm lịch hẹn vào phòng
void Clinic_Room::addAppointment(const Appointment& appointment) {
    if (checkAvailability(appointment.getDate(), appointment.getTime())) {
        schedule.addLast(appointment);
        setStatus("Booked");  // Cập nhật trạng thái phòng sau khi đặt lịch
    }
    else {
        cout << "Room is not available at this time." << endl;
    }
}

// Hủy lịch hẹn trong phòng dựa trên ngày và giờ
void Clinic_Room::removeAppointment(const string& date, const string& time) {
    if (schedule.empty()) {
        cout << "List Appointment is false!" << endl;
        setStatus("Available");
        return;
    }
    bool found = false;
    for (int i = 0; i < schedule.length(); i++) {
        Appointment& appt = schedule.get(i);
        if (appt.getDate() == date && appt.getTime() == time) {
            schedule.removeAtIndex(i);
            cout << "Appointment on " << date << " at " << time << " has been removed." << endl;
            found = true;
            break;
        }
        if (found == false) {
            cout << "No appointment found at the specified time." << endl;
        }
    }


}

// Hiển thị lịch hẹn của phòng
void Clinic_Room::viewSchedule() const {
    if (schedule.empty()) {
        cout << "No appointments scheduled for this room." << endl;
    }
    else {
        cout << "Schedule for room " << roomID << ":" << endl;
        for (int i = 0; i < schedule.length(); i++) {
            Appointment& appt = schedule.get(i);
            cout << "Appointment with " << appt.getPatientName() << " on " << appt.getDate() << " at " << appt.getTime() << " with Dr. " << appt.getDoctorName() << endl;
        }
    }
}

// Xóa toàn bộ lịch hẹn
void Clinic_Room::clearSchedule() {
    for (int i = 0; i < schedule.length(); i++) {
        schedule.removeFirst();
    }
    setStatus("Available");
}


//int main() {
//    // Tạo phòng khám
//    Clinic_Room room1(101, "Examination Room", "Available");
//    Clinic_Room room2(102, "Surgery Room", "Available");
//
//    // Tạo một số cuộc hẹn
//    Appointment appt1(1, 1001, 101, 101, "2024-10-25", "09:00", "Dr. John Doe", "Alice Smith", "Examination Room", "Scheduled");
//    Appointment appt2(2, 1002, 101, 101, "2024-10-25", "14:00", "Dr. John Doe", "Bob Johnson", "Examination Room", "Scheduled");
//    Appointment appt3(3, 1003, 102, 102, "2024-10-26", "10:00", "Dr. Emily White", "Charlie Brown", "Surgery Room", "Scheduled");
//
//    // Thêm các cuộc hẹn vào phòng
//    cout << "\n--- Adding Appointments to Room 1 ---" << endl;
//    room1.addAppointment(appt1);
//    room1.addAppointment(appt2);
//
//    // Hiển thị lịch hẹn của phòng 1
//    cout << "\n--- View Room 1 Schedule ---" << endl;
//    room1.viewSchedule();
//
//    // Kiểm tra tính sẵn sàng của phòng 1
//    cout << "\n--- Checking Room 1 Availability ---" << endl;
//    if (room1.checkAvailability("2024-10-25", "09:00")) {
//        cout << "Room 1 is available on 2024-10-25 at 09:00" << endl;
//    }
//    else {
//        cout << "Room 1 is NOT available on 2024-10-25 at 09:00" << endl;
//    }
//
//    // Hủy cuộc hẹn đầu tiên trong phòng 1
//    cout << "\n--- Cancel Appointment in Room 1 ---" << endl;
//    room1.removeAppointment("2024-10-25", "09:00");
//
//    // Hiển thị lại lịch sau khi hủy
//    cout << "\n--- View Room 1 Schedule After Cancellation ---" << endl;
//    room1.viewSchedule();
//
//    // Thêm lịch hẹn vào phòng 2 và hiển thị lịch
//    cout << "\n--- Adding and Viewing Appointments in Room 2 ---" << endl;
//    room2.addAppointment(appt3);
//    room2.viewSchedule();
//
//    // Xóa toàn bộ lịch hẹn của phòng 1
//    cout << "\n--- Clearing Room 1 Schedule ---" << endl;
//    room1.clearSchedule();
//    room1.viewSchedule();
//
//    return 0;
//}