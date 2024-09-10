VOID spol_gblk(VOID)
{
	BYTE    handle;

#if GEMDOS
	handle = Fopen( (const char *)spol_path, 0x0000 );
#else
	handle = dos_open( spol_path, 0x0000 );
#endif
	if (handle)
	{
#if GEMDOS
		Fseek( spol_fcnt, handle, 0x0000 );
		spol_cntr = (WORD)Fread( handle, SPLSIZE, (VOID *)spol_pbuf );
#else
		dos_lseek( handle, 0x0000, spol_fcnt );
		spol_cntr = dos_read( handle, SPLSIZE, spol_pbuf );
#endif
		if ( spol_cntr != SPLSIZE )
			spol_sts = TRUE;
		spol_fcnt += LW( spol_cntr );
#if GEMDOS
		Fclose( handle );
#else
		dos_close( handle );
#endif
		spol_ptr = spol_bufr;
	}
	else
	{
		spol_sts = TRUE;
		spol_cntr = 0;
	}
}