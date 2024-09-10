bool CDetour::Detour ( BYTE * &jmp, BYTE * &orig, const BYTE * &det, int iPatchType, int len )
{
	DWORD	dwBack = 0;
	int		i = 0;
	BYTE	*pPatchBuf = NULL;

	// Allocate space for the jump
	jmp = (BYTE *)malloc( len + 5 );

	// Force page protection flags to read|write
	MEMORY_BASIC_INFORMATION	mbi;
	VirtualQuery( (void *)orig, &mbi, sizeof(mbi) );
	VirtualProtect( mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &mbi.Protect );

	// Copy the overwritten opcodes at the original to the malloced space
	memcpy( jmp, orig, len );

	// Increment to the end of the opcodes at the malloced space
	jmp += len;

	// Place a jump back to the original at this point
	jmp[0] = 0xE9;
	*( DWORD * ) ( jmp + 1 ) = ( DWORD ) ( orig + len - jmp ) - 5;

	// Generate a random opcode
	int		iTmpRnd = ( rand() * 0xFF ) + rand();
	BYTE	bTmpRnd = ( BYTE ) iTmpRnd;

	// Place a jump at the original to the detour function
	pPatchBuf = new BYTE[len];

	// Pad out the bytes with NOPs so we don't have ends of intructions
	memset( pPatchBuf, 0x90, len );

	// Write the opcodes to the buffer according to patch type
	switch ( iPatchType )
	{
	case DETOUR_TYPE_JMP:
		pPatchBuf[0] = '\xE9';
		*(DWORD *) &pPatchBuf[1] = ( DWORD ) ( det - orig ) - 5;
		break;

	case DETOUR_TYPE_PUSH_RET:
		pPatchBuf[0] = '\x68';
		*(DWORD *) &pPatchBuf[1] = ( DWORD ) det;
		pPatchBuf[5] = '\xC3';
		break;

	case DETOUR_TYPE_PUSH_FUNC:
		pPatchBuf[0] = '\x68';
		*(DWORD *) &pPatchBuf[1] = ( DWORD ) det;
		break;

	case DETOUR_TYPE_CALL_FUNC:
		pPatchBuf[0] = '\xE8';
		*(DWORD *) &pPatchBuf[1] = ( DWORD ) ( det - orig ) - 5;
		break;

	default:
		return false;
	}

	// Write the detour
	for ( i = 0; i < len; i++ )
		orig[i] = pPatchBuf[i];

	// Put the old page protection flags back
	VirtualProtect( mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect );

	FlushInstructionCache( GetCurrentProcess(), orig, len );

	return true;
}