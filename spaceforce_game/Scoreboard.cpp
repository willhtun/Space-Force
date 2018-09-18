#include "Scoreboard.h"

Scoreboard::Scoreboard(Screen * s) {
	m_screen = s;
}

void Scoreboard::enterCompetitors(std::string teamNames[], int teamSize) {
	for (int i = 0; i < teamSize; i++) {
		teams[i] = teamNames[i];
	}
}

void Scoreboard::printScoreBoard() {
	m_screen->clear();

	// Title
	m_screen->gotoXY(43, 1);
	m_screen->printString("  _______________  ");
	m_screen->gotoXY(43, 2);
	m_screen->printString("//               \\\\");
	m_screen->gotoXY(43, 3);
	m_screen->printString("||  SCORE BOARD  ||");
	m_screen->gotoXY(43, 4);
	m_screen->printString("\\\\_______________//");

	// Lines
	for (int i = 0; i < 5; i++) {
		m_screen->gotoXY(19, 11 + i);
		m_screen->printChar('|');
		m_screen->gotoXY(19, 23 + i);
		m_screen->printChar('|');
		m_screen->gotoXY(85, 11 + i);
		m_screen->printChar('|');
		m_screen->gotoXY(85, 23 + i);
		m_screen->printChar('|');
	}
	for (int i = 0; i < 11; i++) {
		m_screen->gotoXY(35, 14 + i);
		m_screen->printChar('|');
		m_screen->gotoXY(69, 14 + i);
		m_screen->printChar('|');
	}
	for (int i = 0; i < 10; i++) {
		m_screen->gotoXY(52, i+10);
		m_screen->printChar('|');
	}

	// Winner bracket
	for (int i = 0; i < 15; i++) {
		m_screen->gotoXY(44, 8);
		m_screen->printChar('|');
		m_screen->gotoXY(60, 8);
		m_screen->printChar('|');
		m_screen->gotoXY(45 + i, 7);
		m_screen->printChar('-');
		m_screen->gotoXY(45 + i, 9);
		m_screen->printChar('-');
	}

	// Teams
	for (int i = 0; i < 4; i++) {
		m_screen->gotoXY(6, 10 + (i * 6));
		m_screen->printString("[ " + getCompetitor(i) + " ]" + "---+");
	}
	for (int i = 0; i < 4; i++) {
		m_screen->gotoXY(85, 10 + (i * 6));
		m_screen->printString("+---[ " + getCompetitor(i + 4) + " ]");
	}

	for (int i = 0; i < 2; i++) {
		m_screen->gotoXY(20, 13 + (2 * i * 6));
		m_screen->printString("--[ " + getWinner('q', i) + " ]---+");
	}
	for (int i = 0; i < 2; i++) {
		m_screen->gotoXY(69, 13 + (2* i * 6));
		m_screen->printString("+---[ " + getWinner('q', i + 2) + " ]--");
	}

	m_screen->gotoXY(36, 19);
	m_screen->printString("--[ " + getWinner('s', 0) + " ]----+");
	m_screen->gotoXY(53, 19);
	m_screen->printString("----[ " + getWinner('s', 1) + " ]--");

	m_screen->gotoXY(49, 8);
	m_screen->printString(getWinner('f', 0));

	m_screen->gotoXY(38, 35);
	m_screen->printString("< Press ENTER twice to quit >");
	m_screen->gotoXY(0, 35);
}

std::string parseString(std::string input, int sel) {
	int separator = 0;
	int count = 0;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == ',') {
			if (count == sel)
				return input.substr(separator + count, i - separator - count);
			separator = i;
			count++;
		}
	}
	return input.substr(separator + 1, input.length());
}

void writeString(std::string& input, int sel, std::string toWrite) {
	int separator = 0;
	int count = 0;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == ',') {
			if (count == sel) {
				input.replace(separator + count, i - separator - count, toWrite);
				return;
			}
			separator = i;
			count++;
		}
	}
	input.replace(separator + 1, input.length(), toWrite);
	return;
}

std::string Scoreboard::getCompetitor(int num) {
	int index = (num) / 2;
	int position = num % 2;
	return parseString(quarter[index], position);
}

std::string Scoreboard::getTeamName(int teamID) {
	return teams[teamID];
}

void Scoreboard::setWinner(char league, int num, int teamID) {
	switch (league) {
	case 'q':
		if (num >= 4)
			num = 3;
		writeString(quarter[num], 2, getTeamName(teamID));
		break;
	case 's':
		if (num >= 2)
			num = 1;
		writeString(semi[num], 2, getTeamName(teamID));
		break;
	case 'f':
		writeString(finals, 2, getTeamName(teamID));
		break;
	default:
		break;
	}
}

std::string Scoreboard::getWinner(char league, int num) {
	switch (league) {
	case 'q':
		if (num >= 4)
			num = 3;
		return parseString(quarter[num], 2);
	case 's':
		if (num >= 2)
			num = 1;
		return parseString(semi[num], 2);
	case 'f':
		return parseString(finals, 2);
	default:
		return "Invalid arg";
	}
}