/*************************************************************************
	Constructor
*************************************************************************/
CHelperSystem::CHelperSystem() : 
	m_pXMLParser(0)
{
	s_pMe = this;

	//Set work dir
	char szDir[MAX_PATH] = {0};
	GetCurrentDirectoryA(MAX_PATH, szDir);
	PathAppendA(szDir, "..\\Helper");
	PathAddBackslashA(szDir);
	m_strWorkDictory = szDir;

	// create TinyXML Parser.
	m_pXMLParser = new CHelperTinyXMLParser;
	// load all helper items.
	m_pHelpItemSet = new CHelperItemSet();
	//debug begin
	//m_pHelpItemSet->ShowPaihang(true);
	//m_pHelpItemSet->InitPaihangTree("104");
	//enddebug
	m_pHelpItemSet->LoadItemSet(CHelperSystem::GetMe()->GetWorkDictory() + "HelperItems.xml");
}