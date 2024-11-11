#pragma once
#ifndef DOCTOR_H
#define DOCTOR_H
#include <iostream>
#include <string>
#include "Linked_List.cpp"
#include "User.h"
#include "Appointment.h"

using namespace std;

class Doctor : public User,public Person {
private:
    string specialty;                     // Chuyên môn của bác sĩ
    LinkedList<Appointment> appointments;     // Danh sách các cuộc hẹn của bác sĩ

public:
    // Constructor
    Doctor(const string& name, const string& dateOfBirth, const string& gender, const string& address, const string& phoneNumber,const string& username, const string& password, int id, const string& specialty);
    Doctor(const Doctor& other);
    ~Doctor(){}
    // Getters và Setters
    string getSpecialty() const;
    void setSpecialty(const string& specialty);

    // Quản lý lịch hẹn
    void addAppointment(const Appointment& appointment);
    void removeAppointment(const string& patientName, const string& date, const string& time,const int& appointment_ID);
    void viewSchedule();
    bool isDoctorAvailable(const string& date, const string& time) const;

    // Tra cứu thông tin bệnh nhân
    void lookupPatientInfo(const string& patientName,const int& patient_ID) const;

    // Ghi lại báo cáo chẩn đoán
    void setDiagnosisReport(int patient_ID, const string& report);


    //ve bang cho appointment
    void drawTablePatient(int startX, int startY, int numRows);
    void fillAppointmentDetailsForPatient(LinkedList<Appointment>& appointments, int startX, int startY);


};
#endif
