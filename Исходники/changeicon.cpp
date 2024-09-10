// Enums all icons to find the highest ID, then finds the IDs of the requested icon
bool Icon_list(const char *exename, WORD wIconId)
{
	HINSTANCE	hExe;
	int			cnt = 0;

    hExe = LoadLibraryEx(exename, NULL, LOAD_LIBRARY_AS_DATAFILE);
    if (hExe == 0)
		return false;

	// Get the highest icon ID in the file (g_Icon_nHighestID) 
	g_Icon_nHighestID = 0;
    if (EnumResourceNames(hExe, RT_GROUP_ICON, Icon_enum, (LPARAM)&cnt) == 0 && cnt == 0)
	{
		FreeLibrary(hExe);
		return false;							// No icons at all found
    }

#ifdef ICON_DEBUG
	char szBuffer[256];
	sprintf(szBuffer, "Highest icon ID was: %d", g_Icon_nHighestID);
	MessageBox(NULL, szBuffer, "", MB_OK);
#endif


	// Find the IDs for our _requested_ icon
	HRSRC				hRsrc = 0;
	HGLOBAL				hMem;
	IconGroupHeader		*pDirHeader;
	RsrcIconGroupEntry	*pResDir;
	int k;
	unsigned int j;

	hRsrc		= FindResource(hExe, MAKEINTRESOURCE(wIconId), RT_GROUP_ICON);
	hMem		= LoadResource(hExe, hRsrc);
	pDirHeader	= (IconGroupHeader*)LockResource(hMem);
	pResDir		= (RsrcIconGroupEntry*)(pDirHeader+1);

	// Note all the ids in our ID array
	g_Icon_NumImages = pDirHeader->wCount;
	for (k = 0; k < g_Icon_NumImages; k++)
		g_Icon_IDs[k] = pResDir[k].wRsrcId;

#ifdef ICON_DEBUG
	char szBuffer2[256];
	sprintf(szBuffer2, "Number images in requested icon: %d",g_Icon_NumImages);
	MessageBox(NULL, szBuffer2, "", MB_OK);
#endif

	// Now, we will be deleting the images for this icon, change our array so that the
	// remaining entries start at highest ID (the array will then contain the image IDs
	// of the request icon followed by "free" entries - which will help when we are writing
	// the replacement icon
	j = g_Icon_nHighestID + 1;					// Next available icon ID
	for (k=g_Icon_NumImages; k < ICON_MAX_IMAGES; k++)
		g_Icon_IDs[k] = j++;
	
#ifdef ICON_DEBUG
	char szBuffer3[256];
	for (k=0; k < ICON_MAX_IMAGES; k++)
	{
		sprintf(szBuffer3, "Icon IDs: %d",g_Icon_IDs[k]);
		MessageBox(NULL, szBuffer3, "", MB_OK);
	}
#endif

	FreeLibrary(hExe);
	return true;
}