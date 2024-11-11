#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Menu.h"
#include "Box.h"
#include "Setcolor.h"
#include "Schedule.h"
#include "DoctorSchedule.h"
#include "User.h"
#include "Patient.h"
using namespace std;



//mot so ham bo tro cho Make appointment
static int displayDoctorList(LinkedList<Doctor>& doctors, Patient& patient,LinkedList<Doctor_Schedule>& Infor) {
    patient.drawTableChooseDoctor(20, 7, doctors.length());
    patient.fillDoctorDetails(doctors,Infor, 20, 7);

    gotoxy(35, 1);
    cout << "Choose X to View Doctor Information";
    vector<string> MakeAppt;
    int count = 0;
    for (int i = 0; i < doctors.length(); i++) {
        MakeAppt.push_back(" X");
    }
    MenuBox MakeAppts(8, 9, 2, 4, 11, 1, 203, MakeAppt);
    int choose = MakeAppts.menu() - 1;
    return choose;
}

static void displayDoctorSpecialty(const LinkedList<Doctor>& doctors, LinkedList<Doctor>& result, User& user) {
    LinkedList<string> specialtys;

    // Duyệt qua danh sách bác sĩ để lọc các chuyên khoa duy nhất
    for (int i = 0; i < doctors.length(); i++) {
        Doctor& doctor = doctors.get(i);
        string currentSpecialty = doctor.getSpecialty();

        bool exists = false;
        for (int j = 0; j < specialtys.length(); j++) {
            if (specialtys.get(j) == currentSpecialty) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            specialtys.addLast(currentSpecialty);
        }
    }

    // Chuyển từ LinkedList sang vector để hiển thị trong MenuBox
    vector<string> Content1;
    for (int i = 0; i < specialtys.length(); i++) {
        Content1.push_back(specialtys.get(i));
    }

    // Hiển thị MenuBox để người dùng chọn chuyên khoa
    MenuBox menu(65, 10, 2, 20, 11, 1, 203, Content1);
    int choose = menu.menu() - 1;

    // Kiểm tra lựa chọn hợp lệ
    if (choose < 0 || choose >= Content1.size()) {
        std::cerr << "Invalid choice." << std::endl;
        return; // Trả về danh sách rỗng nếu lựa chọn không hợp lệ
    }

    string specialty = Content1[choose];

    // Lọc danh sách bác sĩ theo chuyên khoa được chọn
    for (int i = 0; i < doctors.length(); i++) {
        Doctor& doctor = doctors.get(i);
        if (doctor.getSpecialty() == specialty) {
            result.addLast(doctor);
        }
    }


    // Hiển thị menu xác nhận
    system("cls");
    gotoxy(62, 15);
    Setcolor(11);
    std::cout << "Are you sure about your action?";
    Setcolor(15);
    vector<string> confirm = { "Exit", "Confirm" };
    MenuBox Confirm(63, 19, 2, 12, 14, 1, 203, confirm);
    int chosen = Confirm.menu2();

    if (chosen == 2) { 
        return;
    }
    else if(chosen ==1) {
        PatientMenu::makeAppointment(user);
    }
    return;
}

