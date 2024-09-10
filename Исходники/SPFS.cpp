void 
SPFS::Open(LPCSTR lpszPackFile)
	{
	if( IsOpen() )           
		throw new SPFSException(_T("other pack file is allready opened !"),SPFS_FILE_ALLREADY_OPENED);
	//  check for file existing.
	if( _access(lpszPackFile,0) ) 
		throw new SPFSException(_T("pack file doesn't exists !"),SPFS_FILE_NOT_FOUND);

	// variable for read count.
	DWORD  readCt    = 0L;
	DWORD  errorCode = 0L;
	string errorStr  = _T("");
/*
	// open pack file.
	HANDLE hPackFile = CreateFile(lpszPackFile,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if( hPackFile   == INVALID_HANDLE_VALUE )
		{
		errorCode = SPFS_FILE_CANT_OPEN;
		errorStr  = _T("can't open file !");
		goto throw_error;
		}
*/
	// open pack file.
	HANDLE hPackFile = CreateFile(lpszPackFile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
	if( hPackFile   == INVALID_HANDLE_VALUE )
		{
		errorCode = SPFS_FILE_CANT_OPEN;
		errorStr  = _T("can't open file !");
		goto throw_error;
		}
	// allocate memory for pack header.
	_pHeader = (PACK_HEADER*)malloc(sizeof(PACK_HEADER));
	// check for pack file validation.
	if( !IsValidPackFile(hPackFile,_pHeader) )
		{
		errorCode = SPFS_FILE_UNKNOWN_FORMAT;
		errorStr  = _T("unknown file format !");
		goto throw_error;
		}
	// set file pointer to the FSS offset.
	if( SetFilePointer(hPackFile,_pHeader->fssHeader.offsetFSS,NULL,FILE_CURRENT) != _pHeader->fssHeader.offsetFSS )
		{
		errorCode = SPFS_CANT_SET_FILE_POINTER;
		errorStr  = _T("can't set file pointer to the beginning of FSS !");
		goto throw_error;
		}

	// allocate memory for file name array.
	_pFNArray  = malloc(_pHeader->fssHeader.fnArraySz);
	// allocate memory for file name offsets array.
	_pFNOArray = (DWORD*)malloc(_pHeader->fssHeader.fnoArraySz);
	// allocate memory for file starting offsets array.
	_pFOArray  = (DWORD*)malloc(_pHeader->fssHeader.foArraySz);

	// read file name array from pack file.
	if( !ReadFile(hPackFile,_pFNArray,_pHeader->fssHeader.fnArraySz,&readCt,NULL)  ||
	    _pHeader->fssHeader.fnArraySz != readCt ) 
		{
		errorCode = SPFS_FILE_CANT_READ;
		errorStr  = _T("can't read file name array from pack file !");
		goto throw_error;
		}
	// read file name offsets array from pack file.
	if( !ReadFile(hPackFile,_pFNOArray,_pHeader->fssHeader.fnoArraySz,&readCt,NULL) ||
	    _pHeader->fssHeader.fnoArraySz != readCt ) 
		{
		errorCode = SPFS_FILE_CANT_READ;
		errorStr  = _T("can't read file name offsets array from pack file !");
		goto throw_error;
		}
	// load file name array from pack file.
	if( !ReadFile(hPackFile,_pFOArray,_pHeader->fssHeader.foArraySz,&readCt,NULL)   ||
	    _pHeader->fssHeader.foArraySz != readCt ) 
		{
		errorCode = SPFS_FILE_CANT_READ;
		errorStr  = _T("can't read from pack file !");
		goto throw_error;
		}
	// set file pointer to the beginning of file.
	if( SetFilePointer(hPackFile,0L,NULL,FILE_BEGIN) == (DWORD)-1 )
		{
		errorCode = SPFS_CANT_SET_FILE_POINTER;
		errorStr  = _T("can't set pack file pointer to the beginning of file !");
		goto throw_error;
		}
	// ------------------------------------------
	_hPackFile    = hPackFile;
	_fnArrAlloc   = _pHeader->fssHeader.fnArraySz;
	_fnArrUsed    = _pHeader->fssHeader.fnArraySz;
	_fnoArrAlloc  = _pHeader->fssHeader.fnoArraySz;
	_foArrAlloc   = _pHeader->fssHeader.foArraySz;
	// ------------------------------------------
	return;

throw_error:
	Close();
	throw new SPFSException(errorStr,errorCode);
	}