void
O2IMDB::
MakeIMElement(O2IMessage &im, O2IMSelectCondition &cond, wstring &xml)
{
	wchar_t tmp[16];
	wstring tmpstr;

	xml += L"<message>" EOL;

	if (cond.mask & IM_XMLELM_IP) {
		ip2e(im.ip, tmpstr);
		xml += L" <ip>";
		xml += tmpstr;
		xml += L"</ip>" EOL;
	}

	if (cond.mask & IM_XMLELM_PORT) {
		swprintf_s(tmp, 16, L"%d", im.port);
		xml += L" <port>";
		xml += tmp;
		xml += L"</port>" EOL;
	}

	if (cond.mask & IM_XMLELM_ID) {
		im.id.to_string(tmpstr);
		xml += L" <id>";
		xml += tmpstr;
		xml += L"</id>" EOL;
	}

	if (cond.mask & IM_XMLELM_PUBKEY) {
		im.pubkey.to_string(tmpstr);
		xml += L" <pubkey>";
		xml += tmpstr;
		xml += L"</pubkey>" EOL;
	}

	if (cond.mask & IM_XMLELM_NAME) {
		xml += L" <name>";
		xml += im.name;
		xml += L"</name>" EOL;
	}

	if (cond.mask & IM_XMLELM_DATE) {
		if (im.date == 0)
			xml += L" <date></date>" EOL;
		else {

			long tzoffset;

#ifdef _WIN32           /** windows */
			_get_timezone(&tzoffset);
#else                   /** unix */
			tzoffset = getGmtOffset();
#endif
			if (!cond.timeformat.empty()) {
				time_t t = im.date - tzoffset;

				wchar_t timestr[TIMESTR_BUFF_SIZE];
				struct tm tm;
#ifdef _WIN32                   /** windows */
				gmtime_s(&tm, &t);
#else                           /** unix */
				gmtime_r(&t, &tm);
#endif
				wcsftime(timestr, TIMESTR_BUFF_SIZE, cond.timeformat.c_str(), &tm);
				xml += L" <date>";
				xml += timestr;
				xml += L"</date>" EOL;
			}
			else {
				time_t2datetime(im.date, - tzoffset, tmpstr);
				xml += L" <date>";
				xml += tmpstr;
				xml += L"</date>" EOL;
			}
		}
	}

	if (cond.mask & IM_XMLELM_MSG) {
		makeCDATA(im.msg, tmpstr);
		xml += L" <msg>";
		xml += tmpstr;
		xml += L"</msg>" EOL;
	}

	if (cond.mask & IM_XMLELM_KEY) {
		im.key.to_string(tmpstr);
		xml += L" <key>";
		xml += tmpstr;
		xml += L"</key>" EOL;
	}

	if (cond.mask & IM_XMLELM_MINE) {
		xml += L" <mine>";
		xml += im.mine ? L"1" : L"0";
		xml += L"</mine>" EOL;
	}

	xml += L"</message>" EOL;
}