static void Func_MakeAppt(const LinkedList<Doctor>& doctors,LinkedList<Doctor>& result,LinkedList<Doctor_Schedule>& doctorSchedules,User& user) {
retry:
    system("cls");
    Setcolor(11);
    gotoxy(58, 7);
    cout << "C H O O S E   F U N C T I O N";
    Setcolor(15);
    vector<string> Contents = { "1. Search doctor by name","2. Search doctor by specialty","3. Search doctor by date and specialty","4. Sort doctors by name","5. View All Doctor","Exit to Menu"};
    MenuBox Menu(50, 10, 2, 45, 14, 1, 203, Contents);
    int choose = Menu.menu();
    Schedule schedule;
    //---------Menu lua chon thoat vong lap--------------//
    vector<string> confirm = { "Back","Confirm" };
    MenuBox Confirm(63, 20, 2, 12, 14, 1, 203, confirm);



    //---------ham thuc hien cac chuc nang lua chon-----------//
    string name,date,time;
    int choose1 = 0, choose2 = 0, choose3 = 0;
    bool Check1 = false, Check2 = false, Check3 = false, Check4 = false;
    Showcur(true);
   
    if(choose == 1) {
        do {
            system("cls");
            if (Check1) {
                Setcolor(12);
                gotoxy(65, 16);
                cout << "(Name not found!)";
                Setcolor(15);
            }
            gotoxy(60, 15);
            cout << "Enter Name Doctor: ";
            gotoxy(79, 15);
            cout << "                            ";
            gotoxy(79, 15);
            getline(cin, name);
            result = schedule.searchDoctorByName(doctors, name);
            Check1 = true;
            system("cls");
        } while (result.length() == 0);
        gotoxy(65, 15);
        Setcolor(11);
        cout << "You Sure Your Action?";
        Setcolor(15);
        choose1 = Confirm.menu2();
        if (choose1 == 1) {
            goto retry;
        }
        else {
            return;
        }
    }
    if (choose == 2) {
        displayDoctorSpecialty(doctors, result, user);
        if (result.length() == 0) {
            cout << "Error!<" << endl;
            PatientMenu::menu(user);
        }
        return;
    }
    if (choose == 3) {
        displayDoctorSpecialty(doctors, result, user);


        //Nhap Ngay va gio
        system("cls");
        Setcolor(14);
        gotoxy(45, 15);
        cout << "Choose Day:";
        gotoxy(83, 15);
        cout << "Choose Time:";
        Setcolor(15);

        Showcur(true);
        do {
            gotoxy(57, 15);
            cout << "                   ";
            gotoxy(57, 15);
            getline(cin, date);

            if (!schedule.isDateFormat(date)) {
                Setcolor(12);
                gotoxy(45, 16);
                cout << "True Fomat (dd/mm/yyyy)!";
                Setcolor(15);
                continue;
            }

            // Kiểm tra xem ngày có hợp lệ cho đặt lịch không
            if (!schedule.CheckTime_MakeAppts(date)) {
                gotoxy(35, 17);
                cout << "Date is not available for appointments!";
                continue;
            }
            Check3 = true;
        } while (Check3==false);

        do {
            gotoxy(96, 15);
            cout << "             ";
            gotoxy(96, 15);
            getline(cin, time);
            if (!schedule.isValidTimeFormat(time)) {
                Setcolor(12);
                gotoxy(83, 16);
                cout << "True Fomat (xx::yy)!";
                Setcolor(15);
                continue;
            }
            Check4 = true;
        } while (Check4==false);

        Showcur(false);


        gotoxy(65, 18);
        Setcolor(11);
        cout << "You Sure Your Action?";
        Setcolor(15);
        choose1 = Confirm.menu2();
        if (choose1 == 1) {
            goto retry;
        }
        else {
            if (result.length() == 0) {
                cout << "Have no doctor!";
                return;
            }

            int day = 0, month = 0, year = 0;
            schedule.extractDateFromString(date, day, month, year);
            string week = schedule.findDayOfWeek(day, month, year);

            int i = 0;
            while (i < result.length()) {
                Doctor_Schedule* DrInfor = nullptr;

                // Tìm thông tin lịch trình của bác sĩ
                for (int j = 0; j < doctorSchedules.length(); j++) {
                    DrInfor = schedule.findScheduleDoctor(result.get(i).getID(), doctorSchedules);

                    if (DrInfor != nullptr &&
                        schedule.containsSubstring(DrInfor->getSchedule(), week) &&
                        schedule.isTimeInRange(time, DrInfor->getTime_Start(), DrInfor->getTime_End())) {
                        break; 
                    }
                }

                // Kiểm tra nếu không tìm thấy hoặc không thỏa mãn điều kiện, xóa bác sĩ khỏi kết quả
                if (DrInfor == nullptr ||
                    !schedule.containsSubstring(DrInfor->getSchedule(), week) ||
                    !schedule.isTimeInRange(time, DrInfor->getTime_Start(), DrInfor->getTime_End())||!schedule.CheckAppointment(time,*DrInfor)) {
                    result.removeAtIndex(i); // Xóa bác sĩ không thỏa mãn điều kiện
                }
                else {
                    i++; 
                }
            }

            //------Thuc hien chuc nang---------//
        }
    }
    if (choose == 4) {
        result = doctors;
        result.sortByName();
        return;
    }


    if (choose == 5) {
        result = doctors;
        return;
    }
    if(choose == 6){
        PatientMenu::menu(user);
        return;
    }

}






//Menu lua chon login hoac signup
void PatientMenu::Main() {
    system("cls");
    ifstream inFile("../PBL2_BKDN/Patient.txt");
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();

    vector<string>PatientData;
    PatientData.push_back("Login");
    PatientData.push_back("SignUp");
    PatientData.push_back("Back");

    MenuBox PatientBOX(PatientData);
    int choose = PatientBOX.menu2();
    switch (choose)
    {
    case 1:
    {
        PatientMenu::login();
        system("pause");
        break;
    }

    case 2:
    {
        PatientMenu::signUp();
        system("pause");
        break;
    }

    case 3:
        Home::menu();
        break;
    }
}

