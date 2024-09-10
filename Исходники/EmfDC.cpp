// main entry for decompiling from a memory buffer
bool KEmfDC::DeCompileBuffer(const TCHAR * outfilename, const void * buffer, KTreeView * pTree, HENHMETAFILE & hEmf)
{
	const EMR * emr = (const EMR *) buffer;
	
	// if not normal EMF file
	while ( ! IsEMFHeader(emr) )
	{
		if ( IsEMFHeader(emr+1) )
		{
			emr ++;

			if ( hEmf==NULL )
				hEmf = SetEnhMetaFileBits(emr[-1].nSize, (const BYTE *) emr);
			
			break;
		}
		else
			emr = (const EMR *) ( ( const char * ) emr + emr->nSize );
	}

	const ENHMETAHEADER * pHeader = (const ENHMETAHEADER *) emr;
	
	if ( pTree==NULL )
	{
		fmt.Open(outfilename);

		HRSRC hRsc = FindResource(hModule, MAKEINTRESOURCE(IDR_PRE), RT_RCDATA);
		
		if ( hRsc )
		{
			HGLOBAL hResData  = LoadResource(hModule, hRsc);
			const char * pPgm = (const char *) LockResource(hResData);

			fmt.Write(pPgm);
		}

		fmt.Indent(1);
		fmt.Newline(); fmt.Write("HGDIOBJ hObj["); fmt.WriteDec((long) pHeader->nHandles); fmt.Write("] = { NULL };");
		fmt.Newline();
	}
	m_nSeq = 1;

	bool bOptimize = false;

	// enumuerate all EMF records
	while ( (emr->iType>=EMR_MIN) && (emr->iType<=EMR_MAX) )
	{
		bool rslt = true;

		if ( bOptimize )
		{
			const EMR * next = (const EMR *) ( ( const char * ) emr + emr->nSize );

			if ( next->iType == emr->iType )
				switch ( emr->iType )
				{
					case EMR_SETWINDOWORGEX:
					case EMR_SETWINDOWEXTEX:
					case EMR_SETVIEWPORTORGEX:
					case EMR_SETVIEWPORTEXTEX:
					case EMR_SETTEXTCOLOR:
					case EMR_SETBKCOLOR:
					case EMR_SETBRUSHORGEX:
					case EMR_SELECTCLIPPATH:
					case EMR_SETTEXTALIGN:
	    
					case EMR_SETBKMODE:
					case EMR_SETARCDIRECTION:
					case EMR_SETPOLYFILLMODE:
					case EMR_SETMAPMODE:
					case EMR_SETSTRETCHBLTMODE:
					case EMR_SETMAPPERFLAGS:
					case EMR_SETICMMODE:
					case EMR_SETROP2:

					case EMR_SETMITERLIMIT:
					case EMR_SETWORLDTRANSFORM:
					case EMR_MOVETOEX:
						fmt.Write("/* */");
						break;
				
					default:
						rslt = Decode(emr, pTree);
				}
			else 
				rslt = Decode(emr, pTree);
		}
		else
			rslt = Decode(emr, pTree);
		
		if (! rslt ) 
			break;

		if ( emr->iType== EMR_EOF )
			break;

		emr = (const EMR *) ( ( const char * ) emr + emr->nSize );
	}
	
	if ( pTree==NULL )
	{
		fmt.Indent(-1);

		HRSRC hRsc = FindResource(hModule, MAKEINTRESOURCE(IDR_POST), RT_RCDATA);
		
		if ( hRsc )
		{
			HGLOBAL hResData  = LoadResource(hModule, hRsc);
			const char * pPgm = (const char *) LockResource(hResData);

			fmt.Write(pPgm);
		}

		fmt.Close();
	}
	
	return true;
}