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

		//Getters and Setters
		Database* getD() const;
		bool getComputer() const;

		void play();

	protected:
		std::vector<Player*> players;

		//Setters and Getters
		void setComputer();
	private:
		std::string name;
		Database* d;
		bool computer = false;
	};

	class AI : public Team {
	public:
		AI(Database* d);

		void draft();
	};

}

#endif