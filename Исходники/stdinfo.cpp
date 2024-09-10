static void SetValue(HWND hwndDlg, int idCtrl, HANDLE hContact, char *szModule, char *szSetting, int special)
{
	char str[80], *pstr = NULL;
	TCHAR* ptstr = NULL;
	char* szProto = GetContactProto(hContact);
	bool proto_service = szProto && (CallProtoService(szProto, PS_GETCAPS, PFLAGNUM_4, 0) & PF4_INFOSETTINGSVC);

	DBVARIANT dbv = { DBVT_DELETED };

	int unspecified;
	if (szModule == NULL)
		unspecified = 1;
	else if (proto_service)
		unspecified = Proto_GetContactInfoSetting(hContact, szProto, szModule, szSetting, &dbv, 0);
	else
		unspecified = db_get_s(hContact, szModule, szSetting, &dbv, 0);

	if ( !unspecified) {
		switch(dbv.type) {
		case DBVT_BYTE:
			if (special == SVS_GENDER) {
				if (dbv.cVal == 'M') ptstr = TranslateT("Male");
				else if (dbv.cVal == 'F') ptstr = TranslateT("Female");
				else unspecified = 1;
			}
			else if (special == SVS_MONTH) {
				if (dbv.bVal>0 && dbv.bVal <= 12) {
					pstr = str;
					GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_SABBREVMONTHNAME1-1+dbv.bVal, str, SIZEOF(str));
				}
				else unspecified = 1;
			}
			else if (special == SVS_TIMEZONE) {
				if (dbv.cVal == -100) unspecified = 1;
				else {
					pstr = str;
					mir_snprintf(str, SIZEOF(str), dbv.cVal?"UTC%+d:%02d":"UTC", -dbv.cVal/2, (dbv.cVal&1)*30);
				}
			}
			else {
				unspecified = (special == SVS_ZEROISUNSPEC && dbv.bVal == 0);
				pstr = _itoa(special == SVS_SIGNED?dbv.cVal:dbv.bVal, str, 10);
			}
			break;

		case DBVT_WORD:
			if (special == SVS_COUNTRY) {
				WORD wSave = dbv.wVal;
				if (wSave == (WORD)-1) {
					char szSettingName[100];
					mir_snprintf(szSettingName, SIZEOF(szSettingName), "%sName", szSetting);
					if ( !db_get_ts(hContact, szModule, szSettingName, &dbv)) {
						ptstr = dbv.ptszVal;
						unspecified = false;
						break;
					}
				}

				pstr = Translate((char*)CallService(MS_UTILS_GETCOUNTRYBYNUMBER, wSave, 0));
				unspecified = pstr == NULL;
			}
			else {
				unspecified = (special == SVS_ZEROISUNSPEC && dbv.wVal == 0);
				pstr = _itoa(special == SVS_SIGNED?dbv.sVal:dbv.wVal, str, 10);
			}
			break;

		case DBVT_DWORD:
			unspecified = (special == SVS_ZEROISUNSPEC && dbv.dVal == 0);
			if (special == SVS_IP) {
				struct in_addr ia;
				ia.S_un.S_addr = htonl(dbv.dVal);
				pstr = inet_ntoa(ia);
				if (dbv.dVal == 0) unspecified = 1;
			}
			else pstr = _itoa(special == SVS_SIGNED?dbv.lVal:dbv.dVal, str, 10);
			break;

		case DBVT_ASCIIZ:
			unspecified = (special == SVS_ZEROISUNSPEC && dbv.pszVal[0] == '\0');
			pstr = dbv.pszVal;
			break;

		case DBVT_UTF8:
			unspecified = (special == SVS_ZEROISUNSPEC && dbv.pszVal[0] == '\0');
			if ( !unspecified)
			{	WCHAR* wszStr;
			Utf8Decode(dbv.pszVal, &wszStr);
			SetDlgItemTextW(hwndDlg, idCtrl, TranslateTS(wszStr));
			mir_free(wszStr);
			goto LBL_Exit;
			}

			pstr = dbv.pszVal;
			Utf8Decode(dbv.pszVal, NULL);
			break;

		default:
			pstr = str;
			lstrcpyA(str, "???");
			break;
		}
	}

	if (unspecified)
		SetDlgItemText(hwndDlg, idCtrl, TranslateT("<not specified>"));
	else if (ptstr != NULL)
		SetDlgItemText(hwndDlg, idCtrl, ptstr);
	else
		SetDlgItemTextA(hwndDlg, idCtrl, pstr);

LBL_Exit:
	EnableWindow(GetDlgItem(hwndDlg, idCtrl), !unspecified);
	if (proto_service)
		Proto_FreeInfoVariant(&dbv);
	else
		db_free(&dbv);
}