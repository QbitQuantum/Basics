WORD FAR PASCAL _export	CIFDLLIni (WORD usReqTyp, DWORD ulPrm001, DWORD ulPrm002) 
{
	WORD	usCmpCod;

	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	GlobalCompact (0);

	/////////////////////////////////////////////////////////////////////////
	// If (CIFINIREQ == usReqTyp), check for accelerator key
	/////////////////////////////////////////////////////////////////////////
	if ((CIFSYSINI == usReqTyp) && (!ulPrm002 || !strlen ((LPSTR) ulPrm002))) {
		/////////////////////////////////////////////////////////////////////
		// Check for accelerator key and/or AppKey/UsrKey combo
		/////////////////////////////////////////////////////////////////////
		if (REGDEMKEY == ChkRegKey (CIFGlo.RelKeyArr, CIFGlo.SeqNumArr, &usCmpCod)) {
			switch (usCmpCod) {
				case 0xFFFE:
					MsgDspRes (CIFGlo.hLibIns, 0, IDS_INSMEMERR);
					break;
				case 0xFFFD:
					MsgDspRes (CIFGlo.hLibIns, 0, IDS_DOSMEMERR);
					break;
				default:
					MsgDspRes (CIFGlo.hLibIns, 0, IDS_ACCKEYNON);
			} 
			return ((WORD) -1);
		} 
		/////////////////////////////////////////////////////////////////////
		// Load registration key from physical key [1] or string
		/////////////////////////////////////////////////////////////////////
		if (!usCmpCod) CIFGlo.usRegKey = GetEncKey (CIFGlo.SeqNumArr, 1, &usCmpCod);
 		else CIFGlo.usRegKey = ChkRegKey (CIFGlo.RelKeyArr, CIFGlo.SeqNumArr, &usCmpCod);
	}
	if ((CIFSYSINI == usReqTyp) && ulPrm002 && strlen ((LPSTR) ulPrm002)) {
		CIFGlo.usRegKey = ChkRegKey ((LPSTR) ulPrm002, CIFGlo.SeqNumArr, &usCmpCod);
	}

	/////////////////////////////////////////////////////////////////////////
	// If (0 != usReqTyp), initialize internal structures and DLL's
	/////////////////////////////////////////////////////////////////////////
	if (CIFSUBINI == usReqTyp) {
		AmpDLLIni (usReqTyp, ulPrm001, ulPrm002); 
	}

	/********************************************************************/
	/********************************************************************/
	return (0);

}