#pragma once
#include <string>
#include <iostream>
#include "Schedule.h"
using namespace std;


//constructor
Schedule::Schedule() {
    Load_All_File("../PBL2_BKDN/Appt_infor.txt", "../PBL2_BKDN/Doctor_infor.txt", "../PBL2_BKDN/Patient_infor.txt", "../PBL2_BKDN/Room_infor.txt","../PBL2_BKDN/User_infor.txt");
}
Schedule::~Schedule() {
    appointments.clear();
    doctors.clear();
    patients.clear();
    rooms.clear();
    users.clear();
}
//Quan ly benh nhan
void Schedule::addPatient(const Patient& patient) {
    patients.addLast(patient);
}
void Schedule::removePatient(int patientID) {
    bool check = false;
    for (int i = 0; i < patients.length(); i++) {
        Patient patient = patients.get(i);
        if (patient.getID() == patientID) {
            patients.removeAtIndex(i);
            check = true;
        }
    }
    if (!check) {
        cout << "Patient with ID: " << patientID << " not found!" << endl;
    }
}
Patient* Schedule::findPatient(const string& patientName, const int& patient_ID) {
    for (int i = 0; i < patients.length(); i++) {
        Patient& patient = patients.get(i);
        if (patient.getName() == patientName && patient.getID() == patient_ID) {
            return &patient;
        }
    }
    cout << "Patient " << patientName << " with ID " << patient_ID << " not found." << endl;
    return nullptr;
}

// Tìm bệnh nhân theo ID
Patient* Schedule::findPatientByID(int patientID) {
    for (int i = 0; i < patients.length(); i++) {
        if (patients.get(i).getID() == patientID) {
            Patient& patient = patients.get(i);
            return &patient;
        }
    }
    return nullptr;
}

LinkedList<Patient> Schedule::getAllPatients() const {
    return patients;
}
// Tìm bệnh nhân theo tên người dùng
LinkedList<Patient> Schedule::findPatientByUsername(const std::string& username) {
    LinkedList <Patient> matchingPatients;
    for (int i = 0; i < patients.length(); i++) {
        if (patients.get(i).getUsername() == username) {
            matchingPatients.addLast(patients.get(i));
        }
    }
    if (matchingPatients.empty()) {
        cout << "No patients found with username: " << username << endl;
    }
    return matchingPatients;
}

// Hiển thị danh sách bệnh nhân
void Schedule::displayPatients() {
    if (patients.empty()) {
        cout << "No patients available." << endl;
        return;
    }
    for (int i = 0; i < patients.length(); i++) {
        const Patient& patient = patients.get(i);
        cout << "Patient ID: " << patient.getID() << ", Name: " << patient.getName() << endl;
    }
}





//Quan ly Bac Si
void Schedule::addDoctor(const Doctor& doctor) {
    doctors.addLast(doctor);
}
void Schedule::removeDoctor(int doctorID) {
    bool check = false;
    for (int i = 0; i < doctors.length(); i++) {
        Doctor doctor = doctors.get(i);
        if (doctor.getID() == doctorID) {
            doctors.removeAtIndex(i);
            check = true;
        }
    }
    if (!check) {
        cout << "Doctor with ID: " << doctorID << " not found!" << endl;
    }
}
Doctor* Schedule::findDoctor(const string& doctorName, const int& doctor_ID) {
    for (int i = 0; i < doctors.length(); i++) {
        Doctor& doctor = doctors.get(i);
        if (doctor.getName() == doctorName && doctor.getID() == doctor_ID) {
            return &doctor;
        }
    }
    return nullptr;
}
LinkedList<Doctor> Schedule::getAllDoctors() const {
    return doctors;
}

// Tìm bác sĩ theo ID
Doctor* Schedule::findDoctorByID(int doctorID) {
    for (int i = 0; i < doctors.length(); i++) {
        Doctor& doctor = doctors.get(i);
        if (doctor.getID() == doctorID) {
            return &doctor;
        }
    }
    cout << "Doctor with " << doctorID << " not found" << endl;
    return nullptr;
}
Doctor_Schedule* Schedule::findScheduleDoctor(const int& doctorID, LinkedList<Doctor_Schedule>& schedules) {
    for (int i = 0; i < schedules.length(); i++) {
        Doctor_Schedule& schedule = schedules.get(i);
        if (schedule.getDoctorID() == doctorID) {
            return &schedule;
        }
    }
    return nullptr;
}


