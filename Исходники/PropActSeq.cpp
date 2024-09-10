void PropertySequence_cmd_Save (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(PropertySequence_cmd_Save);

	if (NULL != lpArgs[0]) // als Funktion gerufen
		ebSetBool (lpArgs, 0, 0);		// für alle Fälle

WPropertyActionSequence ISeq ((IPropertyActionSequence *)ebGetObject (lpArgs, 1));
HRESULT hr = E_FAIL;

// Versuchen aus SubStream einzulesen
	try {
	// SubStorage eröffnen/erzeugen
	WStorage IStg;

		hr = GetSubPropSeqStorage (IStg.ppi(), true);
		if (FAILED(hr)) _com_issue_error(hr);

	// Description geben lassen
	char cbBuffer[_MAX_PATH];

		hr = ISeq -> GetDescription (cbBuffer, _MAX_PATH, NULL);
		if (FAILED(hr)) _com_issue_error(hr);

	WStream IStm;
	WPersistStream IPersistStm (ISeq);		// throw hr
	string strName = MakeStreamName(cbBuffer);

	// Stream erzeugen
		USES_CONVERSION;
		hr = IStg -> CreateStream (A2OLE(strName.c_str()), 
						STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE, 
						0L, 0L, IStm.ppi());
		if (FAILED(hr)) _com_issue_error(hr);
		
		hr = OleSaveToStream (IPersistStm, IStm);
		if (FAILED(hr)) _com_issue_error(hr);
			
		hr = IStg -> Commit (STGC_DEFAULT);
		if (FAILED(hr)) _com_issue_error(hr);
		
		DEX_SetDirtyGeoDB(true);

	} catch (...) {
		TRACE("Couldn't OleSaveToStream for IPropertyActionSequence\n");
		return;			// Fehler
	}

	if (NULL != lpArgs[0]) // als Funktion gerufen
		ebSetBool (lpArgs, 0, -1);
}