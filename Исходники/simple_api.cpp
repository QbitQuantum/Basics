static bool ReadStringFromFile (const char* pathName, std::string& output)
{
#	ifdef _MSC_VER
	wchar_t widePath[MAX_PATH];
	int res = ::MultiByteToWideChar (CP_UTF8, 0, pathName, -1, widePath, MAX_PATH);
	if (res == 0)
		widePath[0] = 0;
	FILE* file = _wfopen(widePath, L"rb");
#	else // ifdef _MSC_VER
	FILE* file = fopen(pathName, "rb");
#	endif // !ifdef _MSC_VER

	if (file == NULL)
		return false;
	
	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	fseek(file, 0, SEEK_SET);
	if (length < 0)
	{
		fclose( file );
		return false;
	}
	
	output.resize(length);
	size_t readLength = fread(&*output.begin(), 1, length, file);
	
	fclose(file);
	
	if (readLength != length)
	{
		output.clear();
		return false;
	}

	replace_string(output, "\r\n", "\n", 0);
	
	return true;
}