// Tìm bác sĩ theo tên người dùng
LinkedList<Doctor> Schedule::findDoctorByUsername(const string& username) {
    LinkedList<Doctor> matchingDoctors;
    for (int i = 0; i < doctors.length(); i++) {
        Doctor& doctor = doctors.get(i);
        if (doctor.getUsername() == username) {
            matchingDoctors.addLast(doctor);
        }
    }
    if (matchingDoctors.empty()) {
        cout << "No doctors found with username: " << username << endl;
    }
    return matchingDoctors; // Trả về linked list gồm danh sách các bác sĩ có tên username
}

// Hiển thị danh sách bác sĩ
void Schedule::displayDoctors() {
    if (doctors.empty()) {
        cout << "No doctors available." << endl;
        return;
    }
    for (int i = 0; i < doctors.length(); i++) {
        const Doctor& doctor = doctors.get(i);
        cout << "Doctor ID: " << doctor.getID() << ", Name: " << doctor.getName() << endl;
    }
}








//Quan ly phong kham
void Schedule::addClinicRoom(const Clinic_Room& room) {
    rooms.addLast(room);
}
void Schedule::removeClinicRoom(int roomID) {
    bool check = false;
    for (int i = 0; i < rooms.length(); i++) {
        Clinic_Room room = rooms.get(i);
        if (room.getRoomID() == roomID) {
            rooms.removeAtIndex(i);
            check = true;
        }
    }
    if (!check) {
        cout << "Room with ID: " << roomID << " not found!" << endl;
    }
}

Clinic_Room* Schedule::findClinicRoom(const int& roomID) {
    for (int i = 0; i < rooms.length(); i++) {
        Clinic_Room& room = rooms.get(i);
        if (room.getRoomID() == roomID) {
            return &room;
        }
    }
    cout << "Room " << roomID << " not found." << endl;
    return nullptr;
}

LinkedList<Clinic_Room> Schedule::getAllClinicRooms() const {
    return rooms;
}



//QUAN LY LICH HEN
bool Schedule::scheduleAppointment(const Appointment& appointment) {
    //kiem tra xem phong con trong khong
    Clinic_Room* room = findClinicRoom(appointment.getClinic_Room_ID());
    if (room == nullptr || !room->checkAvailability(appointment.getDate(), appointment.getTime())) {
        cout << "Cannot schedule appointment: Room not available." << endl;
        return false;
    }

    //kiem tra bac si và time lam viec
    Doctor* doctor = findDoctor(appointment.getDoctorName(), appointment.getDoctor_ID());
    if (doctor == nullptr) {
        cout << "Cannot schedule appointment: Doctor not found." << endl;
        return false;
    }
    if (!doctor->isDoctorAvailable(appointment.getDate(), appointment.getTime())) {
        return false;
    }
    Patient* patient = findPatient(appointment.getPatientName(), appointment.getPatient_ID());
    //Them cuoc hen vao danh sach 
    room->addAppointment(appointment);
    doctor->addAppointment(appointment);
    patient->addAppointment(appointment);
    appointments.addLast(appointment);

    cout << "Appointment scheduled successfully." << endl;
    return true;
}

//huy cuoc hen

void Schedule::cancelAppointment(const int& patient_ID, const string& date, const string& time) {
    for (int i = 0; i < appointments.length(); i++) {
        Appointment& appt = appointments.get(i);
        if (appt.getPatient_ID() == patient_ID && appt.getDate() == date && appt.getTime() == time && appt.getStatus()!="Finished") {
            appointments.removeAtIndex(i);  // Xóa cuộc hẹn khỏi danh sách
            return;
        }
    }
}

