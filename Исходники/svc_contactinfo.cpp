/**
 * This is the service procedure to retrieve contact information
 *
 * @param	wParam		- not used
 * @param	lParam		- pointer to a CONTACTINFO structure which tells what information is desired
 *
 * @retval	0 - if contact information was found and read correctly 
 * @retval	1 - if any error occured or setting was not found
 **/
INT_PTR GetContactInfo(WPARAM wParam, LPARAM lParam) 
{
	CONTACTINFO *ci = (CONTACTINFO*) lParam;
	INT_PTR result;

	if (ci && ci->cbSize == sizeof(CONTACTINFO) && (ci->szProto != NULL || (ci->szProto = DB::Contact::Proto(ci->hContact)) != NULL))
	{
		switch (ci->dwFlag & 0x7F) {

		//
		// contact name
		//
		case CNF_FIRSTNAME:		{
				result = GCIVarEx(ci, SET_CONTACT_FIRSTNAME);
			} break;

		case CNF_LASTNAME:		{
				result = GCIVarEx(ci, SET_CONTACT_LASTNAME);
			} break;

		case CNF_FIRSTLAST:		{
				result = GCIVarEx(ci, SET_CONTACT_FIRSTLASTNAME);	//first try to read "FullName"
				if(result) result = GCIFirstLast(ci);				//fallback to "FirstName" + "LastName"
			} break;

		case CNF_NICK:			{
				result = GCIVarEx(ci, SET_CONTACT_NICK);
			} break;

		case CNF_CUSTOMNICK:	{
				LPSTR s = ci->szProto;
				ci->szProto = MOD_CLIST;
				result = GCIVar(ci, SET_CONTACT_MYHANDLE);
				ci->szProto = s;
			} break;

		case CNF_LANGUAGE1:			{
				result = GCILangEx(ci, SET_CONTACT_LANG1);
			} break;

		case CNF_LANGUAGE2:			{
				result = GCILangEx(ci, SET_CONTACT_LANG2);
			} break;

		case CNF_LANGUAGE3:			{
				result = GCILangEx(ci, SET_CONTACT_LANG3);
			} break;

		//
		// private contact
		//
		case CNF_STREET:		{
				result = GCIVarEx(ci, SET_CONTACT_STREET);
			} break;

		case CNF_ZIP:			{
				result = GCIVarEx(ci, SET_CONTACT_ZIP); 
			} break;

		case CNF_CITY:			{
				result = GCIVarEx(ci, SET_CONTACT_CITY);
			} break;

		case CNF_STATE:			{
				result = GCIVarEx(ci, SET_CONTACT_STATE);
			} break;

		case CNF_COUNTRY:		{
				result = GCICountry(ci, SET_CONTACT_COUNTRY);
			} break;

		case CNF_PHONE:			{
				result = GCIVarEx(ci, SET_CONTACT_PHONE);
			} break;

		case CNF_FAX:			{
				result = GCIVarEx(ci, SET_CONTACT_FAX);
			} break;

		case CNF_CELLULAR:		{
				result = GCIVarEx(ci, SET_CONTACT_CELLULAR);
			} break;

		case CNF_EMAIL:			{
				result = GCIVarEx(ci, SET_CONTACT_EMAIL);
			} break;

		case CNF_HOMEPAGE:		{
				result = GCIVarEx(ci, SET_CONTACT_HOMEPAGE);
			} break;

		//
		// company information
		//
		case CNF_CONAME:		{
				result = GCIVarEx(ci, SET_CONTACT_COMPANY);
			} break;

		case CNF_CODEPT:		{
				result = GCIVarEx(ci, SET_CONTACT_COMPANY_DEPARTMENT);
			} break;

		case CNF_COPOSITION:	{
				result = GCIVarEx(ci, SET_CONTACT_COMPANY_POSITION);
			} break;

		case CNF_COSTREET:		{
				result = GCIVarEx(ci, SET_CONTACT_COMPANY_STREET);
			} break;

		case CNF_COZIP:			{
				result = GCIVarEx(ci, SET_CONTACT_COMPANY_ZIP);
			} break;

		case CNF_COCITY:		{
				result = GCIVarEx(ci, SET_CONTACT_COMPANY_CITY);
			} break;

		case CNF_COSTATE:		{
				result = GCIVarEx(ci, SET_CONTACT_COMPANY_STATE);
			} break;

		case CNF_COCOUNTRY:		{
				result = GCICountry(ci, SET_CONTACT_COMPANY_COUNTRY);
			} break;

		case CNF_COPHONE:		{
				result = GCIVarEx(ci, SET_CONTACT_COMPANY_PHONE);
			} break;

		case CNF_COFAX:			{
				result = GCIVarEx(ci, SET_CONTACT_COMPANY_FAX);
			} break;

		case CNF_COCELLULAR:	{
				result = GCIVarEx(ci, SET_CONTACT_COMPANY_CELLULAR);
			} break;

		case CNF_COEMAIL:		{
				result = GCIVarEx(ci, SET_CONTACT_COMPANY_EMAIL);
			} break;

		case CNF_COHOMEPAGE:	{
				result = GCIVarEx(ci, SET_CONTACT_COMPANY_HOMEPAGE);
			} break;

		//
		// personal information
		//
		case CNF_ABOUT:			{
				result = GCIVarEx(ci, SET_CONTACT_ABOUT);
			} break;

		case CNF_MYNOTES:		{
				result = GCIVarEx(ci, SET_CONTACT_MYNOTES);
			} break;

		case CNF_AGE:			{
				result = GCIVarEx(ci, SET_CONTACT_AGE);
			} break;	  // returns age (byte, 0==unspecified) ??

		case CNF_GENDER:		{
				ci->bVal = GenderOf(ci->hContact, ci->szProto);
				ci->type = (ci->bVal != 0) ? CNFT_BYTE : 0;
				result = ci->type == 0;
			} break;

		case CNF_BIRTHDAY:		{
				MAnnivDate mda;
				result = mda.DBGetBirthDate(ci->hContact, ci->szProto);
				if (result == 0) {
					ci->bVal = (BYTE) mda.Day();
					ci->type = CNFT_BYTE;
				}
			} break;

		case CNF_BIRTHMONTH:	{
				MAnnivDate mda;
				result = mda.DBGetBirthDate(ci->hContact, ci->szProto);
				if (result == 0) {
					ci->bVal = (BYTE) mda.Month();
					ci->type = CNFT_BYTE;
				}
			} break;

		case CNF_BIRTHYEAR:		{
				MAnnivDate mda;
				result = mda.DBGetBirthDate(ci->hContact, ci->szProto);
				if (result == 0) {
					ci->wVal = (WORD) mda.Year();
					ci->type = CNFT_WORD;
				}
			} break;

		case CNF_BIRTHDATE:		{
				MAnnivDate mda;
				result = mda.DBGetBirthDate(ci->hContact, ci->szProto);
				if (result == 0) {
					SYSTEMTIME st = mda.SystemTime();
					ci->pszVal = NULL;
					if (ci->dwFlag & CNF_UNICODE) {
						WCHAR wszDate[80];
						if (GetDateFormatW(LOCALE_USER_DEFAULT, wParam == 1 ? DATE_LONGDATE : DATE_SHORTDATE, &st, NULL, wszDate, SIZEOF(wszDate))) {
							ci->pszVal = (LPTSTR)mir_wcsdup(wszDate);
						}
					}
					else {
						CHAR szDate[80];
						if (GetDateFormatA(LOCALE_USER_DEFAULT, wParam == 1 ? DATE_LONGDATE : DATE_SHORTDATE, &st, NULL, szDate, SIZEOF(szDate))) {
							ci->pszVal = (LPTSTR)mir_strdup(szDate);
						}
					}
					ci->type = (ci->pszVal != NULL) ? CNFT_ASCIIZ : 0;
					result = ci->type == 0;
				}
			} break;

		case CNF_TIMEZONE:		{
				//use new core tz interface
				if(tmi.prepareList) {
					HANDLE hTz = tmi.createByContact(ci->hContact, TZF_KNOWNONLY);
					if (hTz) {
						LPTIME_ZONE_INFORMATION tzi = tmi.getTzi(hTz);
						int offset = tzi->Bias + tzi->StandardBias;

						char str[80];
						mir_snprintf(str, SIZEOF(str), offset ? "UTC%+d:%02d" : "UTC", offset / -60, abs(offset % 60));
						ci->pszVal =	ci->dwFlag & CNF_UNICODE
										? (TCHAR*)mir_a2u(str) 
										: (TCHAR*)mir_strdup(str);
						ci->type = CNFT_ASCIIZ;
						return 0;
					}
					else {
						ci->pszVal = NULL;
					}
				}
				//fallback use old UIEX method
				else {
					CTimeZone* ptz = GetContactTimeZone(ci->hContact, ci->szProto);
					if (ptz) {
						if (ci->dwFlag & CNF_UNICODE) {
							ci->pszVal = (LPTSTR) mir_t2u(ptz->ptszDisplay);
						}
						else {
							ci->pszVal = (LPTSTR) mir_t2a(ptz->ptszDisplay);
						}
					}
					else {
						/* If a timezone does not exist in CTzMgr, it is a invalid timezone,
						because Windows and CTzMgr know all existing timezones and it
						would not be shown anywhere anyway as UserInfoEx displays only 
						known windows timezones in the details dialog!
						*/
						ci->pszVal = NULL;
					}
				}
				ci->type = (ci->pszVal != NULL) ? CNFT_ASCIIZ : 0;
				result = ci->type == 0;
			} break;

		//
		// information about IM specific stuff
		//
		case CNF_UNIQUEID:		{
				// protocol must define a PFLAG_UNIQUEIDSETTING
				result = CallProtoService(ci->szProto, PS_GETCAPS, PFLAG_UNIQUEIDSETTING, 0);
				if (result != CALLSERVICE_NOTFOUND && result != NULL) {
					result = GCIVar(ci, (LPCSTR) result);
				}
			} break;

		case CNF_DISPLAYUID:	{
				if (!GCIVar(ci, "display_uid"))
					result=0;
				else {
					result = CallProtoService(ci->szProto,PS_GETCAPS,PFLAG_UNIQUEIDSETTING,0);
					if (result != CALLSERVICE_NOTFOUND && result != NULL) {
						result = GCIVar(ci, (LPCSTR) result);
					}
				}
			} break;

		case CNF_DISPLAYNC:
		case CNF_DISPLAY:		{
				INT i;
				for (i = 0; i < NAMEORDERCOUNT; i++) {
					switch (gNameOrder[i]) {
					case 0: // custom name
						{
							// make sure we aren't in CNF_DISPLAYNC mode
							// don't get custom name for NULL contact
							if (ci->hContact != NULL && (ci->dwFlag & 0x7F) == CNF_DISPLAY) {
								BYTE dwFlag = ci->dwFlag;
								ci->dwFlag = (ci->dwFlag & CNF_UNICODE) | CNF_CUSTOMNICK;
								if (!GetContactInfo(NULL, (LPARAM)ci)) {
									ci->dwFlag = dwFlag;
									return 0;
								}
								ci->dwFlag = dwFlag;
							}
						} break;
					case 1: // nick
						{
							if (!GCIVarEx(ci, SET_CONTACT_NICK))
								return 0;
						} break;
					case 2: // First Name
						{
							if (!GCIVarEx(ci, SET_CONTACT_FIRSTNAME))
								return 0;
						} break;
					case 3: // E-mail
						{
							if (!GCIVarEx(ci, SET_CONTACT_EMAIL))
								return 0;
						} break;
					case 4: // Last Name
						{
							if (!GCIVarEx(ci, SET_CONTACT_LASTNAME))
								return 0;
						} break;
					case 5: // Unique id
						{
							// protocol must define a PFLAG_UNIQUEIDSETTING
							result = CallProtoService(ci->szProto, PS_GETCAPS, PFLAG_UNIQUEIDSETTING, 0);
							if (result != CALLSERVICE_NOTFOUND && result != NULL) {
								if (!GCIStr(ci, (LPCSTR) result))
									return 0;
							}
						} break;
					case 6: // first + last name
						{
							if (!GCIFirstLast(ci))
								return 0;
						} break;
					default: // unknown contact
						{
							if (ci->dwFlag & CNF_UNICODE) {
								ci->pszVal = (LPTSTR) mir_wcsdup(TranslateW(L"'(Unknown Contact)'"));
							}
							else {
								ci->pszVal = (LPTSTR) mir_strdup(Translate("'(Unknown Contact)'"));
							}
							ci->type = (ci->pszVal != NULL) ? CNFT_ASCIIZ : 0;
							return ci->type == 0;
						}
					}
				}
			}

		default:				{
				result = 1;
			}
		}
	}
	else
	{
		result = 1;
	}
	return result;
}