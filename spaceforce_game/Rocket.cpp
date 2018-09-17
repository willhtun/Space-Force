#include "Rocket.h"

void Rocket::setElevation(int e) {
	elevation = e;
}

void Rocket::printFrame(int frameNum, int x, int y, bool onLeft) {
	std::string toprint = "";
	if (y < 1)
		y = 1;
	switch (frameNum) {
	case 0:
		for (int i = y; i < 10 + y; i++) {
			s_screen->gotoXY(x, i + 1);
			if (elevation > 700)
				s_screen->printString(frameMask);
			toprint = "";
			toprint += frame0[i - y];

			s_screen->gotoXY(x, i);
			s_screen->printString(toprint);

			if (onLeft) {
				if (i == y)
					s_screen->printString("     <-- " + std::to_string(elevation) + " km");
				else
					s_screen->printString(frameMask);
			}
			else {
				s_screen->gotoXY(52, i);
				if (i == y)
					s_screen->printString(std::to_string(elevation) + " km  -->");
				else
					s_screen->printString(frameMask);
				if (elevation < 2000) {
					s_screen->gotoXY(53, 42);
					s_screen->printString(frameMaskwLight);
				}
			}
		}
		break;
	case 1:
		for (int i = y; i < 10 + y; i++) {
			s_screen->gotoXY(x, i + 1);
			if (elevation > 700)
				s_screen->printString(frameMask);
			toprint = "";
			toprint += frame1[i - y];

			s_screen->gotoXY(x, i);
			s_screen->printString(toprint);

			if (onLeft) {
				if (i == y)
					s_screen->printString("     <-- " + std::to_string(elevation) + " km");
				else
					s_screen->printString(frameMask);
			}
			else {
				s_screen->gotoXY(52, i);
				if (i == y)
					s_screen->printString(std::to_string(elevation) + " km  -->");
				else
					s_screen->printString(frameMask);
				if (elevation < 2000) {
					s_screen->gotoXY(53, 42);
					s_screen->printString(frameMaskwLight);
				}
			}
		}
		break;
	case 2:
		for (int i = y; i < 10 + y; i++) {
			s_screen->gotoXY(x, i + 1);
			s_screen->printString(frameMask);
			toprint = "";
			toprint += frame2[i - y];
			s_screen->gotoXY(x, i);
			s_screen->printString(toprint);
			if (i == y)
				s_screen->printString("     <-- " + std::to_string(elevation) + " km");
			else
				s_screen->printString(frameMask);
		}
		break;
	case 3:
		for (int i = y; i < 10 + y; i++) {
			s_screen->gotoXY(x, i + 1);
			s_screen->printString(frameMask);
			toprint = "";
			toprint += frame3[i - y];
			s_screen->gotoXY(x, i);
			s_screen->printString(toprint);
			if (i == y)
				s_screen->printString("     <-- " + std::to_string(elevation) + " km");
			else
				s_screen->printString(frameMask);
		}
		break;
	case 4:
		for (int i = y; i < 10 + y; i++) {
			s_screen->gotoXY(x, i + 1);
			s_screen->printString(frameMask);
			toprint = "";
			toprint += frame4[i - y];
			s_screen->gotoXY(x, i);
			s_screen->printString(toprint);
			if (i == y)
				s_screen->printString("     <-- " + std::to_string(elevation) + " km");
			else
				s_screen->printString(frameMask);
		}
		break;
	case 5:
		for (int i = y; i < 10 + y; i++) {
			s_screen->gotoXY(x, i + 1);
			s_screen->printString(frameMask);
			toprint = "";
			toprint += frame5[i - y];
			s_screen->gotoXY(x, i);
			s_screen->printString(toprint);
			if (i == y)
				s_screen->printString("     <-- " + std::to_string(elevation) + " km");
			else
				s_screen->printString(frameMask);
		}
		break;
	}

}