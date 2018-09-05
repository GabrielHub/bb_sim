#include "Player.h"
#include "Team.h"
#include "Database.h"
using namespace std;
using namespace Ball;

/*
11/17/2017 - Last Roster Update
A basketball simluation game by Gabriel Ong and Thomas Tierney

Game currently runs with two players drafting teams and then playing each other.
Both players will first draft. They will be given 5 random players to choose for each postion.

Last Edit:
Write play code for Team and then for AI
*/

int main() {
	bool playing = true; // Check if game is still running

	//Create new Database
	Database* dp = new Database();

	//Start actual program
	cout << "Welcome to a Basketball simulator! - Enter 'Exit' at any time to quit!\n" << "Type in the number before a command to enter a command!" << endl;
	cout << "==================================\n" << endl;
	

	string command; //Use a string so if someone types in a nonexistent command we won't run into errors
	// Draft, Game will currently work with 2 players 
	cout << "Player 1, enter your name: \n";
	cin >> command;
	Team* p1 = new Team(command, dp);

	cout << "Play against computer or player 2?\n" << "1. Computer, 2. Player" << endl;
	cin >> command;

	Team* p2;

	if (command == "1") {
		p2 = new AI(dp);
	}
	else {
		cout << "Player 2, enter your name: ";
		cin >> command;
		cout << endl;
		p2 = new Team(command, dp);
	}

	cout << "=================================" << endl;
	p1->draft();
	cout << "\n==============================" << endl;
	p2->draft();
	cout << "\n==============================" << endl;

	cout << "How to play:\n" << "During each possession type 'Enter' " << endl;

	//Code for Playing
	while (playing) {
		
		cin >> command;
		if (command == "Exit" || command == "exit") {
			playing = false;
		}
		else {
			if (p2->getComputer()) {

			}
			else {

			}
		}
	}

	exit(0);
}