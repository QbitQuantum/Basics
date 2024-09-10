VOID FAR OutputTyplib
(
  CHAR * szTypeLibFile
)
{
    HRESULT res;
    ICreateTypeLib FAR * lpdtlib;
#ifndef MAC
    CHAR szTypeLibFileTmp[128];
#endif //!MAC
    WORD wLibFlags;

    fDoingOutput = TRUE;		// signal to error reporting code
    SETITEMCUR(typlib.szLibName);

#ifndef MAC
    // pre-pend ".\" to filename if unqualified name, to work-around OLE path
    // searching bug.

    if (!XStrChr(szTypeLibFile, '\\') && !XStrChr(szTypeLibFile, '/') &&
	 *(szTypeLibFile+1) != ':')
	{	// if unqualified name
	   strcpy(szTypeLibFileTmp, ".\\");
	   strcpy(szTypeLibFileTmp+2, szTypeLibFile);
	   // this name is used later -- don't free it
	   //free(szTypeLibFile);
	   szTypeLibFile = szTypeLibFileTmp;
	}

#endif

    // 1. Get * to ICreateTypeLib interface
    CHECKRESULT(CreateTypeLib(SysKind, ToW(szTypeLibFile), &lpdtlib));

    // WARNING: SetLCID must be called before the anything in the nammgr is used
    // it needs to be called even if the user doesn't specifiy an lcid
    // (in which case we default to an lcid of 0).
    CHECKRESULT(lpdtlib->SetLcid(
       (typlib.attr.fAttr & fLCID) ? typlib.attr.lLcid : 0
	));

    // 2. Set the library name:
    CHECKRESULT(lpdtlib->SetName(ToW(typlib.szLibName)));
    
    // 3. Set the library attributes, if present:
    if (typlib.attr.fAttr & fHELPSTRING)
	CHECKRESULT(lpdtlib->SetDocString(ToW(typlib.attr.lpszHelpString)));

    if (typlib.attr.fAttr & fHELPCONTEXT)
	CHECKRESULT(lpdtlib->SetHelpContext(typlib.attr.lHelpContext));

    if (typlib.attr.fAttr & fHELPFILE)
	CHECKRESULT(lpdtlib->SetHelpFileName(ToW(typlib.attr.lpszHelpFile)));

    if (typlib.attr.fAttr & fVERSION)
	CHECKRESULT(lpdtlib->SetVersion(typlib.attr.wVerMajor, typlib.attr.wVerMinor));

    if (typlib.attr.fAttr & fUUID)
	CHECKRESULT(lpdtlib->SetGuid(*typlib.attr.lpUuid));

    wLibFlags = 0;
    if (typlib.attr.fAttr & fRESTRICTED)
        wLibFlags |= LIBFLAG_FRESTRICTED;
    if (typlib.attr.fAttr2 & f2CONTROL)
        wLibFlags |= LIBFLAG_FCONTROL;
    if (typlib.attr.fAttr & fHIDDEN)
        wLibFlags |= LIBFLAG_FHIDDEN;
    CHECKRESULT(lpdtlib->SetLibFlags(wLibFlags));

    // 4. Output all the typinfo's into the type library
    if (typlib.pEntry)			// if any entries
        OutputTypeInfos(lpdtlib);

    // 5. Save the typlib to the give file
    SETITEMCUR(typlib.szLibName);

    CHECKRESULT(lpdtlib->SaveAllChanges());

    // 6. Cleanup.  All done -- release release the ICreateTypeLib.
    lpdtlib->Release();		// release the ICreateTypeLib

}