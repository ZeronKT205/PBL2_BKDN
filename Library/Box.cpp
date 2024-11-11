#pragma once
#include "Box.h"
#include <conio.h>
#include <vector>
#include <string>
#include <iostream>
#include "Menubox.h"


//ham dung. ham huy
MenuBox::MenuBox(const vector<string>& items) : content(items) {}
MenuBox::MenuBox(int xx, int yy, int h, int w, int t_color, int b_color, int b_color_sang, const vector<string>& items) : xx(xx), yy(yy), h(h), w(w), t_color(t_color), b_color(b_color), b_color_sang(b_color_sang), content(items) {}
void MenuBox::box(int xx, int yy, int h, int w, int t_color, int b_color, string item) {
	SetColor(255);
	gotoXY(xx + 1, yy + 1);
	cout << item;
	textcolor(1);
	//=========ve vien ==========
	SetColor(t_color);
	if (h <= 1 && w <= 1) return;
	for (int ix = xx; ix <= xx + w; ix++) {
		gotoXY(ix, yy);
		cout << char(196);
		gotoXY(ix, yy + h);
		cout << char(196);
	}
	for (int iy = yy; iy <= yy + h; iy++) {
		gotoXY(xx, iy);
		cout << char(179);
		gotoXY(xx + w, iy);
		cout << char(179);
	}
	gotoXY(xx, yy);
	cout << char(218);
	gotoXY(xx + w, yy);
	cout << char(191);
	gotoXY(xx, yy + h);
	cout << char(192);
	gotoXY(xx + w, yy + h);
	cout << char(217);
}
void MenuBox::bright(int xx, int yy, int h, int w, int b_color, string content) {
	textcolor(b_color);
	for (int iy = yy + 1; iy <= yy + h - 1; iy++) {
		for (int ix = xx + 1; ix <= xx + w - 1; ix++) {
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	SetColor(15);
	gotoXY(xx + 1, yy + 1);
	cout << content;
}
void MenuBox::boxes(int xx, int yy, int h, int w, int t_color, int b_color, const vector<string>& content) {
	int n = static_cast<int>(content.size());
	for (int i = 0; i < n; i++) {
		box(xx, yy + 2 * i, h, w, t_color, b_color, content[i]);
		if (i != 0) {
			gotoXY(xx, yy + (i * 2));
			cout << char(195);
			gotoXY(xx + w, yy + (i * 2));
			cout << char(180);
		}
	}
	SetColor(15);
}

int MenuBox::menu() {
	ShowCur(0);
	this->boxes(xx, yy, h, w, t_color, b_color, content);
	int xp = xx;
	int yp = yy;
	int xcu = xp;
	int ycu = yp;
	bool kt = true;
	int choose = 1;
	while (true) {
		if (kt) {
			gotoXY(xcu, ycu);
			this->bright(xcu, ycu, h, w, b_color, content[(ycu - yy) / 2]);
			xcu = xp; ycu = yp;
			this->bright(xp, yp, h, w, b_color_sang, content[(yp - yy) / 2]);
			kt = false;
		}
		if (_kbhit()) {
			char c = _getch();
			if (c == 72) { // Up arrow
				if (yp != yy) {
					kt = true;
					yp -= 2;
					choose = (size_t)((yp - yy) / 2 + 1);
				}
				else {
					kt = true;
					yp = yy + (static_cast<int>(content.size()) - 1) * h;
					choose = static_cast<int>(content.size());
				}
			}
			else if (c == 80) { // Down arrow
				if (yp != yy + (static_cast<int>(content.size()) - 1) * h) {
					kt = true;
					yp += 2;
					choose = (size_t)((yp - yy) / 2 + 1);
				}
				else {
					kt = true;
					yp = yy;
					choose = 1;
				}
			}
			else if (c == 13) { // Enter key
				textcolor(3);
				system("cls");
				SetColor(15);
				return choose;
			}
		}
	}
	SetColor(15);
	return choose;
}

//BOXES WITH m n
void MenuBox::boxesArr(int x, int y, int h, int w, int t_color, int b_color, const vector <string>& content) {
	int n = static_cast<int>(content.size());

	// Tính toán số cột và số hàng
	int rows, cols;
	if (n <= 3) {
		rows = 1;
		cols = n;
	}
	else {
		cols = static_cast<int>(ceil(sqrt(n)));
		rows = static_cast<int>(ceil(static_cast<double>(n) / cols));
	}


	int index = 0;
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (index < n) {  // Kiểm tra nếu vẫn còn phần tử trong content
				int box_x = x + col * (w + 1);  // Khoảng cách giữa các cột
				int box_y = y + row * (h + 1);  // Khoảng cách giữa các hàng
				box(box_x, box_y, h, w, t_color, b_color, content[index]);
				index++;
			}
		}
	}
}

