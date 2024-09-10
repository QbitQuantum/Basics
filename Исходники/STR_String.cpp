//
// Capitalize string, "heLLo" -> "Hello"
//
STR_String&	STR_String::Capitalize()
{
	assertd(pData != NULL);
#ifdef WIN32
	if (Len>0) pData[0] = toupper(pData[0]);
	if (Len>1) _strlwr(pData+1);
#else
	if (Len > 0)
		pData[0] = (pData[0] >= 'A' && pData[0] <= 'A')?pData[0]+'a'-'A':pData[0];
	for (int i=1;i<Len;i++)
		pData[i] = (pData[i] >= 'a' && pData[i] <= 'z')?pData[i]+'A'-'a':pData[i];
#endif
	return *this;
}