#pragma once
#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H
#include <iostream>
#include <string>
#include "User.h"
#include <ctime>
#include <sstream>
#include "Linked_List.cpp"
#include "FileManagement.h"

using namespace std;

class Authentication {
public:
    // Constructor
    Authentication();
    ~Authentication(){}
    void saveUsers(const string& filename, const LinkedList<User>& users);
    void loadUsers(const string& filename, LinkedList<User>& users);

    //QUAN LY DANG NHAP
    bool login(const string& username, const string& password, const string& filename,bool compare(int,int));
    bool signUp(const User& newUser, const string& filename, LinkedList<User>& users);

    //Xu ly dang nhap
    bool CheckUser(const User& newUser);
    bool CheckPassword(const string& password);
    static bool isDotor(int l, int r) {
        return l < r;
    }
    static bool isPatient(int l, int r) {
        return l > r;
    }
    int getnewIDforPatient(const string& filename, LinkedList<User>& users) {
        loadUsers(filename, users);

        // Nếu danh sách người dùng trống, trả về ID mặc định cho bệnh nhân
        if (users.length() == 0) {
            cout << "Length Users = 0" << endl;
            return 1001;
        }

        int newID = -1;

        for (int i = 0; i < users.length(); i++) {
            int currentID = users.get(i).getID();
            if (currentID >= 1000) {
                newID = currentID;
                break;
            }
        }
        if (newID == -1) {
            return 1001;
        }
        for (int i = 0; i < users.length(); i++) {
            int currentID = users.get(i).getID();
            if (currentID >= 1000 && currentID > newID) {
                newID = currentID;
            }
        }
        return newID + 1;
    }
    int getnewIDforAppointment(const LinkedList<Appointment>& appointments) {
        int len = appointments.length();

        // Kiểm tra nếu danh sách trống, bắt đầu với ID = 1
        if (len == 0) {
            cout << "Length Appointments = 0" << endl;
            return 1;
        }

        // Tìm ID lớn nhất trong danh sách
        int maxID = appointments.get(0).getAppointment_ID();
        for (int i = 1; i < len; i++) {  // Bắt đầu từ 1 vì phần tử 0 đã được gán cho maxID
            if (maxID < appointments.get(i).getAppointment_ID()) {
                maxID = appointments.get(i).getAppointment_ID();
            }
        }

        // Trả về ID mới lớn hơn ID lớn nhất
        return maxID + 1;
    }


    //xu ly thoi gian

    //lay ngay thang nam tu chuoi string
    void extractDateFromString(const string& dateStr, int& day, int& month, int& year) {
        stringstream ss(dateStr);
        char delimiter;

        ss >> day >> delimiter >> month >> delimiter >> year;
    } 

    //lay thu trong tuan 
    string findDayOfWeek(int day, int month, int year) {

        tm time_in = { 0, 0, 0, day, month - 1, year - 1900 }; 

        time_t time_temp = mktime(&time_in);

        tm time_out;
        localtime_s(&time_out, &time_temp); 

        int day_of_week = time_out.tm_wday;

        string daysOfWeek[] = {  "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Satuday" };
        return daysOfWeek[day_of_week];
    }

    //kiem tra xem ngay nhap vao co thoa man dieu kien de mak appt khong
    bool CheckTime_MakeAppts(const string& dateStr) {
        int Daynow = 0, Monthnow = 0, Yearnow = 0;
        extractDateFromString(dateStr, Daynow, Monthnow, Yearnow);

        // Lấy thời gian hiện tại
        time_t t = time(0);
        tm now = {};
        localtime_s(&now, &t);  // Dùng localtime_s để thay thế localtime

        int currentYear = now.tm_year + 1900;
        int currentMonth = now.tm_mon + 1;
        int currentDay = now.tm_mday;

        // Chuyển đổi ngày hiện tại và ngày hẹn sang tổng số ngày
        int inputDateDays = Yearnow * 365 + Monthnow * 30 + Daynow;
        int currentDateDays = currentYear * 365 + currentMonth * 30 + currentDay;

        // Kiểm tra nếu ngày hẹn nhỏ hơn hoặc bằng ngày hiện tại
        if (inputDateDays <= currentDateDays) {
            cout << "The appointment date must be at least 1 day after the current date!" << endl;
            return false;
        }

        // Kiểm tra nếu ngày hẹn quá 3 tháng từ ngày hiện tại
        if (inputDateDays > currentDateDays + 90) {
            cout << "The appointment date cannot exceed 3 months from the current date!" << endl;
            return false;
        }

        return true;
    }

    // Kiem tra dinh dang thoi gian lam viec vi du: 18:00, 07:30
    bool isValidTimeFormat(const std::string& time) {
        // Kiểm tra độ dài của chuỗi phải là 5 ký tự
        if (time.size() != 5) return false;

        // Kiểm tra ký tự thứ 3 là dấu ':'
        if (time[2] != ':') return false;

        // Kiểm tra các ký tự còn lại là số
        for (int i = 0; i < time.size(); ++i) {
            if (i != 2 && (time[i] < '0' || time[i] > '9')) {
                return false;
            }
        }

        // Chuyển giờ và phút sang số nguyên
        int hour = stoi(time.substr(0, 2));
        int minute = stoi(time.substr(3, 2));

        // Kiểm tra giờ hợp lệ (0 <= hour <= 23) và phút hợp lệ (0 <= minute <= 59)
        if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
            return false;
        }