//ham login
void PatientMenu::login() {
    Nhan1:
    system("cls");
    Setcolor(15);
    ifstream inFile("../PBL2_BKDN/Patient_login.txt");
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();
    cout << endl << endl << endl;
    //Tao table
    vector<string> Login2 = { "Username: ","Password: " };
    vector<string> Login3 = { "Try again","Back"};
    MenuBox MenuLogin(Login2);
    MenuLogin.box(51, 10, 12, 31, 3, 203, " ");
    MenuLogin.boxes(53,14,2,27,3,203,Login2);
    gotoxy(63, 12); cout << "LOGIN NOW";
    //Dang nhap
    Schedule systemSchedule;
    string username, password;
    Showcur(true);
    gotoxy(63, 15);
    getline(cin, username);
    gotoxy(63, 17);
    getline(cin, password);
    Showcur(false);
    gotoxy(50, 25);
    if (!systemSchedule.login(username, password, "../PBL2_BKDN/User_infor.txt", systemSchedule.isPatient)) {
        system("pause");
        MenuBox MenuLogin2(53,19,2,13,3,11,203,Login3);
        int choose = MenuLogin2.menu2();
        if (choose == 2) {
            PatientMenu::Main();
        }
        else if (choose == 1) {
            goto Nhan1;
        }
        /* -------- Nhap sai thi cho nhap lai hoac lua chon signup --------*/
    }
    else {
        system("pause");
        User* user = systemSchedule.findUser(username, password);
        PatientMenu::menu(*user);
    }
}

//ham signUp
void PatientMenu::signUp() {
    Nhan1:
    system("cls");
    ifstream inFile("../PBL2_BKDN/Patient_SignUp.txt");
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    cout << endl << endl << endl;
    // ve table 
    vector<string> Login2 = { "Username: ","Password: ","Confirm:"};
    vector<string> Login3 = { "Try again","Back" };
    
    MenuBox MenuSignup(Login2);
    MenuSignup.box(51, 10, 15, 31, 3, 203, " ");
    MenuSignup.boxes(53, 14, 2, 27, 3, 203, Login2);
    gotoxy(62, 12); cout << "SIGNUP NOW";

    //Tao tai khoan
    Schedule systemSchedule;
    string username, password, confirm;
    LinkedList<User> users;
    int newID = systemSchedule.getnewIDforPatient("../PBL2_BKDN/User_infor.txt", users);
    

    //Nhap thong tin
    Showcur(true);
    gotoxy(63, 15);
    getline(cin, username);
    gotoxy(63, 17);
    getline(cin, password);
    gotoxy(62, 19);
    getline(cin, confirm);
    Showcur(false);
    gotoxy(45, 28);


    User user(username, password, newID);
    if (password == confirm && systemSchedule.signUp(user, "../PBL2_BKDN/User_infor.txt", users)) {
        gotoxy(57, 28);
        cout << "Sign up successful!" << endl;
    }
    else {
        if (password != confirm) {
            cout << "Passwords do not match. Please try again!" << endl;
        }
        else {
            cout << "Username already exists. Please choose another one." << endl;
        }
        system("pause");
        MenuBox MenuSignup2(53, 21, 2, 13, 3, 11, 203, Login3);
        int choose = MenuSignup2.menu2();
        if (choose == 2) {
            PatientMenu::Main();
        }
        else if (choose == 1) {
            goto Nhan1;
        }
    }
    system("pause");
    Schedule schedule;
    User* user1 = schedule.findUser(username, password);

    PatientMenu::menu(*user1);
    
}
//ham in ra cac lua chon chuc nang sau khi login
int PatientMenu::printTask() {
    system("cls");
    ifstream inFile("../PBL2_BKDN/Patient_Function.txt");
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();

    vector<string> Content;
    Content.push_back("1.View Appointment");
    Content.push_back("2.Make Appointment");
    Content.push_back("3.Cancle Appointment");
    Content.push_back("4.View My Information");
    Content.push_back("5.Update My Infomation");
    Content.push_back("6.Change Password");
    Content.push_back("7.Sign out");

    MenuBox PatientMenu(35, 7, 2, 30, 11, 1, 203, Content);
    int choose = PatientMenu.menu2();

    return choose;
}

void PatientMenu::menu(User& user) {
    int choose = PatientMenu::printTask();
    switch (choose) {
    case 1:
        PatientMenu::viewAppointment(user);
        break;
    case 2:
        PatientMenu::makeAppointment(user);
        break;

    case 3:
        PatientMenu::cancelAppointment(user);
        break;

    case 4:
        PatientMenu::viewMyInfornation(user);
        break;

    case 5:
        PatientMenu::updateInformation(user);
        break;
    case 6:
        PatientMenu::changePassword(user);      
        break;

    case 7:
        system("cls");
        Home::menu();;
        break;
    }
}

