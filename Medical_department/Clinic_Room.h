#pragma once
#ifndef CLINIC_ROOM_H
#define CLINIC_ROOM_H
#include <iostream>
#include <string>
#include "Linked_List.cpp"
#include "Appointment.h"

using namespace std;

class Clinic_Room {
private:
    int roomID;                       // Mã phòng khám
    string roomType;                     // Loại phòng (phòng khám, phòng phẫu thuật, v.v.)
    string status;                       // Tình trạng phòng (Available, Booked)
    LinkedList<Appointment> schedule;        // Lịch hẹn đã đặt trong phòng

public:
    // Constructor
    Clinic_Room(const int& roomID, const string& roomType, const string& status = "Available");
    Clinic_Room(const Clinic_Room& other);
    Clinic_Room() {
        roomID = 0;
    }
    ~Clinic_Room(){}
    // Getters và Setters
    int getRoomID() const;
    string getRoomType() const;
    string getStatus() const;
    void setStatus(const string& newStatus);

    // Quản lý lịch hẹn
    bool checkAvailability(const string& date, const string& time) const;
    void addAppointment(const Appointment& appointment);
    void removeAppointment(const string& date, const string& time);
    void viewSchedule() const;
    void clearSchedule();
};
#endif