        return true;
    }
    
    //lay nam hien tai 
    int getCurrentYear() {
        time_t now = time(0);
        tm timeInfo;

        // Sử dụng localtime_s để lấy thời gian hiện tại
        if (localtime_s(&timeInfo, &now) != 0) {
            return -1;
        }

        return 1900 + timeInfo.tm_year;  // tm_year đếm từ 1900
    }

    //Check phong trong
    bool CheckAvailability(const string& date, const string& time, const LinkedList<Appointment>& appointments , const int& RoomID) {
        for (int i = 0; i < appointments.length(); i++) {
            Appointment& appt = appointments.get(i);
            if (appt.getClinic_Room_ID() == RoomID && appt.getDate() == date && appt.getTime() == time) {
                return false;
            }
        }
        return true;
    }



    //xu ly trung lap va dua ra chuoi da loai bo trung lap
    bool isDuplicate(const std::string items[], int size, const std::string& item) {
        for (int i = 0; i < size; ++i) {
            if (items[i] == item) {
                return true;
            }
        }
        return false;
    }
    std::string removeDuplicates(const std::string& input) {
        std::string items[100];  // Mảng lưu các phần tử duy nhất (giới hạn 100 phần tử)
        int uniqueCount = 0;     // Số lượng phần tử duy nhất
        std::string result;
        std::string item;

        for (size_t i = 0; i <= input.size(); ++i) {
            if (i == input.size() || input[i] == ',') {
                // Kiểm tra và thêm phần tử vào mảng nếu không trùng lặp
                if (!isDuplicate(items, uniqueCount, item)) {
                    items[uniqueCount++] = item;
                    if (!result.empty()) {
                        result += ",";
                    }
                    result += item;
                }
                item.clear();
            }
            else {
                item += input[i];
            }
        }
        return result;
    }
    
    //Kiem tra chuoi nay co nam trong chuoi kia 
    bool containsSubstring(const std::string& mainString, const std::string& subString) {
        std::istringstream ss(mainString);
        std::string token;

        // Duyệt qua từng phần của mainString được tách bởi dấu phẩy
        while (std::getline(ss, token, ',')) {
            // Xóa khoảng trắng thừa nếu có
            token.erase(0, token.find_first_not_of(' '));
            token.erase(token.find_last_not_of(' ') + 1);

            if (token == subString) {
                return true;
            }
        }
        return false;
    }


    //kiem tra chuoi nhap vao co phai chuoi so hay khong
    bool isNumeric(const std::string& str) {
        for (char c : str) {
            if (c < '0' || c > '9') {
                return false;
            }
        }
        return !str.empty(); // Đảm bảo chuỗi không rỗng
    }




    //kiẻm tra ngay co hop le theo đúng định dang 
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    bool isValidDate(int day, int month, int year) {
        if (year < 0) return false;  // Không giới hạn năm nhưng đảm bảo năm là số dương
        if (month < 1 || month > 12) return false;

        int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if (month == 2 && isLeapYear(year)) {  // Kiểm tra năm nhuận cho tháng 2
            daysInMonth[1] = 29;
        }

        return day >= 1 && day <= daysInMonth[month - 1];
    }
    bool isDateFormat(const std::string& date) {
        // Kiểm tra độ dài chuỗi phải là 10 ký tự (dd/mm/yyyy)
        if (date.size() != 10) return false;

        // Kiểm tra ký tự phân cách '/' ở vị trí thứ 3 và thứ 6
        if (date[2] != '/' || date[5] != '/') return false;

        // Kiểm tra các ký tự còn lại là số
        for (int i = 0; i < date.size(); ++i) {
            if ((i != 2 && i != 5) && (date[i] < '0' || date[i] > '9')) {
                return false;
            }
        }

        // Lấy ngày, tháng, và năm từ chuỗi
        int day = std::stoi(date.substr(0, 2));
        int month = std::stoi(date.substr(3, 2));
        int year = std::stoi(date.substr(6, 4));

        // Kiểm tra tính hợp lệ của ngày, tháng, và năm
        return isValidDate(day, month, year);
    }


    //kiem tra gio nhap vao có nam trong gio lam viec cua bac si khong
    // Hàm chuyển đổi chuỗi thời gian "hh:mm" sang số phút kể từ 00:00
    int convertToMinutes(const std::string& time) {
        int hours, minutes;
        char colon;
        std::istringstream(time) >> hours >> colon >> minutes;
        return hours * 60 + minutes;
    }

    // Hàm kiểm tra xem inputTime có nằm giữa startTime và endTime không, và không phải "12:00" hay "12:30"
    bool isTimeInRange(const std::string& inputTime, const std::string& startTime, const std::string& endTime) {
        // Điều kiện loại trừ cho "12:00" và "12:30"
        if (inputTime == "12:00" || inputTime == "12:30") {
            return false;
        }

        // Chuyển đổi tất cả thời gian sang phút
        int inputMinutes = convertToMinutes(inputTime);
        int startMinutes = convertToMinutes(startTime);
        int endMinutes = convertToMinutes(endTime);

        // Kiểm tra xem inputTime có nằm giữa startTime và endTime không
        return (inputMinutes >= startMinutes && inputMinutes <= endMinutes);
    }

};


#endif