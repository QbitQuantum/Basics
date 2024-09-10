/* Process a given event */
DWORD ProcessEvent(EVT_HANDLE hEvent)
{
    EVT_HANDLE hProviderMetadata = NULL;
	PEVT_VARIANT eventInfo = NULL;
    LPWSTR pwsMessage = NULL;
    LPWSTR pwszPublisherName = NULL;
	ULONGLONG eventTime;
	ULONGLONG keyword;
    DWORD status = ERROR_SUCCESS;
	int event_id = 0;
	int winlevel = 0;
	int level = 0;

	WCHAR source[SOURCE_SZ];
	WCHAR hostname[HOSTNAME_SZ];
	WCHAR * formatted_string = NULL;
	WCHAR * tstamp = NULL;
	WCHAR * index = NULL;
	WCHAR defmsg[ERRMSG_SZ];
	WCHAR tstamped_message[SYSLOG_DEF_SZ];

    /* Get and store the publishers new Windows Events name */
	eventInfo = GetEventInfo(hEvent);
	if (eventInfo) {
		pwszPublisherName = (LPWSTR)eventInfo[0].StringVal;
	}
	else {
		return ERR_CONTINUE;
	}
	eventTime = eventInfo[1].FileTimeVal;
	event_id = eventInfo[2].UInt16Val;

	/* Check for the "Microsoft-Windows-" prefix in the publisher name */
	/* and remove it if found. Saves 18 characters in the message */
	if(wcsncmp(pwszPublisherName, L"Microsoft-Windows-", 18) == 0)
		wcsncpy_s(source, COUNT_OF(source), pwszPublisherName+18, _TRUNCATE);
	else
		wcsncpy_s(source, COUNT_OF(source), pwszPublisherName, _TRUNCATE);

	/* Format Event Timestamp */
	if ((tstamp = WinEventTimeToString(eventTime)) == NULL)
		tstamp = L"TIME_ERROR";

	/* Add hostname for RFC compliance (RFC 3164) */
	if (ProgramUseIPAddress == TRUE) {
		_snwprintf_s(hostname, HOSTNAME_SZ, _TRUNCATE, L"%S", ProgramHostName);
	} else {
		if (ExpandEnvironmentStringsW(L"%COMPUTERNAME%", hostname, COUNT_OF(hostname)) == 0) {
			wcscpy_s(hostname, COUNT_OF(hostname), L"HOSTNAME_ERR");
			Log(LOG_ERROR|LOG_SYS, "Cannot expand %COMPUTERNAME%");
		}
    }

	/* replace every space in source by underscores */
	index = source;
	while( *index ) {
		if( *index == L' ' ) {
			*index = L'_';
		}
		index++;
	}

	/* Add Timestamp and hostname then format source & event ID for consistency with Event Viewer */
    if(SyslogIncludeTag)
    {
        _snwprintf_s(tstamped_message, COUNT_OF(tstamped_message), _TRUNCATE, L"%s %s %S: %s: %i: ",
            tstamp,
            hostname,
            SyslogTag,
            source,
            event_id
        );
    }
    else
    {
        _snwprintf_s(tstamped_message, COUNT_OF(tstamped_message), _TRUNCATE, L"%s %s %s: %i: ",
            tstamp,
            hostname,
            source,
            event_id
        );
    }

	/* Get the handle to the provider's metadata that contains the message strings. */
	hProviderMetadata = EvtOpenPublisherMetadata(NULL, pwszPublisherName, NULL, 0, 0);
	if (NULL == hProviderMetadata) {
		if (LogInteractive)
			Log(LOG_ERROR|LOG_SYS, "OpenPublisherMetadata failed for Publisher: \"%S\"", source);
		return ERR_CONTINUE;
	}

	/* Get the message string from the event */
	pwsMessage = GetMessageString(hProviderMetadata, hEvent);
	if (pwsMessage == NULL) {
		Log(LOG_ERROR|LOG_SYS, "Error getting message string for event DETAILS: Publisher: %S EventID: %i", source, event_id);
		return ERR_CONTINUE;
	}

	/* Get string and strip whitespace */
	formatted_string = CollapseExpandMessageW(pwsMessage);

	/* Create a default message if resources or formatting didn't work */
	if (formatted_string == NULL) {
        if(SyslogIncludeTag)
        {
		    _snwprintf_s(defmsg, COUNT_OF(defmsg), _TRUNCATE,
                L"%S: (Facility: %u, Status: %s)",
                SyslogTag,
			    HRESULT_FACILITY(event_id),
			    FAILED(event_id) ? L"Failure" : L"Success"
		    );
        }
        else
        {
            _snwprintf_s(defmsg, COUNT_OF(defmsg), _TRUNCATE,
                L"(Facility: %u, Status: %s)",
			    HRESULT_FACILITY(event_id),
			    FAILED(event_id) ? L"Failure" : L"Success"
		    );
        }
		formatted_string = defmsg;
	}

	/* Get Event Error Level. In the case of Security Events,
	 * set Failures to Error instead of notice using the
	 * keyword attribute
	 */
	keyword = (EvtVarTypeNull == eventInfo[4].Type) ? 0 : eventInfo[4].UInt64Val;
	if ((keyword & WINEVENT_KEYWORD_AUDIT_FAILURE) != 0) {
        // Add AUDIT_FAILURE message for better parsing
        wcsncat_s(tstamped_message, COUNT_OF(tstamped_message), L"AUDIT_FAILURE ", _TRUNCATE);
		winlevel = WINEVENT_ERROR_LEVEL;
    }
	else
		winlevel = (int)eventInfo[3].ByteVal;

	/* Select syslog level */
	switch (winlevel) {
		case WINEVENT_CRITICAL_LEVEL:
			level = SYSLOG_BUILD(SyslogFacility, SYSLOG_CRIT);
			break;		
		case WINEVENT_ERROR_LEVEL:
			level = SYSLOG_BUILD(SyslogFacility, SYSLOG_ERR);
			break;
		case WINEVENT_WARNING_LEVEL:
			level = SYSLOG_BUILD(SyslogFacility, SYSLOG_WARNING);
			break;
		case WINEVENT_INFORMATION_LEVEL:
			level = SYSLOG_BUILD(SyslogFacility, SYSLOG_NOTICE);
			break;
		case WINEVENT_AUDIT_LEVEL:
            wcsncat_s(tstamped_message, COUNT_OF(tstamped_message), L"AUDIT_SUCCESS ", _TRUNCATE);
			level = SYSLOG_BUILD(SyslogFacility, SYSLOG_NOTICE);
			break;
		case WINEVENT_VERBOSE_LEVEL:
			level = SYSLOG_BUILD(SyslogFacility, SYSLOG_DEBUG);
			break;

		/* Everything else */
		default:
			level = SYSLOG_BUILD(SyslogFacility, SYSLOG_NOTICE);
			break;
	}

	/* Combine the message strings */
	wcsncat_s(tstamped_message, COUNT_OF(tstamped_message), formatted_string, _TRUNCATE);

	/* Send the event to the Syslog Server */
	/* Making sure it is severe enough to be logged */
	if (SyslogLogLevel == 0 || (SyslogLogLevel >= (DWORD)winlevel && winlevel > 0))
		if (SyslogSendW(tstamped_message, level))
			status = ERR_FAIL;

	/* Cleanup memory and open handles */
	if(pwsMessage)
		free(pwsMessage);
	if(eventInfo)
		free(eventInfo);

	if (hProviderMetadata)
		EvtClose(hProviderMetadata);
	if (hEvent)
		EvtClose(hEvent);

	return status;
}