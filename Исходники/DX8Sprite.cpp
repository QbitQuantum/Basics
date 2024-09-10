bool DirectGraphicsSprite::LoadImage(char *Filename, int xs, int ys, int xfs, int yfs, 
														 int xfc,  int yfc)
{
	if(GameRunning == false) 
		return false;

	bool			fromrar;
	HRESULT			hresult;
	char			*pData; 
	char			Temp[256];
	unsigned long	Size; 

	// zuerst eine evtl benutzte Textur freigeben
	SafeRelease(itsTexture);

	fromrar = false;

	// Zuerst checken, ob sich die Grafik in einem MOD-Ordner befindet
	if (CommandLineParams.RunOwnLevelList == true)
	{
		sprintf_s(Temp, "levels/%s/%s", CommandLineParams.OwnLevelList, Filename);
		if (FileExists(Temp))
			goto loadfile;
	}

	// Dann checken, ob sich das File im Standard Ordner befindet
	sprintf_s(Temp, "data/%s", Filename);
	if (FileExists(Temp))
		goto loadfile;

	// Auch nicht? Dann ist es hoffentlich im RAR file
	if (urarlib_get(&pData, &Size, Filename, RARFILENAME, convertText(RARFILEPASSWORD)) == false)
	{		
		sprintf_s(Temp, "\n-> Error loading %s from Archive !\n", Filename);
		Protokoll.WriteText(Temp, true);
		return false;
	}
	else
		fromrar = true;

loadfile:

	// normal von Platte laden?
	if (fromrar == false)
	{
		// Textur laden
		hresult = D3DXCreateTextureFromFileEx(
				  lpD3DDevice,
				  Temp,
				  NULL, NULL,				  // x und y Grösse des Sprites (aus Datei übernehmen)
				  1,                          // Nur eine Version der Textur
				  0,                          // Immer 0 setzen
				  D3DFMT_UNKNOWN,			  // Format aus der Datei lesen
				  D3DPOOL_MANAGED,            // DX bestimmt wo die Textur gespeichert wird 
				  D3DX_FILTER_NONE,			  // Keine Filter verwenden
				  D3DX_FILTER_NONE,
				  0xFFFF00FF,                 // Colorkeyfarbe (Lila)
				  NULL,						  // Keine Image Info
				  NULL,						  // Keine Palette angeben
				  &itsTexture);
	}
	else
	{
		// Textur aus Speicher erzeugen
		hresult = D3DXCreateTextureFromFileInMemoryEx(
				  lpD3DDevice,
				  (LPVOID)pData,
				  Size, 
				  NULL, NULL,				  // x und y Grösse des Sprites (aus Datei übernehmen)
				  1,                          // Nur eine Version der Textur
				  0,                          // Immer 0 setzen
				  D3DFMT_UNKNOWN,			  // Format aus der Datei lesen
				  D3DPOOL_MANAGED,            // DX bestimmt wo die Textur gespeichert wird 
				  D3DX_FILTER_NONE,			  // Keine Filter verwenden
				  D3DX_FILTER_NONE,
				  0xFFFF00FF,                 // Colorkeyfarbe (Lila)
				  NULL,						  // Keine Image Info
				  NULL,						  // Keine Palette angeben
				  &itsTexture);

		free(pData);
	}

	// Fehler beim Laden ?
	if(hresult != D3D_OK)
	{
		strcpy_s(Temp, strlen("Fehler beim Laden von ") + 1, "Fehler beim Laden von ");
		strcat_s(Temp, strlen(Filename) + 1, Filename);
		strcat_s(Temp, 4, " !\n");
		Protokoll.WriteText(Temp, true);
		return false;
	}
	
	// Grösse der Textur anpassen
	D3DSURFACE_DESC desc;
	itsTexture->GetLevelDesc(0,&desc);	

	// Grösse setzen
	itsXSize		= (float)desc.Width;
	itsYSize		= (float)desc.Height;
	itsXFrameCount	= xfc;
	itsYFrameCount	= yfc;
	itsXFrameSize	= xfs;
	itsYFrameSize	= yfs;
	itsRect.left	= 0;
	itsRect.top		= 0;
	itsRect.right	= (int)itsXSize;
	itsRect.bottom	= (int)itsYSize;

	// Ausschnitte vorberechnen
	for (int i = 0; i < xfc * yfc; i++)
	{
		itsPreCalcedRects[i].top	= (i/itsXFrameCount) * itsYFrameSize;
		itsPreCalcedRects[i].left	= (i%itsXFrameCount) * itsXFrameSize;
		itsPreCalcedRects[i].right  = itsPreCalcedRects[i].left + itsXFrameSize;
		itsPreCalcedRects[i].bottom = itsPreCalcedRects[i].top  + itsYFrameSize;
	}

	itsRect = itsPreCalcedRects[0];

	// Bild korrekt geladen
	sprintf_s(Temp, "%s %s %s %s", TextArray [TEXT_LADE_BITMAP], Filename, TextArray [TEXT_LADEN_ERFOLGREICH], "\n");
	Protokoll.WriteText(Temp, false);			

	DisplayLoadInfo(Temp);

	LoadedTextures++;							// Anzahl der geladenen Texturen erhöhen
	//_itoa_s(LoadedTextures, Temp, 10);
//	Protokoll.WriteText(Temp, false);
//	Protokoll.WriteText(" Sprite Textur(en) geladen !\n", false);
	return true;
}