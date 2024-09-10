/* Creates the ls monthname abbreviation array, so we don't have to
 * re-calculate them each time.
 */
void InitLsMonths(void)
{
	struct tm lt;
	int i;

	memset(gLsMon, 0, sizeof(gLsMon));
	(void) Localtime(0, &lt);
	lt.tm_mday = 15;
	lt.tm_hour = 12;
	for (i=0; i<12; i++) {
		lt.tm_mon = i;
		(void) strftime(gLsMon[i], sizeof(gLsMon[i]) - 1, "%b", &lt);
	}
	(void) strcpy(gLsMon[i], "BUG");
}	/* InitLsMonths */