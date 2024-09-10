ASSERTDATA


//+----------------------------------------------------------------------------
//
//      Member:
//              CDataAdviseCache::CreateDataAdviseCache, static public
//
//      Synopsis:
//              Creates an instance of the CDataAdviseCache
//
//      Arguments:
//              [pp] -- pointer to a location to where to return the
//                      newly created CDataAdviseCache
//
//      Returns:
//              E_OUTOFMEMORY, S_OK
//
//      Notes:
//
//      History:
//              11/02/93 - ChrisWe - file cleanup and inspection
//
//-----------------------------------------------------------------------------

#pragma SEG(CreateDataAdviseCache)
FARINTERNAL CDataAdviseCache::CreateDataAdviseCache(LPDATAADVCACHE FAR* pp)
{
	VDATEHEAP();

	VDATEPTRIN(pp, LPDATAADVCACHE);

	// try to allocate the CDataAdviseCache
	if(NULL == (*pp = new DATAADVCACHE))
		return ReportResult(0, E_OUTOFMEMORY, 0, 0);

	// initialize the DataAdviseHolder member
	if(CreateDataAdviseHolder(&((*pp)->m_pDAH)) != NOERROR)
	{
		// free the DataAdviseCache
		delete *pp;
		*pp = NULL;

		return ReportResult(0, E_OUTOFMEMORY, 0, 0);
	}

	return(NOERROR);
}