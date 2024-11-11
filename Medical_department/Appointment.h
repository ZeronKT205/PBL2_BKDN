#pragma once
#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <string>
using namespace std;

class Appointment {
private:
    int appointment_ID;
    int patient_ID;
    int doctor_ID;
    int clinic_Room_ID;
    string date;            // Ngày diễn ra cuộc hẹn (dd-mm-yyyy)
    string time;   // Giờ diễn ra cuộc hẹn (hh:mm)
    string doctorName;      // Tên bác sĩ phụ trách
    string patientName;     // Tên bệnh nhân
    string clinicRoom;      // Phòng khám diễn ra cuộc hẹn
    string status;          // Trạng thái của cuộc hẹn (Scheduled, Cancelled, Completed)
    string diagnosisReport; // Báo cáo chẩn đoán của bác sĩ (nếu có)

public:
    // Constructor
    Appointment(int appointment_ID, int patient_ID, int doctor_ID, int clinic_Room_ID,const string& date, const string& time, const string& doctorName, const string& patientName, const string& clinicRoom, const string& status = "Schedule");
    ~Appointment(){}
    // Getters
    int getAppointment_ID() const;
    int getPatient_ID() const;
    int getDoctor_ID() const;
    int getClinic_Room_ID() const;
    string getDate() const;
    string getTime() const;
    string getDoctorName() const;
    string getPatientName() const;
    string getClinicRoom() const;
    string getStatus() const;
    string getDiagnosisReport() const;

    // Setters
    void setAppointment_ID(int Appointment_ID);
    void setPatient_ID(int Patient_ID);
    void setDoctor_ID(int Doctor_ID);
    void setClinic_Room_ID(int Clinic_Room_ID);
    void setDate(const string& newDate);
    void setTime(const string& newTime);
    void setDoctorName(const string& newDoctorName);
    void setPatientName(const string& newPatientName);
    void setClinicRoom(const string& newClinicRoom);
    void setStatus(const string& newStatus);
    void setDiagnosisReport(const string& report);

    // Phương thức kiểm tra trạng thái cuộc hẹn
    bool isScheduled() const;
    bool isCancelled() const;
    bool isCompleted() const;
};
#endif APPOINTMENT_H
