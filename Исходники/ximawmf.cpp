/**********************************************************************
 Function:	ConvertWmfFiletoEmf
 Purpose:	Converts a Windows Metafile into an Enhanced Metafile
**********************************************************************/
HENHMETAFILE CxImageWMF::ConvertWmfFiletoEmf(CxFile *fp, METAFILEHEADER *metafileheader)
{
	HENHMETAFILE	hMeta;
	long			lenFile;
	long			len;
	BYTE			*p;
	METAHEADER		mfHeader;
	DWORD			seekpos;

	hMeta = 0;

	// get length of the file
	lenFile = fp->Size();

	// a placeable metafile starts with a METAFILEHEADER
	// read it and check metafileheader
	len = fp->Read(metafileheader, 1, sizeof(METAFILEHEADER));
	if (len < sizeof(METAFILEHEADER)) return (hMeta);

	if (CheckMetafileHeader(metafileheader)) {
		// This is a placeable metafile 
		// Convert the placeable format into something that can
		// be used with GDI metafile functions 
		seekpos = sizeof(METAFILEHEADER);
	} else {
		// Not a placeable wmf. A windows metafile?
		// at least not scaleable.
		// we could try to convert, but would loose ratio. don't allow this
		return (hMeta);

		//metafileheader->bbox.right = ?;
		//metafileheader->bbox.left = ?;
		//metafileheader->bbox.bottom = ?;
		//metafileheader->bbox.top = ?;
		//metafileheader->inch = ?;
		//
		//seekpos = 0;
		// fp->Seek(0, SEEK_SET);	// rewind
	}

	// At this point we have a metaheader regardless of whether
	// the metafile was a windows metafile or a placeable metafile
	// so check to see if it is valid. There is really no good
	// way to do this so just make sure that the mtType is either
	// 1 or 2 (memory or disk file) 
	// in addition we compare the length of the METAHEADER against
	// the length of the file. if filelength < len => no Metafile

	len = fp->Read(&mfHeader, 1, sizeof(METAHEADER));
	if (len < sizeof(METAHEADER)) return (hMeta);

	if ((mfHeader.mtType != 1) && (mfHeader.mtType != 2)) return (hMeta);

	// Length in Bytes from METAHEADER
	len = mfHeader.mtSize * 2;
	if (len > lenFile) return (hMeta);

	// Allocate memory for the metafile bits 
	p = (BYTE *)malloc(len);
	if (!p)	return (hMeta);

	// seek back to METAHEADER and read all the stuff at once
	fp->Seek(seekpos, SEEK_SET);
	lenFile = fp->Read(p, 1, len);
	if (lenFile != len)	{
		free(p);
		return (hMeta);
	}

	// the following (commented code)  works, but adjusts rclBound of the
	// Enhanced Metafile to full screen.
	// the METAFILEHEADER from above is needed to scale the image

//	hMeta = SetWinMetaFileBits(len, p, NULL, NULL);

	// scale the metafile (pixels/inch of metafile => pixels/inch of display)

	METAFILEPICT	mfp;
	int cx1, cy1;
	HDC hDC;

	hDC = ::GetDC(0);
	cx1 = ::GetDeviceCaps(hDC, LOGPIXELSX);
	cy1 = ::GetDeviceCaps(hDC, LOGPIXELSY);

	memset(&mfp, 0, sizeof(mfp));

	mfp.mm = MM_ANISOTROPIC;
	mfp.xExt = (metafileheader->bbox.right - metafileheader->bbox.left) * cx1 / metafileheader->inch;
	mfp.yExt = (metafileheader->bbox.bottom - metafileheader->bbox.top) * cy1 / metafileheader->inch;
	mfp.hMF = 0;

	// in MM_ANISOTROPIC mode xExt and yExt are in MM_HIENGLISH
	// MM_HIENGLISH means: Each logical unit is converted to 0.001 inch
	//mfp.xExt *= 1000;
	//mfp.yExt *= 1000;
	// ????
	//int k = 332800 / ::GetSystemMetrics(SM_CXSCREEN);
	//mfp.xExt *= k;	mfp.yExt *= k;

	// fix for Win9x
	while ((mfp.xExt < 6554) && (mfp.yExt < 6554))
	{
		mfp.xExt *= 10;
		mfp.yExt *= 10;
	}

	hMeta = SetWinMetaFileBits(len, p, hDC, &mfp);

	if (!hMeta){ //try 2nd conversion using a different mapping
		mfp.mm = MM_TEXT;
		hMeta = SetWinMetaFileBits(len, p, hDC, &mfp);
	}

	::ReleaseDC(0, hDC);

	// Free Memory
	free(p);

	return (hMeta);
}