#pragma once
#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H
#include <iostream>
#include <string>
#include <fstream>
#include "Doctor.h"
#include "Patient.h"
#include "Appointment.h"
#include "Clinic_Room.h"
#include "DoctorSchedule.h"
#include "Linked_List.cpp"
using namespace std;

class FileManagement {
public:
    // Constructor
    FileManagement() {}
    ~FileManagement(){}

    // Lưu danh sách bác sĩ vào file
    void saveDoctors(const string& filename, const LinkedList<Doctor>& doctors);

    // Đọc danh sách bác sĩ từ file
    void loadDoctors(const string& filename, LinkedList<Doctor>& doctors);

    // Lưu danh sách bệnh nhân vào file
    void savePatients(const string& filename, const LinkedList<Patient>& patients);

    // Đọc danh sách bệnh nhân từ file
    void loadPatients(const string& filename, LinkedList<Patient>& patients);

    // Lưu danh sách cuộc hẹn vào file
    void saveAppointments(const string& filename, const LinkedList<Appointment>& appointments);

    // Đọc danh sách cuộc hẹn từ file
    void loadAppointments(const string& filename, LinkedList<Appointment>& appointments);

    // Lưu danh sách phòng khám vào file
    void saveClinicRooms(const string& filename, const LinkedList<Clinic_Room>& rooms);

    // Đọc danh sách phòng khám từ file
    void loadClinicRooms(const string& filename, LinkedList<Clinic_Room>& rooms);

    //Luu danh sach thong tin Shcedule cua bac si vao file
    void saveDoctor_Shcedule(const string& filename, const LinkedList<Doctor_Schedule>& DrSchedule);

    //Doc danh sach thong tin Schedule cua bac si tu file
    void loadDoctor_Schedule(const string& filename, LinkedList<Doctor_Schedule>& DrSchedule);

};

#endif





