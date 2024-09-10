bool CGrandDataFile::ReadDataFile(CDbVista* pDb, const CString &strNameWithPath, CString *pstrMsg)
{

	static float fLastGoodGamma1 = 0.0;	// 11-Aug-2005 SFK best guess to substitute
	static float fLastGoodGamma2 = 0.0;	// 11-Aug-2005 SFK best guess to substitute
	static float fLastGoodGamma1Unc = 0.0;	// 11-Aug-2005 SFK best guess to substitute
	static float fLastGoodGamma2Unc = 0.0;	// 11-Aug-2005 SFK best guess to substitute

    struct db_float_data_rec	dbFloatData;  /* database record structure */
	struct db_day_rec	dbDay;   /* database record structure */ 
    struct GRAND_DATA_PT GrandPt;

    int i;
    DATE dFirstTimeInDay, dLastTimeInDay, dFirstTimeInFile;
    unsigned long ulPtsInDaySoFar; /* how many data pts in day so far */
    unsigned long ulPtsInDay;	    /* how many data pts in entire day */
    DATE dPrevTime;
    int iInvalidData;	    		/* number of records not belonging in the day */
    int iOutOfOrder;
    int iGamAdjust;
    char szDateStr[MAX_DT_LEN+1], szFirst[MAX_DT_LEN+1], szLast[MAX_DT_LEN+1];
	char szTempDate[MAX_DT_LEN+1], szTempTime[MAX_DT_LEN+1];
	bool bFirstPoint = true;
	bool bDayAlreadyExists = false;
	bool bOverwrote = false;
	CString TempStr;	
	DATE  dCurrentPtJulianTime = -1;
	//CMyDateTime DateCvt;
	double dMilliSecs;

	//SCR00227
	//Use CheckSignatureEx() because the return is testable.
	m_lFileOffset = 0;
	m_lUsableFileLength = 0;
	m_bIsSignedFile = false;
	m_lUsableBytesReadIn = 0;

	unsigned char *publicKey, *signatureTimestamp; //not used
	const char *inputFileName = LPCTSTR(strNameWithPath);

	int iRetval = CheckSignatureEx (inputFileName, &m_lFileOffset, &m_lUsableFileLength,  
				&publicKey, &signatureTimestamp );

	/*char* temp = new char[100];
	sprintf (temp,"check signature returns offset of %i from check signature",m_lFileOffset);
	MessageBox (NULL, temp, "heather's debug message", MB_OK|MB_ICONWARNING);
	delete [] temp;*/
	// iRetval interpretation (From Cesare's InLineVerifier.c file)
	//0 = Successfully verified
	//1 = File is CORRUPTED - signature is invalid
	//3 = Verified OK, but CA authority is unknown
	//-14 = Input file has no S/MIME format
	// All others are failures.
	switch(iRetval)
	{
	case 0:
		{
			//Signature is valid
			m_bIsSignedFile = true;
			break;
		}
	case 3:
		{
			//Signature CA unknown
			if (pstrMsg)
			{
				pstrMsg->Format("\nCode %d Warning: Signed file %s has an unknown CA.",
					iRetval,
					m_Dir.StripPathFromFilename(strNameWithPath));
			}
			m_bIsSignedFile = true;
			break;
		}
	case -1:
		{
			if (pstrMsg)
			{
				pstrMsg->Format("\nCode %d Warning: CheckSignature library returned out of memory error for file %s.",
					iRetval,
					m_Dir.StripPathFromFilename(strNameWithPath));
			}
			//Library out of memory error, try to continue
			m_bIsSignedFile = true;
			break;
		}
	case 1:
		{
			//Invalid signature, try anyway.
			if (pstrMsg)
			{
				pstrMsg->Format("\nCode %d Warning: Signed file %s has invalid signature.",
					iRetval,
					m_Dir.StripPathFromFilename(strNameWithPath));
			}

			m_bIsSignedFile = true;
			break;
		}
	case -10:
		{
			//Input file does not exist
			if (pstrMsg)
			{
				pstrMsg->Format("\nCode %d Error: File %s does not exist.",
					iRetval,
					m_Dir.StripPathFromFilename(strNameWithPath));
			}
			m_bIsSignedFile = false;
			return false;
		}
	case -11:
		{
			//Input file empty
			if (pstrMsg)
			{
				pstrMsg->Format("\nCode %d Error: File %s is empty.",
					iRetval,
					m_Dir.StripPathFromFilename(strNameWithPath));
			}
			m_bIsSignedFile = false;
			return false;
		}
	case -12:
		{
			//IO Error
			if (pstrMsg)
			{
				pstrMsg->Format("\nCode %d Error: IO error reading file %s.",
					iRetval,
					m_Dir.StripPathFromFilename(strNameWithPath));
			}
			m_bIsSignedFile = false;
			return false;
		}
	case -14:
		{
			//There is no signature on this file
			//Treat as normal
			m_bIsSignedFile = false;
			break;
		}
	default:
		{
			//This file is no good...and we don't know why.
			if (pstrMsg)
			{
				pstrMsg->Format("\nCode %d Error: Signed file %s failed signature check.",
					iRetval,
					m_Dir.StripPathFromFilename(strNameWithPath));
			}
			return false;
		}
	}

   /* ------------------------------------------------------------------
    *	Read header information
    * ----------------------------------------------------------------*/
	if (!ReadHeader(strNameWithPath, pstrMsg)) 
	{
		//MessageBox (NULL, "could not read header", "heather's debug message", MB_OK|MB_ICONWARNING);
		if (mpFile) 
			CloseDataFile();

		return(false);
	}

   /* ------------------------------------------------------------------
    *	During read of header, got the station number.  Verify from the
	*	Facility Configuration Com that this is a valid station number and
	*	is a GRAND type.
	*	First verify that a database framework exists for this facility
    * ----------------------------------------------------------------*/
	if (pDb->mbDatabaseCleared) 	// no framework yet
	{
		pDb->BuildDatabaseFramework(pDb->msFacNum);
		pDb->mbDatabaseCleared = false;
	}

	struct db_sta_rec dbSta;
	bool bExists = m_pFacCfg->GetStationRecord(pDb->msFacNum, msStaNum, &dbSta);
	if (!bExists) 
	{
		if (pstrMsg) pstrMsg->Format("\nError: Skipping file %s with unknown station",m_Dir.StripPathFromFilename(strNameWithPath));
		return(false);
	}
	if (dbSta.s_sta_type != GRAND_TYPE) 
	{
		if (pstrMsg) pstrMsg->Format("\nError: Skipping file %s with unexpected station type %d",m_Dir.StripPathFromFilename(strNameWithPath), dbSta.s_sta_type);
		return(false);
	}
	CString strStationName = dbSta.sz_sta_name;
	CGrandData GInst(pDb, msStaNum, false, m_bQuietMode);

	// 02-Mar-2005 SFK Make sure this station is in the database framework		
	pDb->AddStationToDatabaseFramework(pDb->msFacNum, msStaNum);
	//MessageBox (NULL, "added station in db", "heather's debug message", MB_OK|MB_ICONWARNING);
	// By the time get here, know we have GRAND data and a valid station number
   /* ------------------------------------------------------------------
    *	This routine tries to eliminate bad data from the GRAND from
    *	getting into the database and corrupting it.  If the GRAND
    *	problem is ever found and fixed this can be removed.
    *	Check the size of the file, if it is 109 bytes long, it is
    *	probably a bad data file and should not be imported.  If the
    *	user responds within a certain time, allow him to decide whether
    *	or not to import the data.  The default is to end the import
    *	process for this file.
    
    *	FIX for timeouts***************************************
    * ----------------------------------------------------------------*/
	m_lFileLength = _filelength(fileno(mpFile));  //SCR00227

    if (m_lFileLength == 109) 
	{
		if (pstrMsg) 
		{
			pstrMsg->Format("Error: \nSkipping file %s (date=%02d.%02d.%02d): bad data size of 109", 
				mstrFilenameWithPath, miYr, miMon, miDay);
		}
		if (mpFile) 
			CloseDataFile();

		miErrorNum = iSKIP_FILE;
		return(false);
	}    

   /* ------------------------------------------------------------------
    *	Determine the limits of julian times that belong in this day
    * ----------------------------------------------------------------*/
    sprintf(szDateStr,"%02d.%02d.%02d", miYr, miMon, miDay); 
	DATE dDayStart = m_MyDateTime.DateTimeStrsToDATETimestamp(szDateStr, "00:00:00");
	DATE dFirstTimeInNextDay = dDayStart + 1;
       
   /* ------------------------------------------------------------------
    *	Check if record for this day already exists in database
    * -----------------------------------------------------------------*/
	DB_D_INTERVAL DayInFile;
	ulPtsInDaySoFar = 0;
	bOverwrote = false;

	int iStatus = GInst.DayExists(dDayStart, &ulPtsInDaySoFar, &DayInFile);

	if (iStatus == iDB_BAD) 
	{
		miErrorNum = iStatus;
		if (mpFile) CloseDataFile();
		return(false);
	}
	dbDay.d_day_beg_time_key = DayInFile.dStart;
	dbDay.d_day_end_time = 0;
                                                          
   /* ------------------------------------------------------------------
    *	If data already in database, either automatically overwrite the 
    *	data or ask the user if they want to overwrite.
    * ----------------------------------------------------------------*/
    if (iStatus == iDAY_IN_DB)   // day exists in db
	{
		// check to see if can just add to the existing day; this is allowed

		if (mdTimestampOfFirstRecordInFile > DayInFile.dEnd)  // will add to end of day
		{
			bDayAlreadyExists = true;
		}
		else
		{
			//Determine if we are going to overwrite the existing day's data or not.  
			//If not, say so and exit.
			//If so, do it.

			//The only time we have to ask 
			//the user if he really wants to overwrite the existing data
			//is when the quiet mode is OFF (i.e. we are allowed to ask) and the
			//input command says to overwrite (mbOverwrite is true).

			//Otherwise, we just do what the input command says.  Therefore, initialize the
			//local boolean to do waht the input command says.
			bool local_overwrite_flag = mbOverwrite;

			//Was "NOT FOR NDAR".  REINSERTED 11/26/2007 PJM
			//Now determine if we need to ask
			if (!m_bQuietMode && mbOverwrite)  //this is the only case in which we need to ask
			{
				//..so ask using a message box
        		TempStr.Format(
					"File %s contains data from %s which already exists in database.  Do you want to overwrite the day?",
					mstrFilenameWithPath, szDateStr);

				if (MessageBox(NULL, TempStr, "GrandCom: Day Already In Database", MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2) == IDNO) 
					local_overwrite_flag = false;
				else
					local_overwrite_flag = true;
			}
			
			if (!local_overwrite_flag)  //Don't overwrite. Just say we are not, clean up, and bail.
			{
				if (pstrMsg)
				{
					pstrMsg->Format("\nSkipping file %s (date=%02d.%02d.%02d): day's data already in database", 
							mstrFilenameWithPath, miYr, miMon, miDay);
				}

				if (mpFile) 
					CloseDataFile();

				miErrorNum = iSKIP_FILE;

				return true;
			}

   			iStatus = GInst.DeleteDay(dDayStart);

			if (iStatus != iDAY_IN_DB) 
			{
				miErrorNum = iStatus;
				if (mpFile) CloseDataFile();
				return false;	
			}

   			bOverwrote = true;
		}
	}	
	


   /* ------------------------------------------------------------------
    *	If day is not already in db, create a new day record with all db linkages needed.
	*	If day is in db, then add to the existing record.
    * ----------------------------------------------------------------*/
	if (!bDayAlreadyExists) 
	{
		if (!GInst.CreateDay(dDayStart)) 
		{
			miErrorNum = GInst.miErrorNum;
			if (mpFile) CloseDataFile();
			return(false);
		}
		i = 0;
		dPrevTime = 0.0;
		dLastTimeInDay = 0.0;        
		ulPtsInDaySoFar = 0;
		bFirstPoint = true;
		GInst.mbFillingExistingRec = false;
	}
	else 
	{ // data exists, adding to day
	
		if (!GInst.GetMultipleDbRecord(DayInFile.dEnd, &i, &dbFloatData, BEFORE)) 
		{
			miErrorNum = GInst.miErrorNum;
			if (mpFile) CloseDataFile();
			return false;
		}
			
		if (i == (NUM_RAW_DATA_PTS_IN_MULTIPLE_DB_RECORD-1)) 
		{
			i = 0;
			GInst.mbFillingExistingRec = false;
		}
		else 
		{
			i++;
			GInst.mbFillingExistingRec = true;
			ulPtsInDaySoFar = ulPtsInDaySoFar - i;
		}
		dPrevTime = dbDay.d_day_end_time;
		dLastTimeInDay = DayInFile.dEnd;//	dbDay.ul_day_end_time;
		dFirstTimeInFile = mdTimestampOfFirstRecordInFile;
		dFirstTimeInDay = DayInFile.dStart;	//dbDay.ul_day_beg_time;
		bFirstPoint = false;
	}

	iInvalidData = 0;
	iOutOfOrder = 0;
	iGamAdjust = 0; 
	
   /* ------------------------------------------------------------------
    *	Read records from the raw data file one at a time until all read.
    *	A group of individual records are combined into a single multiple
    *	record in the database.  As each record becomes full, write it
    *	to the database.
    * ----------------------------------------------------------------*/
	size_t items = 1;									//SCR00227
	size_t itemsize = sizeof(struct GRAND_DATA_PT);	//SCR00227  (36)
	int numitemstoreadeachtime = 1;
	int numitemsreadsofar = 0;

	unsigned int  ValidRecords = 0, SkippedRecords = 0, NonAcqRecords = 0; // BI0 counters

	while (items != 0)
	{
		if (BI0)
		{
			itemsize = sizeof(struct DMGGRAND_DATA_PT_HDR) + sizeof(struct DMGGRAND_DATA_PT_BDY);
			struct DMGGRAND_DATA_PT_HDR biorh;
			char  biff[512];

			unsigned int tag;
			while (fread(&tag,sizeof(unsigned int),1,mpFile)) // scan to next data record
			{
				if (tag ^ 0xFFFFFFFF) // anything but the mask
				{
					sprintf(biff,"0x%08x; skipping\n",tag);
					OutputDebugString(biff);
				}
				else
					break;
			}
			// hdr and data reads go here
			if (items = fread(&biorh,sizeof(struct DMGGRAND_DATA_PT_HDR),1,mpFile)) // got a data record header
			{
				unsigned short DCSv = 0, JSCSv = 0; 

				// doin that endian boogie thang
				biorh.ulJulianTime = _byteswap_ulong(biorh.ulJulianTime);
				biorh.usJSCS = _byteswap_ushort(biorh.usJSCS);
				byte* time = (byte*)(&biorh);	
				for (int i = 0; i < 4; i++)	JSCSv += time[i];
				bool timebad, databad;
				timebad = (JSCSv != biorh.usJSCS);

				if (biorh.OpCode != 0x15)  // not an acquire record, read through it
				{
					byte dross[1024];
					if (items = fread(dross,biorh.Len - 4,1,mpFile)) // data starts after the opcode, len was data len + 2 opcode + 2 data cs, so read len-4 to get to end of data, 2 more for data cs
					{
						unsigned short datacs;
						items = fread(&datacs,2,1,mpFile);
						for (int i = 0; i < (biorh.Len - 4); i++) DCSv += dross[i];	
						datacs= _byteswap_ushort(datacs);
						databad = (DCSv != datacs);
					}
				}
				else if (biorh.OpCode == 0x15)  // acquire record
				{ 
					struct DMGGRAND_DATA_PT_BDY bior;
					if (items = fread(&bior,sizeof(struct DMGGRAND_DATA_PT_BDY),1,mpFile))
					{
						numitemsreadsofar += items; // jfl todo not skipping records based on bad checksums just yet

						bior.usDCS = _byteswap_ushort(bior.usDCS);
						bior.usGrandStatus  = _byteswap_ushort(bior.usGrandStatus);
						bior.A.ul = _byteswap_ulong(bior.A.ul);
						bior.B.ul = _byteswap_ulong(bior.B.ul);
						bior.C.ul = _byteswap_ulong(bior.C.ul);
						bior.G1.ul = _byteswap_ulong(bior.G1.ul);
						bior.G1u.ul = _byteswap_ulong(bior.G1u.ul);
						bior.G2.ul = _byteswap_ulong(bior.G2.ul);
						bior.G2u.ul = _byteswap_ulong(bior.G2u.ul);
						bior.usElapsedTime  = _byteswap_ulong(bior.usElapsedTime);

						byte* data = (byte*)(&bior);
						for (int i = 0; i < (biorh.Len - 4); i++) DCSv += data[i];	
						databad = (DCSv != bior.usDCS);

						GrandPt.ulJulianTime = biorh.ulJulianTime;
						GrandPt.usElapsedTime = bior.usElapsedTime;
						GrandPt.usGrandStatus = bior.usGrandStatus;
						GrandPt.fA = bior.A.f;
						GrandPt.fB = bior.B.f;
						GrandPt.fC = bior.C.f;
						GrandPt.fG1 = bior.G1.f;
						GrandPt.fG1u = bior.G1u.f;
						GrandPt.fG2 = bior.G2.f;
						GrandPt.fG2u = bior.G2u.f;
					}
				}
			}
		}
		else
		{
			items = fread(&GrandPt, itemsize, numitemstoreadeachtime, mpFile);
			if (items == 0)
				break;
			//for a signed file, if we read beyond the "real" data and into
			//the footer, then we are finished reading.
			m_lUsableBytesReadIn += numitemstoreadeachtime * itemsize;
			numitemsreadsofar += items;

			if (m_bIsSignedFile && (m_lUsableBytesReadIn > m_lUsableFileLength))
			{
				//MessageBox (NULL, "rad thinks it is signed", "heather's debug message", MB_OK|MB_ICONWARNING);
				break;
			}
		}
		dCurrentPtJulianTime = m_MyDateTime.MyTimestampToDATETimestamp((double)GrandPt.ulJulianTime);

	   /* ------------------------------------------------------------------
		*   If the point's julian time is not in this day, note it and skip this point.
		* ----------------------------------------------------------------*/
		if ((dCurrentPtJulianTime < dDayStart) || (dCurrentPtJulianTime >= dFirstTimeInNextDay)) 
		{
			iInvalidData++;

			if (iInvalidData < 100) 	// print only the first 100 invalid data points
			{
				m_MyDateTime.DATETimestampToDateTimeStrs(dCurrentPtJulianTime, szTempDate, szTempTime, GEN_DTF_IAEA, GEN_DTF_HMSM);
				TempStr.Format("\nInvalid record time in file %s: %10ld %s %s",m_Dir.StripPathFromFilename(strNameWithPath), GrandPt.ulJulianTime, szTempDate, szTempTime);
				*pstrMsg += TempStr;
			}
			else 
			{	// 21-Jan-2005 SFK Don't print everything with big bad file
				if (iInvalidData == 100) 
				{
					TempStr.Format("\nToo many invalid data records in file %s to list details for each record.", m_Dir.StripPathFromFilename(strNameWithPath));
					*pstrMsg += TempStr;
				}
			}
			continue;
		}
		
	   /* ------------------------------------------------------------------
		*   If the point is out of order count it.  
		*	If the points are in order then set a new prev point
		* ----------------------------------------------------------------*/
		if (bFirstPoint) 
			dPrevTime = dCurrentPtJulianTime;

		if ((dCurrentPtJulianTime < dPrevTime) && (!bFirstPoint)) 
		{
			iOutOfOrder++;
			if (mbSkipOutOfOrder == true) continue;
		}
		else
		{
			dPrevTime = dCurrentPtJulianTime; 
		}

	   /* ------------------------------------------------------------------
		*   The largest point in the day is the last point and the smallest
		*	point in the day is the first point.
		* ----------------------------------------------------------------*/
		if (dCurrentPtJulianTime > dLastTimeInDay)
		{
			dLastTimeInDay = dCurrentPtJulianTime;
		}
		if (bFirstPoint) 
		{
			dFirstTimeInDay = dCurrentPtJulianTime;
			dFirstTimeInFile = dFirstTimeInDay;
			bFirstPoint = false;
		}	
		else 
		{
			if (dCurrentPtJulianTime < dFirstTimeInDay) 
			{
				dFirstTimeInDay = dCurrentPtJulianTime;
				dFirstTimeInFile = dFirstTimeInDay;
			}
		}

	   /* ------------------------------------------------------------------
		*   If this is the first record of a multiple record (index = 0),
		*   fill in the julian time of the 1st record and the number of
		*	pts in the day so far.
		* ----------------------------------------------------------------*/
		if (i == 0) 
		{	   
			dbFloatData.d_fdata_beg_time_key = dCurrentPtJulianTime;
			dbFloatData.ul_fdata_pts_so_far = ulPtsInDaySoFar;
		}

	   /* ------------------------------------------------------------------
		*   Fill the database record.
		*	Reverse the polarity of the authentication status bit
		* ----------------------------------------------------------------*/
		dbFloatData.d_fdata_time[i]  = dCurrentPtJulianTime;
		dbFloatData.ul_fdata_status[i] = (unsigned long)(GrandPt.usGrandStatus ^ 0x0002);
		dbFloatData.d_fdata_etime[i] = (double)GrandPt.usElapsedTime;
		dbFloatData.f_data_chan1[i]	 = GrandPt.fA;
		dbFloatData.f_data_chan2[i]	 = GrandPt.fB;
		dbFloatData.f_data_chan3[i]	 = GrandPt.fC;
		dbFloatData.f_data_chan4[i]	 = GrandPt.fG1;
		dbFloatData.f_data_chan5[i]	 = GrandPt.fG2;
		dbFloatData.f_data_chan6[i]	 = GrandPt.fG1u;
		dbFloatData.f_data_chan7[i]	 = GrandPt.fG2u;
		//if (GrandPt.fA > 1000.) {
		//	i=i;  //debug hit point
		//}

	   /* ------------------------------------------------------------------
		*   Alter IC data points with readings greater than 900000
		*   (when IC couldn't get good data).  Either put in value of previous
		*   point or set value to 0.
		*   point.
		* ----------------------------------------------------------------*/
		// 11-Aug-2005 SFK  Reworked the following section to handle the various gamma conditions
		//					and setting different status bits for the different conditions.
		if ((dbFloatData.f_data_chan4[i] >= SATURATED_G-1.0)  || (dbFloatData.f_data_chan5[i] >= SATURATED_G-1.0)) {
			iGamAdjust++;	
			
			// is this because  gamma 1 signal is saturated?
			if ((dbFloatData.f_data_chan4[i] >= SATURATED_G) && (dbFloatData.f_data_chan4[i] < INVALID_G)) {
				dbFloatData.f_data_chan4[i] = fLastGoodGamma1;								// replace with last good gamma point
				dbFloatData.ul_fdata_status[i] = dbFloatData.ul_fdata_status[i] | SATURATED_BIT;	
			}
			// is this because the gamma 1 signal is invalid (didn't get any readings in the time period)
			if ((dbFloatData.f_data_chan4[i] >= INVALID_G) && (dbFloatData.f_data_chan4[i] < OFFSET_G)) {
				dbFloatData.f_data_chan4[i] = fLastGoodGamma1;								// replace with last good gamma point
				dbFloatData.ul_fdata_status[i] = dbFloatData.ul_fdata_status[i] | INVALID_G_BIT;
			}
			// is this because offsets were being taken on gamma 1
			if (dbFloatData.f_data_chan4[i] >= OFFSET_G) {
				dbFloatData.f_data_chan4[i] = fLastGoodGamma1;									// replace with last good gamma point
				dbFloatData.ul_fdata_status[i] = dbFloatData.ul_fdata_status[i] | OFFSET_BIT;	// 28-Jun-2005 SFK Added an offset bit
			}

			// is this because  gamma 2 signal is saturated?
			if ((dbFloatData.f_data_chan5[i] >= SATURATED_G) && (dbFloatData.f_data_chan5[i] < INVALID_G)) {
				dbFloatData.f_data_chan5[i] = fLastGoodGamma2;								// replace with last good gamma point
				dbFloatData.ul_fdata_status[i] = dbFloatData.ul_fdata_status[i] | SATURATED_BIT;	
			}
			// is this because the gamma 2 signal is invalid (didn't get any readings in the time period)
			if ((dbFloatData.f_data_chan5[i] >= INVALID_G) && (dbFloatData.f_data_chan5[i] < OFFSET_G)) {
				dbFloatData.f_data_chan5[i] = fLastGoodGamma2;								// replace with last good gamma point
				dbFloatData.ul_fdata_status[i] = dbFloatData.ul_fdata_status[i] | INVALID_G_BIT;
			}
			// is this because offsets were being taken on gamma 2
			if (dbFloatData.f_data_chan5[i] >= OFFSET_G) {
				dbFloatData.f_data_chan5[i] = fLastGoodGamma2;								// replace with last good gamma point
				dbFloatData.ul_fdata_status[i] = dbFloatData.ul_fdata_status[i] | OFFSET_BIT;	// 28-Jun-2005 SFK Added an offset bit
			}
		}	
		else {	// if the gammas were within range, remember their last good reading to substitute above
			if (dbFloatData.f_data_chan4[i] < SATURATED_G) fLastGoodGamma1 =  dbFloatData.f_data_chan4[i];
			if (dbFloatData.f_data_chan5[i] < SATURATED_G) fLastGoodGamma2 =  dbFloatData.f_data_chan5[i];
		}
		
		// 29-Jun-2005 SFK Now check if the uncertainty values are > 9000 and < 10000 which indicates either
		// offsets or not enough readings to be really "good" measurement or ADC at full scale 
		// which indicates signal changing very fast
		// 11-Aug-2005 SFK  The status bits are set when reading the actual gamma channels.  Here just
		//					decide whether to replace the present reading with the last good reading.
		if (dbFloatData.f_data_chan6[i] >= SATURATED_U) {
			dbFloatData.f_data_chan6[i] = fLastGoodGamma1Unc;
		}
		else {
			fLastGoodGamma1Unc = dbFloatData.f_data_chan6[i];		// remember last good reading to substitute above
		}
		if (dbFloatData.f_data_chan7[i] >= SATURATED_U) {
			dbFloatData.f_data_chan7[i] = fLastGoodGamma2Unc;
		}
		else {
			fLastGoodGamma2Unc = dbFloatData.f_data_chan7[i];		// remeber last good reading to substitute above
		}

		// 09-Feb-2005 SFK Check to see if ms are in the Gamma 2 (xxx ms are encoded as 8xxx00)
		if ((dbFloatData.f_data_chan5[i] >= GAMMA2_IS_MS) && (dbFloatData.f_data_chan5[i] < SATURATED_G)) {
			dMilliSecs = dbFloatData.f_data_chan5[i] - GAMMA2_IS_MS;
			dMilliSecs = dMilliSecs/100;
			// convert to DATE
			dMilliSecs = dMilliSecs/dMILLISEC_PER_DAY;
			// add ms to original elapsed time and the timestamp
			dbFloatData.d_fdata_time[i] += dMilliSecs;
			dbFloatData.d_fdata_etime[i] = dbFloatData.d_fdata_etime[i]/10;  // Elapsed time is in tenths of sec
		}


		i++;	// count the point just processed

		if (i == NUM_RAW_DATA_PTS_IN_MULTIPLE_DB_RECORD) {  //78

			// about to grow database, check size limit and recover here, see BMEND-8
			// TBD note: this technique should be extened to all other datatypes, not just grand
			bool toobig = false;
			ULONG cursize, maxsize;
			double maxpercentsize = 0.95;	// TBD note: this should be externally configured
			pDb->CheckDatabaseSize(maxpercentsize, cursize, maxsize, toobig);
			if (toobig)
			{
				if (pstrMsg) 
					pstrMsg->Format("\nSkipping file %s. The database size %ul bytes is more than %3.0f%% (%ul) of max %ul bytes.", 
					strNameWithPath, cursize, (maxpercentsize * 100), ULONG(maxpercentsize * maxsize), maxsize);
				miErrorNum = iFILE_READ_ERR;
				if (mpFile) CloseDataFile();
				return(false);
			}

		   /* ------------------------------------------------------------------
			*	When have enough data to fill multiple record, create the new
			*	record, fill it and attach to database.
			* ----------------------------------------------------------------*/
			GInst.mdbFloatDataRec = dbFloatData;
			if (!GInst.AddData(pstrMsg)) 
			{
				miErrorNum = GInst.miErrorNum;
				if (mpFile) CloseDataFile();
				return(false);
			}
			ulPtsInDaySoFar += i;	// accumulate points read so far
			//MessageBox (NULL, "wrote multiple points to db", "heather's debug message", MB_OK|MB_ICONWARNING);
			i = 0;
		}
	}

   /* ------------------------------------------------------------------
	*	Got an error reading the data file.  Are expecting an EOF
	*	error.	If it's anything else, then abort and delete partial
	*	data already in the db.  If it's EOF, close	the raw data file
	*	and continue.
	* ----------------------------------------------------------------*/
	int dum = feof(mpFile);
	if (!m_bIsSignedFile && (feof(mpFile) == 0)) 
	{
		if (pstrMsg) pstrMsg->Format("\nImport Error Reading File %s.  File Error = %s", mstrFilenameWithPath, strerror(errno));
		if (mpFile) CloseDataFile();
		GInst.DeleteDay(dDayStart);
		miErrorNum = iFILE_READ_ERR;
		if (mpFile) CloseDataFile();
		//MessageBox (NULL, "import error", "heather's debug message", MB_OK|MB_ICONWARNING);
		return(false);
	}
	if (mpFile) CloseDataFile();

   /* ------------------------------------------------------------------
	*	Are at the end of the raw data file.  Fill the julian times
	*	of the unfilled records with 0 and write the partially filled
	*	record to the data base.
	* ----------------------------------------------------------------*/
	ulPtsInDay = ulPtsInDaySoFar + i;

	if (i > 0) 
	{
		while (i < NUM_RAW_DATA_PTS_IN_MULTIPLE_DB_RECORD) 
		{
			dbFloatData.d_fdata_time[i] = 0;
			i++;
		}
		GInst.mdbFloatDataRec = dbFloatData;
		if (!GInst.AddData(pstrMsg)) 
		{
			miErrorNum = GInst.miErrorNum;
			return(false);
		}

	}
   /* ------------------------------------------------------------------
    *	If there was no data for this day, delete the record you added
    *	at the start of reading the raw data file.  Print out some hints for the
	*	user as to why no data points are in the day.
    * ----------------------------------------------------------------*/
    if (ulPtsInDay == 0) 
	{
		GInst.DeleteDay(dDayStart);
		DB_D_INTERVAL DumDayInFile;
		unsigned long ulDumPtsInDaySoFar;
		int iStatus = GInst.DayExists(dDayStart, &ulDumPtsInDaySoFar, &DumDayInFile);

		if (pstrMsg) 
		{ 
			if (dCurrentPtJulianTime == 0) 
			{
				pstrMsg->Format("No data points in this file.");
			}
			else 
			{
				m_MyDateTime.DATETimestampToDateTimeStrs(dCurrentPtJulianTime, szTempDate, szTempTime, GEN_DTF_IAEA, GEN_DTF_HMSM);

    			pstrMsg->Format("\nHeader from file %s indicates data from %s, file data from %s\n", 
					mstrFilenameWithPath, szDateStr, szTempDate);

   				if (iOutOfOrder > 0)
				{
					TempStr.Format("  %5d pts out of order.", iOutOfOrder);
					*pstrMsg += TempStr;
				}

				if (iInvalidData > 0)
				{
					TempStr.Format("  %5d rec(s) with invalid times.",iInvalidData);
					*pstrMsg += TempStr;
				}
			}
		}    
		return true;
    }

   /* ------------------------------------------------------------------
    *	Some data from this day in database - now update the day record
    *	describing this day.
    *	First, find the day record.  Then read it, update the pts field
    *	and then write it back to the database.
    * ----------------------------------------------------------------*/
	iStatus = GInst.GetDayData(dDayStart, &dbDay);
	if (iStatus != iDAY_IN_DB) 
	{
		miErrorNum = iStatus;
		return (false);
	}
    dbDay.ul_day_total_pts = ulPtsInDay;
    dbDay.d_day_end_time = dLastTimeInDay;
	dbDay.d_day_beg_time = dFirstTimeInDay;
	iStatus = GInst.AddDayData(&dbDay);
	//MessageBox (NULL, "updated day record", "heather's debug message", MB_OK|MB_ICONWARNING);

   /* ------------------------------------------------------------------
    *	Log which file was just imported successfully.  Include date, station
    *	name, file name and first/last time in the file.
    *	Also log if the day's data was overwritten and if there were
    *	any points out of order or data with invalid times.
    * ----------------------------------------------------------------*/
    if (pstrMsg) 
	{ 
		m_MyDateTime.DATETimestampToDateTimeStrs(dFirstTimeInFile, szTempDate, szFirst, GEN_DTF_IAEA, GEN_DTF_HMSM);
		m_MyDateTime.DATETimestampToDateTimeStrs(dLastTimeInDay, szTempDate, szLast, GEN_DTF_IAEA, GEN_DTF_HMSM);		
		TempStr.Format("\n%s  %25s  %s    %s    %s    %5ld", szDateStr, strStationName, m_Dir.StripPathFromFilename(strNameWithPath), szFirst, szLast, ulPtsInDay);
		*pstrMsg += TempStr;
		if (bOverwrote) 
		{
			TempStr.Format("  Overwrote existing day's data.");
			*pstrMsg += TempStr;
		}
		if (bDayAlreadyExists) 
		{
			TempStr.Format("  Added to existing day's data.");
			*pstrMsg += TempStr;
		}
		if (iOutOfOrder > 0) 
		{
			TempStr.Format("  %5d pts out of order.", iOutOfOrder);
			*pstrMsg += TempStr;
		}
		if (iInvalidData > 0) 
		{
			TempStr.Format("  %5d rec(s) with invalid times.",iInvalidData);
			*pstrMsg += TempStr;
		}
		if (iGamAdjust > 0) 
		{
			TempStr.Format("  %5d rec(s) with adjusted gamma values.",iGamAdjust); // 11-Aug-2005 SFK Made message more accurate
			*pstrMsg += TempStr;
		}
    }    
	//MessageBox (NULL, "exiting readdatafile", "heather's debug message", MB_OK|MB_ICONWARNING);
    return(true);
}