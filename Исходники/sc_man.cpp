bool FScanner::OpenFile (const char *name)
{
	Close ();

	FileReader fr;
	if (!fr.OpenFile(name)) return false;
	auto filesize = fr.GetLength();
	auto filebuff = fr.Read();
	if (filebuff.Size() == 0 && filesize > 0) return false;

	ScriptBuffer = FString((const char *)filebuff.Data(), filesize);
	ScriptName = name;	// This is used for error messages so the full file name is preferable
	LumpNum = -1;
	PrepareScript ();
	return true;
}