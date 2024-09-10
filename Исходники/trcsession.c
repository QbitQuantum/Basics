static VOID TestTraceNotepad()
{
	PROCESS_INFORMATION pi;
	JPFSV_HANDLE NpCtx;
	PROC_SET Set;
	DWORD_PTR FailedProc;
	UINT Tracepoints, Count;
	UINT EnumCount = 0;
	JPFSV_TRACEPOINT Tracepnt;

	TEST_OK( CdiagCreateSession( NULL, NULL, &DiagSession ) );

	//
	// Launch notepad.
	//
	LaunchNotepad( &pi );

	//
	// Give notepad some time to start...
	//
	Sleep( 1000 );

	//
	// Start a trace.
	//
	TEST_OK( JpfsvLoadContext( pi.dwProcessId, NULL, &NpCtx ) );
	TEST( JPFSV_E_NO_TRACESESSION == JpfsvGetTracepointContext( NpCtx, 0xF00, &Tracepnt ) );

	TEST_OK( JpfsvAttachContext( NpCtx, JpfsvTracingTypeDefault, NULL ) );

	//
	// Instrument some procedures.
	//
	Set.Count = 0;
	Set.ContextHandle = NpCtx;
	Set.Process = JpfsvGetProcessHandleContext( NpCtx );
	TEST( Set.Process );

	TEST( SymEnumSymbols(
		Set.Process,
		0,
		L"user32!*",
		AddProcedureSymCallback,
		&Set ) );

	TEST_OK( JpfsvStartTraceContext(
		NpCtx,
		5,
		1024,
		DiagSession ) );
	TEST( E_UNEXPECTED == JpfsvStartTraceContext(
		NpCtx,
		5,
		1024,
		DiagSession ) );

	TEST( Set.Count > 0 );

	TEST_OK( JpfsvCountTracePointsContext( NpCtx, &Count ) );
	TEST( 0 == Count );

	TEST_OK( JpfsvSetTracePointsContext(
		NpCtx,
		JpfsvAddTracepoint,
		Set.Count,
		Set.Procedures,
		&FailedProc ) );
	// again - should be a noop.
	TEST_OK( JpfsvSetTracePointsContext(
		NpCtx,
		JpfsvAddTracepoint,
		Set.Count,
		Set.Procedures,
		&FailedProc ) );
	TEST( FailedProc == 0 );

	TEST_OK( JpfsvCountTracePointsContext( NpCtx, &Tracepoints ) );
	TEST( Tracepoints > Set.Count / 2 );	// Duplicate-cleaned!
	TEST( Tracepoints <= Set.Count );

	TEST_OK( JpfsvGetTracepointContext( NpCtx, Set.Procedures[ 0 ], &Tracepnt ) );
	TEST( Tracepnt.Procedure == Set.Procedures[ 0 ] );
	TEST( wcslen( Tracepnt.SymbolName ) );
	TEST( wcslen( Tracepnt.ModuleName ) );

	TEST( JPFSV_E_TRACEPOINT_NOT_FOUND == JpfsvGetTracepointContext( NpCtx, 0xBA2, &Tracepnt ) );

	//
	// Count enum callbacks.
	//
	TEST_OK( JpfsvEnumTracePointsContext(
		NpCtx,
		CountTracepointsCallback,
		&EnumCount ) );
	TEST( EnumCount == Tracepoints );

	//
	// Pump a little...
	//
	Sleep( 2000 );

	//
	// Stop while tracing active -> implicitly revoke all tracepoints.
	//
	TEST_OK( JpfsvStopTraceContext( NpCtx, TRUE ) );
	TEST_OK( JpfsvCountTracePointsContext( NpCtx, &Count ) );
	TEST( 0 == Count );

	//
	// Trace again.
	//
	TEST_OK( JpfsvStartTraceContext(
		NpCtx,
		5,
		1024,
		DiagSession ) );
	TEST_OK( JpfsvSetTracePointsContext(
		NpCtx,
		JpfsvAddTracepoint,
		Set.Count,
		Set.Procedures,
		&FailedProc ) );
	TEST( FailedProc == 0 );

	TEST_OK( JpfsvCountTracePointsContext( NpCtx, &Count ) );
	TEST( Tracepoints == Count );

	//
	// Pump a little...
	//
	Sleep( 2000 );

	//
	// Clean shutdown.
	//
	TEST_OK( JpfsvSetTracePointsContext(
		NpCtx,
		JpfsvRemoveTracepoint,
		Set.Count,
		Set.Procedures,
		&FailedProc ) );
	TEST( FailedProc == 0 );

	TEST_OK( JpfsvCountTracePointsContext( NpCtx, &Count ) );
	TEST( 0 == Count );

	TEST_OK( JpfsvStopTraceContext( NpCtx, TRUE ) );
	TEST_OK( DetachContextSafe( NpCtx ) );
	TEST_OK( JpfsvUnloadContext( NpCtx ) );

	TEST_OK( CdiagDereferenceSession( DiagSession ) );

	//
	// Kill notepad.
	//
	TEST( TerminateProcess( pi.hProcess, 0 ) );
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	//
	// Wait i.o. not to confuse further tests with dying process.
	//
	Sleep( 1000 );
}