//cac FUNCTION cua Patient
void PatientMenu::viewAppointment(User& user) {
    Schedule* schedule = new Schedule();  // Tạo đối tượng Schedule
    Patient* patient = schedule->findPatientByID(user.getID());  // Tìm bệnh nhân dựa trên ID người dùng

    // Kiểm tra xem có bệnh nhân hợp lệ hay không
    if (patient == nullptr) {
        gotoxy(65, 25);
        cout << "User has no appointment";
        system("pause");
        delete schedule;  // Giải phóng bộ nhớ cho schedule
        PatientMenu::menu(user);  // Quay lại menu chính
        return;
    }

    LinkedList<Appointment>& allAppointments = schedule->getAllAppointments();  // Lấy tất cả các cuộc hẹn
    LinkedList<Appointment> patientAppointments;  // Danh sách cuộc hẹn của bệnh nhân

    // Duyệt qua tất cả các cuộc hẹn và lọc ra những cuộc hẹn của bệnh nhân hiện tại
    for (int i = 0; i < allAppointments.length(); i++) {
        if (patient->getID() == allAppointments.get(i).getPatient_ID()) {
            patientAppointments.addLast(allAppointments.get(i));
        }
    }

    // Kiểm tra nếu bệnh nhân không có cuộc hẹn nào
    if (patientAppointments.length() == 0) {
        cout << "No appointments found for this patient.";
        system("pause");
        delete schedule;  // Giải phóng bộ nhớ cho schedule
        PatientMenu::menu(user);  // Quay lại menu chính
        return;
    }

    // Vẽ bảng và điền thông tin cuộc hẹn cho bệnh nhân
    patient->drawTablePatient(15, 7, patientAppointments.length());
    patient->fillAppointmentDetailsForPatient(patientAppointments, 15, 7);

    // Hiển thị bảng và tạm dừng hệ thống
    gotoxy(65, 38);
    system("pause");

    // Giải phóng bộ nhớ và quay lại menu chính
    delete schedule;
    PatientMenu::menu(user);
}

void PatientMenu::makeAppointment(User& user) {
    Schedule *schedule = new Schedule();  // Tạo đối tượng Schedule cục bộ
    Patient* patient = schedule->findPatientByID(user.getID());  // Tìm bệnh nhân dựa trên ID người dùng

    if (patient == nullptr) {
        gotoxy(55, 5);
        cout << "You must update your Information!";
        system("pause");
        delete schedule;
        PatientMenu::menu(user);  // Quay lại menu chính
        return;
    }

    LinkedList<Doctor> doctortmp = schedule->getAllDoctors();
    LinkedList<Doctor_Schedule> doctorSchedules;
    schedule->loadDoctor_Schedule("../PBL2_BKDN/Doctor_Schedule.txt", doctorSchedules);
    //----------------Show ra cac ham chuc nang-------------------//
    system("cls");
    LinkedList<Doctor> doctors;
    Func_MakeAppt(doctortmp,doctors,doctorSchedules, user);
    
    system("cls");
    if (doctors.length() == 0) {
        gotoxy(65, 15);
        cout << "Have no doctor in your choose!" << endl;
        system("pause");
        PatientMenu::menu(user);
    }


    //----------------Show ra cac ham chuc nang-------------------//


    int choose = displayDoctorList(doctors, *patient, doctorSchedules);

    if (choose < 0 || choose >= doctors.length()) {
        cout << "Invalid selection. Please try again." << endl;
        system("pause");
        delete schedule;
        PatientMenu::menu(user);
        return;
    }

    Doctor& doctor = doctors.get(choose);
    Doctor_Schedule* DrSchedule = schedule->findScheduleDoctor(doctor.getID(), doctorSchedules);

    if (DrSchedule == nullptr) {
        cout << "No schedule found for the selected doctor." << endl;
        system("pause");
        delete schedule;
        PatientMenu::menu(user);
        return;
    }
    LinkedList<Appointment> appointments = schedule->getAllAppointments();
    Showcur(true);
    system("cls");
    DrSchedule->displayDoctorInfo();
    string date;
    string timeSlot;
    gotoxy(65, 25);
    cout << "Choose Date: ";
    bool Check = false;
    do {
        gotoxy(77, 25);
        cout << "                   ";
        gotoxy(77, 25);
        getline(cin, date);

        // Kiểm tra xem chuỗi có phải là định dạng ngày hợp lệ không
        if (!schedule->isDateFormat(date)) {
            gotoxy(52, 26);
            cout << "Invalid date format! Please enter in format dd/MM/yyyy";
            continue; // Yêu cầu người dùng nhập lại
        }

        // Kiểm tra xem ngày có hợp lệ cho đặt lịch không
        if (!schedule->CheckTime_MakeAppts(date)) {
            gotoxy(52, 26);
            cout << "Date is not available for appointments!";
            continue; // Yêu cầu người dùng nhập lại
        }

        // Lấy slot thời gian dựa trên ngày hợp lệ
        timeSlot = DrSchedule->Table_Time(date, doctor, appointments);
        if (timeSlot != "ERROR!") {
            Check = true;
        }

    } while (Check == false);
    int newID = schedule->getnewIDforAppointment(appointments);
    Showcur(false);
    //Chon phong
    LinkedList <Clinic_Room> rooms = schedule->getAllClinicRooms();
    string roomType;
    int roomID = 0;
    for (int i = 0; i < rooms.length(); i++) {
        if (rooms.get(i).getRoomType() == doctor.getSpecialty() && schedule->CheckAvailability(date, timeSlot, appointments, rooms.get(i).getRoomID())) {
            roomID = rooms.get(i).getRoomID();
            roomType = rooms.get(i).getRoomType();     
            break;
        }
    }
    if (roomID!=0) {
        Appointment newAppointment(newID, user.getID(), DrSchedule->getDoctorID(), roomID, date, timeSlot, doctor.getName(), patient->getName(), roomType);
        appointments.addLast(newAppointment);
        schedule->saveAppointments("../PBL2_BKDN/Appt_infor.txt", appointments);
        gotoxy(65, 32);
        cout << "Appointment scheduled successfully!" << endl;
        system("pause");
        delete schedule;
        PatientMenu::menu(user);  // Quay lại menu chính
    }
    else {
        system("cls");
        gotoxy(65, 32);
        cout << "Have no Rooms available!" << endl;
        system("pause");
        delete schedule;
        PatientMenu::menu(user);
    }
}

