BOOL JpfsvpSearchSymbolCommand(
	__in PJPFSV_COMMAND_PROCESSOR_STATE ProcessorState,
	__in PCWSTR CommandName,
	__in UINT Argc,
	__in PCWSTR* Argv
	)
{
	SEARCH_SYMBOL_CTX Ctx;
	HANDLE Process = JpfsvGetProcessHandleContext( ProcessorState->Context );

	UNREFERENCED_PARAMETER( CommandName );

	if ( Argc < 1 )
	{
		( ProcessorState->OutputRoutine ) ( L"Usage: x <mask>\n" );
		return FALSE;
	}

	Ctx.OutputRoutine = ProcessorState->OutputRoutine;
	Ctx.ContextHandle = ProcessorState->Context;

	if ( ! SymEnumSymbols(
		Process,
		0,
		Argv[ 0 ],
		JpfsvsOutputSymbol,
		&Ctx ) )
	{
		DWORD Err = GetLastError();
		JpfsvpOutputError( 
			ProcessorState, HRESULT_FROM_WIN32( Err ) );
		return FALSE;
	}

	return TRUE;
}