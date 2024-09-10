/**
 * name:	ExportModule
 * desc:	write all settings from a database module to file
 * param:	hContact	- handle of contact the module is owned from
 *			pszModule	- name of the module to save
 *			file		- file to write the settings to
 * return	nothing
 **/
static void ExportModule(MCONTACT hContact, LPCSTR pszModule, FILE* file)
{
	DB::CEnumList	Settings;

	if (!Settings.EnumSettings(hContact, pszModule))
	{
		DBVARIANT dbv;
		LPSTR here;
		WORD j;
		int i;
		LPSTR pszSetting;
		//char tmp[32];

		// print the module header..
		fprintf(file, "\n[%s]\n", pszModule);

		for (i = 0; i < Settings.getCount(); i++)
		{
			pszSetting = Settings[i];

			if (!DB::Setting::GetAsIs(hContact, pszModule, pszSetting, &dbv))
			{
				switch (dbv.type) 
				{
					case DBVT_BYTE:
						{
							fprintf(file, "%s=b%u\n", pszSetting, dbv.bVal);
						}
						break;

					case DBVT_WORD:
						{
							fprintf(file, "%s=w%u\n", pszSetting, dbv.wVal);
						}
						break;

					case DBVT_DWORD:
						{
							fprintf(file, "%s=d%u\n", pszSetting, dbv.dVal);
						}
						break;

					case DBVT_ASCIIZ:
					case DBVT_UTF8:
						{
							for (here = dbv.pszVal; here && *here; here++) 
							{
								switch (*here) {
									// convert \r to STX
									case '\r':
										*here = 2;
										break;

									// convert \n to ETX
									case '\n':
										*here = 3;
								}
							}
							if (dbv.type == DBVT_UTF8) 
								fprintf(file, "%s=u%s\n", pszSetting, dbv.pszVal);
							else
								fprintf(file, "%s=s%s\n", pszSetting, dbv.pszVal);
						}
						break;

					case DBVT_BLOB:
						{
							fprintf(file, "%s=n", pszSetting);
							for (j = 0; j < dbv.cpbVal; j++)
							{
								fprintf(file, "%02X ", (BYTE)dbv.pbVal[j]);
							}
							fputc('\n', file);
						}
						break;
				}
				db_free(&dbv);
			}
		}
	}
}