	VOID CMT::distJournal(VOID)
	{
		this->posCurrent = this->center;
		this->posChange = this->distCoeff * norm(posCurrent - posPrev);
		if (posChange < this->distThresh) { posChange = 0; }
		this->posGrowth += this->posChange;
		this->posPrev = this->posCurrent;

		this->noteFile << LocalTime(TRUE);
		if (posChange == 0) { this->noteFile << "\n"; }
		else { this->noteFile << "\t" << to_string(posChange) << "\n"; }
	}