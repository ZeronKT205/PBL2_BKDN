#pragma once
#include "Doctor.h"
#include "Setcolor.h"
#include "Patient.h"
using namespace std;


//structure
Doctor::Doctor(const string& name, const string& dateOfBirth, const string& gender, const string& address, const string& phoneNumber, const string& username, const string& password, int id, const string& specialty) :Person(name, dateOfBirth, gender, address, phoneNumber), User(username, password, id), specialty(specialty) {}

Doctor::Doctor(const Doctor& other) :User(other.getUsername(), other.getPassword(), other.getID()), Person(other.getName(), other.getDateOfBirth(), other.getGender(), other.getAddress(), other.getPhoneNumber()) {
    this->specialty = other.getSpecialty();
}
//getter & Setter
string Doctor::getSpecialty() const {
    return specialty;
}

void Doctor::setSpecialty(const string& specialty) {
    this->specialty = specialty;
}

// Quản lý lịch hẹn

//Them cuoc hen
void Doctor::addAppointment(const Appointment& appointment) {
    appointments.addLast(appointment);
}

//xoa cuoc hen
void Doctor::removeAppointment(const string& patientName, const string& date, const string& time, const int& appointment_ID) {
    if (appointments.empty()) {
        cout << "List Appointments is empty!" << endl;
        return;
    }
    int check = false;
    for (int i = 0; i < appointments.length(); i++) {
        if (appointments.get(i).getPatientName() == patientName && appointments.get(i).getDate() == date && appointments.get(i).getTime() == time && appointments.get(i).getAppointment_ID() == appointment_ID) {
            appointments.removeAtIndex(i);
            check = true;
        }
    }
    if (check == false) {
        cout << "No appointment found for " << patientName << " on " << date << " at " << time << endl;
    }
}

//xem lich hen

void Doctor::viewSchedule() {
    if (appointments.empty()) {
        cout << "List Appointment is empty!" << endl;
        return;
    }
    cout << "Schedule for Dr. " << getName() << ":" << endl;
    for (int i = 0; i < appointments.length(); i++) {
        Appointment& appt = appointments.get(i);
        cout << "Appointment with " << appt.getPatientName() << " on " << appt.getDate() << " at " << appt.getTime() << " in room " << appt.getClinicRoom() << endl;
    }
}

//Kiem tra bac si có ranh vào thoi gian do hay khong
bool Doctor::isDoctorAvailable(const string& date, const string& time) const {
    for (int i = 0; i < appointments.length(); i++) {
        const Appointment& appt = appointments.get(i);
        if (appt.getDate() == date && appt.getTime() == time) {
            return false;  // Bác sĩ đã có lịch, không rảnh
        }
    }
    return true;  // Bác sĩ rảnh vào thời gian đó
}

//tra cuu thong tin benh nhan

void Doctor::lookupPatientInfo(const string& patientName, const int& patient_ID) const {
    if (appointments.empty()) {
        cout << "List Appointment is empty!" << endl;
        return;
    }
    bool check = false;
    for (int i = 0; i < appointments.length(); i++) {
        const Appointment& appt = appointments.get(i);
        if (appt.getPatientName() == patientName && appt.getPatient_ID() == patient_ID) {
            cout << "Patient: " << appt.getPatientName() << endl;
            cout << "Appointment on: " << appt.getDate() << " at " << appt.getTime() << endl;
            cout << "Clinic Room: " << appt.getClinicRoom() << endl;
            check = true;
        }
    }
    if (check == false) {
        cout << "No appointment found for patient:" << endl;
    }
}


//ghi lai bao cao chuan doan
void Doctor::setDiagnosisReport(int patient_ID, const string& report) {
    if (appointments.empty()) {
        cout << "List of Appointments is empty!" << endl;
        return;
    }

    bool found = false;
    for (int i = 0; i < appointments.length(); i++) {
        Appointment& appt = appointments.get(i);  // Lấy tham chiếu để có thể cập nhật giá trị
        if (appt.getPatient_ID() == patient_ID) {   // So sánh theo ID thay vì tên
            appt.setDiagnosisReport(report);      // Gọi phương thức setDiagnosisReport của Appointment
            cout << "Diagnosis report updated for patient ID: " << patient_ID << endl;
            found = true;
            break;  // Thoát khỏi vòng lặp ngay khi tìm thấy đúng bệnh nhân
        }
    }

    if (!found) {
        cout << "Patient with ID " << patient_ID << " not found in the list of Appointments!" << endl;
    }
}


