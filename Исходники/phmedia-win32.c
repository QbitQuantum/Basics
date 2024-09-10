BOOL CALLBACK acmDriverEnumCallback( HACMDRIVERID hadid, DWORD dwInstance, DWORD fdwSupport ){
	MMRESULT mmr;
	HACMDRIVER driver;
	int i;

	ACMDRIVERDETAILS details;
	details.cbStruct = sizeof(ACMDRIVERDETAILS);
	mmr = acmDriverDetails( hadid, &details, 0 );

	mmr = acmDriverOpen( &driver, hadid, 0 );

	for(i = 0; i < details.cFormatTags; i++ ){
	  ACMFORMATTAGDETAILS fmtDetails;
	  ZeroMemory( &fmtDetails, sizeof(fmtDetails) );
	  fmtDetails.cbStruct = sizeof(ACMFORMATTAGDETAILS);
	  fmtDetails.dwFormatTagIndex = i;
	  mmr = acmFormatTagDetails( driver, &fmtDetails, ACM_FORMATTAGDETAILSF_INDEX );
	  if( fdwSupport & ACMDRIVERDETAILS_SUPPORTF_CODEC ) {
		 /* fprintf(stderr, "supported codec: %s\n" ,details.szLongName ); */
	      if( fmtDetails.dwFormatTag == WAVE_FORMAT_MSG723 )
		  {
			  g_g723Drivers = /* 1 */ 0;
/*	!		  fprintf(stderr, "Find Codec  %s\n" ,details.szLongName ); */
#if 0
			  fprintf(stderr, "G723 cFormatTags %i\n" ,details.cFormatTags );
			  fprintf(stderr, "G723 cFilterTags %i\n" ,details.cFilterTags);
#endif
			  return -1;
		  }
	      else if( fmtDetails.dwFormatTag == WAVE_FORMAT_GSM610 )
		  {
			  g_gsmDrivers = 1;
/* !			  fprintf(stderr, "Find Codec  %s\n" ,details.szLongName ); */
			  return -1;
		  }
	  }
	  else
	  {
/* !		  fprintf(stderr, "Unsupported codec: %s\n" ,details.szLongName ); */
	  }
	}
	mmr = acmDriverClose( driver, 0 );
	return -1;
}