int MenuBox::menu2() {
	ShowCur(0);
	this->boxesArr(xx, yy, h, w, t_color, b_color, content);

	// Lấy kích thước và số hàng/cột của grid
	int n = static_cast<int>(content.size());
	int rows, cols;
	if (n <= 3) {
		rows = 1;
		cols = n;
	}
	else {
		cols = static_cast<int>(ceil(sqrt(n))); // Số cột
		rows = static_cast<int>(ceil(static_cast<double>(n) / cols)); // Số hàng
	}

	// Các biến để theo dõi vị trí hàng và cột hiện tại
	int currentRow = 0;
	int currentCol = 0;

	// Lấy vị trí vệt sáng ban đầu
	int xp = xx + currentCol * (w + 1);  // Chỉ cách 1 đơn vị theo trục X
	int yp = yy + currentRow * (h + 1);  // Khoảng cách theo trục Y vẫn giữ nguyên
	int xcu = xp;
	int ycu = yp;
	bool kt = true;
	int choose = 1;
	int content_bf = currentRow * cols + currentCol;
	while (true) {
		if (kt) {
			// Tắt vệt sáng ở vị trí cũ
			gotoXY(xcu, ycu);
			this->bright(xcu, ycu, h, w, b_color, content[content_bf]);

			// Bật vệt sáng ở vị trí mới
			xcu = xp;
			ycu = yp;
			this->bright(xp, yp, h, w, b_color_sang, content[currentRow * cols + currentCol]);
			content_bf = currentRow * cols + currentCol;
			kt = false;
		}

		if (_kbhit()) {
			char c = _getch();

			// Mũi tên lên (Up arrow)
			if (c == 72) {
				if (n % cols == 0) {
					if (currentRow > 0) {
						kt = true;
						currentRow--;
					}
					else {
						kt = true;
						currentRow = rows - 1;
					}
				}
				else {
					if (currentCol < (n % cols)) {
						if (currentRow > 0) {
							kt = true;
							currentRow--;
						}
						else {
							kt = true;
							currentRow = rows - 1;
						}
					}
					else {
						if (currentRow > 0) {
							kt = true;
							currentRow--;
						}
						else {
							kt = true;
							currentRow = rows - 2;
						}
					}
				}

			}

			// Mũi tên xuống (Down arrow)
			else if (c == 80) {
				if (n % cols == 0) {

					if (currentRow < rows - 1) {
						kt = true;
						currentRow++;
					}
					else {
						kt = true;
						currentRow = 0;
					}
				}
				else {

					if (currentRow < rows - 1) {
						kt = true;

						if (currentRow == rows - 2 && currentCol >= (n % cols)) {
							currentRow = 0;
						}
						else {
							currentRow++;
						}
					}
					else {
						kt = true;
						currentRow = 0;
					}
				}

			}

			// Mũi tên trái (Left arrow)
			else if (c == 75) { // Mũi tên trái (Left arrow)
				if (n % cols == 0) {

					if (currentCol > 0) {
						kt = true;
						currentCol--;
					}
					else {

						kt = true;
						currentCol = cols - 1;
					}
				}
				else {

					if (currentCol > 0) {
						kt = true;
						currentCol--; // Di chuyển sang trái
					}
					else {
						kt = true;

						if (currentRow == rows - 1) {
							currentCol = (n % cols) - 1; // Đặt cột tại vị trí hợp lệ cuối cùng của hàng
						}
						else {
							currentCol = cols - 1; // Quay về cột cuối cùng của hàng hiện tại
						}
					}
				}
			}

			// Mũi tên phải (Right arrow)
			else if (c == 77) {
				if (n % cols == 0) {
					if (currentCol < cols - 1) {
						kt = true;
						currentCol++;
					}
					else {
						kt = true;
						currentCol = 0;
					}
				}
				else {
					if (currentRow != rows - 1) {
						if (currentCol < cols - 1) {
							kt = true;
							currentCol++;
						}
						else {
							kt = true;
							currentCol = 0;
						}
					}
					else {
						if (currentCol < n % cols - 1) {
							kt = true;
							currentCol++;
						}
						else {
							kt = true;
							currentCol = 0;
						}
					}
				}
			}

			// Phím Enter
			else if (c == 13) {
				textcolor(3);
				system("cls");
				SetColor(15);
				return currentRow * cols + currentCol + 1; // Trả về vị trí đã chọn
			}

			// Cập nhật vị trí vệt sáng sau khi di chuyển
			xp = xx + currentCol * (w + 1); // Chỉ cách 1 đơn vị theo trục X
			yp = yy + currentRow * (h + 1); // Khoảng cách theo trục Y vẫn giữ nguyên
		}
	}
	
	return choose;
}



void MenuBox::boxtime(int x, int y, int h, int w, int t_color, int b_color, const vector <string>& content) {
	int n = static_cast<int>(content.size());
	// Tính toán số cột và số hàng
	int rows, cols;
	if (n <= 6) {
		rows = 1;
		cols = n;
	}
	else {
		cols = 6;
		rows = static_cast<int>(ceil(static_cast<double>(n) / cols));
	}


	int index = 0;
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (index < n) {  // Kiểm tra nếu vẫn còn phần tử trong content
				int box_x = x + col * (w + 1);  // Khoảng cách giữa các cột
				int box_y = y + row * (h + 1);  // Khoảng cách giữa các hàng
				box(box_x, box_y, h, w, t_color, b_color, content[index]);
				index++;
			}
		}
	}
}


