#pragma once
#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <iostream>
#include <string>
#include "FileManagement.h"
#include "Authentication.h"
#include "Linked_List.cpp"
#include "Appointment.h"
#include "Clinic_Room.h"
#include "Doctorschedule.h"
#include "Patient.h"
#include "Doctor.h"
using namespace std;

class Schedule :public FileManagement,public Authentication {
private:
    LinkedList<Appointment> appointments;   // Danh sách các cuộc hẹn
    LinkedList<Clinic_Room> rooms;          // Danh sách các phòng khám
    LinkedList<Patient> patients;           // Danh sachs cac benh nhan
    LinkedList<Doctor> doctors;             // Danh sách các bác sĩ
    LinkedList<User> users;

public:
    // Constructor
    Schedule();
    ~Schedule();

    //Quan ly benh nhan
    void addPatient(const Patient& patient);
    void removePatient(int patientID);
    Patient* findPatient(const string& patientName, const int& patient_ID);
    Patient* findPatientByID(int patientID);
    LinkedList<Patient> getAllPatients() const;
    LinkedList <Patient> findPatientByUsername(const string& username); // Tìm bệnh nhân theo tên người dùng
    void displayPatients();                        // Hiển thị danh sách bệnh nhân




    // Quản lý bác sĩ
    void addDoctor(const Doctor& doctor);
    void removeDoctor(int doctorID);
    Doctor* findDoctor(const string& doctorName, const int& doctor_ID);
    Doctor* findDoctorByID(int doctorID);
    LinkedList<Doctor> getAllDoctors() const;
    LinkedList<Doctor> findDoctorByUsername(const string& username); // Tìm bác sĩ theo tên người dùng
    LinkedList<Doctor> searchDoctorByName(const LinkedList<Doctor>& doctors, const std::string& nameToFind) {
        LinkedList<Doctor> result;
        for (int i = 0; i < doctors.length();i++) {
            Doctor &doctor = doctors.get(i);
            // Check if the name contains the search string (case-sensitive)
            if (doctor.getName().find(nameToFind) != std::string::npos) {
                result.addLast(doctor); // Assuming addLast is a method to add at the end of LinkedList
            }
        }
        return result;
    }
    Doctor_Schedule* findScheduleDoctor(const int& doctorID, LinkedList<Doctor_Schedule>& schedules);
    void displayDoctors();                                     // Hiển thị danh sách bác sĩ
    



    // Quản lý phòng khám
    void addClinicRoom(const Clinic_Room& room);
    void removeClinicRoom(int roomID);
    bool CheckAppointment(const string& time,const Doctor_Schedule& schedule) {
        for (int i = 0; i < appointments.length(); i++) {
            if (schedule.getDoctorID() == appointments.get(i).getDoctor_ID() && appointments.get(i).getTime() == time) {
                return false;
            }
        }
        return true;
    }
    Clinic_Room* findClinicRoom(const int& roomID);
    LinkedList<Clinic_Room> getAllClinicRooms() const;



    // Quản lý lịch hẹn
    bool scheduleAppointment(const Appointment& appointment);
    void cancelAppointment(const int& patient_ID, const string& date, const string& time);
    void viewAppointments() const;
    Appointment* findAppointmentByID(int appointmentID);
    LinkedList<Appointment>& getAllAppointments();

    //Quan Ly User
    void addUser(const User& user);
    void removeUser(int userID);
    User* findUser(const string& username, const string& password);
    LinkedList<User> getAllUser() const;


    // Cập nhật thông tin người dùng (bệnh nhân/bác sĩ)
    void updateDoctorInfo(int doctorID, const Doctor& newDoctorInfo);    // Cập nhật thông tin bác sĩ
    void updatePatientInfo(int patientID, const Patient& newPatientInfo); // Cập nhật thông tin bệnh nhân

    void Save_All_File(const string& fileAppt, const string& fileDoctor, const string& filePatient, const string& fileRoom, const string& fileuser) {
        this->saveAppointments(fileAppt, appointments);
        this->saveDoctors(fileDoctor, doctors);
        this->savePatients(filePatient, patients);
        this->saveClinicRooms(fileRoom, rooms);
        this->saveUsers(fileuser, users);
    }
    void Load_All_File(const string& fileAppt, const string& fileDoctor, const string& filePatient, const string& fileRoom, const string& fileuser) {
        this->loadAppointments(fileAppt,appointments);
        this->loadDoctors(fileDoctor,doctors);
        this->loadPatients(filePatient,patients);
        this->loadClinicRooms(fileRoom,rooms);
        this->loadUsers(fileuser, users);
    }
};
#endif 
