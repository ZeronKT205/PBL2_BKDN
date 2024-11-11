#pragma once
#ifndef BOX_H
#define BOX_H
#include <iostream>
#include <vector>
using namespace std;

class MenuBox {
private:
	int xx = 45;
	int yy = 14;
	int h = 2, w = 20;
	int t_color = 11;
	int b_color = 1;
	int b_color_sang = 203;
	const vector<string> content;

public:
	void bright(int x, int y, int h, int w, int b_color, string content);
	void boxes(int x, int y, int h, int w, int t_color, int b_color, const vector <string>& content);
	void box(int x, int y, int h, int w, int t_color, int b_color, string content);
	void boxesArr(int x, int y, int h, int w, int t_color, int b_color, const vector <string>& content);
	void boxtime(int x, int y, int h, int w, int t_color, int b_color, const vector <string>& content);
	MenuBox(const vector<string>& items);
	MenuBox(int xx, int yy, int h, int w, int t_color, int b_color, int b_color_sang, const vector<string>& items);
	~MenuBox() {}

	int menu();
	int menu2();
	int menu3();
};



#endif
