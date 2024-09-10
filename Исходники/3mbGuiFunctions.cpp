void IOMessageBox(RESLT Res, HWND Hwnd, TCHAR *AppendBuffer)
{
	TCHAR header[SIZE_64];
	TCHAR message[SIZE_128];

	switch(Res)
	{
	case OK:
		break;
	case OK_EOFREACHED:
		strcpy_s(header, sizeof(header), "End Of File Reached");

		// the -1 in _snprintf_s() is to ensure room for terminating null character.
		if(_tcslen(AppendBuffer) != 0)
			_snprintf_s(message, SIZE_128, SIZE_128, "Reached end of file in file:\n  %s", AppendBuffer);
		else
			strcpy_s(message, sizeof(message), header);
		break;
	case MEMALLOC_ERROR:
		strcpy_s(header, sizeof(header), "Memory Allocation Error");
		if(_tcslen(AppendBuffer) != 0)
		{
			_snprintf_s(message, SIZE_128, SIZE_128,
				"Couldn't initialize enough memory for data:\n  %s\nTry closing some applications.", AppendBuffer);
		}
		else
		{
			strcpy_s(message, sizeof(message), header);
		}
		break;

	case OPENFILEREAD_ERROR:
	case OPENFILEWRITE_ERROR:
		strcpy_s(header, sizeof(header), "File Open Error");
		if(_tcslen(AppendBuffer) != 0)
			_snprintf_s(message, SIZE_128, SIZE_128, "Unable to open file:\n  %s", AppendBuffer);
		else
			strcpy_s(message, sizeof(message), header);
		break;

	case CREATEBINARYOUTPUT_ERROR:
	case OPENTEXTOUTPUTFILE_ERROR:
		break;

	case FILEREAD_ERROR:
		strcpy_s(header, sizeof(header), "Read Error, file not read in.");
		if(_tcslen(AppendBuffer) != 0)
		{
			_snprintf_s(message, SIZE_128, SIZE_128, "A Read Error occured while reading\nmemory associated with file:\n  %s",
				AppendBuffer);
		}
		else
		{
			strcpy_s(message, sizeof(message), header);
		}
		break;

	case FILEWRITE_ERROR:
		strcpy_s(header, sizeof(header), "Write Error, file may not have properly written to disk.");
		if(_tcslen(AppendBuffer) != 0)
		{
			_snprintf_s(message, SIZE_128, SIZE_128, "A Write Error occured while writing\nmemory associated with file:\n  %s",
				AppendBuffer);
		}
		else
		{
			strcpy_s(message, sizeof(message), header);
		}
		break;

	case WRONGFILETYPE_ERROR:
		strcpy_s(header, sizeof(header), "Wrong File Type Error");
		if(_tcslen(AppendBuffer) != 0)
			_snprintf_s(message, SIZE_128, SIZE_128, "%s\nis the wrong file type for this application", AppendBuffer);
		else
			strcpy_s(message, sizeof(message), header);
		break;
	case INVALIDHANDLE_ERROR:
		strcpy_s(header, sizeof(header), "Invalid Handle");
		if(_tcslen(AppendBuffer) != 0)
		{
			_snprintf_s(message, SIZE_128, SIZE_128, "The handle to file\n  %s\nis invalid so the file can't be accessed",
				AppendBuffer);
		}
		else
		{
			strcpy_s(message, sizeof(message), "The handle to the requested file is\ninvalid and therefore inaccessable");
		}
		break;

	case USERMODELLINELENGTHEXCEEDED_ERROR:
		strcpy_s(header, sizeof(header), "User Model Maximum Line Length Exceeded");
		if(_tcslen(AppendBuffer) != 0)
			_snprintf_s(message, SIZE_128, SIZE_128, "File %s\nhas too many columns of data.\nFile not read in.", AppendBuffer);
		else
			strcpy_s(message, sizeof(message), header);
		break;

	case UNRECOGNIZED_SPECIES_MATRIX_PARAM_ERROR:
		strcpy_s(header, sizeof(header), "Species File Param Unrecognized");
		if(_tcslen(AppendBuffer) != 0)
			_snprintf_s(message, SIZE_128, SIZE_128, "File %s\nhas an unrecognized model type.\nFile not read in.", AppendBuffer);
		else
			strcpy_s(message, sizeof(message), header);
		break;
	default:
		strcpy_s(header, sizeof(message), "Unknown Error");
		if(_tcslen(AppendBuffer) != 0)
			_snprintf_s(message, SIZE_128, SIZE_128, "File %s\nhas an unknown error.  File not read in.", AppendBuffer);
		else
			strcpy_s(message, sizeof(message), header);
		break;
	}
	MessageBox(Hwnd, message, header, MB_ICONEXCLAMATION);
}