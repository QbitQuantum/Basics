/* Put the local names of weekdays into the wds. */
void
mkweekdays(struct weekdays *wds)
{
	int i, len, width = 0;
	struct tm tm;
	wchar_t buf[20];

	memset(&tm, 0, sizeof(tm));

	for (i = 0; i != 7; i++) {
		tm.tm_wday = (i+1) % 7;
		wcsftime(buf, sizeof(buf), L"%a", &tm);
		for (len = 2; len > 0; --len) {
			if ((width = wcswidth(buf, len)) <= 2)
				break;
		}
		wmemset(wds->names[i], L'\0', 4);
		if (width == 1)
			wds->names[i][0] = L' ';
		wcsncat(wds->names[i], buf, len);
		wcsncat(wds->names[i], L" ", 1);
	}
}