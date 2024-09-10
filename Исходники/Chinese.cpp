//------------------------------------------------------
// Class:       TChineseCalendar
// Function:    ChineseNewMoonOnOrAfter
// Arguments:   TReal
//
// Comments:    corrects for chinese month starting at noon
//				in Beijing
//
// Return:      TInt - new moon
//------------------------------------------------------
TInt TChineseCalendar::ChineseNewMoonOnOrAfter(TReal aJulianDay) const
	{
	TReal newMoon;
	TReal timeZone;
	TInt rtn;

	AdjustJDToNoon(aJulianDay);

	timeZone = ChineseTimeZone(aJulianDay);
	newMoon = UniversalFromLocal(aJulianDay,timeZone);
	newMoon = NewMoonAtOrAfter(newMoon);
	newMoon = LocalFromUniversal(newMoon,timeZone);

	AdjustJDFromNoon(newMoon);
	Floor(rtn,newMoon);

	return rtn;
	}