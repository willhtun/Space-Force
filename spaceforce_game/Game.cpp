#include "Game.h"
#include <string>
#include <math.h>

const int BOARD_HEIGHT = 50;
const int BOARD_WIDTH = 101; // Must be odd number

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

Game::Game(int width, int height)
 : m_screen(BOARD_WIDTH, BOARD_HEIGHT + 10), m_board(BOARD_WIDTH, BOARD_HEIGHT, &m_screen), rocket_p1(&m_screen), rocket_p2(&m_screen), m_launchpad(&m_screen), m_scoreboard(&m_screen)
{
}

void Game::printCountDown(int c) {
	for (int i = 0; i < 5; i++) {
		m_screen.gotoXY(20, 10 + i);
		m_screen.printString(m_board.getCountDown(c, i));
		m_screen.gotoXY(BOARD_WIDTH / 2 + 20, 10 + i);
		m_screen.printString(m_board.getCountDown(c, i));
	}
}

void Game::cursorClear() {
	m_screen.gotoXY(0, BOARD_HEIGHT + 1);
}

void Game::play()
{
	// Server Variables
	bool isReady = false;
	// Variables
	char input;
	bool pressedLeft = false, firstPress = true;
	int taps = 0;
	int taps_oppo = 0;
	int timeReset;
	int frames = 1;

	m_board.printBoard();
	m_launchpad.printLaunchPad(0);

	m_screen.gotoXY(13, 42);
	m_screen.printString("( )");
	m_screen.gotoXY(63, 42);
	m_screen.printString("(x)");

	// Scoreboard
	m_scoreboard.printScoreBoard();

	waitForEnter();

	// Waiting to connect
	Timer timer;
	frames = 1;
	while (!isReady) {
		while (timer.elapsed() < 500 * frames) {}
		if (frames % 4 == 0) {
			m_screen.gotoXY(13, 20);
			m_screen.printString("Waiting for opponent   ");
		}
		if (frames % 4 == 1) {
			m_screen.gotoXY(13, 20);
			m_screen.printString("Waiting for opponent.  ");
		}
		if (frames % 4 == 2) {
			m_screen.gotoXY(13, 20);
			m_screen.printString("Waiting for opponent.. ");
		}
		if (frames % 4 == 3) {
			m_screen.gotoXY(13, 20);
			m_screen.printString("Waiting for opponent...");
		}
		m_screen.gotoXY(67, 20);
		m_screen.printString("(x) Disconnected");
		cursorClear();
		frames++;
		if (getCharIfAny(input)) {
			if (input == ARROW_UP) {
				m_screen.gotoXY(13, 20);
				m_screen.printString("                       ");
				m_screen.gotoXY(67, 20);
				m_screen.printString("                       ");
				isReady = true;
			}
		}

	}
	
	//CountDown
	timeReset = timer.elapsed();
	for (int i = 1; i <= 5; i++) {
		printCountDown(i);
		while (i != 5 && timer.elapsed() - timeReset < 1000 * i) {}
	}

	// Tap 
	frames = 1;
	discardPendingKeys();
	timeReset = timer.elapsed();
	while (timer.elapsed() - timeReset < 5000) { // 4 sec 4000
		getCharIfAny(input);
		if (input == ARROW_LEFT && (!pressedLeft || firstPress)) {
			taps++;
			pressedLeft = true;
			firstPress = false;
			m_screen.gotoXY(13, 42);
			m_screen.printString("(o)");
		}
		else if (input == ARROW_RIGHT && (pressedLeft || firstPress)) {
			taps++;
			pressedLeft = false;
			firstPress = false;
			m_screen.gotoXY(13, 42);
			m_screen.printString("( )");
		}
		
		m_screen.gotoXY(0, BOARD_HEIGHT + 3);
		m_screen.printStringClearLine(std::to_string(taps));

		frames++;
	}	

	// Time's Up
	frames = 1;
	timeReset = timer.elapsed();
	while (frames < 7) {
		while ((timer.elapsed() - timeReset) < 500 * frames) {}
		m_board.printTimesUp(frames);
		frames++;
	}

	// Delay
	timeReset = timer.elapsed();
	while ((timer.elapsed() - timeReset) < 1000) {}

	// Takeoff
	frames = 1;
	int launchpad_frameNum = 1;
	int flameLoopCount = 0;
	timeReset = timer.elapsed();
	while (1){
		while ((timer.elapsed() - timeReset) < 100 * frames) {}
		m_launchpad.printLaunchPad(launchpad_frameNum);
		launchpad_frameNum++;
		frames++;
		if (launchpad_frameNum == 14 && flameLoopCount < 4) {
			launchpad_frameNum = 12;
			flameLoopCount++;
		}
		if (launchpad_frameNum == 15 && taps == 0) {
			m_launchpad.printLaunchPad(11);
			break;
		}
		if (launchpad_frameNum > 19)
			break;
	}


	// Movement (tentative)
	double totalDistance = 0;
	double prevTotalDistance = 0;
	double changeInDistance = 0;

	double totalDistance_oppo = 0;
	double prevTotalDistance_oppo = 0;
	double changeInDistance_oppo = 0;

	double t;
	frames = 1;

	Timer movementTimer;

	if (taps > 0 || taps_oppo > 0) {
		while (changeInDistance >= 0 || changeInDistance_oppo >= 0) {

			while (movementTimer.elapsed() < (1000 * frames) / 60) { /* delay */ }
			t = (movementTimer.elapsed() / 200); // Slow down slower

			prevTotalDistance = totalDistance;
			totalDistance = (taps / 2.0)*(sqrt(1 - ((t - taps)*(t - taps) / (taps*taps))));
			changeInDistance = totalDistance - prevTotalDistance;

			prevTotalDistance_oppo = totalDistance_oppo;
			totalDistance_oppo = (taps_oppo / 2.0)*(sqrt(1 - ((t - taps_oppo)*(t - taps_oppo) / (taps_oppo*taps_oppo))));
			changeInDistance_oppo = totalDistance_oppo - prevTotalDistance_oppo;

			srand(time(NULL));

			if (changeInDistance >= 0) {
				rocket_p1.setElevation((totalDistance * 500) + (rand() % 100));
				rocket_p1.printFrame((frames / 10) % 2, 18, 35 - totalDistance, true);
			}

			if (changeInDistance_oppo >= 0) {
				rocket_p2.setElevation((totalDistance_oppo * 500) + (rand() % 100));
				rocket_p2.printFrame((frames / 10) % 2, 68, 35 - totalDistance_oppo, false);
			}
		
			frames++;
		}

		/*
		timeReset = movementTimer.elapsed();
		while (movementTimer.elapsed() - timeReset < 1000 / 5) {}
		rocket_p1.printFrame(2, 18, 35 - totalDistance);
		rocket_p2.printFrame(2, 68, 35 - totalDistance);

		timeReset = movementTimer.elapsed();
		while (movementTimer.elapsed() -s timeReset < 1000 / 3) {}
		rocket_p1.printFrame(3, 18, 35 - totalDistance);
		rocket_p2.printFrame(3, 68, 35 - totalDistance);

		timeReset = movementTimer.elapsed();
		while (movementTimer.elapsed() - timeReset < 1000 / 2) {}
		rocket_p1.printFrame(4, 18, 35 - totalDistance);
		rocket_p2.printFrame(4, 68, 35 - totalDistance);

		timeReset = movementTimer.elapsed();
		while (movementTimer.elapsed() - timeReset < 1000 / 1) {}
		rocket_p1.printFrame(5, 18, 35 - totalDistance);
		rocket_p2.printFrame(5, 68, 35 - totalDistance);
		*/

		cursorClear();
	}

	int winner;
	if (taps > taps_oppo)
		winner = 1;
	else if (taps < taps_oppo)
		winner = 0;
	else
		winner = 2;
	m_board.printWinner(winner);
	cursorClear();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}