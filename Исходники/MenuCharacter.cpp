DBOOL CMenuCharacter::DeleteB2CFile(char *szFile)
{
	char	str1[128];

	sprintf(str1, "players\\%s", szFile);

	// Don't delete the default files
	if(_mbscmp((const unsigned char*)szFile, (const unsigned char*)"caleb.b2c") == 0)	return DFALSE;
	if(_mbscmp((const unsigned char*)szFile, (const unsigned char*)"ophelia.b2c") == 0)	return DFALSE;
	if(_mbscmp((const unsigned char*)szFile, (const unsigned char*)"ishmael.b2c") == 0)	return DFALSE;
	if(_mbscmp((const unsigned char*)szFile, (const unsigned char*)"gabby.b2c") == 0)	return DFALSE;
	
	if(!remove(str1))
		return	DTRUE;
	else
		return	DFALSE;
}