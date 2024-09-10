// converts the supplied string into a 64-bit time object (UTC)
uint64_t CTimeSupport::ConvertStringToTime(const string& timeString) {

	char buffer[26];
	struct tm time_tm;
	char* end_ptr = NULL;

	// reset the structure
	time_t convertTimeT = time(NULL);
	gmtime_s(&time_tm, &convertTimeT);

	char* pTime           = (char*)timeString.c_str();
	unsigned char timeLen = (unsigned char)timeString.size();

	// establish the month
	bool foundMonth = false;
	for(unsigned int i = 0; i < 12; i++) {
		if(strncmp(pTime + 4, MONTHS[i], 3) == 0) {
			time_tm.tm_mon = i;
			foundMonth     = true;
			break;
		}
	}

	if(!foundMonth) {
		cout << "ERROR: Unable to convert the month when parsing the timestamp." << endl;
		exit(1);
	}

	// establish the day of the month
	unsigned char startPos = 8;
	while(pTime[startPos] == ' ') startPos++;

	unsigned char endPos = startPos;
	while(pTime[endPos] != ' ') endPos++;
	unsigned char monthDayLen = endPos - startPos;

	//bool hasLeadingZero = false;
	//if((buffer[startPos] == '0') && (monthDayLen > 1)) hasLeadingZero = true;

	memcpy(buffer, pTime + startPos, monthDayLen);
	buffer[monthDayLen] = 0;

	time_tm.tm_mday = (int)strtol(buffer, &end_ptr, 10);
	if(end_ptr == buffer) {
		cout << "ERROR: Could not convert the day of the month string to an integer." << endl;
		exit(1);
	}

	// establish the hour
	startPos = endPos + 1;
	endPos = startPos;
	while(pTime[endPos] != ':') endPos++;
	unsigned int hourLen = endPos - startPos;

	memcpy(buffer, pTime + startPos, hourLen);
	buffer[hourLen] = 0;

	time_tm.tm_hour = (int)strtol(buffer, &end_ptr, 10);
	if(end_ptr == buffer) {
		cout << "ERROR: Could not convert the hour string to an integer." << endl;
		exit(1);
	}

	// establish the minutes
	memcpy(buffer, pTime + startPos + hourLen + 1, 2);
	buffer[2] = 0;

	time_tm.tm_min = (int)strtol(buffer, &end_ptr, 10);
	if(end_ptr == buffer) {
		cout << "ERROR: Could not convert the minute string to an integer." << endl;
		exit(1);
	}

	// establish the seconds
	memcpy(buffer, pTime + startPos + hourLen + 4, 2);
	buffer[2] = 0;

	time_tm.tm_sec = (int)strtol(buffer, &end_ptr, 10);
	if(end_ptr == buffer) {
		cout << "ERROR: Could not convert the second string to an integer." << endl;
		exit(1);
	}

	// establish the year
	memcpy(buffer, pTime + timeLen - 4, 4);
	buffer[4] = 0;

	time_tm.tm_year = (int)strtol(buffer, &end_ptr, 10) - 1900;
	if(end_ptr == buffer) {
		cout << "ERROR: Could not convert the year string to an integer." << endl;
		exit(1);
	}

	// UTC has no DST
	time_tm.tm_isdst = 0;

	// automatically guess the rest
	time_tm.tm_yday  = -1;
	time_tm.tm_wday  = -1;

	// convert the tm structure into epoch time
	return ConvertTimeT(mktime(&time_tm) - GetUtcOffset());
}