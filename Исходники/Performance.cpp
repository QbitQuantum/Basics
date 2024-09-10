//printing the report
std::string ProfileMapToString(){
	//PROFILE_SECTION();
	profileCritSec.Enter();
	//IntVec2 startReportPos = IntVec2(50, 800);

	std::string outputProfileMap ="\n//===========================================================================================================\n";
	
	ProfileReports profileReportsInMap;
	if (CreateProfileReportsFromProfileMap(profileReportsInMap, true)) {
		for (ProfileReport& report : profileReportsInMap) {
			outputProfileMap += report.ProfileReportToString();
		}
	}

	//clear profile map
	s_profileMap.clear();

	outputProfileMap += "\n//===========================================================================================================\n";
	
	profileCritSec.Exit();

	return outputProfileMap;
}