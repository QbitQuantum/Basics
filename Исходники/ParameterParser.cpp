static bool parse_parameter(const TCHAR *str, const size_t len, const TCHAR *arg_name, bool *first, TCHAR *dest_buff, size_t dest_size)
{
	if(*first)
	{
		*first = false;
		return false;
	}

	bool bSuccess = false;
	
	if((len > 1) && (str[0] == T('/')))
	{
		TCHAR *buffer = new TCHAR[len];
		memset(buffer, 0, sizeof(TCHAR) * len);
		STRNCPY(buffer, &str[1], len-1);

		TCHAR *offset = STRCHR(buffer, T('='));
		if(offset != NULL)
		{
			offset[0] = T('\0');
			if(STRICMP(buffer, arg_name) == 0)
			{
				bSuccess = true;
				STRNCPY(dest_buff, &offset[1], dest_size);
				dest_buff[dest_size-1] = T('\0');
			}
		}
		else
		{
			if(STRICMP(buffer, arg_name) == 0)
			{
				bSuccess = true;
				dest_buff[0] = T('\0');
			}
		}
	
		delete [] buffer;
	}

	return bSuccess;
}