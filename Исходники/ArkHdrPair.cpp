// adds a file into the ark and hdr
// 
// args:	external filename of file on pc that you want to insert
//			internal filename to insert as in the ark and hdr
//			flag for whether to encrypt files when adding them
//				true:	to encrypt "*.dtb" files when they are added
//				false:	if "*.dtb" files being added are already encrypted
// returns:	true if inserted successfully
bool ArkHdrPair::AddFile(const char* srcFilepath, const char* arkFilename, bool performEncrypts)
{
	// ensure file doesnt already exist in ark
	FileEntrySetIter iter;
	const FileEntry* p_entry = First(iter, arkFilename);
	if(p_entry != NULL)
		return false;
	
	// file doesnt already exist, so add it
	bool encrypted = performEncrypts && (strstr(arkFilename, ".dtb") != 0);
	s64 filesize = GetFilesize(srcFilepath);
	if(filesize < 0)
		return false;
	FileEntry entry(arkFilename, srcFilepath, filesize, 0, encrypted);
	mFileCollection.Add(entry);
	mHasChanged = true;
	return true;
}