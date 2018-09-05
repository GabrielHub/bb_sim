#include "Player.h"
#include "Database.h"
#include "Team.h"

using namespace std;

namespace Ball {
	//Constructor declaration
	Team::Team(const string& name, Database* d, int pos) : name(name), d(d), tPoint(0), tAssist(0), tRebound(0), tSteal(0), tBlock(0), tTurnover(0), possession(pos) {}

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
		cout << "and " << *players[4] << endl;
		buildStats();
	}

	//Goes over drafted players and builds tendencies and stats for the team
	void Team::buildStats() {
		// Set base numbers
		tto = 0;
		orMod = 0;
		stlMod = 0;
		blkMod = 0;

		//Loop through players to find stats
		for (size_t i = 0; i < players.size(); ++i) {
			float temp = players[i]->getOrt(); // Holding variable
			//cout << "ORT: " << temp << endl;

			if (temp > orMod) {
				orMod = temp;
			} // Get the best Offensive Rebound Tendency

			tto += players[i]->getTurnovers(); // Finding total Turnovers

			temp = players[i]->getBlocks();
			if (temp > blkMod) {
				blkMod = temp;
			} //Get best blocker's avg blocks

			stlMod += players[i]->getSteals(); // Add to total steals
		}
		
		//Build ORT
		if ((orMod * 100) > 25.0) {
			orMod = 22.6 + ((orMod * 100) - 25.0);
		}
		else {
			orMod = 22.6 - (25.0 - (orMod * 100));
		}

		//Build block
		blkMod = 6.9 + (blkMod - 2); 

		//Build Steal
		stlMod = (10.4 - stlMod) + (stlMod - 5.7);
		
		//Temporary debugger
		debugDisplay();
	}

	//Code to play teams, returns a number that corresponds to who owns the next possession
	int Team::play(Team* rhs) {
		//REVISION: Insert jumpball here instead of possession going to p1
		if (steal(rhs->stlMod)) {
			tTurnover += 1;
			rhs->tSteal += 1;
			return rhs->possession;
		}
		else {
			//Next do block
			if (block(rhs->blkMod)) {

			}

			//Then do shot

			//Then do the hokeypoke
		}
		return possession;
	}

	//Debugging
	void Team::debugDisplay() const {
		cout << "DEBUGGING" << endl;
		cout << "===================================" << endl;
		cout << name << " has " << tto << " Total Turnovers, " << orMod << " OR%, " << stlMod << " Steal %, " << blkMod << " block %." << endl;
	}

	//Steal code is done!
	bool Team::steal(float turnovers) {
		/*
		Steals per game should be based on your teams total steals, avg that against the min and max in the nba rn. 10.4 max, 5.7 min.
		Steal % is now (10.4 - stlMod) + (stlMod - 5.7) 
		A steal will happen if a random number picked between the steal % to a hundred is less than the opposing total turnovers
		*/
		srand(time(NULL));

		int stealPercent = rand() % 100 + int(stlMod + 0.5);
		if (stealPercent <= turnovers) {
			return true;
		}
		else {
			return false;
		}
	} 

	bool Team::shot() {

		return false;
	}

	bool Team::block(float block) {
		/*
		Percentage will start at 6.9%. It should max at 9.9% and min at 3.9%.
		Percentage will change by + (block modifier - 2). Note that the number of blocks per game max at 8.9 and min at 3.3.
		*/
		default_random_engine generator;
		bernoulli_distribution distribution(block);

		return false;
	}

	bool Team::rebound(float offensiveRebound) {
		/*
		Offensive Rebouding Percents will start at 22.6%. Using the offensive rebounding modifier, the percent should max at 27% and min at 17%.
		Based on how much higher or lower the Offensive rebounding is from the average, we'll modify the standard 22.6%
		If the % is over 25% we add, if not we subtract. That number can change until we're happy with the results.
		*/
		

		return false;
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

	AI::AI(Database* d) : Team("Computer", d, 2) {
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