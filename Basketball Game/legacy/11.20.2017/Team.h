#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <iostream>
#include <vector>

namespace Ball {
	class Player;
	class Database;

	class Team {
	public:
		// Constructor
		Team(const std::string& name, Database* d);

		//Write a Destructor

		//Drafting code
		virtual void draft();

		//Stat building
		void buildStats();

		//Getters and Setters
		bool getComputer() const;
		Database* getD() const;
		

		void play(Team* rhs);

		//Possession Flowgraph Methods
		/*bool steal(const Player& offense, const Player& defense);

		bool shot(const Player& offense);

		bool block(const Player& deffense);

		bool rebound(const Player& offense, const Player& deffense);*/


	protected:
		std::vector<Player*> players;

		//Setters and Getters
		void setComputer();
	private:
		std::string name;
		Database* d;
		bool computer = false;

		//Changing var during play()
		int tPoint; // Total points by team
		int tRebound; // Total rebounds by team
		int tAssist; // Total assists by team
		int tSteal; // Total steals by team
		int tBlock; // Total blocks by team
		int tTurnover; // Total turnovers by team

		//Constant stats to use
		float orMod; //Offensive Rebounding Modifier
		float blkMod; //Blocking Modifier
		float stlMod; //Steal Modifier
		float tto; //Total Avg Turnovers
	};

	class AI : public Team {
	public:
		AI(Database* d);

		void draft();
	};

}

#endif