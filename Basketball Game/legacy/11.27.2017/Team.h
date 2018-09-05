#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

namespace Ball {
	class Player;
	class Database;

	class Team {
	public:
		// Constructor
		Team(const std::string& name, Database* d, int pos);

		//Write a Destructor

		//Drafting code
		virtual void draft();

		//Stat building
		void buildStats();

		//Getters and Setters
		bool getComputer() const;
		Database* getD() const;

		//Play method
		int play(Team* rhs);

		//Debug Display, will display hidden stats for development check
		void debugDisplay() const;

		//Possession Flowgraph Methods
		bool steal(float turnovers);

		bool shot();

		bool block(float block);

		bool rebound(float offensiveRebound);


	protected:
		std::vector<Player*> players;

		//Setters and Getters
		void setComputer();
	private:
		std::string name;
		Database* d;
		bool computer = false;
		int possession;

		//Changing var during play()
		int tPoint; // Total points by team
		int tRebound; // Total rebounds by team
		int tAssist; // Total assists by team
		int tSteal; // Total steals by team
		int tBlock; // Total blocks by team
		int tTurnover; // Total turnovers by team

		//Constant stats to use
		float orMod; //Offensive Rebounding Modifier %
		float blkMod; //Blocking Modifier, %
		float stlMod; //Steal Modifier, %
		float tto = 0; //Total Avg Turnovers
	};

	class AI : public Team {
	public:
		AI(Database* d);

		void draft();
	};

}

#endif