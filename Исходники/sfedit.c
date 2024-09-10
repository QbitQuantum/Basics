/*** sfeLoadFile - loads a new file into the program.
 ***/
int
sfeLoadFile(char* filename)
    {
    pFile fd;
    pStructInf new_filedata;

	/** open the file. **/
	if (strlen(filename) > 255) return -1;
	fd = fdOpen(filename, O_RDONLY, 0600);
	if (!fd) return -1;

	/** Try to parse it **/
	new_filedata = stParseMsg(fd, 0);
	fdClose(fd,0);
	if (!new_filedata) return -1;
	if (SFE_Globals.Data) stFreeInf(SFE_Globals.Data);
	SFE_Globals.Data = new_filedata;
	SFE_Globals.Modified = 0;

	/** Set the filename and title **/
	strcpy(SFE_Globals.Filename, filename);
	sfeSetTitle(GTK_WINDOW(SFE_Globals.Window), SFE_Globals.Filename);

	/** Rebuild the ui **/
	sfeRebuildUI(SFE_Globals.Data, GTK_TREE(SFE_Globals.TreeView));

    return 0;
    }