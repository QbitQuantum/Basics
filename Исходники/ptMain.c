static GHTTPBool ptaFilePlanetCompletedCallback
(
	GHTTPRequest request,
	GHTTPResult result,
	char * buffer,
	GHTTPByteCount bufferLen,
	void * param
)
{
	ptaFilePlanetInfoData * data = (ptaFilePlanetInfoData *)param;
	int len;
	char description[256];
	char size[64];
	char * mirrorNames[MAX_MIRRORS];
	char * mirrorURLs[MAX_MIRRORS];
	int i;
	char * str;

	// check if the backend is available
	if(__GSIACResult != GSIACAvailable)
		return GHTTPFalse;

	GSI_UNUSED(request);
	GSI_UNUSED(bufferLen);

	// Check for success.
	/////////////////////
	if(result != GHTTPSuccess)
		return ptaFilePlanetInfoFailed(data);

	// Get the description.
	///////////////////////
	len = ptaFillLine(buffer);
	if(len == EOF)
		return ptaFilePlanetInfoFailed(data);
	buffer += len;
	strncpy(description, Line, sizeof(description));
	description[sizeof(description) - 1] = '\0';

	// Get the size.
	////////////////
	len = ptaFillLine(buffer);
	if(len == EOF)
		return ptaFilePlanetInfoFailed(data);
	buffer += len;
	strncpy(size, Line, sizeof(size));
	size[sizeof(size) - 1] = '\0';

	// Get the mirrors.
	///////////////////
	for(i = 0 ; (i < MAX_MIRRORS) && ((len = ptaFillLine(buffer)) != EOF) ; )
	{
		// Adjust the buffer.
		/////////////////////
		buffer += len;

		// Find the tab.
		////////////////
		str = strchr(Line, '\t');
		if(!str)
			continue;

		// Copy off the name.
		/////////////////////
		len = (str - Line);
		mirrorNames[i] = (char *)gsimalloc((unsigned int)len + 1);
		if(!mirrorNames[i])
			break;
		memcpy(mirrorNames[i], Line, (unsigned int)len);
		mirrorNames[i][len] = '\0';

		// Copy off the URL.
		////////////////////
		str++;
		len = (int)strlen(str);
		mirrorURLs[i] = (char *)gsimalloc((unsigned int)len + 1);
		if(!mirrorURLs[i])
		{
			gsifree(mirrorNames[i]);
			break;
		}
		strcpy_s(mirrorURLs[i], sizeof(mirrorURLs)-i, str);

		// One more mirror.
		///////////////////
		i++;
	}

	// Call the callback.
	/////////////////////
	ptaCallFilePlanetInfoCallback(data, PTTrue, description, size, i, mirrorNames, mirrorURLs);

	return GHTTPTrue;
}