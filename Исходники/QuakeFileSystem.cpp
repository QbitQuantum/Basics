//!! change this mechanism
const char *FS_NextPath(const char *prevpath)
{
	static TString<64> Hold;
	if (!prevpath)
	{
		// prev==NULL => return GameDir
		Hold.sprintf("./%s", *FS.GameDir);
		return Hold;							// return GameDir; may be == BASEDIRNAME
	}
	// here: prev==BASEDIRNAME or GameDir
	if (stricmp(prevpath+2, BASEDIRNAME))		// prev!=BASEDIRNAME => return BASEDIRNAME
		return "./" BASEDIRNAME;
	// here: prev==BASEDIRNAME
	return NULL;
}