void PatientMenu::cancelAppointment(User& user) {
    Schedule* schedule = new Schedule();  // Tạo đối tượng Schedule
    Patient* patient = schedule->findPatientByID(user.getID());  // Tìm bệnh nhân dựa trên ID người dùng

    // Kiểm tra xem có bệnh nhân hợp lệ hay không
    if (patient == nullptr) {
        cout << "User has no appointment";
        system("pause");
        delete schedule;  // Giải phóng bộ nhớ cho schedule
        PatientMenu::menu(user);  // Quay lại menu chính
        return;
    }

    LinkedList<Appointment>& allAppointments = schedule->getAllAppointments();  // Lấy tất cả các cuộc hẹn
    LinkedList<Appointment> patientAppointments;  // Danh sách cuộc hẹn của bệnh nhân

    // Duyệt qua tất cả các cuộc hẹn và lọc ra những cuộc hẹn của bệnh nhân hiện tại
    for (int i = 0; i < allAppointments.length(); i++) {
        if (patient->getID() == allAppointments.get(i).getPatient_ID() && allAppointments.get(i).getStatus() == "Schedule") {
            patientAppointments.addLast(allAppointments.get(i));
        }
    }

    // Kiểm tra nếu bệnh nhân không có cuộc hẹn nào
    if (patientAppointments.length() == 0) {
        cout << "No appointments found for this patient.";
        system("pause");
        delete schedule;  // Giải phóng bộ nhớ cho schedule
        PatientMenu::menu(user);  // Quay lại menu chính
        return;
    }

    // Vẽ bảng và điền thông tin cuộc hẹn cho bệnh nhân
    patient->drawTablePatient(15, 7, patientAppointments.length());
    patient->fillAppointmentDetailsForPatient(patientAppointments, 15, 7);

    //ve bang chon X
    vector<string> Cancle;
    int count = 0;
    for (int i = 0; i < patientAppointments.length(); i++) {
        Cancle.push_back(" X");  
        count++;
    }
    gotoxy(35, 1);
    cout << "Choose your Appointment you want to cancle!";

    MenuBox CancleAppt(8, 9, 2, 4, 11, 1, 203, Cancle);
    int choose = CancleAppt.menu() - 1;
    vector<string> Confirm = { "   Back","  Confirm" };
    MenuBox CancleAppt2(65, 10, 2, 14, 11, 1, 203, Confirm);
    int chosen = CancleAppt2.menu2();

    if (chosen == 2) {
        schedule->cancelAppointment(patientAppointments.get(choose).getPatient_ID(), patientAppointments.get(choose).getDate(), patientAppointments.get(choose).getTime());
        schedule->saveAppointments("../PBL2_BKDN/Appt_infor.txt", schedule->getAllAppointments());
        gotoxy(65, 27);
        cout << "Cancle Appointment is successfull!" << endl;
        system("pause");
        delete schedule;
        PatientMenu::menu(user);
    }
    else if (chosen == 2) {
        PatientMenu::menu(user);
    }
}

