bool CIwGameFile::GetFileType(const char* file_path, CIwGameString& type)
{
	int						len = strlen(file_path) - 1;
	const char*				name_ptr = file_path + len;

	// Scan backwards looking for dot
	int index = 0;
	while (len >= 0)
	{
		if (*name_ptr == '.')
		{
			type.setString(name_ptr + 1, index);
			type.ToLower();
			break;
		}
		else
		if (len == 0)
		{
			type.setString(name_ptr, index + 1);
			type.ToLower();
			break;
		}
		name_ptr--;
		index++;
		len--;
	}
	
	return true;
}