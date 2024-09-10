//---------------------------------------------------------------------------
void FullPathFileName::init (char * dir_path, const char * name, char * ext)
{
	destroy();

	size_t total_length = strlen(dir_path);
	total_length += strlen(name);
	total_length += strlen(ext);
	total_length++;


	fullName = (char *)systemHeap->Malloc(total_length);
	gosASSERT(fullName != NULL);
	if (fullName == NULL)
		return;
	fullName[0] = 0;

	if ( strstr( name, dir_path ) != name )
		strcpy_s(fullName, total_length, dir_path);

	if (name)
		strcat_s(fullName, total_length, name);

	// don't append if its already there
	if (ext && _stricmp( fullName + strlen( fullName ) - strlen( ext ), ext ) != 0)
		strcat_s(fullName, total_length, ext);

	// CharLowerA(fullName);
	_strlwr_s(fullName, total_length);
}