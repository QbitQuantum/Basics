// Return 0 if not changed, 1 if changed, 2 if removed
int TrackChange(HANDLE hContact, DBCONTACTWRITESETTING *cws_new, BOOL ignore_remove)
{
	char current_setting[256];
	mir_snprintf(current_setting, MAX_REGS(current_setting), "%sCurrent", cws_new->szSetting);

	int ret = 0;

	DBVARIANT dbv = {0};
#ifdef UNICODE
	BOOL found_current = (DBGetContactSettingW(hContact, cws_new->szModule, current_setting, &dbv) == 0);
#else
	BOOL found_current = (DBGetContactSetting(hContact, cws_new->szModule, current_setting, &dbv) == 0);
#endif
	if (!found_current)
	{
		// Current value does not exist

		if (cws_new->value.type == DBVT_DELETED)
		{
			ret = 0;
		}
		else if (cws_new->value.type == DBVT_ASCIIZ)
		{
			ret = CheckStr(cws_new->value.pszVal, 1, 0);
		}
#ifdef UNICODE
		else if (cws_new->value.type == DBVT_UTF8)
		{
			ret = CheckStr(cws_new->value.pszVal, 1, 0);
		}
		else if (cws_new->value.type == DBVT_WCHAR)
		{
			ret = CheckStr(cws_new->value.pwszVal, 1, 0);
		}
#endif
		else
		{
			ret = 1;
		}
	}
	else
	{
		// Current value exist

		if (cws_new->value.type == DBVT_DELETED)
		{
			if (dbv.type == DBVT_ASCIIZ)
			{
				ret = CheckStr(dbv.pszVal, 2, 0);
			}
#ifdef UNICODE
			else if (dbv.type == DBVT_UTF8)
			{
				ret = CheckStr(dbv.pszVal, 2, 0);
			}
			else if (dbv.type == DBVT_WCHAR)
			{
				ret = CheckStr(dbv.pwszVal, 2, 0);
			}
#endif
			else
			{
				ret = 2;
			}
		}
		else if (dbv.type != cws_new->value.type)
		{
#ifdef UNICODE
			if ( (cws_new->value.type == DBVT_UTF8 || cws_new->value.type == DBVT_ASCIIZ || cws_new->value.type == DBVT_WCHAR)
				&& (dbv.type == DBVT_UTF8 || dbv.type == DBVT_ASCIIZ || dbv.type == DBVT_WCHAR))
			{
				WCHAR tmp_cws_new[1024] = L"";
				if (cws_new->value.type == DBVT_ASCIIZ)
					MultiByteToWideChar(CP_ACP, 0, cws_new->value.pszVal, -1, tmp_cws_new, MAX_REGS(tmp_cws_new));
				else if (cws_new->value.type == DBVT_UTF8)
					MultiByteToWideChar(CP_UTF8, 0, cws_new->value.pszVal, -1, tmp_cws_new, MAX_REGS(tmp_cws_new));
				else if (cws_new->value.type == DBVT_WCHAR)
					lstrcpyn(tmp_cws_new, cws_new->value.pwszVal, MAX_REGS(tmp_cws_new));

				WCHAR tmp_dbv[1024] = L"";
				if (dbv.type == DBVT_ASCIIZ)
					MultiByteToWideChar(CP_ACP, 0, dbv.pszVal, -1, tmp_dbv, MAX_REGS(tmp_dbv));
				else if (dbv.type == DBVT_UTF8)
					MultiByteToWideChar(CP_UTF8, 0, dbv.pszVal, -1, tmp_dbv, MAX_REGS(tmp_dbv));
				else if (dbv.type == DBVT_WCHAR)
					lstrcpyn(tmp_dbv, dbv.pwszVal, MAX_REGS(tmp_dbv));

				ret = (lstrcmpW(tmp_cws_new, tmp_dbv) ? CheckStr(tmp_cws_new, 1, 2) : 0);
			}
			else
#endif
			{
				ret = 1;
			}
		}
		else if (dbv.type == DBVT_BYTE)
		{
			ret = (cws_new->value.bVal != dbv.bVal ? 1 : 0);
		}
		else if (dbv.type == DBVT_WORD)
		{
			ret = (cws_new->value.wVal != dbv.wVal ? 1 : 0);
		}
		else if (dbv.type == DBVT_DWORD)
		{
			ret = (cws_new->value.dVal != dbv.dVal ? 1 : 0);
		}
		else if (dbv.type == DBVT_ASCIIZ)
		{
			ret = (strcmp(cws_new->value.pszVal, dbv.pszVal) ? CheckStr(cws_new->value.pszVal, 1, 2) : 0);
		}
#ifdef UNICODE
		else if (dbv.type == DBVT_UTF8)
		{
			ret = (strcmp(cws_new->value.pszVal, dbv.pszVal) ? CheckStr(cws_new->value.pszVal, 1, 2) : 0);
		}
		else if (dbv.type == DBVT_WCHAR)
		{
			ret = (lstrcmp(cws_new->value.pwszVal, dbv.pwszVal) ? CheckStr(cws_new->value.pwszVal, 1, 2) : 0);
		}
#endif
	}

	if (ret == 1 || (ret == 2 && !ignore_remove))
	{
		// Copy current to old
		char old_setting[256];
		mir_snprintf(old_setting, MAX_REGS(old_setting), "%sOld", cws_new->szSetting);

		if (dbv.type == DBVT_DELETED)
		{
			DBDeleteContactSetting(hContact, cws_new->szModule, old_setting);
		}
		else
		{
			DBCONTACTWRITESETTING cws_old;
			cws_old.szModule = cws_new->szModule;
			cws_old.szSetting = old_setting;
			cws_old.value = dbv;
			CallService(MS_DB_CONTACT_WRITESETTING, (WPARAM)hContact, (LPARAM)&cws_old);
		}


		// Copy new to current
		if (cws_new->value.type == DBVT_DELETED)
		{
			DBDeleteContactSetting(hContact, cws_new->szModule, current_setting);
		}
		else
		{
			DBCONTACTWRITESETTING cws_old;
			cws_old.szModule = cws_new->szModule;
			cws_old.szSetting = current_setting;
			cws_old.value = cws_new->value;
			CallService(MS_DB_CONTACT_WRITESETTING, (WPARAM)hContact, (LPARAM)&cws_old);
		}
	}

	if (found_current)
		DBFreeVariant(&dbv);

	return ret;
}