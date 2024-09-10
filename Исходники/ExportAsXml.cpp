bool CIdentsDBExtension::ExportDataSourceAsXml (LPUNKNOWN pIUnk, HPROJECT hPr, LPCSTR pFName, ULONG &rulCnt) 
{
	if (pIUnk) LPPROGRESSINDICATOR(pIUnk) -> ChangeText (PIFLAG_FILENAME, pFName);

// Datei bilden, wenn diese noch nicht existiert
int fh = _lcreat (pFName, 0);

	if (fh < 0) return false;

bool fRet = false;

	{
	// hier geht's los
	CXMLDocument Doc (fh);		// <?xml ...?>

	char cbBuffer[80];			// TRiAS Version, aktuelle Zeit 
	os_time_and_date now;
	string resVersion (g_cbTRiAS);
	ResString resTempl (IDS_SIGNONVERSION_MODAL, _MAX_PATH);
	
		resVersion += ": ";
		resVersion += resTempl;
	
		ATLTRY(now = os_time_and_date::now());
		strcpy (cbBuffer, resVersion.c_str());
		strcat (cbBuffer, now.to_string(" %e. %B %Y, %T").c_str());
	
		CXMLComment (fh, cbBuffer);
		CXMLComment (fh, ResString (IDS_COPYRIGHT, 100));	// allgemeines Copyright

	// DTD einfügen
		CXMLRawData (fh, s_cbDTD);

	// die eigentlichen Infos ausgeben
	CXMLAttribute Attr ("Version", "1.0");
	CXMLNode MainNode (fh, g_cbTRiASMetadata, Attr);

	ENUMLONGKEY ELK;
	EXPORTDATA ED;

		ED.fh = fh;
		ED.pIUnk = pIUnk;
		ED.ulCnt = rulCnt;

		ELK.eKey = 'i';
		ELK.eFcn = (ENUMLONGKEYPROC)ExportIdentEntryAsXml;
		ELK.ePtr = &ED;
		fRet = DEX_EnumPBDDataEx (hPr, ELK);
		rulCnt = ED.ulCnt;
	}

// Datei wieder schließen
	_lclose (fh);		// Datei schließen
	return fRet;
}