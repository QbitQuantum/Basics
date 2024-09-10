// remove the "*" and return for the purpose of roster...
CString CAirlineID::GetNonStarValue() const
{
	CString str;
	str = m_psz;
	str.Remove( '*' );
	return str;
}