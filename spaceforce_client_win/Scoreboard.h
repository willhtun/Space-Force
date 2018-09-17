#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "UserInterface.h"
#include <string>

struct Competition {
	Competition() {
		winnerName = "[ bcdefg ]";
	}

	std::string winnerName;

	Competition * left;
	Competition * right;
};

class Scoreboard {
public:
	Scoreboard(Screen *s);
	void printScoreBoard();
private:
	Screen * m_screen;
	Competition final_game, semi_game[2], quarter_game[4], qualifier_game[8];
};

#endif // ! SCOREBOARD_H
