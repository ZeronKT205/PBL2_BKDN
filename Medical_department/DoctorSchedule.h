#pragma once
#ifndef DOCTORSCHEDULE_H
#define DOCTORSCHEDULE_H

#include <iostream>
#include <string>
#include "Linked_List.cpp"  // Sử dụng LinkedList tùy chỉnh đã tạo
#include <sstream>
#include "Doctor.h"
#include <ctime>

using namespace std;

class Doctor_Schedule {
private:
    int doctorID=0;
    string doctorName;
    int experienceYears=0;
    string achievements; // Danh sách thành tựu
    string schedule;     // Lịch làm việc
    string Time_Start;
    string Time_End;
    int ArrWeek[9] = { 0 };
    string Arrtmp[9] = { "0","0","Monday","Tuesday","Wednesday","Thursday","Friday","Satuday,","Sunday" };
    //LinkedList <string> DayOff;
public:
    // Constructor
    Doctor_Schedule(int id, const string& name, int startYear, const string& achs, const string& sched, const string& Time_Start,const string& Time_End);
    Doctor_Schedule(){
        doctorID = 0;
        experienceYears = 0;
    }
    // Tính toán số năm kinh nghiệm dựa trên năm bắt đầu làm việc
    int calculateExperienceYears(int startYear);

    // Getter
    int getDoctorID() const;
    string getDoctorName() const;
    int getExperienceYears() const;
    string getAchievements() const;
    string getSchedule() const;
    string getTime_Start() const;
    string getTime_End() const;

    // Setter
    void setDoctorID(int id);
    void setDoctorName(const string& name);
    void setExperienceYears(int startYear);
    void addAchievement(const string& achievement);
    void setSchedule(const string& sched);
    void setTime_Star(string time_Star);
    void setTime_End(string time_End);

    // Hiển thị thông tin bác sĩ
    void displayDoctorInfo();

    //Tach va show achievements
    LinkedList<string> Split_and_Show();
    void Split_Schedule();
    
    //ham tạo lịch để bệnh nhân chọn
    string Table_Time(const string& date, Doctor& doctor, const LinkedList<Appointment>& appointments);
};

#endif