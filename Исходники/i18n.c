static bool setLocaleWindows(USHORT usPrimaryLanguage, USHORT usSubLanguage)
{
	bool success = SUCCEEDED( SetThreadLocale( MAKELCID( MAKELANGID(usPrimaryLanguage, usSubLanguage), SORT_DEFAULT ) ) );

	if (!success)
	{
		info("Failed to set locale to \"%d\"", usPrimaryLanguage);
	}
	else
	{
		debug(LOG_WZ, "Requested locale \"%d\"", usPrimaryLanguage);
	}

	setlocale(LC_NUMERIC, "C"); // set radix character to the period (".")

	return success;
}