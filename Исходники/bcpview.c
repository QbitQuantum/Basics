int LoadBCP(char *fn)
{
	int i, f; uint numfiles, root = 1, id; HTREEITEM pti = TVI_ROOT; int ver, rp;
	if(file) CloseBCP();
	file = fopen(fn, "rb");
	if(!file) fErr(-1, "File not found.");

	idti.hParent = TVI_ROOT;
	idti.hInsertAfter = TVI_LAST;
	idti.item.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	idti.item.pszText = abuf;
	idti.item.cchTextMax = 3;

	fseek(file, 9, SEEK_SET);
	ver = fgetc(file) - '0';
	fseek(file, 0x30, SEEK_SET);

	fseek(file, fentof = _getw(file), SEEK_SET);
	nfiles = _getw(file);
	fent = (fileentry*)malloc(nfiles*20);
	if(!fent) fErr(-2, "Failed to allocate memory for the file position/size table.");
	fread(fent, nfiles*20, 1, file);
	fetime = (FILETIME*)malloc(nfiles*sizeof(FILETIME));
	if(!fetime) fErr(-2092016, "Failed to allocate fetime.");

	fseek(file, fentof+4+nfiles*20, SEEK_SET);
	dirsp = dirstack; htisp = htistack;
	*dirsp = 1000; *htisp = TVI_ROOT;
	while(!feof(file))
	{
		// Directories
		if(root) {root = 0;}
		else
		{
			i = _getw(file);
			if(i)
			{
				// Next level
				dirsp++; // Push
				htisp++;
				dirlev++;
				if(dirlev >= MAX_DIR_LEV) fErr(-209161825, "Maximum directory level reached.");
				*dirsp = i+1;
			}
			while(!(--(*dirsp)))
			{
				dirsp--; // Pop
				htisp--;
				dirlev--;
			}
			if(ver == 2) {cfstr(); bufwtoa();}
			else afstr();
			if(feof(file)) goto flend;

			idti.hParent = *(htisp-1);
			idti.item.cchTextMax = strlen(abuf);
			idti.item.lParam = -1;
			idti.item.iImage = idti.item.iSelectedImage = 0;
			*htisp = TreeView_InsertItem(htree, &idti);
		}
		numfiles = _getw(file);

		// Files in directory listing.
		for(f = 0; f < numfiles; f++)
		{
			if(feof(file)) goto flend;
			id = _getw(file);
			fetime[id].dwLowDateTime = _getw(file);
			fetime[id].dwHighDateTime = _getw(file);
			if(ver == 2) {cfstr(); bufwtoa();}
			else afstr();

			idti.hParent = *htisp;
			idti.item.cchTextMax = strlen(abuf);
			idti.item.lParam = id;
			idti.item.iImage = idti.item.iSelectedImage = fent[id].form + 1;
			TreeView_InsertItem(htree, &idti);
		}
	}
flend:	return 0;
}