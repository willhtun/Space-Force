#include "Board.h"

Board::Board(int w, int h, Screen* s) {
	board = new std::string[h];
	width = w;
	height = h;
	screen = s;
	// Drawboard
	for (int j = 0; j < w; j++) {
		board[0] += '-';
		board[h - 1] += '-';
	}
	for (int i = 1; i < h - 1; i++) {
		for (int j = 0; j < w; j++) {
			if (j == 0 || j == w - 1 || j == (w - 1) / 2)
				board[i] += '|';
			else
				board[i] += ' ';
		}
	}
	// Countdown
	countDown[2][0] = "    _    ";
	countDown[2][1] = "     |   ";
	countDown[2][2] = "     |   ";
	countDown[2][3] = "     |   ";
	countDown[2][4] = "     |   ";
	countDown[1][0] = "   ___   ";
	countDown[1][1] = "      \\  ";
	countDown[1][2] = "   ___|  ";
	countDown[1][3] = "  |      ";
	countDown[1][4] = "  \\___   ";
	countDown[0][0] = "   ___   ";
	countDown[0][1] = "      \\  ";
	countDown[0][2] = "    __|  ";
	countDown[0][3] = "      |  ";
	countDown[0][4] = "   ___/  ";
	countDown[3][0] = "         ";
	countDown[3][1] = " __   __ ";
	countDown[3][2] = "| __ |  |";
	countDown[3][3] = "|__| |__|";
	countDown[3][4] = "         ";
	countDown[4][0] = "         ";
	countDown[4][1] = "         ";
	countDown[4][2] = "         ";
	countDown[4][3] = "         ";
	countDown[4][4] = "         ";

	launchpad_bottom[0] = " [____________________________] ";
	launchpad_bottom[1] = "  //\\\\//\\\\//\\\\//\\\\//\\\\//\\\\//\\\\  ";
	launchpad_bottom[2] = " //  \\/  TEAM WILD WES   \\/  \\\\ ";
	launchpad_bottom[3] = "//===||==||==||==||==||==||===\\\\";

	winText[0] = " _       _______   ____";
	winText[1] = "| |     / /  _/ | / / /";
	winText[2] = "| | /| / // //  |/ / / ";
	winText[3] = "| |/ |/ // // /|  /_/  ";
	winText[4] = "|__/|__/___/_/ |_(_)   ";

	loseText[0] = "    __    ____  _____ ______";
	loseText[1] = "   / /   / __ \\/ ___// ____/";
	loseText[2] = "  / /   / / / /\\__ \\/ __/   ";
	loseText[3] = " / /___/ /_/ /___/ / /___   ";
	loseText[4] = "/_____/\\____//____/_____/   ";

	tieText[0] = "  ________________";
	tieText[1] = " /_  __/  _/ ____/";
	tieText[2] = "  / /  / // __/   ";
	tieText[3] = " / / _/ // /___   ";
	tieText[4] = "/_/ /___/_____/   ";

	timesUp[0] = "                   _                ";
	timesUp[1] = " _____ _          | |               ";
	timesUp[2] = "|_   _|_|_____ ___|/ ___    _ _ ___ ";
	timesUp[3] = "  | | | |     | -_| |_ -|  | | | . |";
	timesUp[4] = "  |_| |_|_|_|_|___| |___|  |___|  _|";
	timesUp[5] = "                               |_|  ";
	
}

void Board::printBoard() {
	for (int i = 0; i < height; i++) {
		screen->gotoXY(0, i);
		screen->printString(board[i]);
	}
	for (int i = 0; i < 4; i++) {
		screen->gotoXY(9, 45 + i);
		screen->printString(launchpad_bottom[i]);
	}
	for (int i = 0; i < 4; i++) {
		screen->gotoXY(59, 45 + i);
		screen->printString(launchpad_bottom[i]);
	}
}

void Board::printWinner(int i_win) {
	if (i_win == 1) {
		for (int i = 0; i < 5; i++) {
			screen->gotoXY(14, 20 + i);
			screen->printString(winText[i]);
			screen->gotoXY(62, 20 + i);
			screen->printString(loseText[i]);
		}
	}
	else if (i_win == 0) {
		for (int i = 0; i < 5; i++) {
			screen->gotoXY(12, 20 + i);
			screen->printString(loseText[i]);
			screen->gotoXY(64, 20 + i);
			screen->printString(winText[i]);
		}
	}
	else {
		for (int i = 0; i < 5; i++) {
			screen->gotoXY(16, 20 + i);
			screen->printString(tieText[i]);
			screen->gotoXY(66, 20 + i);
			screen->printString(tieText[i]);
		}
	}
}

