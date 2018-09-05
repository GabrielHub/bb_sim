#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

namespace Ball {

	class Player;
	class Team;

	class Database {
	public:
		//Constructor
		Database();

		//Destructor
		~Database();

		Player* pick(bool computer);
	private:
		std::vector<Player*> database; //Database of all players (Currently current)
	};
}

#endif