void vncExportACL::PrintSid(PSID psid)
{
    TCHAR name[256], domain[256];
    DWORD cbname = sizeof name, cbdomain = sizeof domain, rc;
    SID_NAME_USE sidUse;

    //!! next line has hardcoded server name !!
    // NULL server name is usually appropriate, though.
    if (LookupAccountSid(NULL, psid, name, &cbname, domain, &cbdomain, &sidUse))
    {
        //Todo: Check if WellKnownSID and reserve special names for them.

        /*		switch ( sidUse )
        		{
        			case SidTypeWellKnownGroup:	type = "well-known group"; break;
        			default:					type = "bad sidUse value"; break;
        		}
        */
        LPWKSTA_INFO_100 wkstainfo = NULL;
        NET_API_STATUS nStatus;
        TCHAR langroup[MAXLEN];
        TCHAR computername[MAXLEN];

        nStatus = NetWkstaGetInfo( 0 , 100 , (LPBYTE *) &wkstainfo);
        if (nStatus == NERR_Success) {
            _tcsncpy(langroup, wkstainfo->wki100_langroup, MAXLEN);
            _tcsncpy(computername, wkstainfo->wki100_computername, MAXLEN);
            langroup[MAXLEN - 1] = _T('\0');
            computername[MAXLEN - 1] = _T('\0');
            // replace computername with a dot
            if (_tcsicmp(computername, domain) == 0)
                _tcscpy(domain,_T("."));
            else if (_tcsicmp(langroup, domain) == 0)
                _tcscpy(domain, _T(".."));
        }
        else
            _tprintf(_T("NetWkstaGetInfo() returned %lu \n"), wkstainfo);

        NetApiBufferFree(wkstainfo);
        wkstainfo = NULL;

        // If domain or username contains whitespace, print enclosing quotes
        if (_tcschr(domain, _T(' ')) || _tcschr(name, _T(' ')))
            _tprintf(_T("\"%s%s%s\"\n"), domain, (domain == 0 || *domain == _T('\0'))? _T(""): _T("\\"), name);
        else
            _tprintf(_T("%s%s%s\n"), domain, (domain == 0 || *domain == _T('\0'))? _T(""): _T("\\"), name);
    }
    else
    {
        rc = GetLastError();
        _tprintf(_T("[%s] *** error %lu\n"), SidToText( psid ), rc);
    }
}