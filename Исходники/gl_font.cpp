bool CFont::Load(const char *name)
{
	TString<64> Filename;
	Filename.sprintf("fonts/%s.font", name);
	char* buf = (char*)GFileSystem->LoadFile(Filename);
	if (!buf)
	{
		appWPrintf("File %s does not exist\n", *Filename);
		return false;
	}
	CSimpleParser text;
	text.InitFromBuf(buf);
	loadingFont = this;
	while (const char *line = text.GetLine())
	{
		if (!ExecuteCommand(line, ARRAY_ARG(fontCommands)))
			appWPrintf("%s: invalid line [%s]\n", name, line);
	}
	// setup remaining fields
	Name    = name;
	spacing = FONT_SPACING;

	delete buf;

	return true;
}