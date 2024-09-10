void _LogXMLStringsToFiles(const CStdString& sExpectedXML, const CStdString& sDiscoveredXML, const TCHAR* const lpszFunction)
{
	CStdString sFunction(lpszFunction);
	int n = sFunction.ReverseFind(_T(':'));
	if( 0 < n)
		sFunction.Delete(0, n+1);

	CStdString lpszRoot = TEST_PATH_MAKE_ABSOLUTE(_T("projects\\Protect\\src\\ApiWordDOMStrategiesTests\\docs\\TestWordDOMStrategies\\"));
	CStdString sExpectedFile(lpszRoot);
	CStdString sDiscoveredFile(lpszRoot);
	sExpectedFile += sFunction + _T("ExpectedXML.txt");	
	sDiscoveredFile += sFunction + _T("DiscoveredXML.txt");	

	MakeSureDirectoryPathExists(CT2A(sExpectedFile.c_str()));
	MakeSureDirectoryPathExists(CT2A(sDiscoveredFile.c_str()));

	WriteStringToFile(sExpectedFile, sExpectedXML);
	WriteStringToFile(sDiscoveredFile, sDiscoveredXML);
}