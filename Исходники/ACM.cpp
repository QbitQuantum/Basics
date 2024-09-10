/// <summary>
/// <c>wACMStreamUnprepareHeader</c> 
/// </summary>
/// <remarks>
/// </remarks>
/// <param name="has"></param>
/// <param name="pash"></param>
/// <param name="fdwUnprepare"></param>
/// <returns>HRESULT __stdcall</returns>
HRESULT __stdcall 
wACMStreamUnprepareHeader(HACMSTREAM has, PACMSTREAMHEADER pash, ULONG fdwUnprepare)
{
	PSTR		pszErrorMessage;
	MMRESULT	hResult;

	InternalFunctionSpew("GameOS_DirectSound", "acmStreamUnprepareHeader(0x%x, 0x%x, 0x%x)", has, pash, fdwUnprepare);
	hResult = acmStreamUnprepareHeader(has, pash, fdwUnprepare);
	if (MMFAILED(hResult))
	{
		pszErrorMessage = ErrorNumberToMessage(hResult);
		//PAUSE(
		if ( InternalFunctionPause(
			"FAILED (0x%x - %s) - acmStreamUnprepareHeader(0x%x, 0x%x, 0x%x)",
			hResult,
			pszErrorMessage,
			has,
			pash,
			fdwUnprepare) )
			ENTER_DEBUGGER;
	}
	return hResult;
}