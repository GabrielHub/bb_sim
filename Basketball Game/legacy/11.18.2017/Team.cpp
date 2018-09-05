#include "Player.h"
#include "Database.h"
#include "Team.h"

using namespace std;

namespace Ball {
	//Constructor declaration
	Team::Team(const string& name, Database* d) : name(name), d(d) {}

	//Drafting code
	void Team::draft() {
		cout << "\n It's " << name << "'s time to draft! You will be given 5 random players to pick from for each position!" << endl;

		for (size_t i = 0; i < 5; ++i) {
			cout << "Pick a player for your " << i + 1 << " slot!" << endl;
			players.push_back(d->pick(false));
			cout << name << " picked " << *players[i] << endl;
		}

		//Display picked team
		cout << name << "'s team is: ";
		for (size_t i = 0; i < 4; ++i) {
			cout << *players[i] << ", ";
		}
		cout << " and " << players[4] << endl;
	}

	//Code to play teams
	void Team::play() {

	}

	Database* Team::getD() const {
		return d;
	}

	bool Team::getComputer() const {
		return computer;
	}

	void Team::setComputer() {
		computer = true;
	}



	//AI Definitions

	AI::AI(Database* d) : Team("Computer", d) {
		setComputer();
	}

	void AI::draft() {
		cout << "The AI is now autodrafting..." << endl;

		for (size_t i = 0; i < 5; ++i) {
			players.push_back(getD()->pick(true));
		}

		//Display picked team
		cout << "Computer's team is: ";
		for (size_t i = 0; i < 4; ++i) {
			cout << *players[i] << ", ";
		}
		cout << " and " << players[4] << endl;
	}
}