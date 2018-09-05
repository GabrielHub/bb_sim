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

	private:
		// Set the Offensive Rebounding Tendency
		void setOrt(float offensive, float defensive) {
			ort = offensive / defensive;
		}
		// Set Three Pointer Tendency
		void setTpt(float threes, float twos) {
			tpt = threes / twos;
		}


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
		int ort; // Offensive Rebounding Tendency, OR/DR
		int tpt; // Three Pointer Tendency, 3PA/FGA

		//Vitals
		bool drafted; //If they are available to draft or not
		std::string name; // Player name
	};
}

#endif