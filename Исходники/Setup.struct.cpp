STAT Setup::getHighestAbility(std::vector<STAT> stats) {
	unsigned int max_value = 0;
	for (unsigned int i = 0; i < NUM_STAT; i++) {
		for (unsigned int j = 0; j < stats.size(); j++) {
			if (stats[j] == STAT(i)) max_value = std::max(max_value, this->getMax(stats[j]));
		}
	}
	if (max_value == getMax(STR)) return STR;
	else if (max_value == getMax(STA)) return STA;
	else if (max_value == getMax(AGI)) return AGI;
	else if (max_value == getMax(SEN)) return SEN;
	else if (max_value == getMax(INT)) return INT;
	else if (max_value == getMax(PSY)) return PSY;
	else return NUM_STAT;
}