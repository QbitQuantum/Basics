	static void
sUnlockMemory(
	HANDLE		hDriver,
	void *		mem,
	PGPSize		numBytes )
{
	PGPMEMLOCKSTRUCT	mls;
	DWORD				dw;
	BOOL				bDIOreturn;

	if ( IsntNull( hDriver ) )
	{
		mls.pMem = mem;
		mls.ulNumBytes = numBytes;
		bDIOreturn = DeviceIoControl(	hDriver, 
										IOCTL_PGPMEMLOCK_UNLOCK_MEMORY, 
										&mls, 
										sizeof( mls ), 
										&mls, 
										sizeof( mls ), 
										&dw, 
										NULL );
		pgpAssertMsg ( bDIOreturn, "DIOC error from page-locking driver" );
		if ( bDIOreturn )
		{
			pgpAssertMsg ( mls.ulError == 0, 
						  "Internal error in page-locking driver" );
		}
	}
	else 
	{
	 	VirtualUnlock ( mem, numBytes );	/* call for good measure*/
	}
}