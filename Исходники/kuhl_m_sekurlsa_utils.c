void kull_m_string_displayFileTime(IN PFILETIME pFileTime)
{
	SYSTEMTIME st;
	char buffer[0xff];
	if(pFileTime)
	{
		if(FileTimeToSystemTime(pFileTime, &st ))
		{
			if(GetDateFormatA(LOCALE_USER_DEFAULT, 0, &st, NULL, buffer, sizeof(buffer)))
			{
				dprintf("%s ", buffer);
				if(GetTimeFormatA(LOCALE_USER_DEFAULT, 0, &st, NULL, buffer, sizeof(buffer)))
					dprintf("%s", buffer);
			}
		}
	}
}