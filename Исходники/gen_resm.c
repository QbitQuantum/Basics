/* Save the state of WinAmp */
void save_state()
{
	int ii;
	int eq;
	char eq_string[EQSIZE];
	int string_pos = 0;
	int list_pos;
	char *song_title;
	char *song_filename;
	char *str_to_write;
	char *tmpstr;
	int str_to_write_len;

	/* Only save if configured to do so currently */
	if ( SendMessage(module.hwndParent, WM_WA_IPC, 0, IPC_ISPLAYING) != 1 ) {
		/* WinAmp is not playing */
		/* Exit this procedure if we're not supposed to save while not playing */
		if ( GetPrivateProfileInt(INI_SECTNAME, KEY_SAVEWHILEPLAYING, DEFAULT_SAVEWHILEPLAYING, ini_path) == 1 )
			/* We're not supposed to save while not playing */
			return;
	}

	/* Write out the playlist */
	SendMessage(module.hwndParent, WM_WA_IPC, 0, IPC_WRITEPLAYLIST);

	/* Write out the current playlist position */
	list_pos = SendMessage(module.hwndParent, WM_WA_IPC, 0, IPC_GETLISTPOS);
	WritePrivateProfileInt(INI_SECTNAME, KEY_PLAYLISTLOC, list_pos, ini_path);

	/* Write out the position in the current song */
	/* If we're only supposed to resume from the beginning, always write 0. */
	if ( GetPrivateProfileInt(INI_SECTNAME, KEY_RESUMEATBEGINNING, DEFAULT_RESUMEATBEGINNING, ini_path) == 1 )
		WritePrivateProfileInt(INI_SECTNAME, KEY_SONGLOC, 0, ini_path);
	else
		WritePrivateProfileInt(INI_SECTNAME, KEY_SONGLOC, SendMessage(module.hwndParent, WM_WA_IPC, 0, IPC_GETOUTPUTTIME), ini_path);

	/* Write out the current equalizer settings */

	for ( ii = 0 ; ii < NUM_EQS ; ii++ ) {
		eq = SendMessage(module.hwndParent, WM_WA_IPC, ii, IPC_GETEQDATA);
		if (ii == 0) 
			sprintf(eq_string+string_pos, "%d", eq);
		else
			sprintf(eq_string+string_pos, ",%d", eq);
		/* Add to the length of the string the number of digits + the comma */
		string_pos += num_digits(eq) + (ii!=0);
	}

	/* Write out the EQ settings */
	WritePrivateProfileString(INI_SECTNAME, KEY_EQ, eq_string, ini_path);
	WritePrivateProfileInt(INI_SECTNAME, KEY_EQPREAMP, SendMessage(module.hwndParent, WM_WA_IPC, PREAMP, IPC_GETEQDATA), ini_path);
	WritePrivateProfileInt(INI_SECTNAME, KEY_EQENABLED, SendMessage(module.hwndParent, WM_WA_IPC, EQENABLED, IPC_GETEQDATA), ini_path);

	/* Write out the song name */
	tmpstr = (char*)SendMessage(module.hwndParent, WM_WA_IPC, list_pos, IPC_GETPLAYLISTFILE);
	if ( !tmpstr ) {
		/* Can't get filename, don't save state.  This is most likely because the playlist has been cleared. */
		WritePrivateProfileInt(INI_SECTNAME, KEY_SONGLOC, 0, ini_path);
		return;
	}
	else
		song_filename = strdup(tmpstr);

	tmpstr = (char*)SendMessage(module.hwndParent, WM_WA_IPC, list_pos, IPC_GETPLAYLISTTITLE);
	if ( !tmpstr ) {
		/* Again, playlist has probably be cleared.  Don't save state. */
		WritePrivateProfileInt(INI_SECTNAME, KEY_SONGLOC, 0, ini_path);		
		return;
	}
	else
		song_title = strdup(tmpstr);

	str_to_write_len = strlen(song_title) + strlen(song_filename) + 1;

	str_to_write = (char*)malloc(sizeof(char)*(str_to_write_len+1));
	_snprintf(str_to_write, SONG_NAME_BUF, "%s-%s", song_filename, song_title);
	
	WritePrivateProfileString(INI_SECTNAME, KEY_SONG_NAME, str_to_write, ini_path);
	free(song_filename);
	free(song_title);
	free(str_to_write);

	/* Force disk cache flush if requested */
	if ( GetPrivateProfileInt(INI_SECTNAME, KEY_FORCEFLUSH, DEFAULT_FORCEFLUSH, ini_path) ) 
		/* Note:  this feature only works because I'm linking to commode.obj! */
		_flushall();
}