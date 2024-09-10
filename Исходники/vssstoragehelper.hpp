			? VTRUE : VFALSE;
	}

	/** Open a compound document file to initialize this object. The file is
	expected to already exist, and will be created only if bCreateIfNeeded
	is VTRUE. Returns VTRUE on success, VFALSE on failure.*/
	VBOOL				OpenFile(	VSTRING_CONST	pszFileName,
									VBOOL			bCreateIfNeeded = VTRUE)
	{
		/* This object should NOT already be initialized!*/
		VASSERT(!m_pWrappedObject)

		if (	FAILED(StgOpenStorage(
			VTEXT_ANY(pszFileName),
			NULL,
			m_nMode,
			NULL,
			0,
			(IStorage**)&m_pWrappedObject)) && bCreateIfNeeded )
		{
			StgCreateDocfile(	VTEXT_ANY(pszFileName),
								STGM_CREATE | m_nMode,
								0,
								(IStorage**)&m_pWrappedObject);
		}

		return (m_pWrappedObject) ? VTRUE : VFALSE;
	}

	/** Open a named storage as a sub-storage of this object, returning a
	pointer to it on success, NULL on failure. The object returned from