void Schedule::viewAppointments() const {
    if (appointments.empty()) {
        cout << "No appointments scheduled." << endl;
        return;
    }
    for (int i = 0; i < appointments.length(); i++) {
        const Appointment& appt = appointments.get(i);
        cout << "Appointment with " << appt.getPatientName() << " on " << appt.getDate() << " at " << appt.getTime() << " in room " << appt.getClinicRoom() << " with Doctor " << appt.getDoctorName() << endl;
    }
}
Appointment* Schedule::findAppointmentByID(int appointmentID) {
    for (int i = 0; i < appointments.length(); i++) {
        Appointment& appt = appointments.get(i);
        if (appt.getAppointment_ID() == appointmentID) {
            return &appt;
        }
    }
    cout << "Appointment with ID: " << appointmentID << " not found!" << endl;
    return nullptr;
}
LinkedList<Appointment>& Schedule::getAllAppointments() {
    return appointments;
}


//QUAN LY USER
void Schedule::addUser(const User& user) {
    users.addLast(user);
}
void Schedule::removeUser(int userID) {
    bool check = false;
    for (int i = 0; i < users.length(); i++) {
        User user = users.get(i);
        if (user.getID() == userID) {
            users.removeAtIndex(i);
            check = true;
        }
    }
    if (check = false) {
        cerr << "User with id " << userID << " not found!" << endl;
    }
}
User* Schedule::findUser(const string& username, const string& password) {
    for (int i = 0; i < users.length(); i++) {
        User& user = users.get(i);
        if (user.getUsername() == username && user.getPassword()==password) {
            return &user;
        }
    }
    return nullptr;
}
LinkedList<User> Schedule::getAllUser() const {
    return users;
}



//QUAN LY CAC CHUC NANG
void Schedule::updateDoctorInfo(int doctorID, const Doctor& newDoctorInfo) {
    Doctor* doctor = findDoctorByID(doctorID);
    if (doctor != nullptr) {
        *doctor = newDoctorInfo;
        cout << "Doctor information updated successfully." << endl;
    }
    else {
        doctors.addLast(newDoctorInfo);
        cout << "Doctor information updated successfully." << endl;
    }
}

void Schedule::updatePatientInfo(int patientID, const Patient& newPatientInfo) {
    Patient* patient = findPatientByID(patientID);
    if (patient != nullptr) {
        *patient = newPatientInfo;
        cout << "Patient information updated successfully." << endl;
    }
    else {
        patients.addLast(newPatientInfo);
        cout << "Patient information updated successfully." << endl;
    }
}



//int main() {
//    // Tạo đối tượng Schedule để quản lý hệ thống
//    Schedule systemSchedule;
//    systemSchedule.Load_All_File("../PBL2_BKDN/Appt_infor.txt", "../PBL2_BKDN/Doctor_infor.txt", "../PBL2_BKDN/Patient_infor.txt", "../PBL2_BKDN/Room_infor.txt");
//
//  
//
//
//    // Hiển thị danh sách bác sĩ
//    cout << "\n--- List of Doctors ---" << endl;
//    systemSchedule.displayDoctors();
//
//    //// Hiển thị danh sách bệnh nhân
//    cout << "\n--- List of Patients ---" << endl;
//    systemSchedule.displayPatients();
//
//    //// Hiển thị danh sách lịch hẹn
//    cout << "\n--- List of Appointments ---" << endl;
//    systemSchedule.viewAppointments();
//
//    //// Hủy lịch hẹn
//    cout << "\n--- Cancel Appointment ---" << endl;
//    systemSchedule.cancelAppointment("Le Van Tam", 1001, "2024/10/21", "10:00");
//
//    //// Hiển thị danh sách lịch hẹn sau khi hủy
//    cout << "\n--- View Appointments After Cancellation ---" << endl;
//    systemSchedule.viewAppointments();
//
//    string username, password;
//    cout << "Username: "; getline(cin, username);
//    cout << "Password: "; getline(cin, password);
//    User user(username, password, 1005);
//    LinkedList<User> users;
//    systemSchedule.signUp(user, "../PBL2_BKDN/User_infor.txt", users);
//
//    //systemSchedule.Save_All_File("../PBL2_BKDN/Appt_infor.txt", "../PBL2_BKDN/Doctor_infor.txt", "../PBL2_BKDN/Patient_infor.txt", "../PBL2_BKDN/Room_infor.txt");
//
//    //return 0;
//}
