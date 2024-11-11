#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Menu.h"
#include "Box.h"
#include "Setcolor.h"
#include "Schedule.h"
#include "DoctorSchedule.h"

using namespace std;


//Menu lua chon login hoac signup
void DoctorMenu::Main() {
	system("cls");
	ifstream inFile("../PBL2_BKDN/Doctor.txt");
	string line;
	while (getline(inFile, line)) {
		cout << line << endl;
	}
	inFile.close();

	//tao content
	vector<string> DoctorData;
	DoctorData.push_back("Login");
	DoctorData.push_back("Back");

	//ve bang
	MenuBox DoctorBox(61,14,2,15,11,1,203,DoctorData);
	int choose = DoctorBox.menu2();
	switch (choose) {
	case 1:
		DoctorMenu::login();
		system("pause");
		break;
	case 2:
		Home::menu();
		break;

	}

}

//ham login
void DoctorMenu::login() {
	Nhan1:
	system("cls");
	Setcolor(15);
	ifstream inFile("../PBL2_BKDN/Doctor_login.txt");
	string line;
	while (getline(inFile, line)) {
		cout << line << endl;
	}
	inFile.close();
	cout << endl << endl << endl;
	//Tao table
	vector<string> Login2 = { "Username: ","Password: " };
	vector<string> Login3 = { "Try again","Back" };
	MenuBox MenuLogin(Login2);
	MenuLogin.box(51, 10, 12, 31, 3, 203, " ");
	MenuLogin.boxes(53, 14, 2, 27, 3, 203, Login2);
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
	if (!systemSchedule.login(username, password, "../PBL2_BKDN/User_infor.txt",systemSchedule.isDotor)) {
		system("pause");
		MenuBox MenuLogin2(53, 19, 2, 13, 3, 11, 203, Login3);
		int choose = MenuLogin2.menu2();
		if (choose == 2) {
			DoctorMenu::Main();
		}
		else if (choose == 1) {
			goto Nhan1;
		}
		/* -------- Nhap sai thi cho nhap lai hoac lua chon signup --------*/
	}
	else {
		system("pause");
		User* user = systemSchedule.findUser(username, password);

		DoctorMenu::menu(*user);
	}
}


//ham in ra cac lua chon chuc nang sau khi login
int DoctorMenu::printTask() {
	system("cls");
	ifstream inFile("../PBL2_BKDN/Doctor_Function.txt");
	string line;
	while (getline(inFile, line)) {
		cout << line << endl;
	}
	inFile.close();

	vector<string> DoctorFunctions;
	DoctorFunctions.push_back("1. View Appointment Schedule");
	DoctorFunctions.push_back("2. Update Appointment Status");
	DoctorFunctions.push_back("3. View Patient Information");
	DoctorFunctions.push_back("4. Update Work Schedule");
	DoctorFunctions.push_back("5. Change My Password");
	DoctorFunctions.push_back("6. Cancle Appointment");
	DoctorFunctions.push_back("7. View My Information");
	DoctorFunctions.push_back("8. Update My Information");
	DoctorFunctions.push_back("9. Sign out");

	MenuBox DoctorMenu(25, 7, 2, 33, 14, 1, 203, DoctorFunctions);
	int choose = DoctorMenu.menu2();

	return choose;

}

void DoctorMenu::menu(User& user) {
	int choose = DoctorMenu::printTask();
	switch (choose) {
	case 1:
		DoctorMenu::viewAppointment(user);
		break;
	case 2:
		DoctorMenu::SetStatusAppointment(user);
		break;
	case 3:
		DoctorMenu::viewPatientAppointment(user);
		break;
	case 4:
		DoctorMenu::UpdateWorkSchedule(user);
		break;
	case 5:
		DoctorMenu::ChangePassword(user);
		break;
	case 6:
		DoctorMenu::CancleAppointment(user);
		break;
	case 7:
		DoctorMenu::viewMyInformation(user);
		break;
	case 8:
		DoctorMenu::updateInformation(user);
	case 9:
		system("cls");
		Home::menu();;
		break;
	}
}

