#include "Scoreboard.h"

Scoreboard::Scoreboard(Screen * s) {
	m_screen = s;

	final_game.left = &semi_game[0];
	final_game.right = &semi_game[1];

	semi_game[0].left = &quarter_game[0];
	semi_game[0].right = &quarter_game[1];
	semi_game[1].left = &quarter_game[2];
	semi_game[1].right = &quarter_game[3];

	quarter_game[0].left = &qualifier_game[0];
	quarter_game[0].right = &qualifier_game[1];
	quarter_game[1].left = &qualifier_game[2];
	quarter_game[1].right = &qualifier_game[3];
	quarter_game[2].left = &qualifier_game[4];
	quarter_game[2].right = &qualifier_game[5];
	quarter_game[3].left = &qualifier_game[6];
	quarter_game[3].right = &qualifier_game[7];
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
		m_screen->printString(qualifier_game[i].winnerName + "---+");
	}
	for (int i = 0; i < 4; i++) {
		m_screen->gotoXY(85, 10 + (i * 6));
		m_screen->printString("+---" + qualifier_game[i+4].winnerName);
	}

	for (int i = 0; i < 2; i++) {
		m_screen->gotoXY(20, 13 + (2 * i * 6));
		m_screen->printString("--" + quarter_game[i].winnerName + "---+");
	}
	for (int i = 0; i < 2; i++) {
		m_screen->gotoXY(69, 13 + (2* i * 6));
		m_screen->printString("+---" + quarter_game[i+2].winnerName + "--");
	}

	m_screen->gotoXY(36, 19);
	m_screen->printString("--" + semi_game[0].winnerName + "----+");
	m_screen->gotoXY(53, 19);
	m_screen->printString("----" + semi_game[1].winnerName + "--");
}