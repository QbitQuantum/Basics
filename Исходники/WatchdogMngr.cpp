int CWatchdogMngr::LoadPidList()
{
	CIniParser oIniParser;

	if ( !oIniParser.Load(m_pPidListFile) )
	{
		throw CWatchdog::exception::exception("Unable to load pidListFile") ;
	}

	LOG("Loaded pidListFile [%s]", m_pPidListFile);

	char*  currentPidList[WTD_PIDLIST_ENTRIES]={0,};
	size_t currentPidListLen=0;
	char   pidFile[256];
	for ( unsigned pos=0
		; oIniParser.GetVar("WTD", "watch", pidFile, sizeof(pidFile), pos)
		  && currentPidListLen < WTD_PIDLIST_ENTRIES
		;  ++pos )
	{
		void*key=pidFile;
		void *el=lfind( &key,currentPidList,&currentPidListLen,sizeof(currentPidList[0]),qsortcmp ) ;
		if ( NULL == el )
		{
			currentPidList[currentPidListLen] = strdup(pidFile);
			LOG( WTD"fw.cfg:[%s]", currentPidList[currentPidListLen] );
			++currentPidListLen ;
		}
	}
	qsort( currentPidList, currentPidListLen, sizeof(currentPidList[0]), qsortcmp );

	/// Check if any pidFile from m_ppPidList is missing from currentPidList.
	for (   unsigned j=0; j < m_nPidListLength && m_ppPidList[j]; ++j )
	{
		void *el=bsearch( &m_ppPidList[j], currentPidList, currentPidListLen, sizeof(currentPidList[0]), qsortcmp) ;
		if ( NULL == el )
		{
			LOG( WTD "STOP watching pid[%s]", m_ppPidList[j]);
			systemf_to( 20, "log2flash 'WTD: STOP watching pid[%s]'&", m_ppPidList[j]);
		}
	}
	/// Free the old list to prepare the copy of the new one.
	clearPidList() ;

	m_nPidListLength=currentPidListLen ;
	m_ppPidList[m_nPidListLength] = 0;

	LOG( WTD"WATCH:%d modules", m_nPidListLength );
	if ( !m_nPidListLength )
	{
		return true ;
	}
	memmove(m_ppPidList, currentPidList, WTD_PIDLIST_ENTRIES*sizeof(currentPidList[0]) );
	for ( unsigned j = 0; j< m_nPidListLength ; j++)
	{
		LOG( WTD "WATCH:[%s]", m_ppPidList[j]);
	}
	return true ;
}