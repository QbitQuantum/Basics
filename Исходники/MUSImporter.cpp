/** Loads a PlayList for playing */
bool MUSImporter::OpenPlaylist(const char* name)
{
	if (PLName[0] != '\0') {
		int len = ( int ) strlen( PLName );
		if (strnicmp( name, PLName, len ) == 0)
			return true;
	}
	if (Playing) {
		return false;
	}
	core->GetAudioDrv()->ResetMusics();
	playlist.clear();
	PLpos = 0;
	if (name[0] == '*') {
		return false;
	}
	char path[_MAX_PATH];
	PathJoin(path, core->GamePath, musicsubfolder, name, NULL);
	printMessage("MUSImporter", "", WHITE);
	printf( "Loading %s...", path );
	if (!str->Open( path, true )) {
		printStatus("NOT FOUND", LIGHT_RED );
		return false;
	}
	printStatus("FOUND", LIGHT_GREEN );
	int c = str->ReadLine( PLName, 32 );
	while (c > 0) {
		if (( PLName[c - 1] == ' ' ) || ( PLName[c - 1] == '\t' ))
			PLName[c - 1] = 0;
		else
			break;
		c--;
	}
	char counts[5];
	str->ReadLine( counts, 5 );
	int count = atoi( counts );
	while (count != 0) {
		char line[64];
		int len = str->ReadLine( line, 64 );
		int i = 0;
		int p = 0;
		PLString pls;
		while (i < len) {
			if (( line[i] != ' ' ) && ( line[i] != '\t' ))
				pls.PLFile[p++] = line[i++];
			else {
				while (i < len) {
					if (( line[i] == ' ' ) || ( line[i] == '\t' ))
						i++;
					else
						break;
				}
				break;
			}
		}
		pls.PLFile[p] = 0;
		p = 0;
		if (line[i] != '@' && ( i < len )) {
			while (i < len) {
				if (( line[i] != ' ' ) && ( line[i] != '\t' ))
					pls.PLTag[p++] = line[i++];
				else
					break;
			}
			pls.PLTag[p] = 0;
			p = 0;
			while (i < len) {
				if (( line[i] == ' ' ) || ( line[i] == '\t' ))
					i++;
				else {
					break;
				}
			}
			if (line[i] == '@')
				strcpy( pls.PLLoop, pls.PLTag );
			else {
				while (i < len) {
					if (( line[i] != ' ' ) && ( line[i] != '\t' ))
						pls.PLLoop[p++] = line[i++];
					else
						break;
				}
				pls.PLLoop[p] = 0;
			}
			while (i < len) {
				if (( line[i] == ' ' ) || ( line[i] == '\t' ))
					i++;
				else
					break;
			}
			p = 0;
		} else {
			pls.PLTag[0] = 0;
			pls.PLLoop[0] = 0;
		}
		while (i < len) {
			if (( line[i] != ' ' ) && ( line[i] != '\t' ))
				i++;
			else {
				while (i < len) {
					if (( line[i] == ' ' ) || ( line[i] == '\t' ))
						i++;
					else
						break;
				}
				break;
			}
		}
		while (i < len) {
			if (( line[i] != ' ' ) && ( line[i] != '\t' ))
				pls.PLEnd[p++] = line[i++];
			else
				break;
		}
		pls.PLEnd[p] = 0;
		playlist.push_back( pls );
		count--;
	}
	return true;
}