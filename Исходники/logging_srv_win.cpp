void LogChannelSyslog::writeLogEntry( const String& entry, LogChannel::LogMessage* pOrigMsg )
{
   WORD wType;
   DWORD dwEventID;

   if ( pOrigMsg->m_level <= LOGLEVEL_ERROR )
   {  
      wType = EVENTLOG_ERROR_TYPE;
	  dwEventID = 3 << 30;
   }
   else if ( pOrigMsg->m_level == LOGLEVEL_WARN )
   {
      wType = EVENTLOG_WARNING_TYPE;
	  dwEventID = 2 << 30;
   }
   else {
      wType = EVENTLOG_INFORMATION_TYPE;
	  dwEventID = 1 << 30;
   }

   // From MS docs; event ID  = gravity | custom | facility | code;
   dwEventID |= (1 << 29) | ((m_facility&0x1FF) << 16) | (pOrigMsg->m_code & 0xFFFF);

   AutoWString w_msg( entry );
   
   const wchar_t* strings[] = { w_msg.w_str() };
   ReportEventW(
	   (HANDLE)m_sysdata,	// __in  HANDLE hEventLog,
	   wType,				// __in  WORD wType,
	   m_facility,			// __in  WORD wCategory,
	   dwEventID,			// __in  DWORD dwEventID,
	   NULL,				// __in  PSID lpUserSid,
	   1,					// __in  WORD wNumStrings,
	   0,					// __in  DWORD dwDataSize,
	   strings,				// __in  LPCTSTR *lpStrings,
	   NULL					// __in  LPVOID lpRawData
	   );

}