void Doctor::drawTablePatient(int startX, int startY, int numRows) {
    Setcolor(11);
    string title = "APPOINTMENT LIST";
    int titlePos = (startX)+(static_cast<long long>(15) * 7 + 5) / 2 - 8;
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
    cout << "|     Date      |     Time      |       Patient      |   Birthday    |     Room      |     RoomID    |     Status    |";

    gotoxy(startX, startY + 2);
    cout << "+";
    for (int i = 0; i < 7; i++) {
        if (i == 2) 
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
void Doctor::fillAppointmentDetailsForPatient(LinkedList<Appointment>& appointments, int startX, int startY) {
    for (int i = 0; i < appointments.length(); i++) {
        gotoxy(startX + 2, startY + 3 + (i * 2)); // Điền thông tin vào cột Date
        cout << appointments.get(i).getDate(); // Date
        gotoxy(startX + 17, startY + 3 + (i * 2)); // Điền thông tin vào cột Time
        cout << appointments.get(i).getTime(); // Time
        gotoxy(startX + 33, startY + 3 + (i * 2)); // Điền thông tin vào cột Doctor
        cout << appointments.get(i).getPatientName(); // Doctor
        gotoxy(startX + 56, startY + 3 + (i * 2)); // Điền thông tin vào cột Room
        Schedule* schedule = new Schedule();
        Patient* patient = schedule->findPatientByID(appointments.get(i).getPatient_ID());
        cout << patient->getDateOfBirth();
        gotoxy(startX + 72, startY + 3 + (i * 2));
        cout << appointments.get(i).getClinicRoom(); // Room
        gotoxy(startX + 89, startY + 3 + (i * 2)); // Điền thông tin vào cột RoomID
        cout <<"  "<< appointments.get(i).getClinic_Room_ID(); // RoomID
        gotoxy(startX + 105, startY + 3 + (i * 2));
        cout << appointments.get(i).getStatus();
    }
}


//int main() {
//    // Tạo đối tượng Doctor
//    Doctor doctor1("Dr. John Doe", "1980-06-15", "Male", "123 Main St", "555-9876", "johndoe", "password123", 101, "Cardiology");
//
//    // Tạo một số cuộc hẹn
//    Appointment appt1(1, 1001, 101, 201, "2024-10-25", "09:00", "Dr. John Doe", "Alice Smith", "Examination Room", "Scheduled");
//    Appointment appt2(2, 1002, 101, 202, "2024-10-26", "14:00", "Dr. John Doe", "Bob Johnson", "Surgery Room", "Scheduled");
//
//    // Thêm các cuộc hẹn vào danh sách của bác sĩ
//    doctor1.addAppointment(appt1);
//    doctor1.addAppointment(appt2);
//
//    // Hiển thị lịch hẹn của bác sĩ
//    cout << "--- Doctor's Schedule ---" << endl;
//    doctor1.viewSchedule();
//
//    // Kiểm tra xem bác sĩ có rảnh vào một thời gian cụ thể không
//    cout << "\n--- Checking Doctor Availability ---" << endl;
//    string date = "2024-10-25";
//    string time = "09:00";
//    if (doctor1.isDoctorAvailable(date, time)) {
//        cout << "Dr. John Doe is available on " << date << " at " << time << endl;
//    }
//    else {
//        cout << "Dr. John Doe is NOT available on " << date << " at " << time << endl;
//    }
//
//    // Ghi lại báo cáo chẩn đoán cho một bệnh nhân
//    cout << "\n--- Setting Diagnosis Report ---" << endl;
//    doctor1.setDiagnosisReport(1001, "Patient shows symptoms of mild flu.");
//
//    // Tra cứu thông tin bệnh nhân
//    cout << "\n--- Looking Up Patient Information ---" << endl;
//    doctor1.lookupPatientInfo("Alice Smith", 1001);
//
//    // Hủy cuộc hẹn của bệnh nhân
//    cout << "\n--- Cancel Appointment ---" << endl;
//    doctor1.removeAppointment("Alice Smith", "2024-10-25", "09:00", 1);
//
//    // Hiển thị lại lịch sau khi hủy
//    cout << "\n--- Doctor's Schedule After Cancellation ---" << endl;
//    doctor1.viewSchedule();
//
//    return 0;
//}