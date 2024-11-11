#pragma once
#include "FileManagement.h"
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include "Authentication.h"
using namespace std;

//Lưu danh sách bác sĩ vào file
void FileManagement::saveDoctors(const string& filename, const LinkedList<Doctor>& doctors) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int i = 0; i < doctors.length(); i++) {
            const Doctor& doctor = doctors.get(i);
            if (i != doctors.length() - 1) {
                outFile << doctor.getID() << "|" << doctor.getName() << "|" << doctor.getDateOfBirth() << "|" << doctor.getGender() << "|" << doctor.getAddress() << "|" << doctor.getPhoneNumber() << "|" << doctor.getUsername() << "|" << doctor.getPassword() << "|" << doctor.getSpecialty() << endl;
            }
            else {
                outFile << doctor.getID() << "|" << doctor.getName() << "|" << doctor.getDateOfBirth() << "|" << doctor.getGender() << "|" << doctor.getAddress() << "|" << doctor.getPhoneNumber() << "|" << doctor.getUsername() << "|" << doctor.getPassword() << "|" << doctor.getSpecialty();
            }
        }
        outFile.close();
    }
    else {
        cerr << "Could not open file for saving doctors: " << filename << endl;
    }
}
void FileManagement::loadDoctors(const std::string& filename, LinkedList<Doctor>& doctors) {
    doctors.clear();
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string id, name, dob, gender, address, phone, username, password, specialty;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, dob, '|');
            getline(ss, gender, '|');
            getline(ss, address, '|');
            getline(ss, phone, '|');
            getline(ss, username, '|');
            getline(ss, password, '|');
            getline(ss, specialty);

            Doctor doctor(name, dob, gender, address, phone, username, password, stoi(id), specialty);
            doctors.addLast(doctor);
        }
        inFile.close();
    }
    else {
        cerr << "Could not open file for loading doctors: " << filename << endl;
    }
}

void FileManagement::savePatients(const string& filename, const LinkedList<Patient>& patients) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int i = 0; i < patients.length(); i++) {
            const Patient& patient = patients.get(i);
            if (i != patients.length() - 1) {
                outFile << patient.getID() << "|" << patient.getName() << "|" << patient.getDateOfBirth() << "|" << patient.getGender() << "|" << patient.getAddress() << "|" << patient.getPhoneNumber() << "|" << patient.getUsername() << "|" << patient.getPassword() << endl;

            }
            else {
                outFile << patient.getID() << "|" << patient.getName() << "|" << patient.getDateOfBirth() << "|" << patient.getGender() << "|" << patient.getAddress() << "|" << patient.getPhoneNumber() << "|" << patient.getUsername() << "|" << patient.getPassword();
            }
        }
        outFile.close();
    }
    else {
        cerr << "Could not open file for loading Patients: " << filename << endl;
    }
}
void FileManagement::loadPatients(const string& filename, LinkedList<Patient>& patients) {
    patients.clear();
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string id, name, dob, gender, address, phone, username, password;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, dob, '|');
            getline(ss, gender, '|');
            getline(ss, address, '|');
            getline(ss, phone, '|');
            getline(ss, username, '|');
            getline(ss, password, '|');

            Patient newPatient(name, dob, gender, address, phone, username, password, stoi(id));
            patients.addLast(newPatient);
        }
        inFile.close();
    }
    else {
        cerr << "Could not open file for loading Patients: " << filename << endl;
    }
}