void PatientMenu::viewMyInfornation(User& user) {
    system("cls");
    Schedule* schedule = new Schedule();
    Patient* patient = schedule->findPatientByID(user.getID());
    if (patient == nullptr) {
        gotoxy(50, 10);
        cout <<"User name: "<< user.getUsername();
        gotoxy(50, 12);
        cout << "Your Information is empty!";
        gotoxy(50, 28);
        system("pause");
        PatientMenu::menu(user);
        delete(patient);
    }
    else {
        Setcolor(14);
        gotoxy(50, 11);      cout << "+-----------------------------------------+" << endl;
        gotoxy(50, 12);      cout << "|            YOUR INFORMATION             |" << endl;
        gotoxy(50, 13);      cout << "+-----------------------------------------+" << endl;
        gotoxy(50, 14);      cout << "|  Username       :                       |" << endl;
        gotoxy(50, 15);      cout << "|-----------------------------------------|" << endl;
        gotoxy(50, 16);      cout << "|  Full Name      :                       |" << endl;
        gotoxy(50, 17);      cout << "|-----------------------------------------|" << endl;
        gotoxy(50, 18);      cout << "|  Birth Date     :                       |" << endl;
        gotoxy(50, 19);      cout << "|-----------------------------------------|" << endl;
        gotoxy(50, 20);      cout << "|  Gender         :                       |" << endl;
        gotoxy(50, 21);      cout << "|-----------------------------------------|" << endl;
        gotoxy(50, 22);      cout << "|  Phone Number   :                       |" << endl;
        gotoxy(50, 23);      cout << "|-----------------------------------------|" << endl;
        gotoxy(50, 24);      cout << "|  Address        :                       |" << endl;
        gotoxy(50, 25);      cout << "+-----------------------------------------+" << endl;
        Setcolor(15);
        gotoxy(70, 14);
        cout<<patient->getUsername();
        gotoxy(70, 16);
        cout << patient->getName();
        gotoxy(70, 18);
        cout << patient->getDateOfBirth();
        gotoxy(70, 20);
        cout << patient->getGender();
        gotoxy(70, 22);
        cout << patient->getPhoneNumber();
        gotoxy(70, 24);
        cout << patient->getAddress();
        gotoxy(55, 29);
        system("pause");
        PatientMenu::menu(user);
    }
}

