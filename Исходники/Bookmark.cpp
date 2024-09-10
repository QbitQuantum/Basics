CBookmark::CBookmark(const std::wstring &strName,const std::wstring &strLocation,const std::wstring &strDescription) :
	m_strName(strName),
	m_strLocation(strLocation),
	m_strDescription(strDescription),
	m_iVisitCount(0)
{
	CoCreateGuid(&m_guid);
	GetSystemTimeAsFileTime(&m_ftCreated);
}