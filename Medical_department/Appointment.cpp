#pragma once
#include "Appointment.h"
#include <iostream>
using namespace std;
// Constructor
Appointment::Appointment(int appointment_ID, int patient_ID, int doctor_ID, int clinic_Room_ID, const string& date, const string& time, const string& doctorName, const string& patientName, const string& clinicRoom, const string& status) : appointment_ID(appointment_ID), patient_ID(patient_ID), doctor_ID(doctor_ID), clinic_Room_ID(clinic_Room_ID), date(date), time(time), doctorName(doctorName), patientName(patientName), clinicRoom(clinicRoom), status(status), diagnosisReport("") {}

// Getters
int Appointment::getAppointment_ID() const { return appointment_ID; }
int Appointment::getPatient_ID() const { return patient_ID; }
int Appointment::getDoctor_ID() const { return doctor_ID; }
int Appointment::getClinic_Room_ID() const { return clinic_Room_ID; }
string Appointment::getDate() const { return date; }
string Appointment::getTime() const { return time; }
string Appointment::getDoctorName() const { return doctorName; }
string Appointment::getPatientName() const { return patientName; }
string Appointment::getClinicRoom() const { return clinicRoom; }
string Appointment::getStatus() const { return status; }
string Appointment::getDiagnosisReport() const { return diagnosisReport; }

// Setters
void Appointment::setAppointment_ID(int Appointment_ID) { appointment_ID = Appointment_ID; }
void Appointment::setPatient_ID(int Patient_ID) { patient_ID = Patient_ID; }
void Appointment::setDoctor_ID(int Doctor_ID) { doctor_ID = Doctor_ID; }
void Appointment::setClinic_Room_ID(int Clinic_Room_ID) { clinic_Room_ID = Clinic_Room_ID; }
void Appointment::setDate(const string& newDate) { date = newDate; }
void Appointment::setTime(const string& newTime) { time = newTime; }
void Appointment::setDoctorName(const string& newDoctorName) { doctorName = newDoctorName; }
void Appointment::setPatientName(const string& newPatientName) { patientName = newPatientName; }
void Appointment::setClinicRoom(const string& newClinicRoom) { clinicRoom = newClinicRoom; }
void Appointment::setStatus(const string& newStatus) { status = newStatus; }
void Appointment::setDiagnosisReport(const string& report) { diagnosisReport = report; }

// Phương thức kiểm tra trạng thái
bool Appointment::isScheduled() const { return status == "Scheduled"; }
bool Appointment::isCancelled() const { return status == "Cancelled"; }
bool Appointment::isCompleted() const { return status == "Completed"; }
