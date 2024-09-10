	// This method clears the list and adds contacts again, according to the current filter settings.
	void RebuildList()
	{
		LPSTR pszProto;
		MTime mtNow;
		MAnnivDate ad;
		int i = 0;
		DWORD age = 0;
		WORD wDaysBefore = db_get_w(NULL, MODNAME, SET_REMIND_OFFSET, DEFVAL_REMIND_OFFSET);
		WORD numMale = 0;
		WORD numFemale = 0;
		WORD numContacts = 0;
		WORD numBirthContacts = 0;

		ShowWindow(_hList, SW_HIDE);
		DeleteAllItems();
		mtNow.GetLocalTime();

		// insert the items into the list
		for (MCONTACT hContact = db_find_first(); hContact; hContact = db_find_next(hContact)) {
			// ignore meta subcontacts here, as they are not interesting.
			if (!db_mc_isSub(hContact)) {
				// filter protocol
				pszProto = Proto_GetBaseAccountName(hContact);
				if (pszProto) {
					numContacts++;
					switch (GenderOf(hContact, pszProto)) {
					case 'M':
						numMale++;
						break;
					case 'F':
						numFemale++;
					}

					if (!ad.DBGetBirthDate(hContact, pszProto)) {
						age += ad.Age(&mtNow);
						numBirthContacts++;

						// add birthday
						if ((_filter.bFilterIndex != FILTER_ANNIV) && (!_filter.pszProto || !_strcmpi(pszProto, _filter.pszProto)))
							AddRow(hContact, pszProto, ad, mtNow, wDaysBefore);
					}

					// add anniversaries
					if (_filter.bFilterIndex != FILTER_BIRTHDAY && (!_filter.pszProto || !_strcmpi(pszProto, _filter.pszProto))) 
						for (i = 0; !ad.DBGetAnniversaryDate(hContact, i); i++)
							if (!_filter.pszAnniv || !mir_tstrcmpi(_filter.pszAnniv, ad.Description()))
								AddRow(hContact, pszProto, ad, mtNow, wDaysBefore);
				}
			}
		}
		ListView_SortItemsEx(_hList, (CMPPROC)cmpProc, this);
		ShowWindow(_hList, SW_SHOW);

		// display statistics
		SetDlgItemInt(_hDlg, TXT_NUMBIRTH, numBirthContacts, FALSE);
		SetDlgItemInt(_hDlg, TXT_NUMCONTACT, numContacts, FALSE);
		SetDlgItemInt(_hDlg, TXT_FEMALE, numFemale, FALSE);
		SetDlgItemInt(_hDlg, TXT_MALE, numMale, FALSE);
		SetDlgItemInt(_hDlg, TXT_AGE, numBirthContacts > 0 ? (age - (age % numBirthContacts)) / numBirthContacts : 0, FALSE);
	}