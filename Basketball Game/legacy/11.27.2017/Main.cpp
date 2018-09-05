#include "Player.h"
#include "Team.h"
#include "Database.h"
using namespace std;
using namespace Ball;

/*
11/21/2017 - Last Roster Update
11/21/2017 - Last Code Base Update
A basketball simluation game by Gabriel Ong and Thomas Tierney

Game currently runs with two players drafting teams and then playing each other. (Also added AI funcitonality)
Both players will first draft. They will be given 5 random players to choose for each postion.

Last Edit:
1. Write build stats code, which means writing getters for Players to build out % modifiers for a team : DONE
2. Build out member functions following flowgraph : Do steals. Based off turnovers and steal modifiers, do those too
3. Write FGA then move on to the flowgraph
3. Write play code for Team and then for AI
*/

int main() {
	bool playing = true; // Check if game is still running

	//Create new Database
	Database* dp = new Database(); //Database Pointer

	//Start actual program
	cout << "Welcome to a Basketball simulator!\n" << "Type in the number before a command to enter a command!" << endl;
	cout << "==================================\n" << endl;
	

	string command; //Use a string so if someone types in a nonexistent command we won't run into errors
	// Draft, Game will currently work with 2 players 
	cout << "Player 1, enter your name: \n";
	cin >> command;
	Team* p1 = new Team(command, dp, 1); // Player One Pointer

	cout << "Play against computer or player 2?\n" << "1. Computer, 2. Player" << endl;
	cin >> command;

	Team* p2; // Player Two Pointer, can be AI or Player

	if (command == "1") {
		p2 = new AI(dp);
	}
	//If anything but '1' is entered, autoselect AI as p2.
	else {
		cout << "Player 2, enter your name: ";
		cin >> command;
		cout << endl;
		p2 = new Team(command, dp, 2);
	}

	cout << "==============================" << endl;
	p1->draft();
	cout << "\n==============================" << endl;
	p2->draft();
	cout << "\n==============================" << endl;

	cout << "How to play:\n" << "During each possession type 'Enter' to continue the game or 'Exit' to quit. " << endl;

	//Code for Playing
	int possession = 1; // Keeps count of whose posession it is.
	int totPos = 0; // Keeps track of the total amount of possessions. Total of 120 possessions
	while (playing) {
		
		cin >> command;
		if (command == "Exit" || command == "exit") {
			playing = false;
		}
		else if (totPos == 120) {
			//Winning code here
			playing = false;
		}
		else {
			//Code for AI play
			if (p2->getComputer()) {
				if (possession == 1) {
					//P1 plays p2
				}
				else if (possession == 2) {
					//p2 plays p1
				}
				else {
					cerr << "Error: Posession error || AI Error" << endl;
					exit(1);
				}
			}
			//Code for 2 Players
			else if (possession == 1) {
				//p1 plays p2
			}
			else if (possession == 2) {
				//p2 plays p1
			}
			else {
				cerr << "Error: Posession error" << endl;
				exit(1);
			}
		}

		totPos += 1; // Add one possession
	}

	exit(0);
}