//ham tao switch case thuc hien chuc nang
void DoctorMenu::viewAppointment(User& user) {
	Schedule* schedule = new Schedule();  // Tạo đối tượng Schedule
	Doctor* doctor = schedule->findDoctorByID(user.getID()); 

	if (doctor == nullptr) {
		gotoxy(65, 25);
		cout << "User has no appointment";
		system("pause");
		delete schedule;  // Giải phóng bộ nhớ cho schedule
		DoctorMenu::menu(user);  // Quay lại menu chính
		return;
	}
	LinkedList<Appointment>& allAppointments = schedule->getAllAppointments();  
	LinkedList<Appointment> doctorAppointments;  
	for (int i = 0; i < allAppointments.length(); i++) {
		if (doctor->getID() == allAppointments.get(i).getDoctor_ID()) {
			doctorAppointments.addLast(allAppointments.get(i));
		}
	}
	
	if (doctorAppointments.length() == 0) {
		cout << "No appointments found for this patient.";
		system("pause");
		delete schedule;  
		DoctorMenu::menu(user);  // Quay lại menu chính
		return;
	}
	doctor->drawTablePatient(22, 7, doctorAppointments.length());
	doctor->fillAppointmentDetailsForPatient(doctorAppointments, 22, 7);


	gotoxy(65, 38);
	system("pause");

	// Giải phóng bộ nhớ và quay lại menu chính
	delete schedule;
	DoctorMenu::menu(user);
}

void DoctorMenu:: SetStatusAppointment(User& user) {
	Schedule* schedule = new Schedule();  // Tạo đối tượng Schedule
	Doctor* doctor = schedule->findDoctorByID(user.getID());
	if (doctor == nullptr) {
		gotoxy(65, 25);
		cout << "User has no appointment";
		system("pause");
		delete schedule;  // Giải phóng bộ nhớ cho schedule
		DoctorMenu::menu(user);  // Quay lại menu chính
		return;
	}
	LinkedList<Appointment>& allAppointments = schedule->getAllAppointments();
	LinkedList<Appointment> doctorAppointments;
	for (int i = 0; i < allAppointments.length(); i++) {
		if (doctor->getID() == allAppointments.get(i).getDoctor_ID()&&(allAppointments.get(i).getStatus()=="Schedule"|| allAppointments.get(i).getStatus() == "Continue")) {
			doctorAppointments.addLast(allAppointments.get(i));
		}
	}
	if (doctorAppointments.length() == 0) {
		cout << "No appointments found for this patient.";
		system("pause");
		delete schedule;
		DoctorMenu::menu(user);  // Quay lại menu chính
		return;
	}
	system("cls");
	//ve bang xem appt
	doctor->drawTablePatient(22, 7, doctorAppointments.length());
	doctor->fillAppointmentDetailsForPatient(doctorAppointments, 22, 7);
	//ve bang chon X
	vector<string> Cancle;
	int count = 0;
	for (int i = 0; i < doctorAppointments.length(); i++) {
		Cancle.push_back(" X");
		count++;
	}
	gotoxy(45, 1);
	cout << "Choose your Appointment you want to Set Status";
	MenuBox CancleAppt(8, 9, 2, 4, 11, 1, 203, Cancle);
	int choose = CancleAppt.menu() - 1;

	system("cls");
	gotoxy(55, 15);
	Setcolor(14);
	cout << "New Status for this Appointment: ";
	vector<string> SetST = { "Continue","Finished" };
	MenuBox Set(71, 17, 2, 15, 11, 1, 203, SetST);
	int chosen = Set.menu();
	bool updated = false;
	if (chosen == 1) {
		Appointment *appointment = schedule->findAppointmentByID(doctorAppointments.get(choose).getAppointment_ID());
		if (appointment != nullptr) {
			appointment->setStatus("Continue");
			updated = true;
		}
	}
	else {
		Appointment* appointment = schedule->findAppointmentByID(doctorAppointments.get(choose).getAppointment_ID());
		if (appointment != nullptr) {
			appointment->setStatus("Finished");
			updated = true;
		}
	}
	if (updated) {
		schedule->saveAppointments("../PBL2_BKDN/Appt_infor.txt", allAppointments);
		gotoxy(55, 30);
		cout << "Change Status successful!";
		system("pause");
	}
	DoctorMenu::menu(user);	
}



