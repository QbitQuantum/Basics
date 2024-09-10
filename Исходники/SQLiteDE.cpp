int
CSQLiteDE::ProcessCSV2SQLite(int PMode,			// currently just the one mode...default is to parse from CSV and create/populate SQLite database
				  bool bSafe,					// if true then use indexing on all tables whilst inserting... much slower but perhaps safer if multiple threads ...
				  char *pszExprName,			// name by which this experiment is identified
				  char *pszExprDescr,			// describes experiment
				  char *pszCtrlConditions,		// control conditions
				  char *pszExprConditions,		// experiment conditions
				  char *pszInFile,				// parse from this input CSV file
				  char *pszDatabase)			// SQLite database file
{
int Rslt;
bool bExtdBins;			// false if CSV file does not contain bins, true if determined that CSV contains bin counts
int sqlite_error;
sqlite3_stmt *prepstatement = NULL;
int ExprID;		// experiment identifier
int TransID;
int ExpresID;
char *pszTransName;
char *pszContOrExpr;
int TransLen;
int NumExons;
int Class;
int Score;
int DECntsScore;
int PearsonScore;
int CtrlUniqueLoci;
int ExprUniqueLoci;
double CtrlExprLociRatio;
double PValueMedian;
double PValueLow95;
double PValueHi95;
int TotCtrlCnts;
int TotExprCnts;
int TotCtrlExprCnts;
double ObsFoldChange;
double FoldMedian;
double FoldLow95;
double FoldHi95;
double ObsPearson;
double PearsonMedian;
double PearsonLow95;
double PearsonHi95;
int CtrlAndExprBins;
int CtrlOnlyBins;
int ExprOnlyBins;
int TotBins;
int BinIdx;
int BinValues[100 * 2];		// sized to contain 100 bin counts for both control and experiment
int *pBinValue;
int NumFields;
int NumElsRead;
int NumBins;
int BinID;
int ExpNumBins;
int ExpNumFields;


// load CSV file and determine number of fields, from these it can be determined if the file also contains the bin counts
CCSVFile *pCSV = new CCSVFile;
if(pCSV == NULL)
	{
	gDiagnostics.DiagOut(eDLFatal,gszProcName,"Unable to instantiate CCSVfile");
	CloseDatabase(true);
	return(eBSFerrObj);
	}
pCSV->SetMaxFields(cDESummMaxBinFields + 10);	// could be upto 100 bins, add 10 in case more fields than expected!
if((Rslt=pCSV->Open(pszInFile))!=eBSFSuccess)
	{
	while(pCSV->NumErrMsgs())
		gDiagnostics.DiagOut(eDLFatal,gszProcName,pCSV->GetErrMsg());
	gDiagnostics.DiagOut(eDLFatal,gszProcName,"Unable to open file: %s",pszInFile);
	delete pCSV;
	return(Rslt);
	}
if((Rslt=pCSV->NextLine()) < 1)	// have to be able to read at least one!
	{
	gDiagnostics.DiagOut(eDLFatal,gszProcName,"Unable to read any lines from %s",pszInFile);
	delete pCSV;
	return(Rslt);
	}
NumFields = pCSV->GetCurFields();		// expecting at least 24, if 24 then summary, if 27+ then summary plus bin counts
if(NumFields < cDESummFields)
	{
	gDiagnostics.DiagOut(eDLFatal,gszProcName,"CSV transcipt expression file '%s' are expected to contain at least %d fields, parsed %d",pszInFile,cDESummFields,NumFields);
	delete pCSV;
	return(eBSFerrFieldCnt);
	}
if(NumFields > cDESummFields && NumFields < cDESummMinBinFields)
	{
	gDiagnostics.DiagOut(eDLFatal,gszProcName,"Expected CSV file '%s' to contain either %d (no bins) or at least %d (with bins) fields, file has %d fields",pszInFile,cDESummFields,cDESummMinBinFields,NumFields);
	delete pCSV;
	return(eBSFerrFieldCnt);
	}
if(NumFields > cDESummMaxBinFields)					// if summary plus bins then expecting at most 100 bins
	{
	gDiagnostics.DiagOut(eDLFatal,gszProcName,"Expected CSV file '%s' to contain no more than 100 bins",pszInFile);
	delete pCSV;
	return(eBSFerrFieldCnt);
	}
if(NumFields == cDESummFields)
	{
	bExtdBins = false;
	NumBins = 0;
	}
else
	{
	bExtdBins = true;
	NumBins = NumBins = 5 + NumFields - cDESummMinBinFields; 
	}
pCSV->Close();

sqlite3_initialize();

if((CreateDatabase(bSafe,pszDatabase))==NULL)
	{
	sqlite3_shutdown();
	return(eBSFerrInternal);
	}

if((Rslt = CreateExperiment(bExtdBins ? 1 : 0,pszInFile,pszExprName,pszExprDescr,pszCtrlConditions,pszExprConditions,NumBins)) < 1)
	{
	CloseDatabase(true);
	return(Rslt);
	}
ExprID = Rslt;

char *pszBeginTransaction = (char *)"BEGIN TRANSACTION";
char *pszEndTransaction = (char *)"END TRANSACTION";
char *pszDropIndexes = (char *)"DROP INDEX IF EXISTS 'Markers_LociID'";

char *pszPragmaSyncOff = (char *)"PRAGMA synchronous = OFF";
char *pszPragmaSyncOn = (char *)"PRAGMA synchronous = ON";
char *pszPragmaJournMem = (char *)"PRAGMA journal_mode = MEMORY";

gDiagnostics.DiagOut(eDLInfo,gszProcName,"sqlite - populating tables");


// synchronous writes off
if((sqlite_error = sqlite3_exec(m_pDB,pszPragmaSyncOff,NULL,NULL,NULL))!=SQLITE_OK)
	{
	gDiagnostics.DiagOut(eDLFatal,gszProcName,"sqlite - can't turn synchronous writes off: %s", sqlite3_errmsg(m_pDB)); 
	CloseDatabase(true);
	return(eBSFerrInternal);
	}

// bracket inserts as a single transaction
if((sqlite_error = sqlite3_exec(m_pDB,pszBeginTransaction,NULL,NULL,NULL))!=SQLITE_OK)
	{
	gDiagnostics.DiagOut(eDLFatal,gszProcName,"sqlite - can't begin transactions: %s",sqlite3_errmsg(m_pDB)); 
	CloseDatabase(true);
	return(eBSFerrInternal);
	}


// load CSV file and start populating the SQLite database
if((Rslt=pCSV->Open(pszInFile))!=eBSFSuccess)
	{
	while(pCSV->NumErrMsgs())
		gDiagnostics.DiagOut(eDLFatal,gszProcName,pCSV->GetErrMsg());
	gDiagnostics.DiagOut(eDLFatal,gszProcName,"Unable to open file: %s",pszInFile);
	delete pCSV;
	CloseDatabase(true);
	return(Rslt);
	}


bExtdBins = false;
NumElsRead = 0;
ExpNumBins = 0;
ExpNumFields = 0;
while((Rslt=pCSV->NextLine()) > 0)			// onto next line containing fields
	{
	if(!(NumElsRead % (bSafe ? 5000 : 100000)) && NumElsRead > 0)
		gDiagnostics.DiagOut(eDLInfo,gszProcName,"Parsed %d CSV lines - Transcripts: %d",NumElsRead, m_NumTrans);

	NumFields = pCSV->GetCurFields();		// expecting at least 24, if 24 then summary, if 27+ then summary plus bin counts
	if(ExpNumFields > 0 && NumFields != ExpNumFields)
		{
		gDiagnostics.DiagOut(eDLFatal,gszProcName,"CSV transcipt expression file '%s' has varying number of fields : expected %d, parsed %d at line %d",pszInFile,ExpNumFields,NumFields,NumElsRead);
		delete pCSV;
		CloseDatabase(true);
		return(eBSFerrFieldCnt);
		}
	if(ExpNumFields == 0)
		{
		ExpNumFields = NumFields;
		if(NumFields < cDESummFields)
			{
			gDiagnostics.DiagOut(eDLFatal,gszProcName,"CSV transcipt expression file '%s' are expected to contain at least %d fields, parsed %d at line %d",pszInFile,cDESummFields,NumFields,NumElsRead);
			delete pCSV;
			CloseDatabase(true);
			return(eBSFerrFieldCnt);
			}
		if(NumFields > cDESummFields)							// summary plus bins?
			{
			if(NumFields < cDESummMinBinFields)					// if summary plus bins then expecting at least 5 bins
				{
				gDiagnostics.DiagOut(eDLFatal,gszProcName,"Expected CSV file '%s' to contain at least 5 bins at line %d",pszInFile,NumElsRead);
				delete pCSV;
				CloseDatabase(true);
				return(eBSFerrFieldCnt);
				}
			if(NumFields > cDESummMaxBinFields)					// if summary plus bins then expecting at most 100 bins
				{
				gDiagnostics.DiagOut(eDLFatal,gszProcName,"Expected CSV file '%s' to contain no more than 100 bins at line %d",pszInFile,NumElsRead);
				delete pCSV;
				CloseDatabase(true);
				return(eBSFerrFieldCnt);
				}

			NumBins = 5 + NumFields - cDESummMinBinFields;
			ExpNumBins = NumBins;
			bExtdBins = true;
			}
		}

	if(!NumElsRead && pCSV->IsLikelyHeaderLine())
		continue;
	NumElsRead += 1;

	// first 20 fields are common to both CSV file types
	pCSV->GetInt(1,&Class);
	pCSV->GetText(2,&pszTransName);
	pCSV->GetInt(3,&TransLen);
	pCSV->GetInt(4,&NumExons);

	pCSV->GetInt(5,&Score);
	pCSV->GetInt(6,&DECntsScore);
	pCSV->GetInt(7,&PearsonScore);
	pCSV->GetInt(8,&CtrlUniqueLoci);
	pCSV->GetInt(9,&ExprUniqueLoci);
	
	pCSV->GetDouble(10,&CtrlExprLociRatio);
	pCSV->GetDouble(11,&PValueMedian);
	pCSV->GetDouble(12,&PValueLow95);
	pCSV->GetDouble(13,&PValueHi95);

	pCSV->GetInt(14,&TotCtrlCnts);
	pCSV->GetInt(15,&TotExprCnts);
	pCSV->GetInt(16,&TotCtrlExprCnts);

	pCSV->GetDouble(17,&ObsFoldChange);
	pCSV->GetDouble(18,&FoldMedian);
	pCSV->GetDouble(19,&FoldLow95);
	pCSV->GetDouble(20,&FoldHi95);
	// file formats diverge dependent on if containing bin counts
	if(!bExtdBins)
		{
		pszContOrExpr = NULL;
		pCSV->GetDouble(21,&ObsPearson);
		pCSV->GetDouble(22,&PearsonMedian);
		pCSV->GetDouble(23,&PearsonLow95);
		pCSV->GetDouble(24,&PearsonHi95);
		TotBins = 0;
		CtrlAndExprBins = 0;
		CtrlOnlyBins = 0;
		ExprOnlyBins = 0;
		}
	else
		{
		pCSV->GetText(21,&pszContOrExpr);
		pCSV->GetDouble(22,&ObsPearson);
		pCSV->GetDouble(23,&PearsonMedian);
		pCSV->GetDouble(24,&PearsonLow95);
		pCSV->GetDouble(25,&PearsonHi95);
		pCSV->GetInt(26,&TotBins);
		pCSV->GetInt(27,&CtrlAndExprBins);
		pCSV->GetInt(28,&CtrlOnlyBins);
		pCSV->GetInt(29,&ExprOnlyBins);
		if(!stricmp(pszContOrExpr,"Control"))
			pBinValue = &BinValues[0];
		else
			pBinValue = &BinValues[1];
		for(BinIdx = 0; BinIdx < NumBins; BinIdx++,pBinValue += 2)
			*pBinValue = pCSV->GetInt(BinIdx + 30,pBinValue);
		}
	if(!bExtdBins || (bExtdBins && stricmp(pszContOrExpr,"Control")))
		{
		TransID = AddTrans(ExprID,pszTransName,NumExons,TransLen,(char *)"N/A");
		ExpresID = AddExpres(ExprID,TransID,Class,Score,DECntsScore,PearsonScore,CtrlUniqueLoci,ExprUniqueLoci,CtrlExprLociRatio,PValueMedian,PValueLow95,PValueHi95,
					TotCtrlCnts,TotExprCnts,TotCtrlExprCnts,ObsFoldChange,FoldMedian,FoldLow95,FoldHi95,ObsPearson,PearsonMedian,PearsonLow95,PearsonHi95,
					CtrlAndExprBins,CtrlOnlyBins,ExprOnlyBins);
		}
	if(bExtdBins && stricmp(pszContOrExpr,"Control"))
		{
		pBinValue = &BinValues[0];
		for(BinIdx = 1; BinIdx <= NumBins; BinIdx++,pBinValue += 2)
			BinID = AddBin(ExprID,TransID,ExpresID,BinIdx,*pBinValue,pBinValue[1]);
		}
	}
gDiagnostics.DiagOut(eDLInfo,gszProcName,"Parsed %d CSV lines - transcripts: %d",NumElsRead, m_NumTrans);

	// end transaction
if((sqlite_error = sqlite3_exec(m_pDB,pszEndTransaction,NULL,NULL,NULL))!=SQLITE_OK)
	{
	gDiagnostics.DiagOut(eDLFatal,gszProcName,"sqlite - can't end transactions on '%s': %s", "Markers",sqlite3_errmsg(m_pDB)); 
	CloseDatabase(true);
	return(eBSFerrInternal);
	}
gDiagnostics.DiagOut(eDLInfo,gszProcName,"Completed populating the sqlite database");

gDiagnostics.DiagOut(eDLInfo,gszProcName,"Generating indexes ...");

tsDEStmSQL *pStms;
pStms = m_StmSQL;
int TblIdx;
for(TblIdx = 0; TblIdx < 4; TblIdx++,pStms++)
	{
	if(pStms->pszCreateIndexes == NULL)
		continue;
	gDiagnostics.DiagOut(eDLInfo,gszProcName,"Creating indexes on table %s ...", pStms->pTblName);
	if((sqlite_error = sqlite3_exec(m_pDB,pStms->pszCreateIndexes,0,0,0))!=SQLITE_OK)
		{
		gDiagnostics.DiagOut(eDLFatal,gszProcName,"sqlite - can't create indexes on table %s : %s", pStms->pTblName,sqlite3_errmsg(m_pDB));
		gDiagnostics.DiagOut(eDLFatal,gszProcName,"sqlite - statement: %s",pStms->pszCreateIndexes);   
		CloseDatabase(true);
		return(eBSFerrInternal);
		}
	}
gDiagnostics.DiagOut(eDLInfo,gszProcName,"Indexes generated");
// synchronous writes off
if((sqlite_error = sqlite3_exec(m_pDB,pszPragmaSyncOn,NULL,NULL,NULL))!=SQLITE_OK)
	{
	gDiagnostics.DiagOut(eDLFatal,gszProcName,"sqlite - can't turn synchronous writes on: %s", sqlite3_errmsg(m_pDB)); 
	CloseDatabase(true);
	return(eBSFerrInternal);
	}

CloseDatabase();
sqlite3_shutdown();
gDiagnostics.DiagOut(eDLInfo,gszProcName,"SQLite database ready for use");
return(eBSFSuccess);
}