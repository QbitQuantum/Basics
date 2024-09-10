/* ********************************************************************************* */
char* extract_filename(char *path, char* fname)
{
	char temp[MAX_PATH];
	int		i,j;
	int		len;

	len = strlen(path);
	memset(temp, 0x0, sizeof(temp));

	deb("path: %s", path);

	for(i=len-1,j=0;i;i--) {
		if(path[i] == '\\' || path[i] == ':' || path[i] == '/' || path[i] == 0x20)
			break;
		else {
			//deb("c %c", path[i]);
			temp[j++] = path[i];
		}
	}
	deb("temp: %s", temp);

	strcpy(fname, temp);
	_strrev(fname);
	deb("extracted name: %s", fname);
	return fname;
}