void DoctorMenu::viewPatientAppointment(User& user) {
	Schedule* schedule = new Schedule();  // Tạo đối tượng Schedule
	Doctor* doctor = schedule->findDoctorByID(user.getID());

	if (doctor == nullptr) {
		gotoxy(65, 25);
		cout << "User has no appointment";
		system("pause");
		delete schedule;  // Giải phóng bộ nhớ cho schedule
		DoctorMenu::menu(user);  // Quay lại menu chính
		return;
	}
	LinkedList<Appointment>& allAppointments = schedule->getAllAppointments();
	LinkedList<Appointment> doctorAppointments;
	for (int i = 0; i < allAppointments.length(); i++) {
		if (doctor->getID() == allAppointments.get(i).getDoctor_ID()) {
			doctorAppointments.addLast(allAppointments.get(i));
		}
	}
	if (doctorAppointments.length() == 0) {
		cout << "No appointments found for this patient.";
		system("pause");
		delete schedule;
		DoctorMenu::menu(user);  // Quay lại menu chính
		return;
	}

Nhan4:
	system("cls");
	//ve bang xem appt
	doctor->drawTablePatient(22, 7, doctorAppointments.length());
	doctor->fillAppointmentDetailsForPatient(doctorAppointments, 22, 7);
	//ve bang chon X
	vector<string> Cancle;
	int count = 0;
	for (int i = 0; i < doctorAppointments.length(); i++) {
		Cancle.push_back(" X");
		count++;
	}
	gotoxy(35, 1);
	cout << "Choose your Appointment you want to view Patient";



	MenuBox CancleAppt(8, 9, 2, 4, 11, 1, 203, Cancle);
	int choose = CancleAppt.menu() - 1;
	int patientID = doctorAppointments.get(choose).getPatient_ID();

	Patient* patient = schedule->findPatientByID(patientID);

	Setcolor(14);
	gotoxy(40, 11);      cout << "+-----------------------------------------+" << endl;
	gotoxy(40, 12);      cout << "|            YOUR INFORMATION             |" << endl;
	gotoxy(40, 13);      cout << "+-----------------------------------------+" << endl;
	gotoxy(40, 14);      cout << "|  Username       :                       |" << endl;
	gotoxy(40, 15);      cout << "|-----------------------------------------|" << endl;
	gotoxy(40, 16);      cout << "|  Full Name      :                       |" << endl;
	gotoxy(40, 17);      cout << "|-----------------------------------------|" << endl;
	gotoxy(40, 18);      cout << "|  Birth Date     :                       |" << endl;
	gotoxy(40, 19);      cout << "|-----------------------------------------|" << endl;
	gotoxy(40, 20);      cout << "|  Gender         :                       |" << endl;
	gotoxy(40, 21);      cout << "|-----------------------------------------|" << endl;
	gotoxy(40, 22);      cout << "|  Phone Number   :                       |" << endl;
	gotoxy(40, 23);      cout << "|-----------------------------------------|" << endl;
	gotoxy(40, 24);      cout << "|  Address        :                       |" << endl;
	gotoxy(40, 25);      cout << "+-----------------------------------------+" << endl;
	Setcolor(15);
	gotoxy(60, 14);
	cout << patient->getUsername();
	gotoxy(60, 16);
	cout << patient->getName();
	gotoxy(60, 18);
	cout << patient->getDateOfBirth();
	gotoxy(60, 20);
	cout << patient->getGender();
	gotoxy(60, 22);
	cout << patient->getPhoneNumber();
	gotoxy(60, 24);
	cout << patient->getAddress();


	vector<string> Confirm = { "     Back","Exit to Menu" };
	MenuBox CancleAppt2(44, 30, 2, 15, 11, 1, 203, Confirm);
	int chosen = CancleAppt2.menu2();

	if (chosen == 1) {
		goto Nhan4;
	}
	else {
		DoctorMenu::menu(user);
	}


}

void DoctorMenu::ChangePassword(User& usern) {
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
	Doctor *doctor = System->findDoctorByID(usern.getID());
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
		goto retry;    // Sử dụng goto để quay lại nhập lại mật khẩu
	}

	if (confirm != password) {
		gotoxy(57, 28);
		cout << "Passwords do not match. Please try again!" << endl;
		system("pause");
		goto retry;    // Sử dụng goto để quay lại nhập lại mật khẩu
	}

	gotoxy(57, 28);
	if (!System->CheckPassword(password)) {
		system("pause");
		goto retry;  // Sử dụng goto để quay lại nhập lại mật khẩu
	}

	if (doctor == nullptr) {
		if (user != nullptr) {
			user->setPassword(password);
		}
		System->saveUsers("../PBL2_BKDN/User_infor.txt", System->getAllUser());
	}
	else {
		// Nếu bệnh nhân tồn tại, cập nhật cả user và bệnh nhân
		user->setPassword(password);
		doctor->setPassword(password);
		System->saveDoctors("../PBL2_BKDN/Doctor_infor.txt", System->getAllDoctors());
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
	DoctorMenu::menu(usern);
}

