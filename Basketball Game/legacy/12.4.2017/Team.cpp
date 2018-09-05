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
			cout << name << " picked " << players[i]->getName() << endl;
		}

		//Display picked team
		cout << name << "'s team is: ";
		for (size_t i = 0; i < 4; ++i) {
			cout << players[i]->getName() << ", ";
		}
		cout << "and " << players[4]->getName() << endl;
		buildStats();
	}

	int Team::getTotalPoints() const {
		return tPoint;
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
		//debugDisplay();
	}

	//Code to play teams, returns a number that corresponds to who owns the next possession
	int Team::play(Team* rhs) {
		//REVISION: Insert jumpball here instead of possession going to p1
		cout << name << " has possession!" << endl;
		if (steal(rhs->stlMod)) {
			cout << "Steal!" << endl;
			tTurnover += 1;
			rhs->tSteal += 1;
			return rhs->possession;
		}
		else {
			//Next do block
			if (block(rhs->blkMod)) {
				cout << "Blocked!" << endl;
				rhs->tBlock += 1;
				//Check for rebound
				if (rebound(orMod)) {
					cout << "Team " << possession << " Offensive Rebound!" << endl;
					tRebound += 1;
					return possession;
				}
				else {
					cout << "Defensive Rebound!" << endl;
					rhs->tRebound += 1;
					return rhs->possession;
				}
			}

			//Then do shot
			else {
				int pointAttempt = shot();
				if (pointAttempt != 0) {
					//If they made the shot
					tPoint += pointAttempt;
					/*
					Assist max % is 0.692, min is 0.486. this is the odds a field goal is assisted. 58.9% chance for an assist.
					At the moment, assists are static.
					*/
					return rhs->possession;
				}
				else {
					//Check for rebound after missed shot
					if (rebound(orMod)) {
						cout << "Team " << possession << " Offensive Rebound!" << endl;
						tRebound += 1;
						return possession;
					}
					else {
						cout << "Defensive Rebound!" << endl;
						rhs->tRebound += 1;
						return rhs->possession;
					}
				}
			}
		}
	}

	void Team::display() const {
		cout << name << " has: " << tPoint << " points, " << tAssist << " assists, " << tRebound << " rebounds, " << tSteal << " steals, " << tBlock << " blocks, and " << tTurnover << " Turnovers." << endl;
		cout << endl;
	}

	//Debugging
	void Team::debugDisplay() const {
		cout << "DEBUGGING" << endl;
		cout << "===================================" << endl;
		cout << name << " has " << tto << " Total Turnovers, " << orMod << " OR%, " << stlMod << " Steal %, " << blkMod << " block %." << endl;
		for (size_t i = 0; i < players.size(); ++i) {
			cout << *players[i] << endl;
		}
	}

	//Steal code is done!
	bool Team::steal(float turnovers) const {
		/*
		StlMod should be based on your teams total steals, avg that against the min and max in the nba rn. 10.4 max, 5.7 min.
		Steal % is now (10.4 - stlMod) + (stlMod - 5.7) 
		A steal will happen if a random number picked between the steal % to a hundred is less than the opposing total turnovers
		*/
		srand(time(NULL));

		int stealPercent = rand() % 100 + int(stlMod + 0.5);
		if (stealPercent <= turnovers) {
			//Add stat to player
			return true;
		}
		else {
			return false;
		}
	} 

	int Team::shot() {
		// At the moment, if a player has already reached their avg fga, pick another player to give a shot to
		int player = statGiver(0);
		cout << players[player]->getName() << " has the ball." << endl;
		
		//See if they take a 3 pointer
		if (rng(players[player]->gettpt())) {
			//cout << players[player]->getName() << " takes a 3 pointer!" << endl;
			if (rng(players[player]->gettpp())) {
				cout << players[player]->getName() << " makes it from 3!" << endl;
				players[player]->setPoints(3);

				//Check for Assist
				if (rng(0.589)) {
					tAssist++;
					int temp_player = statGiver(2);
					while (temp_player == player) {
						temp_player = statGiver(2);
					}
					cout << players[temp_player]->getName() << " gets the assist." << endl;
					players[temp_player]->setAssists();
				}

				return 3;
			}
			else {
				cout << players[player]->getName() << " misses from from beyond the arc." << endl;
				return 0;
			}
		}
		else {
			//Shot for 2 pointer
			cout << players[player]->getName() << " with the attempt!" << endl;
			if (rng(players[player]->getfgp())) {
				cout << "That's for 2!" << endl;
				players[player]->setPoints(2);

				//Check for Assist
				if (rng(0.589)) {
					tAssist++;
					int temp_player = statGiver(2);
					while (temp_player == player) {
						temp_player = statGiver(2);
					}
					cout << players[temp_player]->getName() << " gets the assist." << endl;
					players[temp_player]->setAssists();
				}

				return 2;
			}
			else {
				cout << "He missed." << endl;
				return 0;
			}
		}
	}

	bool Team::block(float block) const {
		/*
		Percentage will start at 6.9%. It should max at 9.9% and min at 3.9%.
		Percentage will change by + (block modifier - 2). Note that the number of blocks per game max at 8.9 and min at 3.3.
		*/
	
		if (rng(block)) {
			//Add stat to player
			return true;
		}
		else {
			return false;
		}
	}

	bool Team::rebound(float offensiveRebound) const {
		/*
		Offensive Rebouding Percents will start at 22.6%. Using the offensive rebounding modifier, the percent should max at 27% and min at 17%.
		Based on how much higher or lower the Offensive rebounding is from the average, we'll modify the standard 22.6%
		If the % is over 25% we add, if not we subtract. That number can change until we're happy with the results.
		*/

		if (rng(offensiveRebound)) {
			//add Stat to player
			return true;
		}
		else {
			//Add stat to player
			return false;
		}
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

	//Function that returns a bool based on a float that is a percent of success
	bool Team::rng(float p) const {
		//default_random_engine generator;
		random_device rd;
		mt19937 gen(rd());
		if (p >= 1) {
			p /= 100;
		}
		bernoulli_distribution dis(p);
		bool ret = dis(gen);
		//cout << "RNG Percent: " << p <<  ", Bool: " << ret << endl;
		return ret;
	}

	//Function that gives a stat to a random player
	int Team::pickPlayer() const {
		srand(time(NULL));
		int player = (rand() % 4) + 0;
		return player;
	}

	//Method that figures out the best player to give a stat to
	int Team::statGiver(int statNum) const {
		int player = pickPlayer(); // Pick initial player
		// Stat for points
		if (statNum == 0) {
			//If a player already took their avg fga, try and get another player. Unless everyone already hit their max.
			if (players[player]->getfga() > players[player]->getMaxfga()) {
				player = pickPlayer();
			}
		}
		// Stat for Rebounds
		else if (statNum == 1) {
			if (players[player]->getRebounds() > players[player]->getMaxReb()) {
				player = pickPlayer();
			}
		}
		//Stat for assists
		else if (statNum == 2) {
			if (players[player]->getAssists() > players[player]->getMaxAssist()) {
				player = pickPlayer();
			}
		}
		//Stat for Steals
		else if (statNum == 3) {
			if (players[player]->getSteals() > players[player]->getMaxSteals()) {
				player = pickPlayer();
			}
		}
		//Stat for Blocks
		else if (statNum == 4) {
			if (players[player]->getBlocks() > players[player]->getMaxBlocks()) {
				player = pickPlayer();
			}
		}

		return player;
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