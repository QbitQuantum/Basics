/* Sun rise-set calculation algorithm.
 * Algorithm description:   http://williams.best.vwh.net/sunrise_sunset_algorithm.htm
 *
 *	Almanac for Computers, 1990
 *	published by Nautical Almanac Office
 *	United States Naval Observatory
 *	Washington, DC 20392
 *
 * Parameters:
 *  yd					- day of the year (1..365)
 *  latitude, longitude	- Sample: 32.27, 34.85 for Netania israel
 *  riseset				- ESUNRISE or ESUNSET
 *
 * Returns: UTC hour of the event (a real number).
*/
double sunriseset( int yd, double latitude, double longitude, ERiseSet riseset )
{
	// 96 degrees    - Calculate Civil twilight time. Used as indication if
	//   it is (usually) bright enough for outdoor activities without additional lighting.
	// 90 degrees 5' - Calculate true Sunrise/Sunset time. Used to check if
	//   the Sun itself is visible above the horizont in ideal conditions.
	const double zenith = 96;

	double sinDec, cosDec, cosH;
	double H, T, UT;

	// Rise / Set
	int op = (riseset==ESUNRISE ? 1:-1);

	// Convert the longitude to hour value and calculate an approximate time
	double lngHour = longitude / 15;

	// if rising time is desired:
	double t = yd + ((12 - (6*op) - lngHour) / 24);

	// Calculate the Sun's mean anomaly
	double M = (0.9856 * t) - 3.289;

	// Calculate the Sun's true longitude
	double L = M + (1.916 * SIN(M)) + (0.020 * SIN(2 * M)) + 282.634;

	// Calculate the Sun's right ascension
	double RA = ATAN(0.91764 * TAN(L));

	// Right ascension value needs to be in the same quadrant as L
	double Lquadrant  = (floor( L/90)) * 90;
	double RAquadrant = (floor(RA/90)) * 90;

	RA = RA + (Lquadrant - RAquadrant);

	// Right ascension value needs to be converted into hours
	RA = RA / 15;

	// Calculate the Sun's declination
	sinDec = 0.39782 * SIN(L);
	cosDec = COS(ASIN(sinDec));

	// Calculate the Sun's local hour angle
	cosH = (COS(zenith) - (sinDec * SIN(latitude))) / (cosDec * COS(latitude));
	if( cosH < -1 || cosH > 1 )
		// The sun never rises or sets on this location (on the specified date)
		return -1;

	// Finish calculating H and convert into hours
	H = 180 + (180 - ACOS(cosH))*op;
	H = H / 15;

	// Calculate local mean time of rising/setting
	T = H + RA - (0.06571 * t) - 6.622;

	// Adjust back to UTC
	UT = T - lngHour;

	// UT potentially needs to be adjusted into the range [0,24) by adding/subtracting 24
	if (UT < 0)   UT += 24;
	if (UT >= 24) UT -= 24;

	return UT;
}