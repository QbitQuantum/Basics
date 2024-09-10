////////////////////////////////////////////////////////////////////////
// Function:	cmp
// Description:	compares to TCHARs - case insensitive
// Author:		James Morley-Smith
// Date:		December 2004
////////////////////////////////////////////////////////////////////////
BOOL cmp(LPCTSTR tc1, LPCTSTR tc2, int iChars)
{
	if (!tc1 || !tc2)
		return false;

	return !_memicmp(tc1, tc2, iChars*sizeof(TCHAR));
}