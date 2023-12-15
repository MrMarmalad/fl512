#include "GameRecord.h"

#include <iostream>


bool GameRecord::equal(GameRecord testRecord, bool strictEq = true) const {
		if (strictEq == true) {
			return (
				this->genre == testRecord.genre &&
				this->name == testRecord.name &&
				this->year == testRecord.year
				);
		}
		else {
			return (
				(this->genre == testRecord.genre || this->genre.empty() || testRecord.genre.empty()) &&
				(this->name == testRecord.name || this->name.empty() || testRecord.name.empty()) &&
				(this->year == testRecord.year || this->year == 0 || testRecord.year == 0)
				);
		}
	}

	bool GameRecord::empty() const {
		if (this->genre.empty() && this->name.empty() && this->year == 0) {
			return true;
		}
		return false;
	}

	void GameRecord::printRecord() const {
		cout << this->name << "\t" << this->genre << "\t" << this->year << endl;
	}