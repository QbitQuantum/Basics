CStdStringW AlphaIndexFormatter::Render(int iValue)
{
	iValue = iValue % 780;
	int iRep = (iValue-1) / 26 + 1;
	int iChar = (iValue-1) % 26 + 'A';

	CStdStringW sResult;
	sResult.resize(iRep, iChar);

	if (m_bLowerCase)
		sResult.ToLower();

	return sResult;
}