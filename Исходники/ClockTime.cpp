bool ClockTime::checkOverdueTime() {
	bool hasElapsed;
	struct tm today;
	time_t currentTime = time(ZERO);	// get local time
	int hr  = _time / TIME_DIVISOR,
		min = _time % TIME_DIVISOR;

	localtime_s( &today, &currentTime); // update tm struct to be local date and time

	if( hr < today.tm_hour ) {
		hasElapsed = true;
	} else if ( hr == today.tm_hour && min <= today.tm_min) {
		hasElapsed = true; 
	} else{
		hasElapsed = false;
	}
	return hasElapsed;
}