//Pabs inserted
//Parts copied from compiler docs - search for ITEMIDLIST in title in msdn
//Adapted from Q132750:"HOWTO: Convert a File Path to an ITEMIDLIST" in the Knowledge Base
STDAPI PathsEqual(LPCTSTR p0, LPCTSTR p1)
{
	LPSHELLFOLDER pFolder;
	HRESULT hr;
	if (SUCCEEDED(hr = SHGetDesktopFolder(&pFolder)))
	{
		LPITEMIDLIST pidl[2] = { NULL, NULL };
		ULONG chEaten;//only needed by parse dispname
		// Convert the paths to ITEMIDLISTs.
		if (SUCCEEDED(hr = pFolder->ParseDisplayName(NULL, NULL,
				const_cast<LPOLESTR>(&*static_cast<T2W>(p0)), &chEaten, &pidl[0], NULL)) &&
			SUCCEEDED(hr = pFolder->ParseDisplayName(NULL, NULL,
				const_cast<LPOLESTR>(&*static_cast<T2W>(p1)), &chEaten, &pidl[1], NULL)))
		{
			hr = pFolder->CompareIDs(0, pidl[0], pidl[1]);
		}

		//free ITEMIDLISTs
		IMalloc* pm;
		SHGetMalloc(&pm);
		pm->Free(pidl[0]);
		pm->Free(pidl[1]);
		pm->Release();

		pFolder->Release();
	}
	return hr;
}