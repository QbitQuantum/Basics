///
/// Disassemble the instruction at the given address, creating an instruction object
///
bool
Disassemble( const DEBUGGER_CONTROLS &objControls, ULONG64 offAddress, ULONG dwProcessor, bool fFlagsRegisterValid, const OPERAND_SET& setProcessorFlags, INSTRUCTION *pInstruction )
{
	// Disassemble the instruction
	ULONG cchInstruction;
	ULONG dwAssemblyOptions;
	HRESULT dwResult;

	// For ARM/THUMB processors, mask off the lowest address bit
	if( (dwProcessor == IMAGE_FILE_MACHINE_ARM) || (dwProcessor == IMAGE_FILE_MACHINE_THUMB) || (dwProcessor == IMAGE_FILE_MACHINE_ARMNT) )
	{
		offAddress = offAddress & ~0x1;
	}

	objControls.pDebugControl->GetAssemblyOptions( &dwAssemblyOptions );
	objControls.pDebugControl->SetAssemblyOptions( dwAssemblyOptions & ~(DEBUG_ASMOPT_NO_CODE_BYTES | DEBUG_ASMOPT_SOURCE_LINE_NUMBER) );
	objControls.pDebugControl->DisassembleWide( offAddress, 0, NULL, 0, &cchInstruction, &pInstruction->offNextInstruction );
	pInstruction->pwzInstructionBuffer = new WCHAR[cchInstruction + 1];

	if( pInstruction->pwzInstructionBuffer == NULL )
	{
		return( false );
	}

	dwResult = objControls.pDebugControl->DisassembleWide( offAddress, 0, (PWSTR) pInstruction->pwzInstructionBuffer, cchInstruction + 1, NULL, &pInstruction->offNextInstruction );
	objControls.pDebugControl->SetAssemblyOptions( dwAssemblyOptions );

	if( dwResult != S_OK )
	{
		return( false );
	}
	else
	{
		pInstruction->offAddress = offAddress;
		_wcslwr_s( (PWSTR) pInstruction->pwzInstructionBuffer, cchInstruction );
	}

	// Check for disassembly errors that would cause infinite loops, this is usually due to a mismatch
	// between the debugger machine mode and the process machine mode (x86 versus x64)
	if( pInstruction->offAddress == pInstruction->offNextInstruction )
	{
		return( false );
	}

	// Check for a mismatch in the disassembly
	if( wcsstr( pInstruction->pwzInstructionBuffer, L"disassembly not possible" ) != NULL )
	{
		return( false );
	}

	// Store the instruction flags information
	pInstruction->fFlagsRegisterValid = fFlagsRegisterValid;

	// Parse the fields for the continued processing
	PWSTR pwzIndex = (PWSTR) pInstruction->pwzInstructionBuffer;
	pInstruction->pwzAddress = (PCWSTR) pwzIndex ;
	ParseDisassemblyFieldInPlace( &pwzIndex, NULL );
	pInstruction->pwzOpCode = (PCWSTR) pwzIndex;
	ParseDisassemblyFieldInPlace( &pwzIndex, NULL );
	pInstruction->pwzMnemonic = (PCWSTR) pwzIndex;

	switch( dwProcessor )
	{
		case IMAGE_FILE_MACHINE_I386:
			{
				ParseDisassemblyFieldInPlace( &pwzIndex, X86_MNEMONIC_PREFIXES );
			}
			break;

		case IMAGE_FILE_MACHINE_AMD64:
			{
				ParseDisassemblyFieldInPlace( &pwzIndex, X64_MNEMONIC_PREFIXES );
			}
			break;

		case IMAGE_FILE_MACHINE_ARM:
		case IMAGE_FILE_MACHINE_THUMB:
		case IMAGE_FILE_MACHINE_ARMNT:
			{
				ParseDisassemblyFieldInPlace( &pwzIndex, ARM_MNEMONIC_PREFIXES );
			}
			break;

		default:
			return( false );
	}
	pInstruction->pwzArguments = (PCWSTR) pwzIndex;
	
	if( pInstruction->pwzArguments != NULL )
	{
		size_t cchArguments = wcslen( pInstruction->pwzArguments );

		if( cchArguments > 0 )
		{
			if( pInstruction->pwzArguments[cchArguments - 1] == '\n' )
			{
				((PWSTR) pInstruction->pwzArguments)[cchArguments - 1] = '\0';
			}
		}
	}

	// Check for invalid op codes or menmonics, that indicate a disassembly failure
	if( *pInstruction->pwzMnemonic == '?' )
	{
		return( false );
	}

	if( *pInstruction->pwzOpCode == '<' )
	{
		return( false );
	}

	// Classify the instruction
	//
	// Note that we don't consider our inability to match an instruction to be an error here, we'll continue with it
	// until we find an error in the actual disassembly routines (above)
	switch( dwProcessor )
	{
		case IMAGE_FILE_MACHINE_I386:
			{
				ClassifyX86Instruction( pInstruction );
				return( true );
			}

		case IMAGE_FILE_MACHINE_AMD64:
			{
				ClassifyX64Instruction( pInstruction );
				return( true );
			}

		case IMAGE_FILE_MACHINE_ARM:
		case IMAGE_FILE_MACHINE_THUMB:
		case IMAGE_FILE_MACHINE_ARMNT:
			{
				ClassifyARMInstruction( pInstruction, setProcessorFlags );
				return( true );
			}

		default:
			return( false );
	}
}