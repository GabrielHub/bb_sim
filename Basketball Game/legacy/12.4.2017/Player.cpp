#include "Player.h"
using namespace std;

namespace Ball {
	//Constructor
	Player::Player(float fgm, float fga, float fgp, float tpm, float tpa, float tpp, float offr, float defr, float ast, float blk, float stl, float to, float pts, const std::string& name)
		: fgm(fgm), fga(fga), fgp(fgp), tpm(tpm), tpa(tpa), tpp(tpp), offr(offr), defr(defr), ast(ast), blk(blk), stl(stl), to(to), pts(pts), name(name), drafted(false) {}

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
		os << rhs.name << ":\n " << rhs.points << " | " << rhs.assists << " | " << rhs.rebounds << " | " << rhs.steals << " | " << rhs.blocks << " |" ;
		return os;
	}


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
	float Player::getMaxSteals() const {
		return stl;
	}
	float Player::getMaxBlocks() const {
		return blk;
	}
	string Player::getName() const {
		return name;
	}
	int Player::getfga() const {
		return fieldgoalattempts;
	}
	float Player::getMaxfga() const {
		return fga;
	}
	float Player::gettpt() const {
		//cout << name << " tpa " << tpa << " fga " << fga << endl;
		return tpa / fga;
	}
	float Player::getfgp() const {
		return fgp;
	}
	float Player::gettpp() const {
		return tpp;
	}
	float Player::getMaxReb() const { 
		return offr + defr;
	}
	float Player::getMaxAssist() const {
		return ast;
	}
	int Player::getAssists() const {
		return assists;
	}
	int Player::getRebounds() const {
		return rebounds;
	}
	int Player::getSteals() const {
		return steals;
	}
	int Player::getBlocks() const {
		return blocks;
	}

	void Player::setPoints(int add) {
		points += add;
	}
	void Player::setAssists() {
		assists++;
	}
	void Player::setRebounds() {
		rebounds++;
	}
	void Player::setSteals() {
		steals++;
	}
	void Player::setBlocks() {
		blocks++;
	}
	void Player::setTurnovers() {
		turnovers++;
	}
	void Player::setfga() {
		fga++;
	}
}