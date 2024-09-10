STDMETHODIMP COAHolder::Advise(IAdviseSink FAR* pAdvSink,
		DWORD FAR* pdwConnection)
{
	VDATEHEAP();

	int iAdv;  // records the first free entry found, or (-1)
	int iAdvScan; // counts across array entries
	IAdviseSink FAR *FAR *ppIAS; // points at the array entry being examined
	IAdviseSink FAR *pIAS; // the actual entry at *ppIAS

	M_PROLOG(this);
	VDATEIFACE(pAdvSink);
	HRESULT hr = NOERROR;

	LEDebugOut((DEB_ITRACE, "%p _IN COAHolder::Advise ( %p , %p )"
		"\n", this, pAdvSink, pdwConnection));

 	// Validate where to return the connection.
	if (pdwConnection)
	{
		VDATEPTRIN(pdwConnection, DWORD);

		// Default to error case
		*pdwConnection = 0;
	}

	// check our zombie state and stabilize.  If we are in a zombie
	// state, we do not want to be adding new advise sinks.

	CStabilize stabilize((CSafeRefCount *)this);

	if( IsZombie() )
	{
		hr = ResultFromScode(CO_E_RELEASED);
		goto errRtn;
	}


	// find an empty slot and clean up disconnected handlers
	for (iAdv = (-1), ppIAS = m_ppIAS, iAdvScan = 0;
			iAdvScan < m_iSize; ++ppIAS, ++iAdvScan)
	{
		if ((pIAS = *ppIAS) == NULL)
		{
			// NULL entries are handled below, to catch
			// any of the below cases creating new NULL values
			;
		}
		else if (!IsValidInterface(pIAS))
		{
			// not valid; don't try to release
			*ppIAS = NULL;
		}
		else if (!CoIsHandlerConnected(pIAS))
		{
			// advise sink not connected to server anymore; release
			// REVIEW, why do we have to constantly poll these
			// to see if they are ok?
			pIAS->Release();
			*ppIAS = NULL;
		}

		// if first NULL, save rather than extend array
		if ((*ppIAS == NULL) && (iAdv == (-1)))
			iAdv = iAdvScan;
	}

	// if we didn't find an empty slot, we have to add space
	if (iAdv == (-1))
	{

		ppIAS = (IAdviseSink FAR * FAR *)PubMemRealloc(m_ppIAS,
			sizeof(IAdviseSink FAR *)*(m_iSize + COAHOLDER_GROWBY));
				
		if (ppIAS != NULL)
		{
                        // zero out new space
                        _xmemset((void FAR *) (ppIAS + m_iSize), 0,
                                 sizeof(IAdviseSink *) * COAHOLDER_GROWBY);
			// this is the index of the new element to use
			iAdv = m_iSize;

			// replace the old array
			m_ppIAS = ppIAS;
			m_iSize += COAHOLDER_GROWBY;
		}
		else
		{
			// quit if there was an error
			hr = ReportResult(0, E_OUTOFMEMORY, 0, 0);
		}
	}