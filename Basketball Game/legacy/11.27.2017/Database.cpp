#include "Player.h"
#include "Team.h"
#include "Database.h"
using namespace std;

namespace Ball {

	//Constructor that builds database using Players.txt file
	Database::Database() {
		cout << "Loading players..." << endl;
		ifstream ifs("Players.txt");
		if (!ifs) {
			cerr << "Could not open the file, Failed to open players." << endl;
			exit(1);
		} //Check if file could not be opened

		  //Input Variables
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
		string fName;
		string lName;
		string name;

		while (ifs >> fName >> lName) {
			ifs >> fgm;
			ifs >> fga;
			ifs >> fgp;
			ifs >> tpm;
			ifs >> tpa;
			ifs >> tpp;
			ifs >> offr;
			ifs >> defr;
			ifs >> ast;
			ifs >> blk;
			ifs >> stl;
			ifs >> to;
			ifs >> pts;
			name = fName + " " + lName;
			database.push_back(new Player(fgm, fga, fgp, tpm, tpa, tpp, offr, defr, ast, blk, stl, to, pts, name));
		}
		cout << "All Players loaded! \n=======================================" << endl;
		ifs.close();
	}

	Database::~Database() {
		//Remove from heap
		for (Player*& i : database) {
			delete i;
		}
		database.clear();
	}

	Player* Database::pick(bool computer) {
		srand(time(NULL)); //Random Seed
		//Check if AI team or not
		if (computer) {
			int num = rand() % (database.size() - 1);
			while (database[num]->isDrafted()) {
				num = rand() % (database.size() - 1);
			}
			database[num]->getDrafted();
			return new Player(*database[num]);
		}
		else {
			int command;
			vector<int> ind;
			for (size_t i = 0; i < 5; ++i) {
				int num = rand() % (database.size() - 1);
				while (database[num]->isDrafted()) {
					num = rand() % (database.size() - 1);
				}
				ind.push_back(num);
				cout << " " << i + 1 << ". " << *database[num];
			}
			cout << "\n Pick a player by typing in the number before their name!" << endl;
			cin >> command;
			while (command >= 6 || command <= 0 || database[ind[command - 1]]->isDrafted()) {
				cout << "Either that player is already drafted or you entered the command wrong. Try again!" << endl;
				cin >> command;
			}
			database[ind[command - 1]]->getDrafted();
			return new Player(*database[ind[command - 1]]);
		}
	}
}