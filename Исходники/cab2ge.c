BOOL STDCALL gcabe_flushfolder( HFCI hfci )
{
   if ( !FCIFlushFolder( hfci, get_next_cabinet, progress ))
	{
      FCIDestroy( hfci );
		return FALSE;
	}
   return TRUE;
}