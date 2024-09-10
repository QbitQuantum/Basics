int main ( int argc, char ** argv )
{
	if ( argc==2 )
		COMMIT_STEP = atoi ( argv[1] );

	// threads should be initialized before memory allocations
	char cTopOfMainStack;
	sphThreadInit();
	MemorizeStack ( &cTopOfMainStack );

	CSphString sError;
	CSphDictSettings tDictSettings;
	tDictSettings.m_bWordDict = false;

	ISphTokenizer * pTok = sphCreateUTF8Tokenizer();
	CSphDict * pDict = sphCreateDictionaryCRC ( tDictSettings, NULL, pTok, "rt1", sError );
	CSphSource_MySQL * pSrc = SpawnSource ( "SELECT id, channel_id, UNIX_TIMESTAMP(published) published, "
		"title, UNCOMPRESS(content) content FROM posting WHERE id<=10000 AND id%2=0", pTok, pDict );

	ISphTokenizer * pTok2 = sphCreateUTF8Tokenizer();
	CSphDict * pDict2 = sphCreateDictionaryCRC ( tDictSettings, NULL, pTok, "rt2", sError );
	CSphSource_MySQL * pSrc2 = SpawnSource ( "SELECT id, channel_id, UNIX_TIMESTAMP(published) published, "
		"title, UNCOMPRESS(content) content FROM posting WHERE id<=10000 AND id%2=1", pTok2, pDict2 );

	CSphSchema tSrcSchema;
	if ( !pSrc->UpdateSchema ( &tSrcSchema, sError ) )
		sphDie ( "update-schema failed: %s", sError.cstr() );

	CSphSchema tSchema; // source schema must be all dynamic attrs; but index ones must be static
	tSchema.m_dFields = tSrcSchema.m_dFields;
	for ( int i=0; i<tSrcSchema.GetAttrsCount(); i++ )
		tSchema.AddAttr ( tSrcSchema.GetAttr(i), false );
	g_iFieldsCount = tSrcSchema.m_dFields.GetLength();

	CSphConfigSection tRTConfig;
	sphRTInit ( tRTConfig, true );
	sphRTConfigure ( tRTConfig, true );
	SmallStringHash_T< CSphIndex * > dTemp;
	sphReplayBinlog ( dTemp, 0 );
	ISphRtIndex * pIndex = sphCreateIndexRT ( tSchema, "testrt", 32*1024*1024, "data/dump", false );
	pIndex->SetTokenizer ( pTok ); // index will own this pair from now on
	pIndex->SetDictionary ( pDict );
	if ( !pIndex->Prealloc ( false ) )
		sphDie ( "prealloc failed: %s", pIndex->GetLastError().cstr() );
	pIndex->PostSetup();
	g_pIndex = pIndex;

	// initial indexing
	int64_t tmStart = sphMicroTimer();

	SphThread_t t1, t2;
	sphThreadCreate ( &t1, IndexingThread, pSrc );
	sphThreadCreate ( &t2, IndexingThread, pSrc2 );
	sphThreadJoin ( &t1 );
	sphThreadJoin ( &t2 );

#if 0
	// update
	tParams.m_sQuery = "SELECT id, channel_id, UNIX_TIMESTAMP(published) published, title, "
		"UNCOMPRESS(content) content FROM rt2 WHERE id<=10000";
	SetupIndexing ( pSrc, tParams );
	DoIndexing ( pSrc, pIndex );
#endif

	// search
	DoSearch ( pIndex );

	// shutdown index (should cause dump)
	int64_t tmShutdown = sphMicroTimer();

#if SPH_ALLOCS_PROFILER
	printf ( "pre-shutdown allocs=%d, bytes=" INT64_FMT "\n", sphAllocsCount(), sphAllocBytes() );
#endif
	SafeDelete ( pIndex );
#if SPH_ALLOCS_PROFILER
	printf ( "post-shutdown allocs=%d, bytes=" INT64_FMT "\n", sphAllocsCount(), sphAllocBytes() );
#endif

	int64_t tmEnd = sphMicroTimer();
	printf ( "shutdown done in %d.%03d sec\n", (int)((tmEnd-tmShutdown)/1000000), (int)(((tmEnd-tmShutdown)%1000000)/1000) );
	printf ( "total with shutdown %d.%03d sec, %.2f MB/sec\n",
		(int)((tmEnd-tmStart)/1000000), (int)(((tmEnd-tmStart)%1000000)/1000),
		g_fTotalMB*1000000.0f/(tmEnd-tmStart) );

#if SPH_DEBUG_LEAKS || SPH_ALLOCS_PROFILER
	sphAllocsStats();
#endif
#if USE_WINDOWS
	PROCESS_MEMORY_COUNTERS pmc;
	HANDLE hProcess = OpenProcess ( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId() );
	if ( hProcess && GetProcessMemoryInfo ( hProcess, &pmc, sizeof(pmc)) )
	{
		printf ( "--- peak-wss=%d, peak-pagefile=%d\n", (int)pmc.PeakWorkingSetSize, (int)pmc.PeakPagefileUsage );
	}
#endif

	SafeDelete ( pIndex );
	sphRTDone ();
}