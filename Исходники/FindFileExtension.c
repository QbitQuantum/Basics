/*--------------------------------------------------------------------------*/ 
char *FindFileExtension(char *filename)
{
	char *extension = NULL;
	if (filename)
	{
		#ifndef _MSC_VER
		int lengthfilename = (int) strlen(filename);
		int  i = lengthfilename;

		while(filename[i] != '.' && i > 0) i--;

		if(i > 0)
		{
			int lengthextension = lengthfilename - i;
			extension = (char*)MALLOC(sizeof(char)*(lengthextension+1));
			if (extension) sprintf(extension,"%s",&filename[i]);
		}
		#else
		{
			wchar_t *wcFilename = to_wide_string(filename);
			if (wcFilename)
			{
				extension = wide_string_to_UTF8(PathFindExtensionW(wcFilename));
				FREE(wcFilename);
				wcFilename = NULL;
			}
		}
		#endif
	}
	return extension;
}