//
//	Declaration:
//	bool CBinaryDataFile::ReadEvtHeader(const CString &strNameWithPath, CString *pstrErrorMsg)
//
//	Input:	strNameWithPath		filename with full path that is to be opened
//			
//	Output:	pstrErrorMsg	error, if any
//
//			mdVersionNumber		version number read from header
//			msStaNum			station number read from header
//			miYr				year read from header
//			miMon				month read from header
//			miDay				day read from header
//			mulTimestampOfFirstRecordInFile		julian time of first record in the file
//
//	Return:	true (header read) / false (some kind of error, see pstrErroMsg)
//	
//  date    /	author	revision
//  -----------------	--------
//	17-Oct-2002	SFK		Created from ReadBIDHeader in GrandDataFile.cpp in GRAND COM
//	21-Jun-2005 SFK		Pick up station number from first record rather than getting it
//						out of the header due to a problem in MIC 1.9.0.7
//////////////////////////////////////////////////////////////////
bool CBinaryDataFile::ReadEvtHeader(const CString &strNameWithPath, CString *pstrErrorMsg)
{
    int iHdrSize;
    char str[54];
	struct BinaryEventFileRec Rec;
	struct OpCode OpRec;
	fpos_t pos;
	CMyDateTime MyDate;

   /* ------------------------------------------------------------------
    *	Open the file
    * ----------------------------------------------------------------*/
	if (!OpenDataFile(strNameWithPath, pstrErrorMsg)) return(false);

	// generate an error message in case we get an error in any of the reads,
	// will clear at end of function if all okay
	if (pstrErrorMsg) {
		miErrorNum = iFILE_READ_ERR;
		pstrErrorMsg->Format("\nError: Unexpected error reading header for file %s", strNameWithPath);
	}
	
   /* ------------------------------------------------------------------
    *	Read the first 4 bytes to get the number of bytes in header.
    *	Based on the location of the number, determine whether the data
    *	file is from CDMPC or LANL GRAND Collect.  The CDMPC number
    *	must be decremented by 1.
    * ----------------------------------------------------------------*/
    if (fread(str, 4, 1, mpFile) != 1) return(false);
    str[4] = '\0';    
    iHdrSize = atoi(str);
    if (str[3] == ' ') iHdrSize = iHdrSize - 1; // this file formed by CDMPC
	if (iHdrSize <= 22) return(false);

   /* ------------------------------------------------------------------
    *	The next 5 bytes no longer contain useful information,	just
    *	skip by them.
    * ----------------------------------------------------------------*/
    if (fread(str, 5, 1, mpFile) != 1) return(false);
       
   /* ------------------------------------------------------------------
    *	Read past the version number in the next 5 bytes.
    * ----------------------------------------------------------------*/
    if (fread(str, 5, 1, mpFile) != 1) return(false);
	str[5] = '\0';
	mdVersionNumber = atof(str);

   /* ------------------------------------------------------------------
    *  Read station of logging node and put it in return variable.
    * ----------------------------------------------------------------*/
    if (fread(str, 3, 1, mpFile) != 1) return(false);
    str[3] = '\0';
    msStaNum = atoi(str);
//	msStaNum += 1000;

   /* ------------------------------------------------------------------
    *	Read year and put it in return variable.
    * ----------------------------------------------------------------*/
    if (fread(str, 3, 1, mpFile) != 1) return(false);
    str[3] = '\0';
    miYr = atoi(str);
	//3-aug-2005 hn Added a four digit year.
	if (miYr < 86)
	{
		miYr4 = miYr + 2000;
	}
	else
	{
		miYr4 = miYr + 1900;
	}


   /* ------------------------------------------------------------------
    *	Read month and put it in return variable.
    * ----------------------------------------------------------------*/
    if (fread(str, 3, 1, mpFile) != 1) return(false);
    str[3] = '\0';
    miMon = atoi(str);
	if ((miMon < 1) || (miMon >12)) return(false);

   /* ------------------------------------------------------------------
    *	Read day and put it in return variable.
    * ----------------------------------------------------------------*/
    if (fread(str, 3, 1, mpFile) != 1) return(false);
    str[3] = '\0';
    miDay = atoi(str);
	if ((miDay < 1) || (miDay >31)) return(false);

	/* ------------------------------------------------------------------
    *	Read past the expansion space in the header so the file pointer
    *	is positioned at the beginning of the first data point at exit.
    * ----------------------------------------------------------------*/
    if (fread(str, (iHdrSize - 22), 1, mpFile)!= 1) return(false);
    
   /* ------------------------------------------------------------------
    *	Save the position of the file pointer.
	*	Read the first record in the file to get the time of it.  Will
	*	read the first record as if it is a binary record since we are
	*	only interested in the julian time in the record and that is in
	*	the same position in all types of records in an .evt/.bny file.
    *	Restore file pointer to just at the first record.
    * ----------------------------------------------------------------*/
	if(fgetpos(mpFile, &pos ) != 0) return(false);
	// 01-Sep-2005 SFK Fixed for reading old files that might have other types
	//					of records interspersed with binary records.
	bool bFoundBinaryRecord = false;
	do {
		if (fread(&OpRec, sizeof(struct OpCode), 1, mpFile) == 0) return(false);
		if ((OpRec.RecTypeA == '3') && (OpRec.RecTypeB == '2')) {
			if (fread(&Rec, sizeof(struct BinaryEventFileRec), 1, mpFile) == 0) return(false);
			msStaNum = Rec.usNode;		// 21-Jun-2005 SFK  Pick up station number from first record
			mdTimestampOfFirstRecordInFile = MyDate.MyTimestampToDATETimestamp((double)Rec.uiTime);
			if(fsetpos(mpFile, &pos ) != 0) return(false);
			bFoundBinaryRecord = true;
		}
		else {	// was not a binary record -- skip past the record
			fpos_t FilePosition;
			fgetpos(mpFile, &FilePosition);
			FilePosition += OpRec.sRecSize - 2;	// subtract the opcode bytes that you've already read
			fsetpos(mpFile, &FilePosition);
		}
	} while (!bFoundBinaryRecord);
               
	if (pstrErrorMsg) pstrErrorMsg->Empty();
	miErrorNum = 0;	// no error
    return(true);

}