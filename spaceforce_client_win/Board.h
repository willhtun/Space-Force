#ifndef BOARD_H
#define BOARD_H

#include <string>
#include "UserInterface.h"

class Board {
public:
	Board(int w, int h, Screen *s);
	void printBoard();
	void printWinner(int i_win);
	void printTimesUp(int frame);
	std::string getCountDown(int cd, int line);
private:
	std::string* board;
	std::string launchpad_bottom[4];
	std::string countDown[5][5];
	std::string winText[5];
	std::string loseText[5];
	std::string tieText[5];
	std::string timesUp[6];
	Screen *screen;
	int height, width;
};

class LaunchPad {
public:
	LaunchPad(Screen* s);
	void printLaunchPad(int frame);
private:
	Screen * screen;
	std::string teamName;
	std::string launchpad[20][11];

};

#endif // ! BOARD_H
