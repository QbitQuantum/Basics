	char *pPRI;
	size_t lenPRI;
	uchar *pTimeStamp;
	uchar *pHOSTNAME;
	size_t lenHOSTNAME;
	uchar *pTAG;
	int lenTAG;
	uchar *pMSG;
	size_t lenMSG;
	size_t lenTotal;
CODESTARTstrgen
	/* first obtain all strings and their length (if not fixed) */
	pPRI = getPRI(pMsg);
	lenPRI = strlen(pPRI);
	pTimeStamp = (uchar*) getTimeReported(pMsg, tplFmtRFC3164Date, NULL);
	pHOSTNAME = (uchar*) getHOSTNAME(pMsg);
	lenHOSTNAME = getHOSTNAMELen(pMsg);
	getTAG(pMsg, &pTAG, &lenTAG);
	if(lenTAG > 32)
		lenTAG = 32; /* for forwarding, a max of 32 chars is permitted (RFC!) */
	pMSG = getMSG(pMsg);
	lenMSG = getMSGLen(pMsg);

	/* calculate len, constants for spaces and similar fixed strings */
	lenTotal = 1 + lenPRI + 1 + CONST_LEN_TIMESTAMP_3164 + 1 + lenHOSTNAME + 1 + lenTAG + lenMSG + 1;
	if(pMSG[0] != ' ')
		++lenTotal; /* then we need to introduce one additional space */

	/* now make sure buffer is large enough */
	if(lenTotal  >= iparam->lenBuf)
		CHKiRet(ExtendBuf(iparam, lenTotal));