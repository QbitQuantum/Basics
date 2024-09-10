/**
* CStringW::operator>
* @date Modified Mar 02, 2006
*/
bool CStringW::operator>(const CStringW& str) const
{
	return wcsicmp(m_strTheString.c_str(), str.m_strTheString.c_str()) > 0;
}