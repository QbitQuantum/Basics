bool CalcOptions::getFontValue(const char *name, CHARFORMAT *fmt)
{
	const std::string& key = findKey(name);
	if(!key.length())
		return false;

	// extract font properties
	char buff[MaxLineLength+1];
	strcpy_s(buff, sizeof(buff), key.c_str());

   char *nextToken;
	fmt->dwMask = atoi(strtok_s(buff, ", ", &nextToken));
	fmt->dwEffects = atoi(strtok_s(NULL, ", ", &nextToken));
	fmt->yHeight = atoi(strtok_s(NULL, ", ", &nextToken));
	fmt->crTextColor = atoi(strtok_s(NULL, ", ", &nextToken));
   strcpy_s(fmt->szFaceName, sizeof(fmt->szFaceName), strtok_s(NULL, ",", &nextToken));
	return true;
}