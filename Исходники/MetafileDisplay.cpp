int CMetafileDisplay::LoadBits(UINT uiBuf, LPVOID pBuf)
{
#pragma pack(2)
typedef struct 
{
	DWORD   key;
	WORD	hmf;
	short	left;
	short	top;
	short	right;
	short	bottom;
	WORD    inch;
	DWORD	reserved;
	WORD    checksum;
} AMETAHEADER;
#pragma pack()

	if (enhMF != NULL)
	{
		DeleteEnhMetaFile(enhMF);
		enhMF = NULL;
	}

	// See if this is an enhanced metafile
	ENHMETAHEADER *emhdr = (ENHMETAHEADER *)pBuf;
	if (uiBuf >= sizeof(ENHMETAHEADER)
	 && emhdr->iType == EMR_HEADER
	 && emhdr->dSignature == ENHMETA_SIGNATURE)
	{
		enhMF = SetEnhMetaFileBits(uiBuf, (CONST BYTE *)pBuf);
	}
	else if (uiBuf >= sizeof(METAHEADER))
	{
		METAFILEPICT mp = {MM_ANISOTROPIC, 1000, 1000, NULL};
		AMETAHEADER *ahdr = (AMETAHEADER *)pBuf;
		METAHEADER *mhdr = (METAHEADER *)pBuf;
		// See if this is a placeable metafile
		if (ahdr->key == 0x9AC6CDD7)
		{
			mp.xExt = ((LONG)(ahdr->right - ahdr->left) * 25401) / (LONG)ahdr->inch;
			mp.yExt = ((LONG)(ahdr->bottom - ahdr->top) * 25401) / (LONG)ahdr->inch;
			mhdr = (METAHEADER *) (ahdr + 1);
		}
		UINT uiSizeMF = (UINT) mhdr->mtSize * 2;
		HDC dcRef = ::GetDC(NULL);
		enhMF = SetWinMetaFileBits(uiSizeMF, (LPBYTE)mhdr, dcRef, &mp);
		::ReleaseDC(NULL, dcRef);
	}

	return (enhMF == NULL) ? -1 : 0;
}