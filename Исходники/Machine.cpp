bool Machine::isValidPattern(wstring pattern)
{
	int i;
	for (i = 0; i < pattern.length(); i++)
	{
		if (m_pLanguageSet.find(pattern[i]) == m_pLanguageSet.end())
		{
			return false;
		}
	}
	return true;
}