void FileManagement::saveAppointments(const string& filename, const LinkedList<Appointment>& appointments) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int i = 0; i < appointments.length(); i++) {
            Appointment appt = appointments.get(i);
            if (i != appointments.length() - 1) {
                outFile << appt.getAppointment_ID() << "|"
                    << appt.getPatient_ID() << "|"
                    << appt.getDoctor_ID() << "|"
                    << appt.getClinic_Room_ID() << "|"
                    << appt.getDate() << "|"
                    << appt.getTime() << "|"
                    << appt.getDoctorName() << "|"
                    << appt.getPatientName() << "|"
                    << appt.getClinicRoom() << "|"
                    << appt.getStatus() << endl;
            }
            else {
                outFile << appt.getAppointment_ID() << "|"
                    << appt.getPatient_ID() << "|"
                    << appt.getDoctor_ID() << "|"
                    << appt.getClinic_Room_ID() << "|"
                    << appt.getDate() << "|"
                    << appt.getTime() << "|"
                    << appt.getDoctorName() << "|"
                    << appt.getPatientName() << "|"
                    << appt.getClinicRoom() << "|"
                    << appt.getStatus();
            }
        }
        outFile.close();
    }
    else {
        cerr << "Could not open file for loading Appointments : " << filename << endl;
    }
}
void FileManagement::loadAppointments(const string& filename, LinkedList<Appointment>& appointments) {
    appointments.clear();
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string appointmentID, patientID, doctorID, clinicRoomID, date, time, doctorName, patientName, clinicRoom, status;

            getline(ss, appointmentID, '|');
            getline(ss, patientID, '|');
            getline(ss, doctorID, '|');
            getline(ss, clinicRoomID, '|');
            getline(ss, date, '|');
            getline(ss, time, '|');
            getline(ss, doctorName, '|');
            getline(ss, patientName, '|');
            getline(ss, clinicRoom, '|');
            getline(ss, status);

            Appointment newAppointment(stoi(appointmentID), stoi(patientID), stoi(doctorID), stoi(clinicRoomID), date, time, doctorName, patientName, clinicRoom, status);
            appointments.addLast(newAppointment);
        }
        inFile.close();
    }
    else {
        cerr << "Could not open file for loading Appointments: " << filename << endl;
    }
}

void FileManagement::saveClinicRooms(const string& filename, const LinkedList<Clinic_Room>& rooms) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int i = 0; i < rooms.length(); i++) {
            Clinic_Room room = rooms.get(i);
            if (i != rooms.length() - 1) {
                outFile << room.getRoomID() << "|" << room.getRoomType() << "|" << room.getStatus() << endl;
            }
            else {
                outFile << room.getRoomID() << "|" << room.getRoomType() << "|" << room.getStatus();
            }
        }
        outFile.close();
    }
    else {
        cerr << "Could not open file for loading Clinics : " << filename << endl;
    }
}
void FileManagement::loadClinicRooms(const string& filename, LinkedList<Clinic_Room>& rooms) {
    rooms.clear();
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string roomID, roomType, status;

            getline(ss, roomID, '|');
            getline(ss, roomType, '|');
            getline(ss, status);

            Clinic_Room newRoom(stoi(roomID), roomType, status);
            rooms.addLast(newRoom);
        }
        inFile.close();
    }
    else {
        cerr << "Could not open file for loading Clinics: " << filename << endl;
    }
}

void FileManagement::saveDoctor_Shcedule(const string& filename, const LinkedList<Doctor_Schedule>& DrSchedule) {
    ofstream outFile(filename);
    Authentication Check;
    int CurrentYear = Check.getCurrentYear();
    if (outFile.is_open()) {
        for (int i = 0; i < DrSchedule.length(); i++) {
            const Doctor_Schedule& schedule = DrSchedule.get(i);
            if (i != DrSchedule.length() - 1) {
                outFile << schedule.getDoctorID() << "|"
                    << schedule.getDoctorName() << "|"
                    << CurrentYear - schedule.getExperienceYears() << "|"
                    << schedule.getAchievements() << "|"
                    << schedule.getSchedule() << "|"
                    << schedule.getTime_Start() << "|"
                    << schedule.getTime_End() << endl;
            }
            else {
                outFile << schedule.getDoctorID() << "|"
                    << schedule.getDoctorName() << "|"
                    << CurrentYear - schedule.getExperienceYears() << "|"
                    << schedule.getAchievements() << "|"
                    << schedule.getSchedule() << "|"
                    << schedule.getTime_Start() << "|"
                    << schedule.getTime_End();
            }
        }
        outFile.close();

    }
    else {
        std::cerr << "Could not open file for saving Doctor Schedules: " << filename << std::endl;
    }
}

void FileManagement::loadDoctor_Schedule(const string& filename, LinkedList<Doctor_Schedule>& DrSchedule) {
    DrSchedule.clear();
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string idStr, name, expYearsStr, achievementsStr, dayStr, startTime, endTime;
            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, expYearsStr, '|');
            getline(ss, achievementsStr, '|');
            getline(ss, dayStr, '|');
            getline(ss, startTime, '|');
            getline(ss, endTime);


            int id = static_cast<int>(stoi(idStr));
            int experienceYears = static_cast<int>(stoi(expYearsStr));
            Doctor_Schedule newschedule(id, name, experienceYears, achievementsStr, dayStr, startTime, endTime);
            DrSchedule.addLast(newschedule);
        }
        inFile.close();
    }
    else {
        cerr << "Could not open file: " << filename << endl;
        return;
    }
}