void DoctorMenu::UpdateWorkSchedule(User& user) {
	Schedule* schedule = new Schedule();  // Create a Schedule object
	Doctor* doctor = schedule->findDoctorByID(user.getID());

	if (doctor == nullptr) {
		gotoxy(65, 25);
		cout << "You must update your information!" << endl;
		system("pause");
		delete schedule;
		DoctorMenu::menu(user);
		return;
	}

	LinkedList<Doctor_Schedule> List_DrInfor;
	schedule->loadDoctor_Schedule("../PBL2_BKDN/Doctor_Schedule.txt", List_DrInfor);
	Doctor_Schedule* DrInfor = schedule->findScheduleDoctor(user.getID(), List_DrInfor);

	if (DrInfor == nullptr) { //can chinh sua
		cout << "You have not updated any information, you must update all!" << endl;
		string Time_Start, Time_End, achievements, Days;
		int Year_Start = 0;
		

		//Tieu de:
		Setcolor(14);
		gotoxy(30, 7);
		cout << "Year of starting work: ";
		gotoxy(30, 8);
		cout << "Time begin of Day: ";
		gotoxy(30, 9);
		cout << "Time end of Day: ";

		Showcur(true);

		int currentYear = schedule->getCurrentYear();
		//Nhap gia tri
		do {
			gotoxy(53, 7);
			cout << "             ";
			gotoxy(53, 7);
			cin>> Year_Start;
			cin.ignore();
		} while (Year_Start > currentYear);

		do {
			gotoxy(49, 8);
			cout << "             ";
			gotoxy(49, 8);
			getline(cin, Time_Start);
		} while (!schedule->isValidTimeFormat(Time_Start));

		do {
			gotoxy(46, 9);
			cout << "             ";
			gotoxy(46, 9);
			getline(cin, Time_End);
		} while (!schedule->isValidTimeFormat(Time_End));






		// Input Achievements
		int n = 0;
		gotoxy(30, 10);
		cout << "Enter the number of Achievements you want to add: ";
		do {
			gotoxy(78, 10);
			cout << "         ";
			gotoxy(78, 10);
			cin >> n;
			cin.ignore();
		} while (n < 1);

		for (int i = 0; i < n; i++) {
			string achievementtmp;
			gotoxy(30, 11 + i);
			cout << "Achievements " << i + 1 << ": ";
			gotoxy(47, 11 + i);
			getline(cin, achievementtmp);
			if (!achievementtmp.empty()) {
				achievements += (i == 0 ? "" : ",") + achievementtmp;
			}
		}

		// Input Days of the Week
		int N = 0;
		do {
			gotoxy(30, 11 + n);
			cout << "Enter the number of Days (0 <x<= 7): ";
			gotoxy(68, 11 + n);
			cout << "      ";
			gotoxy(68, 11 + n);
			cin >> N;
			cin.ignore();  // Clear the newline from the input buffer
		} while (N <= 0 || N > 7);

		for (int i = 0; i < N; i++) {
			string day;
			gotoxy(30, 12 + n + i);
			cout << "Day " << i + 1 << ": ";
			bool validDay = false;
			do {
				gotoxy(38, 12 + n + i);
				cout << "                 ";  // Clear previous input
				gotoxy(38, 12 + n + i);
				getline(cin, day);
				if (day == "Monday" || day == "Tuesday" || day == "Wednesday" || day == "Thursday" ||
					day == "Friday" || day == "Saturday" || day == "Sunday") {
					Days += "," + day;  // Append day if valid
					validDay = true;
				}
				else {
					gotoxy(40, 16 + i);
					cout << "Invalid day. Please enter again (e.g., Monday): ";
				}
			} while (!validDay);
		}
		// Create new schedule for the doctor
		Days = schedule->removeDuplicates(Days);
		Doctor_Schedule newSchedule_Doctor(doctor->getID(), doctor->getName(), Year_Start, achievements, Days, Time_Start, Time_End);
		List_DrInfor.addLast(newSchedule_Doctor);
		schedule->saveDoctor_Shcedule("../PBL2_BKDN/Doctor_Schedule.txt", List_DrInfor);
		delete schedule;  // Clean up the allocated schedule
		DoctorMenu::menu(user);
	}
	else {
		vector<string> Items = { "Update Time Work", "Add Day Work", "Add Achievements", "Update Year of begin" };
		MenuBox menu(40, 10, 2, 25, 11, 1, 203, Items);
		int choose = menu.menu2();
		bool updated = false;
		if (choose == 1) {  // Update Time Work
			Setcolor(11);
			gotoxy(25, 10);
			Showcur(true);
			cout << "U P D A T E   Y O U R   T I M E   W O R K";
			string Time_Startn, Time_Endn;
			Setcolor(14);
			gotoxy(40, 15);
			cout << "Time_Start:";
			gotoxy(40, 16);
			cout << "Time_End:";
			Setcolor(15);

			do {
				gotoxy(52, 15);
				cout << "                    ";
				gotoxy(52, 15);
				getline(cin, Time_Startn);
			} while (!schedule->isValidTimeFormat(Time_Startn));

			do {
				gotoxy(50, 16);
				cout << "                    ";
				gotoxy(50, 16);
				getline(cin, Time_Endn);
			} while (!schedule->isValidTimeFormat(Time_Endn));
			Showcur(false);

			// Confirmation menu
			vector<string> Confirm = { "   Back", "  Confirm" };
			MenuBox Change(30, 25, 2, 14, 11, 1, 203, Confirm);
			int chosen = Change.menu2();

			if (chosen == 1) {
				DoctorMenu::UpdateWorkSchedule(user);
			}
			else {
				DrInfor->setTime_Star(Time_Startn);
				DrInfor->setTime_End(Time_Endn);
				updated = true;
			}
		}
		if (choose == 2) {  // Add Day Work
			Setcolor(11);
			gotoxy(50, 10);
			cout << "A D D   D A Y   W O R K";
			string Days = DrInfor->getSchedule();  // Start with current schedule
			int n = 0;
			gotoxy(40, 14);
			cout << "Input Day of Number You Want To Add [1,7]: ";
			do {
				gotoxy(83, 14);
				cout << "        ";
				gotoxy(83, 14);
				cin >> n;
				cin.ignore();
			} while (n < 1 || n > 7);

			for (int i = 1; i <= n; i++) {
				string day;
				gotoxy(40, 14 + i);
				cout << "Day " << i << ":";
				bool validDay = false;
				do {
					gotoxy(47, 14 + i);
					cout << "                 ";  // Clear previous input
					gotoxy(47, 14 + i);
					getline(cin, day);
					if (day == "Monday" || day == "Tuesday" || day == "Wednesday" || day == "Thursday" ||
						day == "Friday" || day == "Saturday" || day == "Sunday") {
						Days += "," + day;  // Append day if valid
						validDay = true;
					}
					else {
						gotoxy(40, 25);
						cout << "Invalid day. Please enter again (Ex: Monday): ";
					}
				} while (!validDay);
			}
			
			// Confirmation menu
			vector<string> Confirm2 = { "   Back", "  Confirm" };
			MenuBox Change2(30, 25, 2, 14, 11, 1, 203, Confirm2);
			int chosen2 = Change2.menu2();

			if (chosen2 == 1) {
				DoctorMenu::UpdateWorkSchedule(user);
			}
			else {
				Days = schedule->removeDuplicates(Days);
				DrInfor->setSchedule(Days);  // Set updated schedule
				updated = true;
			}
		}
		if (choose == 3) {
			Showcur(true);
			Setcolor(11);
			gotoxy(50, 10);
			cout << "A D D   A C H I E V E M E N T S";
			int n = 0;
			gotoxy(40, 14);
			cout << "Input the Achievements of Number You Want To Add: ";

			do {
				gotoxy(98, 14);
				cout << "         ";
				gotoxy(98, 14);
				cin >> n;
				cin.ignore();
			} while (n < 1);
			for (int i = 1; i <= n; i++) {
				string achievement;
				gotoxy(40, 14 + i);
				cout << "Achievement " << i << ":";
				gotoxy(55, 14 + i);
				getline(cin, achievement);
				if (!achievement.empty()) {
					DrInfor->addAchievement(achievement);
				}
			}
			// Confirmation menu
			vector<string> Confirm2 = { "   Back", "  Confirm" };
			MenuBox Change2(45, 25, 2, 14, 11, 1, 203, Confirm2);
			int chosen2 = Change2.menu2();

			if (chosen2 == 1) {
				DoctorMenu::UpdateWorkSchedule(user);
			}
			else {
				updated = true;
			}
		}
		if (choose == 4) {
			Setcolor(14);
			gotoxy(45, 16);
			cout << "Year of begin: ";
			int year = 0;
			int currentYear = schedule->getCurrentYear();
			Setcolor(15);
			do {
				gotoxy(61, 16);
				cout << "         ";
				gotoxy(61, 16);
				cin >> year;
			} while (year > currentYear);
			vector<string> Confirm2 = { "   Back", "  Confirm" };
			MenuBox Change2(45, 25, 2, 14, 11, 1, 203, Confirm2);
			int chosen2 = Change2.menu2();

			if (chosen2 == 1) {
				DoctorMenu::UpdateWorkSchedule(user);
			}
			else {
				DrInfor->setExperienceYears(year);
				updated = true;
			}
		}
		if (updated) {
			schedule->saveDoctor_Shcedule("../PBL2_BKDN/Doctor_Schedule.txt", List_DrInfor);
		}

		delete schedule;  // Clean up the allocated schedule
		DoctorMenu::menu(user);
	}
}