void PatientMenu::updateInformation(User& user) {
    Schedule* System = new Schedule();
    Patient* patient = System->findPatientByID(user.getID());

    // Nếu thông tin chưa được lưu trước đó, tạo Patient mới
    if (patient == nullptr) {
        Nhan1:
        vector<string> Content2 = { "Full name:","Birthday:","Gender:","Address:","Phonenumber:" };
        MenuBox UpdateInf(Content2);
        UpdateInf.box(51, 10, 20, 41, 3, 203, " ");
        UpdateInf.boxes(53, 14, 2, 37, 3, 203, Content2);
        gotoxy(64, 12);
        cout << "YOUR INFORMATION";

        // Nhập thông tin
        string name, birthday, gender, address, phone;
        Showcur(true); // Hiển thị con trỏ chuột

        //Nhap Name
        gotoxy(65, 15); getline(cin, name);

        //Nhap Birthday
        int count1 = 0;
        do {
            if (count1 == 1) {
                Setcolor(12);
                gotoxy(94, 17);
                cout << "True Fomat (dd/mm/yy)";
                Setcolor(15);
            }
            gotoxy(63, 17);
            cout << "               ";
            gotoxy(63, 17);
            getline(cin, birthday);
            count1 = 1;
        } while (!System->isDateFormat(birthday));

        //Nhap gioi tinh
        int count2 = 0;
        do {
            if (count2 == 1) {
                Setcolor(12);
                gotoxy(94, 19);
                cout << "(Male/Female)";
                Setcolor(15);
            }
            gotoxy(61, 19);
            cout << "                     ";
            gotoxy(61, 19);
            getline(cin, gender);
            count2 = 1;
        } while (gender != "Male" && gender != "Female");

        //Nhap dia chi
        gotoxy(62, 21); getline(cin, address);

        //Nhap so dt
        int count3 = 0;
        do {
            if (count3 == 1) {
                Setcolor(12);
                gotoxy(93, 23);
                cout << "(Phonemunber not found!)";
                Setcolor(15);
            }
            gotoxy(66, 23);
            cout << "               ";
            gotoxy(66, 23);
            getline(cin, phone);

            count3 = 1;
        } while (!System->isNumeric(phone));


        Showcur(false); // Ẩn con trỏ chuột

        // Hiển thị menu xác nhận
        gotoxy(54, 25);
        vector<string> Items = { "Try again", "Confirm" };
        MenuBox Menu(58, 26, 2, 13, 3, 11, 203, Items);
        int choose = Menu.menu2();

        if (choose == 2) { // Người dùng xác nhận
            // Tạo bệnh nhân mới và thêm vào hệ thống
            Patient* newPatient = new Patient(name, birthday, gender, address, phone, user.getUsername(), user.getPassword(), user.getID());
            System->addPatient(*newPatient);
            System->savePatients("../PBL2_BKDN/Patient_infor.txt", System->getAllPatients());
            cout << "Information saved successfully!" << endl;
            delete newPatient; // Giải phóng bộ nhớ
            PatientMenu::menu(user); // Quay lại menu
        }
        else if (choose == 1) {
            goto Nhan1; // Thử lại nếu người dùng chọn "Try again"
        }

    }
    else {
        // Nếu thông tin bệnh nhân đã tồn tại, hiển thị tùy chọn cập nhật
        vector<string> Content = { "Change Full name", "Change Birthday", "Change Gender", "Change Address", "Change Phonenumber","Update All", "Back"};
        vector<string> Items = { "Try again", "Confirm" };
        MenuBox Menu(55, 18, 2, 13, 3, 11, 203, Items);

        MenuBox UpdateOptions(Content);

        bool updated = false; // Biến theo dõi nếu có thay đổi thông tin
        int option = UpdateOptions.menu2();
        Showcur(true); // Hiển thị con trỏ chuột

        if (option == 1) {
            Update1:
            system("cls");
            // Thay đổi tên
            Setcolor(203);
            gotoxy(51, 15);
            cout << "New Full Name:";
            Setcolor(15);
            gotoxy(65, 15);
            string name;
            getline(cin, name);
            patient->setName(name);
            int choose = Menu.menu2();
            if (choose == 1) {
                goto Update1;
            }
            else if (choose == 2) {
                updated = true;
            }
        }
        else if (option == 2) {
            // Thay đổi ngày sinh
            Update2:
            system("cls");
            Setcolor(203);
            gotoxy(52, 15);
            cout << "New Birthday:";
            Setcolor(15);
            string birthday;
            
            //chay den khi nhap ngay hop le
            int count = 0;
            do {
                if (count == 1) {
                    Setcolor(12);
                    gotoxy(52, 16);
                    cout << "True Fomat (dd/mm/yy)";
                    Setcolor(15);
                }
                gotoxy(65, 15);
                cout << "                  ";
                gotoxy(65, 15);
                getline(cin, birthday);
                count = 1;
            } while (!System->isDateFormat(birthday));
            patient->setDateOfBirth(birthday);
            int choose = Menu.menu2();
            if (choose == 1) {
                goto Update2;
            }
            else if (choose == 2) {
                updated = true;
            }
        }
        else if (option == 3) {
            // Thay đổi giới tính
            Update3:
            system("cls");
            Setcolor(203);
            gotoxy(54, 15);
            cout << "New Gender:";
            Setcolor(15);
            string gender;
            int count = 0;
            do {
                if (count == 1) {
                    Setcolor(12);
                    gotoxy(54, 16);
                    cout << "(Male/Female)";
                    Setcolor(15);
                }
                gotoxy(65, 15);
                cout << "                     ";
                gotoxy(65, 15);
                getline(cin, gender);
                count = 1;
            } while (gender != "Male" && gender != "Female");
            patient->setGender(gender);
            int choose = Menu.menu2();
            if (choose == 1) {
                goto Update3 ;
            }
            else if (choose == 2) {
                updated = true;
            }
        }
        else if (option == 4) {
            // Thay đổi địa chỉ
        Update4:
            system("cls");
            Setcolor(203);
            gotoxy(53, 15);
            cout << "New Address:";
            Setcolor(15);
            gotoxy(65, 21);
            string address;
            getline(cin, address);
            patient->setAddress(address);
            int choose = Menu.menu2();
            if (choose == 1) {
                goto Update4;
            }
            else if (choose == 2) {
                updated = true;
            }
        }
        else if (option == 5) {
            // Thay đổi số điện thoại
            Update5:
            Setcolor(203);
            gotoxy(49, 15);
            cout << "New PhoneNumber:";
            Setcolor(15);
            string phone;
            int count = 0;
            do {
                if (count == 1) {
                    Setcolor(12);
                    gotoxy(49, 16);
                    cout << "(Phonemunber not found!)";
                    Setcolor(15);
                }
                gotoxy(65, 15);
                cout << "                 ";
                gotoxy(65, 15);
                getline(cin, phone);
                count = 1;
            } while (!System->isNumeric(phone));
            patient->setPhoneNumber(phone);
            int choose = Menu.menu2();
            if (choose == 1) {
                goto Update5;
            }
            else if (choose == 2) {
                updated = true;
            }
        }
        else if (option == 6) {
        Update6:
            vector<string> Content2 = { "Full name:","Birthday:","Gender:","Address:","Phonenumber:" };
            MenuBox UpdateInf(Content2);
            UpdateInf.box(51, 10, 20, 41, 3, 203, " ");
            UpdateInf.boxes(53, 14, 2, 37, 3, 203, Content2);
            gotoxy(64, 12);
            cout << "YOUR INFORMATION";

            // Nhập thông tin
            string name, birthday, gender, address, phone;
            Showcur(true); // Hiển thị con trỏ chuột

            //Nhap Name
            gotoxy(65, 15); getline(cin, name);

            //Nhap Birthday
            int count1 = 0;
            do {
                if (count1 == 1) {
                    Setcolor(12);
                    gotoxy(94, 17);
                    cout << "True Fomat (dd/mm/yy)";
                    Setcolor(15);
                }
                gotoxy(63, 17);
                cout << "               ";
                gotoxy(63, 17);
                getline(cin, birthday);
                count1 = 1;
            } while (!System->isDateFormat(birthday));
            
            //Nhap gioi tinh
            int count2 = 0;
            do {
                if (count2 == 1) {
                    Setcolor(12);
                    gotoxy(94, 19);
                    cout << "(Male/Female)";
                    Setcolor(15);
                }
                gotoxy(61, 19);
                cout << "                     ";
                gotoxy(61, 19);
                getline(cin, gender);
                count2 = 1;
            } while (gender != "Male" && gender != "Female");

            //Nhap dia chi
            gotoxy(62, 21); getline(cin, address);
            
            //Nhap so dt
            int count3 = 0;
            do {
                if (count3 == 1) {
                    Setcolor(12);
                    gotoxy(93, 23);
                    cout << "(Phonemunber not found!)";
                    Setcolor(15);
                }
                gotoxy(66, 23);
                cout << "               ";
                gotoxy(66, 23);
                getline(cin, phone);

                count3 = 1;
            } while (!System->isNumeric(phone));


            Showcur(false); // Ẩn con trỏ chuột

            // Hiển thị menu xác nhận
            gotoxy(54, 25);
            vector<string> Items = { "Try again", "Confirm" };
            MenuBox Menu(58, 26, 2, 13, 3, 11, 203, Items);
            int choose = Menu.menu2();

            if (choose == 2) { // Người dùng xác nhận
                patient->setName(name);
                patient->setDateOfBirth(birthday);
                patient->setGender(gender);
                patient->setAddress(address);
                patient->setPhoneNumber(phone);

                updated = true;               
            }
            else if (choose == 1) {
                goto Update6; // Thử lại nếu người dùng chọn "Try again"
            }

        }
        else if (option == 7) {
            // Quay lại mà không thay đổi gì
            PatientMenu::menu(user);
            return;
        }

        Showcur(false); // Ẩn con trỏ chuột sau khi nhập

        if (updated) {
            // Nếu có thay đổi thông tin, lưu lại và quay lại menu
            System->savePatients("../PBL2_BKDN/Patient_infor.txt", System->getAllPatients());
            cout << "Information updated successfully!" << endl;
            PatientMenu::menu(user);
        }
    }
}