void Board::printTimesUp(int frame) {
	if (frame % 2 == 1) {
		for (int i = 0; i < 6; i++) {
			screen->gotoXY(8, 20 + i);
			screen->printString(timesUp[i]);
			screen->gotoXY(58, 20 + i);
			screen->printString(timesUp[i]);
		}
	}
	else {
		for (int i = 0; i < 6; i++) {
			screen->gotoXY(8, 20 + i);
			screen->printString("                                    ");
			screen->gotoXY(58, 20 + i);
			screen->printString("                                    ");
		}
	}
}

std::string Board::getCountDown(int cd, int line) {
	return countDown[cd - 1][line];
}

void LaunchPad::printLaunchPad(int frame) {
	for (int i = 0; i < 11; i++) {
		screen->gotoXY(9, 34 + i);
		screen->printString(launchpad[frame][i]);
	}
	for (int i = 0; i < 11; i++) {
		screen->gotoXY(59, 34 + i);
		screen->printString(launchpad[frame][i]);
	}
}

LaunchPad::LaunchPad(Screen* s) {
	screen = s;

	launchpad[0][0] = "                                ";
	launchpad[0][1] = "                                ";
	launchpad[0][2] = "                                ";
	launchpad[0][3] = "                                ";
	launchpad[0][4] = "                      |\\        ";
	launchpad[0][5] = "               /\\     |X|       ";
	launchpad[0][6] = "              /__\\    |X|       ";
	launchpad[0][7] = "              |()|____|X|       ";
	launchpad[0][8] = "    (o)      /    \\   |X|       ";
	launchpad[0][9] = "     |      <_|TT|_>  |X|       ";
	launchpad[0][10] = "  ___|________\\==/____|X|_____  ";

	launchpad[1][0] = "                                ";
	launchpad[1][1] = "                                ";
	launchpad[1][2] = "                                ";
	launchpad[1][3] = "                                ";
	launchpad[1][4] = "                      |\\        ";
	launchpad[1][5] = "               /\\     |X|       ";
	launchpad[1][6] = "              /__\\    |X|       ";
	launchpad[1][7] = "              |()| ___|X|       ";
	launchpad[1][8] = "    (o)      /    \\   |X|       ";
	launchpad[1][9] = "     |      <_|TT|_>  |X|       ";
	launchpad[1][10] = "  ___|________\\==/____|X|_____  ";

	launchpad[2][0] = "                                ";
	launchpad[2][1] = "                                ";
	launchpad[2][2] = "                                ";
	launchpad[2][3] = "                                ";
	launchpad[2][4] = "                      |\\        ";
	launchpad[2][5] = "               /\\     |X|       ";
	launchpad[2][6] = "              /__\\    |X|       ";
	launchpad[2][7] = "              |()|  __|X|       ";
	launchpad[2][8] = "    (o)      /    \\   |X|       ";
	launchpad[2][9] = "     |      <_|TT|_>  |X|       ";
	launchpad[2][10] = "  ___|________\\==/____|X|_____  ";

	launchpad[3][0] = "                                ";
	launchpad[3][1] = "                                ";
	launchpad[3][2] = "                                ";
	launchpad[3][3] = "                                ";
	launchpad[3][4] = "                      |\\        ";
	launchpad[3][5] = "               /\\     |X|       ";
	launchpad[3][6] = "              /__\\    |X|       ";
	launchpad[3][7] = "              |()|   _|X|       ";
	launchpad[3][8] = "    (o)      /    \\   |X|       ";
	launchpad[3][9] = "     |      <_|TT|_>  |X|       ";
	launchpad[3][10] = "  ___|________\\==/____|X|_____  ";

	launchpad[4][0] = "                                ";
	launchpad[4][1] = "                                ";
	launchpad[4][2] = "                                ";
	launchpad[4][3] = "                                ";
	launchpad[4][4] = "                      |\\        ";
	launchpad[4][5] = "               /\\     |X|       ";
	launchpad[4][6] = "              /__\\    |X|       ";
	launchpad[4][7] = "              |()|    |X|       ";
	launchpad[4][8] = "    (o)      /    \\   |X|       ";
	launchpad[4][9] = "     |      <_|TT|_>  |X|       ";
	launchpad[4][10] = "  ___|________\\==/____|X|_____  ";

	launchpad[5][0] = "                                ";
	launchpad[5][1] = "                                ";
	launchpad[5][2] = "                                ";
	launchpad[5][3] = "                                ";
	launchpad[5][4] = "                                ";
	launchpad[5][5] = "               /\\     |\\        ";
	launchpad[5][6] = "              /__\\    |X|       ";
	launchpad[5][7] = "              |()|    |X|       ";
	launchpad[5][8] = "    (o)      /    \\   |X|       ";
	launchpad[5][9] = "     |      <_|TT|_>  |X|       ";
	launchpad[5][10] = "  ___|________\\==/____|X|_____  ";

	launchpad[6][0] = "                                ";
	launchpad[6][1] = "                                ";
	launchpad[6][2] = "                                ";
	launchpad[6][3] = "                                ";
	launchpad[6][4] = "                                ";
	launchpad[6][5] = "               /\\               ";
	launchpad[6][6] = "              /__\\    |\\        ";
	launchpad[6][7] = "              |()|    |X|       ";
	launchpad[6][8] = "    (o)      /    \\   |X|       ";
	launchpad[6][9] = "     |      <_|TT|_>  |X|       ";
	launchpad[6][10] = "  ___|________\\==/____|X|_____  ";

	launchpad[7][0] = "                                ";
	launchpad[7][1] = "                                ";
	launchpad[7][2] = "                                ";
	launchpad[7][3] = "                                ";
	launchpad[7][4] = "                                ";
	launchpad[7][5] = "               /\\               ";
	launchpad[7][6] = "              /__\\              ";
	launchpad[7][7] = "              |()|    |\\        ";
	launchpad[7][8] = "    (o)      /    \\   |X|       ";
	launchpad[7][9] = "     |      <_|TT|_>  |X|       ";
	launchpad[7][10] = "  ___|________\\==/____|X|_____  ";

	launchpad[8][0] = "                                ";
	launchpad[8][1] = "                                ";
	launchpad[8][2] = "                                ";
	launchpad[8][3] = "                                ";
	launchpad[8][4] = "                                ";
	launchpad[8][5] = "               /\\               ";
	launchpad[8][6] = "              /__\\              ";
	launchpad[8][7] = "              |()|              ";
	launchpad[8][8] = "    (o)      /    \\   |\\        ";
	launchpad[8][9] = "     |      <_|TT|_>  |X|       ";
	launchpad[8][10] = "  ___|________\\==/____|X|_____  ";

	launchpad[9][0] = "                                ";
	launchpad[9][1] = "                                ";
	launchpad[9][2] = "                                ";
	launchpad[9][3] = "                                ";
	launchpad[9][4] = "                                ";
	launchpad[9][5] = "               /\\               ";
	launchpad[9][6] = "              /__\\              ";
	launchpad[9][7] = "              |()|              ";
	launchpad[9][8] = "    (o)      /    \\             ";
	launchpad[9][9] = "     |      <_|TT|_>  |\\        ";
	launchpad[9][10] = "  ___|________\\==/____|X|_____  ";

	launchpad[10][0] = "                                ";
	launchpad[10][1] = "                                ";
	launchpad[10][2] = "                                ";
	launchpad[10][3] = "                                ";
	launchpad[10][4] = "                                ";
	launchpad[10][5] = "               /\\               ";
	launchpad[10][6] = "              /__\\              ";
	launchpad[10][7] = "              |()|              ";
	launchpad[10][8] = "    (o)      /    \\             ";
	launchpad[10][9] = "     |      <_|TT|_>            ";
	launchpad[10][10] = "  ___|________\\==/____|\\______  ";

	launchpad[11][0] = "                                ";
	launchpad[11][1] = "                                ";
	launchpad[11][2] = "                                ";
	launchpad[11][3] = "                                ";
	launchpad[11][4] = "                                ";
	launchpad[11][5] = "               /\\               ";
	launchpad[11][6] = "              /__\\              ";
	launchpad[11][7] = "              |()|              ";
	launchpad[11][8] = "    (o)      /    \\             ";
	launchpad[11][9] = "     |      <_|TT|_>            ";
	launchpad[11][10] = "  ___|________\\==/____________  ";

	launchpad[12][0] = "                                ";
	launchpad[12][1] = "                                ";
	launchpad[12][2] = "                                ";
	launchpad[12][3] = "                                ";
	launchpad[12][4] = "                                ";
	launchpad[12][5] = "               /\\               ";
	launchpad[12][6] = "              /__\\              ";
	launchpad[12][7] = "              |()|              ";
	launchpad[12][8] = "    (o)      /    \\             ";
	launchpad[12][9] = "     |      <_|TT|_>            ";
	launchpad[12][10] = "  ___|_______v\\==/v___________  ";

	launchpad[13][0] = "                                ";
	launchpad[13][1] = "                                ";
	launchpad[13][2] = "                                ";
	launchpad[13][3] = "                                ";
	launchpad[13][4] = "                                ";
	launchpad[13][5] = "               /\\               ";
	launchpad[13][6] = "              /__\\              ";
	launchpad[13][7] = "              |()|              ";
	launchpad[13][8] = "    (o)      /    \\             ";
	launchpad[13][9] = "     |      <_|TT|_>            ";
	launchpad[13][10] = "  ___|______v^\\==/^v__________  ";

	launchpad[14][0] = "                                ";
	launchpad[14][1] = "                                ";
	launchpad[14][2] = "                                ";
	launchpad[14][3] = "                                ";
	launchpad[14][4] = "                                ";
	launchpad[14][5] = "               /\\               ";
	launchpad[14][6] = "              /__\\              ";
	launchpad[14][7] = "              |()|              ";
	launchpad[14][8] = "    (o)      /    \\             ";
	launchpad[14][9] = "     |      <_|TT|_>            ";
	launchpad[14][10] = "  ___|_____v^v\\==/v^v_________  ";

	launchpad[15][0] = "                                ";
	launchpad[15][1] = "                                ";
	launchpad[15][2] = "                                ";
	launchpad[15][3] = "                                ";
	launchpad[15][4] = "               /\\               ";
	launchpad[15][5] = "              /__\\              ";
	launchpad[15][6] = "              |()|              ";
	launchpad[15][7] = "             /    \\             ";
	launchpad[15][8] = "    (o)     <_|TT|_>            ";
	launchpad[15][9] = "     |        \\==/              ";
	launchpad[15][10] = "  ___|_________V^_____________  ";

	launchpad[16][0] = "                                ";
	launchpad[16][1] = "                                ";
	launchpad[16][2] = "                                ";
	launchpad[16][3] = "               /\\               ";
	launchpad[16][4] = "              /__\\              ";
	launchpad[16][5] = "              |()|              ";
	launchpad[16][6] = "             /    \\             ";
	launchpad[16][7] = "            <_|TT|_>            ";
	launchpad[16][8] = "    (o)       \\==/              ";
	launchpad[16][9] = "     |         ^V               ";
	launchpad[16][10] = "  ___|_________V^_____________  ";

	launchpad[17][0] = "                                ";
	launchpad[17][1] = "                                ";
	launchpad[17][2] = "               /\\               ";
	launchpad[17][3] = "              /__\\              ";
	launchpad[17][4] = "              |()|              ";
	launchpad[17][5] = "             /    \\             ";
	launchpad[17][6] = "            <_|TT|_>            ";
	launchpad[17][7] = "              \\==/              ";
	launchpad[17][8] = "    (o)        V^               ";
	launchpad[17][9] = "     |         ^V               ";
	launchpad[17][10] = "  ___|________^V^V____________  ";

	launchpad[18][0] = "                                ";
	launchpad[18][1] = "               /\\               ";
	launchpad[18][2] = "              /__\\              ";
	launchpad[18][3] = "              |()|              ";
	launchpad[18][4] = "             /    \\             ";
	launchpad[18][5] = "            <_|TT|_>            ";
	launchpad[18][6] = "              \\==/              ";
	launchpad[18][7] = "               ^V               ";
	launchpad[18][8] = "    (o)        V^               ";
	launchpad[18][9] = "     |         ^V               ";
	launchpad[18][10] = "  ___|_______V^V^V^___________  ";

	launchpad[18][0] = "               /\\               ";
	launchpad[18][1] = "              /__\\              ";
	launchpad[18][2] = "              |()|              ";
	launchpad[18][3] = "             /    \\             ";
	launchpad[18][4] = "            <_|TT|_>            ";
	launchpad[18][5] = "              \\==/              ";
	launchpad[18][6] = "               ^V               ";
	launchpad[18][7] = "               V^               ";
	launchpad[18][8] = "    (o)        ^V               ";
	launchpad[18][9] = "     |         V^               ";
	launchpad[18][10] = "  ___|________________________  ";


}