//huy cuoc hen
void DoctorMenu::CancleAppointment(User& user) {
	Schedule* schedule = new Schedule();  // Tạo đối tượng Schedule
	Doctor* doctor = schedule->findDoctorByID(user.getID());

	if (doctor == nullptr) {
		gotoxy(65, 25);
		cout << "User has no appointment";
		system("pause");
		delete schedule;  // Giải phóng bộ nhớ cho schedule
		DoctorMenu::menu(user);  // Quay lại menu chính
		return;
	}
	LinkedList<Appointment>& allAppointments = schedule->getAllAppointments();
	LinkedList<Appointment> doctorAppointments;
	for (int i = 0; i < allAppointments.length(); i++) {
		if (doctor->getID() == allAppointments.get(i).getDoctor_ID()&& allAppointments.get(i).getStatus() == "Schedule") {
			doctorAppointments.addLast(allAppointments.get(i));
		}
	}
	if (doctorAppointments.length() == 0) {
		cout << "No appointments found for this patient.";
		system("pause");
		delete schedule;
		DoctorMenu::menu(user);  // Quay lại menu chính
		return;
	}

	//ve bang xem appt
	doctor->drawTablePatient(22, 7, doctorAppointments.length());
	doctor->fillAppointmentDetailsForPatient(doctorAppointments, 22, 7);
	//ve bang chon X
	vector<string> Cancle;
	int count = 0;
	for (int i = 0; i < doctorAppointments.length(); i++) {
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
		schedule->cancelAppointment(doctorAppointments.get(choose).getPatient_ID(), doctorAppointments.get(choose).getDate(), doctorAppointments.get(choose).getTime());
		schedule->saveAppointments("../PBL2_BKDN/Appt_infor.txt", schedule->getAllAppointments());
		gotoxy(65, 27);
		cout << "Cancle Appointment is successfull!" << endl;
		system("pause");
		delete schedule;
		DoctorMenu::menu(user);
	}
	else {
		delete schedule;
		DoctorMenu::menu(user);
	}

}


