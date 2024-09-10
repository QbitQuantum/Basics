// false when: a) no skin file b) absent one of skin shaders
static bool SetMd3Skin(const char *skinName, CModelSkin &skin)
{
	// load skin file
	TString<MAX_QPATH> Filename;
	Filename.sprintf("models/players/%s.skin", skinName);
	char	*buf;
	if (!(buf = (char*) GFileSystem->LoadFile(Filename)))
	{
		Com_DPrintf("no skin: %s\n", *Filename);
		return false;
	}

	// parse skin
	memset(&skin, 0, sizeof(skin));
	bool result = true;
	CSimpleParser text;
	text.InitFromBuf(buf);

	int numSurfs = 0;
	while (const char *line = text.GetLine())
	{
		const char *p = strchr(line, ',');
		if (!p || !p[1]) continue;		// no shader
		// check/load shader

		// special processing of "nodraw" shader
		const char *n = strrchr(p+1, '/');
		if (n) n++; else n = p+1;
		if (!strnicmp(n, "nodraw", 6) && (n[6] == 0 || n[6] == '.'))	// "nodraw" or "nodraw.ext"
		{
			Com_DPrintf("nodraw for %s/%s\n", skinName, line);
			continue;
		}

		CBasicImage *shader = RE_RegisterSkin(p+1);
		if (!shader)
		{
			// code based on gl_trimodel.cpp::SetMd3Skin()
			TString<64> MName;			// new skin name
			// try to find skin forcing model directory
			MName.filename(Filename);
			char *mPtr = MName.rchr('/');
			if (mPtr)	mPtr++;			// skip '/'
			else		mPtr = MName;

			const char *sPtr = strrchr(p+1, '/');
			if (sPtr)	sPtr++;			// skip '/'
			else		sPtr = p+1;

			strcpy(mPtr, sPtr);		// make "modelpath/skinname"
			shader = RE_RegisterSkin(MName, true);
		}
		if (numSurfs >= ARRAY_COUNT(skin.surf))
		{
			appWPrintf("Too much skin surfaces in %s\n", skinName);
			result = false;
			break;
		}
		// store info
		skin.surf[numSurfs].Name.toLower(line, p-line+1);
		skin.surf[numSurfs].shader = shader;
//		appPrintf("%s %d : [%s] <- %s\n", skinName, numSurfs, *skin.surf[numSurfs].Name, *shader->Name);
		numSurfs++;
	}
	if (result)
		skin.numSurfs = numSurfs;

	delete buf;

	return result;
}