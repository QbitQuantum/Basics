//***************************************************************************************
HRESULT CBCGPShellList::DisplayParentFolder ()
{
	ASSERT_VALID (g_pShellManager);

	HRESULT hr = E_FAIL;
	if (m_pidlCurFQ == NULL)
	{
		return hr;
	}

	BCGCBITEMINFO info;
	int nLevel = g_pShellManager->GetParentItem (m_pidlCurFQ, info.pidlFQ);

	if (nLevel < 0)
	{
		return hr;
	}

	if (nLevel == 0)	// Desktop
	{
		hr = DisplayFolder (&info);
	}
	else
	{
		LPSHELLFOLDER pDesktopFolder;
		hr = SHGetDesktopFolder(&pDesktopFolder);

		if (SUCCEEDED (hr))
		{
			info.pParentFolder = pDesktopFolder;
			info.pidlRel = info.pidlFQ;

			hr = DisplayFolder (&info);
			pDesktopFolder->Release();
		}
	}

	g_pShellManager->FreeItem (info.pidlFQ);
	return hr;
}