#include "Player.h"
using namespace std;

namespace Ball {
	//Constructor
	Player::Player(float fgm, float fga, float fgp, float tpm, float tpa, float tpp, float offr, float defr, float ast, float blk, float stl, float to, float pts, const std::string& name)
		: fgm(fgm), fga(fga), fgp(fgp), tpm(tpm), tpp(tpp), offr(offr), defr(defr), ast(ast), blk(blk), stl(stl), to(to), pts(pts), name(name), drafted(false) {
		/*setOrt(offr, defr);
		setTpt(tpa, fga);*/
	}

	//Copy Constructor
	Player::Player(const Player& rhs) {
		fgm = rhs.fgm;
		fga = rhs.fga;
		fgp = rhs.fgp;
		tpm = rhs.tpm;
		tpa = rhs.tpa;
		tpp = rhs.tpp;
		offr = rhs.offr;
		defr = rhs.defr;
		ast = rhs.ast;
		blk = rhs.blk;
		stl = rhs.stl;
		to = rhs.to;
		pts = rhs.pts;
		name = rhs.name;
	}

	//Overload display operator
	ostream& operator<<(ostream& os, const Player& rhs) {
		os << rhs.name;
		return os;
	}

	

	// Set the Offensive Rebounding Tendency
	/*void Player::setOrt(float offensive, float defensive) {
		ort = offensive / defensive;
	}*/
	// Set Three Pointer Tendency
	/*void Player::setTpt(float threes, float twos) {
		tpt = threes / twos;
	}*/

	//Getters and Setters
	bool Player::isDrafted() const {
		return drafted;
	}
	void Player::getDrafted() {
		drafted = true;
	}
	float Player::getTurnovers() const {
		return to;
	}
	float Player::getOrt() const {
		return offr / (defr + offr);
	}
	float Player::getSteals() const {
		return stl;
	}
	float Player::getBlocks() const {
		return blk;
	}
}