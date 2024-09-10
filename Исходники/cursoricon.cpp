HICON CURSORICON_LoadFromBuf(const BYTE * bits,DWORD filesize,INT width, INT height,BOOL fCursor, UINT loadflags)
{
	const CURSORICONFILEDIRENTRY *entry;
	const CURSORICONFILEDIR *dir;
	POINT hotspot;
	INT depth=1;

	/* Check for .ani. */
	if (memcmp( bits, "RIFF", 4 ) == 0)
	{//not support
        return  (HCURSOR)CreateIconFromResource((PBYTE)bits,filesize,FALSE,0x00030000);
	}

	dir = (const CURSORICONFILEDIR*) bits;
	if ( filesize < FIELD_OFFSET( CURSORICONFILEDIR, idEntries[dir->idCount] ))
		return 0;

	if(!(loadflags & LR_MONOCHROME))
	{
		HDC hdc=GetDC(NULL);
		depth=GetDeviceCaps(hdc,BITSPIXEL);
		ReleaseDC(NULL,hdc);
	}
	if ( fCursor )
		entry = CURSORICON_FindBestCursorFile( dir, filesize, width, height, depth, loadflags );
	else
		entry = CURSORICON_FindBestIconFile( dir, filesize, width, height, depth, loadflags );

	/* check that we don't run off the end of the file */
	if ( !entry || entry->dwDIBOffset > filesize || entry->dwDIBOffset + entry->dwDIBSize > filesize )
		return 0;

	hotspot.x = entry->xHotspot;
	hotspot.y = entry->yHotspot;
	return create_icon_from_bmi( (const BITMAPINFO *)&bits[entry->dwDIBOffset], filesize - entry->dwDIBOffset,
		NULL, NULL, NULL, hotspot, !fCursor, width, height, loadflags );
}