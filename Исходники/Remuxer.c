int CreateFileOutputW( REMUXER *pRemuxer, wchar_t* pFileName, int nOutputFormat, int nMaxTrackNum)
{
	//pRemuxer->output_file = fopen( pFileName, "wb" );
#ifdef WIN32	
	//pRemuxer->output_file  = FOPEN( pFileName, _O_WRONLY|_O_BINARY|_O_CREAT, _SH_DENYNO , _S_IREAD|_S_IWRITE );
	pRemuxer->output_file = _wsopen( (wchar_t*)pFileName, _O_RDONLY|_O_BINARY, _SH_DENYNO , _S_IREAD|_S_IWRITE );
#else
	pRemuxer->output_file  = open( (char*)pFileName, O_WRONLY|O_CREAT, 0666 );
#endif	

	if ( pRemuxer->output_file )
	{
		SageLog(( _LOG_TRACE, 3, TEXT("Output file %s"), pFileName ));
	} else
		return 0;

	pRemuxer->output_track[0] = CreateTracks(nMaxTrackNum);
	pRemuxer->output_track[0]->track_type = nOutputFormat;
	if ( IS_PS_TYPE( nOutputFormat ) )
	{
		int build_header_in_buffer; //if es block has space to build a PACK+PES
		build_header_in_buffer = SourceIsTSType( pRemuxer->demuxer );
		pRemuxer->ps_builder = CreatePSBuilder( pRemuxer->output_track[0], ES_PACKET_SIZE, build_header_in_buffer );
		pRemuxer->ps_builder->dumper.stream_dumper = (DUMP)PSOutputDataFileDumper;
		pRemuxer->ps_builder->dumper.stream_dumper_context = pRemuxer;
	} else
	if ( IS_TS_TYPE(nOutputFormat) )
	{
		pRemuxer->ts_builder = CreateTSBuilder( pRemuxer->output_track[0], nOutputFormat );
		pRemuxer->ts_builder->dumper.stream_dumper = (DUMP)TSOutputDataFileDumper;
		pRemuxer->ts_builder->dumper.stream_dumper_context = pRemuxer;
	}
	return 1;
}