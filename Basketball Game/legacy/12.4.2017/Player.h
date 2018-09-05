#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <vector>

namespace Ball {

	class Player {
	public:
		// Constructor Declaration
		Player(float fgm, float fga, float fgp, float tpm, float tpa, float tpp, float offr, float defr, float ast, float blk, float stl, float to, float pts, const std::string& name);

		//Copy Constructor
		Player(const Player& rhs);

		//Write Operator Overload <<
		friend std::ostream& operator<<(std::ostream& os, const Player& rhs);

		bool isDrafted() const;

		void getDrafted();

		//Getters
		float getTurnovers() const; 
		float getOrt() const;
		float getMaxSteals() const; // returns avg steals 
		float getMaxBlocks() const; // returns avg blocks
		std::string getName() const;
		int getfga() const; // returns fga
		float getMaxfga() const; // returns the avg fga player takes
		float gettpt() const; //returns three point tendency
		float getfgp() const;
		float gettpp() const;
		float getMaxReb() const; // returns avg rebounds player takes
		float getMaxAssist() const; // returns avg assists
		int getAssists() const;
		int getRebounds() const;
		int getSteals() const;
		int getBlocks() const;

		//Setters
		void setPoints(int add);
		void setAssists();
		void setRebounds();
		void setSteals();
		void setBlocks();
		void setTurnovers();
		void setfga();
	private:
		// Set the Offensive Rebounding Tendency
		//void setOrt(float offensive, float defensive);
		// Set Three Pointer Tendency
		//void setTpt(float threes, float twos);

		//Dynamic Stats
		int points = 0;
		int assists = 0;
		int rebounds = 0;
		int steals = 0;
		int blocks = 0;
		int turnovers = 0;
		int fieldgoalattempts = 0;

		//Average Stats
		float fgm; // Field Goals Made
		float fga; // Field Goals Attempted
		float fgp; // Field Goal Percentage %
		float tpm; // Three Pointers Made
		float tpa; // Three Pointers Attempted
		float tpp; // Three Pointer Percentage %
		float offr; // Offensive Rebounds
		float defr; // Defensive Rebounds
		float ast; // Assists
		float blk; // Blocks
		float stl; // steals
		float to; // turnovers
		float pts; // Points avg

		//Other 
		//float ort; // Offensive Rebounding Tendency, OR/DR
		//float tpt; // Three Pointer Tendency, 3PA/FGA

		//Vitals
		bool drafted; //If they are available to draft or not
		std::string name; // Player name
	};
}

#endif