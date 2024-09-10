void AFXAPI AfxOleTermOrFreeLib(BOOL bTerm, BOOL bJustRevoke)
{
	if (bTerm)
	{
		AfxOleTerm(bJustRevoke);
	}
	else
	{
		// initialize _afxTickCount if necessary
		if (!_afxTickInit)
		{
			_afxTickCount = ::GetTickCount();
			++_afxTickInit;
		}

		// only call CoFreeUnusedLibraries if one minute has gone by
		if (GetTickCount() - _afxTickCount > 60000)
		{
			CoFreeUnusedLibraries();
			_afxTickCount = ::GetTickCount();
		}
	}
}