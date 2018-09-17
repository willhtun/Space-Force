#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "UserInterface.h"
#include "Board.h"
#include "Rocket.h"
#include "Scoreboard.h"
#include "client.h"
#include <string>
// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
    void play();
    void displayPrompt(std::string s);
	void printCountDown(int c);
	void cursorClear();
    // [Add other members as necessary.]

  private:
	TCPClient tcp_client;
    Screen m_screen;
	Board m_board;
	Scoreboard m_scoreboard;
	Rocket rocket_p1;
	Rocket rocket_p2;
	LaunchPad m_launchpad;
    // [Add other members as necessary.]
};

#endif // GAME_INCLUDED
