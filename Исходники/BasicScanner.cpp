// IS MEMBER 
// Is the testchar (2nd arg) found in the first set (1st arg)? If
// so return true. Note there is an equivalent function in StringUtils but
// we put this here for cohesion.
bool BasicScanner::isMemberOf(const char* ikCharSet, char iTestChar)
{
	UInt theSetLen = strlen(ikCharSet);
	for (UInt i = 0; i < theSetLen; i++)
	{
		if (iTestChar == ikCharSet[i])
			return true;
	}
	return false;
}