#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "UserInterface.h"
#include <string>

class Scoreboard {
public:
	Scoreboard(Screen *s);
	void printScoreBoard();
	void enterCompetitors(std::string teamNames[], int teamSize);
	std::string getTeamName(int teamID);
	std::string getCompetitor(int num);
	void setWinner(char league, int num, int teamID);
	std::string getWinner(char league, int num);
private:
	Screen * m_screen;
	std::string teams[8];
	std::string quarter[4] = { "Team1,Team2,Winq_1", // quarter 1
								"Team3,Team4,Winq_4", // quarter 2
								"Team5,Team6,Winq_5", // ... 3
								"Team7,Team8,Winq_7" }; // ... 4
	std::string semi[2] = { "Team1,Team4,Winner", // semi 1
							"Team5,Team7,Winner" }; //semi 2
	std::string finals = { "Team1,Team2,Winner" }; // final
};

#endif // ! SCOREBOARD_H
