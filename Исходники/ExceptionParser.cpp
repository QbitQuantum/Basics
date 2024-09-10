CExceptionParser::~CExceptionParser(void)
{
	if(m_hProcess)
		SymCleanup(m_hProcess);
}