//Xem thong tin cua bac si
void DoctorMenu::viewMyInformation(User& user) {
	system("cls");
	Schedule* schedule = new Schedule();
	Doctor* doctor = schedule->findDoctorByID(user.getID());
	
	if (doctor == nullptr) {
		gotoxy(50, 10);
		cout << "User name: " << user.getUsername();
		gotoxy(50, 12);
		cout << "Your Information is empty!";
		gotoxy(50, 28);
		system("pause");
		DoctorMenu::menu(user);
		delete schedule;
	}
	else {
		LinkedList <Doctor_Schedule> List_DrInfor;
		schedule->loadDoctor_Schedule("../PBL2_BKDN/Doctor_Schedule.txt", List_DrInfor);
		Doctor_Schedule* DrInfor = schedule->findScheduleDoctor(user.getID(), List_DrInfor);
		Setcolor(14);
		gotoxy(60, 5);      cout << "+-----------------------------------------+" << endl;
		gotoxy(60, 6);      cout << "|            YOUR INFORMATION             |" << endl;
		gotoxy(60, 7);      cout << "+-----------------------------------------+" << endl;
		gotoxy(60, 8);      cout << "|  Username       :                       |" << endl;
		gotoxy(60, 9);      cout << "|-----------------------------------------|" << endl;
		gotoxy(60, 10);     cout << "|  Full Name      :                       |" << endl;
		gotoxy(60, 11);     cout << "|-----------------------------------------|" << endl;
		gotoxy(60, 12);     cout << "|  Birth Date     :                       |" << endl;
		gotoxy(60, 13);     cout << "|-----------------------------------------|" << endl;
		gotoxy(60, 14);     cout << "|  Gender         :                       |" << endl;
		gotoxy(60, 15);     cout << "|-----------------------------------------|" << endl;
		gotoxy(60, 16);     cout << "|  Phone Number   :                       |" << endl;
		gotoxy(60, 17);     cout << "|-----------------------------------------|" << endl;
		gotoxy(60, 18);     cout << "|  Address        :                       |" << endl;
		gotoxy(60, 19);     cout << "+-----------------------------------------+" << endl;
		gotoxy(60, 20);     cout << "|  Specialty      :                       |" << endl;
		gotoxy(60, 21);     cout << "+-----------------------------------------+" << endl;
		gotoxy(60, 22);     cout << "|  Experiences    :                       |" << endl;
		gotoxy(60, 23);     cout << "+-----------------------------------------+" << endl;
		gotoxy(60, 24);     cout << "|  Time_Start     :                       |" << endl;
		gotoxy(60, 25);     cout << "+-----------------------------------------+" << endl;
		gotoxy(60, 26);     cout << "|  Time_End       :                       |" << endl;
		gotoxy(60, 27);     cout << "+-----------------------------------------+" << endl;



		Setcolor(15);
		gotoxy(80, 8);
		cout << doctor->getUsername();
		gotoxy(80, 10);
		cout << doctor->getName();
		gotoxy(80, 12);
		cout << doctor->getDateOfBirth();
		gotoxy(80, 14);
		cout << doctor->getGender();
		gotoxy(80, 16);
		cout << doctor->getPhoneNumber();
		gotoxy(80, 18);
		cout << doctor->getAddress();
		gotoxy(80, 20);
		cout << doctor->getSpecialty();
		if (DrInfor != nullptr) {
			gotoxy(80, 22);
			cout << DrInfor->getExperienceYears();
			gotoxy(80, 24);
			cout << DrInfor->getTime_Start();
			gotoxy(80, 26);
			cout << DrInfor->getTime_End();
		}
		

		
		gotoxy(55, 29);
		system("pause");
		delete schedule;
		DoctorMenu::menu(user);
	}
}

