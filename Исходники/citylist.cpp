bool CityList::parseLine(FILE* fp, Entry& entry, UINT& namePos)
{
	TCHAR buf[512];

	if (fgets(buf, sizeof(buf) / sizeof(buf[0]) - 1, fp) != NULL) {
		TCHAR* p;
		TCHAR* first = NULL;
		TCHAR* last = NULL;

		for (p = buf; p[0] != '\0' && p[0] != ';'; p += _tclen(p)) {
			if (p[0] == ' ' || p[0] == '\t' || p[0] == '\r' || p[0] == '\n') {
				// Found white space.
				if (last == NULL)
					last = p;
			}
			else {
				if (first == NULL)
					first = p;
				last = NULL;
			}
		}

		// Strip trailing spaces if any, and any comments.
		if (last != NULL)
			last[0] = '\0';
		else
			p[0] = '\0';

		if (first != NULL) {
			int latitude, longitude, name;
			if (_stscanf(first, "%d %d %n", &latitude, &longitude, &name) == 2
					&& first[name] != '\0') {
				entry.latitude = float(latitude) / 10000.0f;
				entry.longitude = float(longitude) / 10000.0f;
				entry.nameOff = namePos;
				UINT nameEnd = namePos + _tcslen(first + name) + 1;
				moreNames(nameEnd);
				_tcscpy(mpCityNames + namePos, first + name);
				namePos = nameEnd;
				return true;
			}
		}
	}
	return false;
}