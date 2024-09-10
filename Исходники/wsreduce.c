VOID
wsRedInitModules()
{
	wsrmod_t 	*pWsrMod;					// Pointer to wsrmod struct
	wsphdr_t 	WspHdr;						// WSP file header
					// Module path name
	static CHAR szModPath[CCHMAXPATHCOMP] = "";
	UINT		uiMod = 0;					// Index of module into WsrMod[]
	UINT		cFxns = 0;					// Number of functions for this module
	ULONG		ulTimeStamp = 0;			// Time stamp
	CHAR		szFileTmp[CCHMAXPATHCOMP]; 	// Temporary file name
	ULONG		ulTDFID = 0;				// TDF Identifier
	wsphdr_t    wsHDR;


	for (uiMod = 0; uiMod < cModsTot; uiMod++)
	{
		pWsrMod = &WsrMod[uiMod];

		/* Open module's input WSP file.  Read and validate
		 * WSP file header.
		 */


		rc = WsWSPOpen(pWsrMod->wsrmod_un.wsrmod_pchModFile,
				&(pWsrMod->wsrmod_hFileWSP), (PFN) wsRedExit,
				&WspHdr, ERROR);

		strcpy(szFileTMI, pWsrMod->wsrmod_un.wsrmod_pchModFile);
		_strupr(szFileTMI);
		strcpy(strstr(szFileTMI,".WSP"),".TMI");


		if (ulTimeStamp == 0)
		{
			/* Time stamp and number of snapshots do not
			 * vary across modules, so grab them from
			 * the first module's WSP header.
			 */
			ulTimeStamp = WspHdr.wsphdr_ulTimeStamp;
			cSnapsTot = WspHdr.wsphdr_ulSnaps;
			cbBitStr = cSnapsTot * sizeof(ULONG);
		}
		else
		if (WspHdr.wsphdr_ulTimeStamp != ulTimeStamp)
			wsRedExit(ERROR, PRINT_MSG, MSG_FILE_BAD_HDR, (ULONG)-1L,
					pWsrMod->wsrmod_un.wsrmod_pchModFile);

		/* Keep module name in memory. */
		if ((pWsrMod->wsrmod_un.wsrmod_pchModName =
			_strdup(szModPath)) == NULL)
			wsRedExit(ERROR, PRINT_MSG, MSG_NO_MEM,
					WspHdr.wsphdr_dtqo.dtqo_cbPathname,
					szModPath);

		/* Keep track of module's first function slot. */
		pWsrMod->wsrmod_ulFxn = cFxnsTot;
		pWsrMod->wsrmod_ulOffWSP = WspHdr.wsphdr_ulOffBits;

		/*
		 * Open associated TMI file.  Assume it lives in WSDIR.
		 * Read and validate TMI header. Increment cFxnsTot.
		 */
		fseek(pWsrMod->wsrmod_hFileWSP,0L,SEEK_SET);
		fread(&wsHDR,sizeof(wsphdr_t),1,pWsrMod->wsrmod_hFileWSP);
		fseek(pWsrMod->wsrmod_hFileWSP,sizeof(wsphdr_t),SEEK_SET);
		fread(szFileTmp,wsHDR.wsphdr_dtqo.dtqo_cbPathname,1, pWsrMod->wsrmod_hFileWSP);
		szFileTmp[wsHDR.wsphdr_dtqo.dtqo_cbPathname] = '\0';

		szFileTMI[0] = '\0';
		strcat(szFileTMI,szFileTmp);
		strcat(szFileTMI, ".TMI");

		cTmiFxns = WsTMIOpen(szFileTMI, &(pWsrMod->wsrmod_hFileTMI),
					(PFN) wsRedExit,
					0, (PCHAR)0);
		cFxns = WspHdr.wsphdr_dtqo.dtqo_SymCnt;




#ifdef DEBUG
	printf("%s file header: # fxns = %ld, TDF ID = 0x%x\n", szFileTMI,
			cFxns, (UINT) WspHdr.wsphdr_dtqo.dtqo_usID);
#endif /* DEBUG */

		pWsrMod->wsrmod_clFxns = cFxns;
		cFxnsTot += cFxns;


	}	/* End For */

	// If no function data to analyze, just exit without error.
	if (cFxnsTot == 0)
		wsRedExit(NO_ERROR, NO_MSG, NO_MSG, 0, NULL);
}