void PatientMenu::changePassword(User& usern) {
retry:
    system("cls");
    // Vẽ bảng thay đổi mật khẩu
    vector<string> Menu = { "Current Password:", "New Password:", "Confirm Password:" };
    vector<string> Items = { "Try again", "Confirm" };

    MenuBox MenuSignup(Menu);
    MenuSignup.box(51, 10, 15, 41, 3, 203, " ");
    MenuSignup.boxes(53, 14, 2, 37, 3, 203, Menu);

    gotoxy(65, 12);
    cout << "CHANGE PASSWORD";

    // Đọc các thông tin mật khẩu
    Schedule* System = new Schedule();
    Patient* patient = System->findPatientByID(usern.getID());
    User* user = System->findUser(usern.getUsername(), usern.getPassword());

    string CurrPassword, password, confirm;
    Showcur(true);
    gotoxy(72, 15);
    getline(cin, CurrPassword);
    gotoxy(68, 17);
    getline(cin, password);
    gotoxy(72, 19);
    getline(cin, confirm);
    Showcur(false);

    // Kiểm tra mật khẩu hiện tại
    if (usern.getPassword() != CurrPassword) {
        gotoxy(57, 28);
        cout << "Current password is incorrect. Please try again!" << endl;
        system("pause");
        goto retry;  // Sử dụng goto để quay lại nhập lại mật khẩu
    }

    if (confirm != password) {
        gotoxy(57, 28);
        cout << "Passwords do not match. Please try again!" << endl;
        system("pause");
        goto retry;  // Sử dụng goto để quay lại nhập lại mật khẩu
    }

    gotoxy(57, 28);
    if (!System->CheckPassword(password)) {
        system("pause");
        goto retry;  // Sử dụng goto để quay lại nhập lại mật khẩu
    }

    if (patient == nullptr) {
        if (user != nullptr) {
            user->setPassword(password);
        }
        System->saveUsers("../PBL2_BKDN/User_infor.txt", System->getAllUser());
    }
    else {
        // Nếu bệnh nhân tồn tại, cập nhật cả user và bệnh nhân
        user->setPassword(password);
        patient->setPassword(password);
        System->savePatients("../PBL2_BKDN/Patient_infor.txt", System->getAllPatients());
        System->saveUsers("../PBL2_BKDN/User_infor.txt", System->getAllUser());
    }
    gotoxy(54, 21);
    vector<string> Content = { "Try again", "Confirm" };
    MenuBox Menubox(58, 22, 2, 13, 3, 11, 203, Content);
    int choice = Menubox.menu2();

    gotoxy(57, 28);
    cout << "Password changed successfully!" << endl;
    system("pause");

    // Quay về menu chính
    PatientMenu::menu(usern);
}
