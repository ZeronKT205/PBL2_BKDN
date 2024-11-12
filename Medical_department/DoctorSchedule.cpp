#pragma once
#include <ctime>
#include <sstream>
#include "DoctorSchedule.h"
#include "Setcolor.h"
#include "Box.h"
#include "Authentication.h"
#include <vector>
#include <iomanip>
using namespace std;


Doctor_Schedule::Doctor_Schedule(int id, const string& name, int startYear, const string& achs, const string& sched,const string& Time_Start,const string& Time_End)
    : doctorID(id), doctorName(name), achievements(achs), schedule(sched),Time_Start(Time_Start),Time_End(Time_End) {
    experienceYears = calculateExperienceYears(startYear);
}

int Doctor_Schedule::calculateExperienceYears(int startYear) {
    Authentication Check;
    int currentYear = Check.getCurrentYear();
    return currentYear - startYear;
}

// Getter
int Doctor_Schedule::getDoctorID() const {
    return doctorID;
}

string Doctor_Schedule::getDoctorName() const {
    return doctorName;
}

int Doctor_Schedule::getExperienceYears() const {
    return experienceYears;
}

string Doctor_Schedule::getAchievements() const {
    return achievements;
}

string Doctor_Schedule::getSchedule() const {
    return schedule;
}

string Doctor_Schedule::getTime_Start() const {
    return Time_Start;
}
string Doctor_Schedule::getTime_End() const {
    return Time_End;
}






// Setter
void Doctor_Schedule::setDoctorID(int id) {
    doctorID = id;
}

void Doctor_Schedule::setDoctorName(const string& name) {
    doctorName = name;
}

void Doctor_Schedule::setExperienceYears(int startYear) {
    experienceYears = calculateExperienceYears(startYear);
}

void Doctor_Schedule::addAchievement(const string& achievement) {
    achievements = achievements + ',' + achievement;
}

void Doctor_Schedule::setSchedule(const string& sched) {
    schedule = sched;
}
void Doctor_Schedule::setTime_Star(string time_Star) {
    Time_Start = time_Star;
}
void Doctor_Schedule::setTime_End(string time_End) {
    Time_End = time_End;
}

static void drawTree(int x, int y) {
    Setcolor(10);
    gotoxy(x, y);         std::cout << "*";
    gotoxy(x - 1, y + 1); std::cout << "***";
    gotoxy(x - 2, y + 2); std::cout << "*****";
    gotoxy(x - 3, y + 3); std::cout << "*******";
    Setcolor(12);
    gotoxy(x, y + 4);     std::cout << "|";
    Setcolor(15);
}

void Doctor_Schedule::displayDoctorInfo() {
    Setcolor(14);
    gotoxy(52, 6);
    cout << "___________________________________";
    gotoxy(52, 7);
    cout << "|           " << doctorName << endl;
    gotoxy(52, 8);
    cout << "| Experience Years: " << experienceYears << " years";
    gotoxy(52, 9);
    cout << "| Start_Time: " << this->Time_Start << endl;
    gotoxy(52, 10);
    cout << "| End_Time: " << this->Time_End << endl;
    gotoxy(52, 11);
    cout << "| Achievements: " << endl;
    LinkedList<string> content = Split_and_Show();
    for (int i = 0; i < content.length(); i++) {
        gotoxy(52, 12+i);
        cout << "|   ~" << content.get(i) << endl;
    }
    drawTree(95, 10);
    drawTree(42, 10);
    Setcolor(15);
}

LinkedList<string> Doctor_Schedule::Split_and_Show() {
    LinkedList<string> content;
    stringstream ss(achievements);
    string token;
    while (getline(ss, token, ',')) {
        content.addLast(token);
    }
    return content;
}


void Doctor_Schedule:: Split_Schedule() {
    stringstream ss(schedule);
    string token;
    while (getline(ss, token, ',')) {
        if (token == "Monday") ArrWeek[2] = 1;
        else if (token == "Tuesday") ArrWeek[3] = 1;
        else if (token == "Wednesday") ArrWeek[4] = 1;
        else if (token == "Thursday") ArrWeek[5] = 1;
        else if (token == "Friday") ArrWeek[6] = 1;
        else if (token == "Satuday") ArrWeek[7] = 1;
        else if (token == "Sunday") ArrWeek[8] = 1;

    }
}



string Doctor_Schedule::Table_Time(const string& date, Doctor& doctor, const LinkedList<Appointment>& appointments) {
    Authentication Check;
    int day = 0, month = 0, year = 0;
    Check.extractDateFromString(date, day, month, year);
    string find = Check.findDayOfWeek(day, month, year);

    stringstream ss(schedule);
    string token;
    bool C = false;
    while (getline(ss, token, ',')) {
        if (token == find) {
            C = true;
            break;
        }
    }

    if (!C) {
        cout << "There is no doctor's schedule today" << endl;
        return "ERORR!";
    }

    // Lấy danh sách thời gian đã đặt của bác sĩ cho ngày đó
    LinkedList<string> Time_Dr;
    Time_Dr.addLast("12:00");
    Time_Dr.addLast("12:30");
    for (int i = 0; i < appointments.length(); i++) {
        if (doctor.getID() == appointments.get(i).getDoctor_ID() && appointments.get(i).getDate() == date&& appointments.get(i).getStatus()!="Finished") {
            Time_Dr.addLast(appointments.get(i).getTime());
        }
    }

    // Điền danh sách thời gian có thể chọn (loại bỏ các thời gian đã đặt)
    int startHour = stoi(Time_Start.substr(0, 2));
    int startMinute = stoi(Time_Start.substr(3, 2));
    int endHour = stoi(Time_End.substr(0, 2));
    int endMinute = stoi(Time_End.substr(3, 2));

    int startTimeInMinutes = startHour * 60 + startMinute;
    int endTimeInMinutes = endHour * 60 + endMinute;
    vector<string> availableTimes;

    int currentMinutes = startTimeInMinutes;
    while (currentMinutes <= endTimeInMinutes) {
        int hour = currentMinutes / 60;
        int minute = currentMinutes % 60;

        // Định dạng thời gian dạng "HH:MM"
        stringstream timeStream;
        timeStream << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute;
        string formattedTime = timeStream.str();

        // Kiểm tra xem thời gian này đã được đặt chưa
        bool isBooked = false;
        for (int j = 0; j < Time_Dr.length(); j++) {
            if (Time_Dr.get(j) == formattedTime) {
                isBooked = true;
                break;
            }
        }

        // Nếu chưa được đặt, thêm vào availableTimes
        if (!isBooked) {
            availableTimes.push_back(formattedTime);
        }

        // Tăng thời gian thêm 30 phút
        currentMinutes += 30;
    }

    // Kiểm tra nếu không có thời gian nào khả dụng
    if (availableTimes.empty()) {
        cout << "No available times for this doctor on the selected date." << endl;
        return "ERORR!";
    }

    // Hiển thị menu cho người dùng chọn thời gian
    MenuBox Menu(50, 28, 2, 8, 11, 1, 203, availableTimes);
    int choose = Menu.menu3()-1;
    return availableTimes[choose];
}