int MenuBox::menu3() {
	ShowCur(0);
	this->boxtime(xx, yy, h, w, t_color, b_color, content);

	// Lấy kích thước và số hàng/cột của grid
	int n = static_cast<int>(content.size());
	int rows, cols;
	if (n <= 6) {
		rows = 1;
		cols = n;
	}
	else {
		cols = 6; // Số cột
		rows = static_cast<int>(ceil(static_cast<double>(n) / cols)); // Số hàng
	}

	// Các biến để theo dõi vị trí hàng và cột hiện tại
	int currentRow = 0;
	int currentCol = 0;

	// Lấy vị trí vệt sáng ban đầu
	int xp = xx + currentCol * (w + 1);  // Chỉ cách 1 đơn vị theo trục X
	int yp = yy + currentRow * (h + 1);  // Khoảng cách theo trục Y vẫn giữ nguyên
	int xcu = xp;
	int ycu = yp;
	bool kt = true;
	int choose = 1;
	int content_bf = currentRow * cols + currentCol;
	while (true) {
		if (kt) {
			// Tắt vệt sáng ở vị trí cũ
			gotoXY(xcu, ycu);
			this->bright(xcu, ycu, h, w, b_color, content[content_bf]);

			// Bật vệt sáng ở vị trí mới
			xcu = xp;
			ycu = yp;
			this->bright(xp, yp, h, w, b_color_sang, content[currentRow * cols + currentCol]);
			content_bf = currentRow * cols + currentCol;
			kt = false;
		}

		if (_kbhit()) {
			char c = _getch();

			// Mũi tên lên (Up arrow)
			if (c == 72) {
				if (n % cols == 0) {
					if (currentRow > 0) {
						kt = true;
						currentRow--;
					}
					else {
						kt = true;
						currentRow = rows - 1;
					}
				}
				else {
					if (currentCol < (n % cols)) {
						if (currentRow > 0) {
							kt = true;
							currentRow--;
						}
						else {
							kt = true;
							currentRow = rows - 1;
						}
					}
					else {
						if (currentRow > 0) {
							kt = true;
							currentRow--;
						}
						else {
							kt = true;
							currentRow = rows - 2;
						}
					}
				}

			}

			// Mũi tên xuống (Down arrow)
			else if (c == 80) {
				if (n % cols == 0) {

					if (currentRow < rows - 1) {
						kt = true;
						currentRow++;
					}
					else {
						kt = true;
						currentRow = 0;
					}
				}
				else {

					if (currentRow < rows - 1) {
						kt = true;

						if (currentRow == rows - 2 && currentCol >= (n % cols)) {
							currentRow = 0;
						}
						else {
							currentRow++;
						}
					}
					else {
						kt = true;
						currentRow = 0;
					}
				}

			}

			// Mũi tên trái (Left arrow)
			else if (c == 75) { // Mũi tên trái (Left arrow)
				if (n % cols == 0) {

					if (currentCol > 0) {
						kt = true;
						currentCol--;
					}
					else {

						kt = true;
						currentCol = cols - 1;
					}
				}
				else {

					if (currentCol > 0) {
						kt = true;
						currentCol--; // Di chuyển sang trái
					}
					else {
						kt = true;

						if (currentRow == rows - 1) {
							currentCol = (n % cols) - 1; // Đặt cột tại vị trí hợp lệ cuối cùng của hàng
						}
						else {
							currentCol = cols - 1; // Quay về cột cuối cùng của hàng hiện tại
						}
					}
				}
			}

			// Mũi tên phải (Right arrow)
			else if (c == 77) {
				if (n % cols == 0) {
					if (currentCol < cols - 1) {
						kt = true;
						currentCol++;
					}
					else {
						kt = true;
						currentCol = 0;
					}
				}
				else {
					if (currentRow != rows - 1) {
						if (currentCol < cols - 1) {
							kt = true;
							currentCol++;
						}
						else {
							kt = true;
							currentCol = 0;
						}
					}
					else {
						if (currentCol < n % cols - 1) {
							kt = true;
							currentCol++;
						}
						else {
							kt = true;
							currentCol = 0;
						}
					}
				}
			}

			// Phím Enter
			else if (c == 13) {
				textcolor(3);
				system("cls");
				SetColor(15);
				return currentRow * cols + currentCol + 1; // Trả về vị trí đã chọn
			}

			// Cập nhật vị trí vệt sáng sau khi di chuyển
			xp = xx + currentCol * (w + 1); // Chỉ cách 1 đơn vị theo trục X
			yp = yy + currentRow * (h + 1); // Khoảng cách theo trục Y vẫn giữ nguyên
		}
	}

	return choose;
}
