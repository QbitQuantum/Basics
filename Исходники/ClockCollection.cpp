bool ClockCollection::AddClocks(std::vector<SuiteRoot> suites, DWORD day_flag, DWORD hour, DWORD min, bool weekly)
{
	if (day_flag > EVERY_DAY || hour > 24 || min > 60)
		return false;

	for (int i = 0; i < DAYS_IN_WEEK; ++i)
	{
		DWORD day_of_week = day_flag & (1 << i);
		if (day_of_week)
			clocks.push_back(Clock(suites, weekly, day_of_week, hour, min));
	}

	return true;
}