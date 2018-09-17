#ifndef ROCKET_H
#define ROCKET_H

#include <stdio.h>

#include <iostream>
#include <string>
#include "UserInterface.h"

class Rocket {
private:
	Screen * s_screen;
	int elevation; 
	std::string frame0[10] = { "      /\\      ",
		"     /__\\     ",
		"     |()|     ",
		"    /    \\   ",
		"   <_|TT|_>   ",
		"     \\==/     ",
		"      ^V      ",
		"      V^      ",
		"      ^V      ",
		"      V^      " };
	std::string frame1[10] = { "      /\\      ",
		"     /__\\     ",
		"     |()|     ",
		"    /    \\     ",
		"   <_|TT|_>   ",
		"     \\==/     ",
		"      V^      ",
		"      ^V      ",
		"      V^      ",
		"      ^V      " };
	std::string frame2[10] = { "      /\\      ",
		"     /__\\     ",
		"     |()|     ",
		"    /    \\     ",
		"   <_|TT|_>   ",
		"     \\==/     ",
		"      V^      ",
		"      ^V      ",
		"      V^      ",
		"              " };
	std::string frame3[10] = { "      /\\      ",
		"     /__\\     ",
		"     |()|     ",
		"    /    \\     ",
		"   <_|TT|_>   ",
		"     \\==/     ",
		"      V^      ",
		"      ^V      ",
		"              ",
		"              " };
	std::string frame4[10] = { "      /\\      ",
		"     /__\\     ",
		"     |()|     ",
		"    /    \\     ",
		"   <_|TT|_>   ",
		"     \\==/     ",
		"      V^      ",
		"              ",
		"              ",
		"              " };
	std::string frame5[10] = { "      /\\      ",
		"     /__\\     ",
		"     |()|     ",
		"    /    \\     ",
		"   <_|TT|_>   ",
		"     \\==/     ",
		"              ",
		"              ",
		"              ",
		"              " };
	std::string frameMask = "                 ";
	std::string frameMaskwLight = "          (o)     ";

public:
	Rocket(Screen *s) {
		s_screen = s;
	}
	void setElevation(int e);
	void printFrame(int frameNum, int x, int y, bool onLeft);
};

#endif