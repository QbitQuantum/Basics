void vmsHttpFlvTrafficAnalyzer::ExtractTitleFromXml(const vmsHttpTrafficCollector::HttpDialog *pDlg, wstring &wstrTitle, const vmsHttpTrafficCollector::HttpDialog* pFlvDlg)
{
	extern LPCSTR strstrni (LPCSTR pszSrc, LPCSTR pszSrch, int lenSrc);
	extern LPCSTR strstrn (LPCSTR pszSrc, LPCSTR pszSrch, int lenSrc);

	wstrTitle = L"";
	
	assert (pDlg != NULL);
	if (!pDlg)
		return;
	assert (pDlg->enCT == vmsHttpTrafficCollector::HttpDialog::XML);
	
	if (pDlg->vbResponseBody.empty ())
		return;

	LPCSTR pszXml = (LPCSTR)&pDlg->vbResponseBody [0];
	int iXmlLen = pDlg->vbResponseBody.size ();

	

	LPCSTR pszXml2 = strstrni (pszXml, "encoding=\"", iXmlLen);
	if (!pszXml2)
		return;
	
	pszXml2 += 10;
	iXmlLen -= pszXml2 - pszXml;
	pszXml = pszXml2;
	if (iXmlLen < 5)
		return;

	if (strnicmp (pszXml, "utf-8", 5))
		return;

	

	USES_CONVERSION;
	tstring tstrRequestUrl = A2CT (pFlvDlg->strRequestUrl.c_str ());
	
	
	string strUrl = vmsXmlHelper::toUtf8noEncode (tstrRequestUrl);
	pszXml2 = strstrn (pszXml, strUrl.c_str (), iXmlLen);

	if (!pszXml2)
	{
		
		strUrl = vmsXmlHelper::toUtf8 (tstrRequestUrl);
		pszXml2 = strstrn (pszXml, strUrl.c_str (), iXmlLen);
		if (!pszXml2)
		{
			
			strUrl = pFlvDlg->strRequestUrl;
			pszXml2 = strstrn (pszXml, strUrl.c_str (), iXmlLen);
		}
	}

	

	LPCSTR pszVideoSectionTag = pszXml;

	if (pszXml2)
	{
		

		bool bAsAttr = pszXml2 [-1] != '>'; 

		if (bAsAttr)
		{
			
			
			while (pszXml2 > pszXml && *pszXml2 != '"')
				pszXml2--;
			pszXml2--;
			if (pszXml2 > pszXml)
			{
				bool bInQ = false;
				while (pszXml2 > pszXml)
				{
					if (*pszXml2 == '"')
						bInQ = !bInQ;
					else if (*pszXml2 == '<' && bInQ == false)
						break;
					pszXml2--;
				}
				if (pszXml2 > pszXml)
					pszVideoSectionTag = pszXml2;
			}
		}
		else
		{
			
			

			
			while (pszXml2 > pszXml && *pszXml2 != '<')
				pszXml2--;
			pszXml2--;
			if (pszXml2 > pszXml)
			{
				
				bool bInT = false; 
				while (pszXml2 > pszXml)
				{
					if (*pszXml2 == '<')
					{
						if (bInT)
						{
							
							bInT = false;
						}
						else
						{
							if (pszXml2 [1] == '/')
							{
								bInT = true; 
							}
							else
							{
								
								
								break;
							}
						}
					}
					pszXml2--;
				}
				if (pszXml2 > pszXml)
					pszVideoSectionTag = pszXml2;
			}
		}
	}

	

	int iXmlLen2 = iXmlLen - (pszVideoSectionTag - pszXml);

	LPCSTR apszTags [] = {"title=\"", "<title>", "name=\"", "<name>"};
	int iTag;
	LPCSTR pszTitle = NULL;
	
	do
	{	
		for (iTag = 0; iTag < sizeof (apszTags)/sizeof (LPCSTR) && pszTitle == NULL; iTag++)
			pszTitle = strstrni (pszVideoSectionTag, apszTags [iTag], iXmlLen2);
		if (!pszTitle)
		{
			if (pszVideoSectionTag != pszXml)
			{
				
				pszVideoSectionTag = pszXml;
				iXmlLen2 = iXmlLen;
			}
			else
			{
				return; 
			}			
		}
	}
	while (pszTitle == NULL);

	pszTitle += strlen (apszTags [iTag]);

	LPCSTR pszTitleE = pszTitle;
	int iXmlLen3 = iXmlLen - (pszTitle - pszXml);
	char chEnd = pszTitle [-1] == '>' ? '<' : '"';
	while (*pszTitleE != chEnd && iXmlLen3)
	{
		pszTitleE++;
		iXmlLen3--;
	}
	if (!iXmlLen3)
		return; 
	string strTitle; strTitle.assign (pszTitle, pszTitleE-pszTitle);

	int n = MultiByteToWideChar (CP_UTF8, 0, strTitle.c_str (), -1, NULL, 0);
	assert (n != 0);
	LPWSTR pwsz = new WCHAR [n+1]; *pwsz = 0;
	MultiByteToWideChar (CP_UTF8, 0, strTitle.c_str (), -1, pwsz, n);
	wstrTitle = pwsz;
	delete [] pwsz;
}