void DoctorMenu::updateInformation(User& user) {
	Schedule* System = new Schedule();  // Tạo đối tượng Schedule
	Doctor* doctor = System->findDoctorByID(user.getID());
	// Nếu thông tin chưa được lưu trước đó, tạo doctor mới
	if (doctor == nullptr) {
	Nhan1:
		vector<string> Contents = { "Full name:","Birthday:","Gender:","Address:","Phonenumber:","Specialty:" };
		MenuBox UpdateInf(Contents);
		UpdateInf.box(51, 10, 22, 41, 3, 203, " ");
		UpdateInf.boxes(53, 14, 2, 37, 3, 203, Contents);
		gotoxy(64, 12);
		cout << "YOUR INFORMATION";

		// Nhập thông tin
		string name, birthday, gender, address, phone, specialty;
		Showcur(true); // Hiển thị con trỏ chuột

		gotoxy(65, 15); getline(cin, name);
		gotoxy(63, 17); getline(cin, birthday);
		gotoxy(61, 19); getline(cin, gender);
		gotoxy(62, 21); getline(cin, address);
		gotoxy(66, 23); getline(cin, phone);
		gotoxy(65, 25); getline(cin, specialty);

		Showcur(false); // Ẩn con trỏ chuột

		// Hiển thị menu xác nhận
		gotoxy(54, 25);
		vector<string> Items = { "Try again", "Confirm" };
		MenuBox Menu(58, 28, 2, 13, 3, 1, 203, Items);
		int choose = Menu.menu2();

		if (choose == 2) { // Người dùng xác nhận

			Doctor* newdoctor = new Doctor(name, birthday, gender, address, phone, user.getUsername(), user.getPassword(), user.getID(), specialty);
			System->addDoctor(*newdoctor);
			System->saveDoctors("../PBL2_BKDN/doctor_infor.txt", System->getAllDoctors());
			cout << "Information saved successfully!" << endl;
			delete newdoctor; // Giải phóng bộ nhớ
			DoctorMenu::menu(user); // Quay lại menu
		}
		else if (choose == 1) {
			goto Nhan1; // Thử lại nếu người dùng chọn "Try again"
		}
	}
	else {
		// Nếu thông tin bệnh nhân đã tồn tại, hiển thị tùy chọn cập nhật
		vector<string> Content = { "Change Full name", "Change Birthday", "Change Gender", "Change Address", "Change Phonenumber","Change Specialty","Update All", "Back" };
		vector<string> Items = { "Try again", "Confirm" };
		MenuBox Menu(55, 18, 2, 13, 11, 1, 203, Items);

		MenuBox UpdateOptions(Content);

		bool updated = false; // Biến theo dõi nếu có thay đổi thông tin
		int option = UpdateOptions.menu2();
		Showcur(true); // Hiển thị con trỏ chuột

		if (option == 1) {
		Update1:
			system("cls");
			// Thay đổi tên
			Setcolor(14);
			gotoxy(51, 15);
			cout << "New Full Name:";
			Setcolor(15);
			gotoxy(65, 15);
			cout << "                 ";
			gotoxy(65, 15);
			string name;
			getline(cin, name);
			doctor->setName(name);
			int choose = Menu.menu2();
			if (choose == 1) {
				goto Update1;
			}
			else if (choose == 2) {
				updated = true;
			}
		}
		else if (option == 2) {
		Update2:
			system("cls");
			Setcolor(14);
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
			doctor->setDateOfBirth(birthday);
			int choose = Menu.menu2();
			if (choose == 1) {
				goto Update2;
			}
			else if (choose == 2) {
				updated = true;
			}
		}
		else if (option == 3) {
		Update3:
			system("cls");
			Setcolor(14);
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
			doctor->setGender(gender);
			int choose = Menu.menu2();
			if (choose == 1) {
				goto Update3;
			}
			else if (choose == 2) {
				updated = true;
			}
		}
		else if (option == 4) {
			// Thay đổi địa chỉ
		Update4:
			system("cls");
			Setcolor(14);
			gotoxy(53, 15);
			cout << "New Address:";
			Setcolor(15);
			gotoxy(65, 15);
			string address;
			getline(cin, address);
			doctor->setAddress(address);
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
		Setcolor(14);
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
			doctor->setPhoneNumber(phone);
			int choose = Menu.menu2();
			if (choose == 1) {
				goto Update5;
			}
			else if (choose == 2) {
				updated = true;
			}
		}
		else if (option == 6) {
			// Thay đổi Chuyen khoa
		Update6:
			Setcolor(203);
			gotoxy(49, 15);
			cout << "New Specialty:";
			Setcolor(15);
			gotoxy(65, 15);
			string Specialty;
			getline(cin, Specialty);
			doctor->setSpecialty(Specialty);
			int choose = Menu.menu2();
			if (choose == 1) {
				goto Update6;
			}
			else if (choose == 2) {
				updated = true;
			}
		}
		else if (option == 7) {
		Update7:
			vector<string> Content2 = { "Full name:","Birthday:","Gender:","Address:","Phonenumber:","Specialty:" };
			MenuBox UpdateInf(Content2);
			UpdateInf.box(51, 10, 22, 41, 3, 203, " ");
			UpdateInf.boxes(53, 14, 2, 37, 3, 203, Content2);
			gotoxy(64, 12);
			cout << "YOUR INFORMATION";

			// Nhập thông tin
			string name, birthday, gender, address, phone, specialty;
			Showcur(true); // Hiển thị con trỏ chuột

			//Nhap Name
			int count = 0;
			do {
				if (count == 1) {
					Setcolor(12);
					gotoxy(93, 15);
					cout << "Full name not allow empty!";
					Setcolor(15);
				}
				gotoxy(65, 15);
				cout << "                ";
				gotoxy(65, 15);
				getline(cin, name);

				count = 1;
			} while (name.empty());

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
			int Check1 = 0;
			do {
				if (Check1 == 1) {
					Setcolor(12);
					gotoxy(93, 21);
					cout << "Address not allow empty!";
					Setcolor(15);
				}
				gotoxy(65, 21);
				cout << "                ";
				gotoxy(65, 21);
				getline(cin, address);

				Check1 = 1;
			} while (address.empty());




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

			int count4 = 0;
			do {
				if (count4 == 1) {
					Setcolor(12);
					gotoxy(93, 25);
					cout << "Specialty not allow empty!";
					Setcolor(15);
				}
				gotoxy(65, 25);
				cout << "                ";
				gotoxy(65, 25);
				getline(cin, specialty);

				count4 = 1;
			} while (specialty.empty());
			Showcur(false); // Ẩn con trỏ chuột

			// Hiển thị menu xác nhận
			gotoxy(54, 25);
			vector<string> Items = { "Try again", "Confirm" };
			MenuBox Menu(58, 28, 2, 13, 3, 11, 203, Items);
			int choose = Menu.menu2();

			if (choose == 2) { // Người dùng xác nhận
				doctor->setName(name);
				doctor->setDateOfBirth(birthday);
				doctor->setGender(gender);
				doctor->setAddress(address);
				doctor->setPhoneNumber(phone);
				doctor->setSpecialty(specialty);
				updated = true;
			}
			else if (choose == 1) {
				goto Update7; // Thử lại nếu người dùng chọn "Try again"
			}

		}
		else if (option == 8) {
			// Quay lại mà không thay đổi gì
			DoctorMenu::menu(user);
			return;
		}

		Showcur(false); // Ẩn con trỏ chuột sau khi nhập

		if (updated) {
			// Nếu có thay đổi thông tin, lưu lại và quay lại menu
			System->saveDoctors("../PBL2_BKDN/doctor_infor.txt", System->getAllDoctors());
			cout << "Information updated successfully!" << endl;
			DoctorMenu::menu(user);
		}
	}
}