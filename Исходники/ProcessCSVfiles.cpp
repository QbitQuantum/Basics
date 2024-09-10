int _tmain(int argc, char* argv[])
{
// determine my process name
_splitpath(argv[0],NULL,NULL,gszProcName,NULL);
#else
int 
main(int argc, const char** argv)
{
// determine my process name
CUtility::splitpath((char *)argv[0],NULL,gszProcName);
#endif
int iScreenLogLevel;		// level of screen diagnostics
int iFileLogLevel;			// level of file diagnostics
char szLogFile[_MAX_PATH];	// write diagnostics to this file

int Rslt;

int iProcMode;			// processing mode
char szRefFile[_MAX_PATH];	// nput from reference csv file
char szFilterRefIDFile[_MAX_PATH];  // exclude any RefIDs in this filter file
char szRelFile[_MAX_PATH];	// input from relative csv file(s)
char szRsltfile[_MAX_PATH];	// output to results CSV file
int iMinLen;			// minimum accepted length
int iMaxLen;			// maximum accepted length


// command line args
struct arg_lit  *help    = arg_lit0("hH","help",                "print this help and exit");
struct arg_lit  *version = arg_lit0("v","version,ver",			"print version information and exit");
struct arg_int *FileLogLevel=arg_int0("f", "FileLogLevel",		"<int>","Level of diagnostics written to logfile 0=fatal,1=errors,2=info,3=diagnostics,4=debug");
struct arg_int *ScreenLogLevel=arg_int0("S", "ScreenLogLevel",	"<int>","Level of diagnostics written to logfile 0=fatal,1=errors,2=info,3=diagnostics,4=debug");
struct arg_file *LogFile = arg_file0("F","log","<file>",		"diagnostics log file");
struct arg_int *ProcMode = arg_int0("m", "mode","<int>",		"processing mode (default 0) 0: Identities (Match/Match+Mismatches), 1: Identities (Match/CoreLength), 2: Aligned Length 3: Score");

struct arg_file *RefFile = arg_file1("i","in","<file>",			"input from reference csv file");
struct arg_file *FilterRefIDFile = arg_file0("X",NULL,"<file>",	"filter out any ref or rel loci with RefIDs in this filter file");
struct arg_file *RelFile = arg_file1("I","in","<file>",			"input from relative csv file(s) - can use wildcards");
struct arg_file *Rsltfile= arg_file1("o","out","<file>",		"output to results CSV file");
struct arg_int *MinLen=arg_int0("l", "MinLen",	"<int>","minimum accepted length");
struct arg_int *MaxLen=arg_int0("L", "MaxLen",	"<int>","maximum accepted length");

struct arg_end *end = arg_end(20);
void *argtable[] = {help,version,FileLogLevel,ScreenLogLevel,LogFile,
			ProcMode,RefFile,FilterRefIDFile,RelFile,Rsltfile,
			MinLen,MaxLen,
			end};

char **pAllArgs;
int argerrors;
argerrors = CUtility::arg_parsefromfile(argc,(char **)argv,&pAllArgs);
if(argerrors >= 0)
	argerrors = arg_parse(argerrors,pAllArgs,argtable);

/* special case: '--help' takes precedence over error reporting */
if (help->count > 0)
        {
		printf("\n%s ", gszProcName);
        arg_print_syntax(stdout,argtable,"\n");
        arg_print_glossary(stdout,argtable,"  %-25s %s\n");
		printf("\nNote: Parameters can be entered into a parameter file, one parameter per line.");
		printf("\n      To invoke this parameter file then precede its name with '@'");
		printf("\n      e.g. %s @myparams.txt\n\n",gszProcName);
		exit(1);
        }

    /* special case: '--version' takes precedence error reporting */
if (version->count > 0)
        {
		printf("\n%s Version %d.%2.2d",gszProcName,cProgVer/100,cProgVer%100);
		exit(1);
        }

if (!argerrors)
	{
	iScreenLogLevel = ScreenLogLevel->count ? ScreenLogLevel->ival[0] : eDLInfo;
	if(iScreenLogLevel < eDLNone || iScreenLogLevel > eDLDebug)
		{
		printf("\nError: ScreenLogLevel '-S%d' specified outside of range %d..%d",iScreenLogLevel,eDLNone,eDLDebug);
		exit(1);
		}
	if(FileLogLevel->count && !LogFile->count)
		{
		printf("\nError: FileLogLevel '-f%d' specified but no logfile '-F<logfile>'",FileLogLevel->ival[0]);
		exit(1);
		}

	iFileLogLevel = FileLogLevel->count ? FileLogLevel->ival[0] : eDLInfo;
	if(iFileLogLevel < eDLNone || iFileLogLevel > eDLDebug)
		{
		printf("\nError: FileLogLevel '-l%d' specified outside of range %d..%d",iFileLogLevel,eDLNone,eDLDebug);
		exit(1);
		}
	if(LogFile->count)
		{
		strncpy(szLogFile,LogFile->filename[0],_MAX_PATH);
		szLogFile[_MAX_PATH-1] = '\0';
		}
	else
		{
		iFileLogLevel = eDLNone;
		szLogFile[0] = '\0';
		}

	iProcMode = ProcMode->count ? ProcMode->ival[0] : eProcModeStandard;
	if(iProcMode < eProcModeStandard || iProcMode > eProcModeScore)
		{
		printf("\nError: Requested processing mode '-x%d' not supported",iProcMode);
		exit(1);
		}

	iMinLen = MinLen->count ? MinLen->ival[0] : 0;
	if(iMinLen < 0)
		{
		printf("\nError: Requested minimum length '-l%d' is negative",iMinLen);
		exit(1);
		}

	iMaxLen = MaxLen->count ? MaxLen->ival[0] : 1000000000;
	if(iMaxLen < iMinLen)
		{
		printf("\nError: Requested maximum ength '-l%d' must be >= minimum %d",iMaxLen,iMinLen);
		exit(1);
		}



	strcpy(szRefFile,RefFile->filename[0]);
	strcpy(szRelFile,RelFile->filename[0]);
	strcpy(szRsltfile,Rsltfile->filename[0]);

	if(FilterRefIDFile->count)
		{
		strncpy(szFilterRefIDFile,FilterRefIDFile->filename[0],sizeof(szFilterRefIDFile));
		szFilterRefIDFile[sizeof(szFilterRefIDFile)-1] = '\0';
		}
	else
		szFilterRefIDFile[0] = '\0';


			// now that command parameters have been parsed then initialise diagnostics log system
	if(!gDiagnostics.Open(szLogFile,(etDiagLevel)iScreenLogLevel,(etDiagLevel)iFileLogLevel,true))
		{
		printf("\nError: Unable to start diagnostics subsystem.");
		if(szLogFile[0] != '\0')
			printf(" Most likely cause is that logfile '%s' can't be opened/created",szLogFile);
		exit(1);
		}

	gDiagnostics.DiagOut(eDLInfo,gszProcName,"Version: %d.%2.2d Processing parameters:",cProgVer/100,cProgVer%100);
	switch(iProcMode) {
		case eProcModeStandard:
			gDiagnostics.DiagOutMsgOnly(eDLInfo,"Processing mode:  Identity = Match/(Match+Mismatch)");
			break;
		case eProcModeIdentity:
			gDiagnostics.DiagOutMsgOnly(eDLInfo,"Processing mode:  Identity = Match/(CoreLength)");
			break;
		case eProcModeAligned:
			gDiagnostics.DiagOutMsgOnly(eDLInfo,"Processing mode:  Aligned = (Match+Mismatch)/CoreLength");
			break;
		case eProcModeScore:
			gDiagnostics.DiagOutMsgOnly(eDLInfo,"Processing mode: score");
			break;
		}

	gDiagnostics.DiagOutMsgOnly(eDLInfo,"reference csv file to process: '%s'",szRefFile);
	gDiagnostics.DiagOutMsgOnly(eDLInfo,"relative csv file(s) to processs: '%s'",szRelFile);
	gDiagnostics.DiagOutMsgOnly(eDLInfo,"results file to generate: '%s'",szRsltfile);
	if(szFilterRefIDFile[0])
		gDiagnostics.DiagOutMsgOnly(eDLInfo,"Exclude any RefIDs in this filter file: '%s'",szFilterRefIDFile);

	gDiagnostics.DiagOutMsgOnly(eDLInfo,"minimum length: %d",iMinLen);
	gDiagnostics.DiagOutMsgOnly(eDLInfo,"maximum length: %d",iMaxLen);

	gStopWatch.Start();
#ifdef _WIN32
	SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);
#endif
	Rslt = Process((etProcMode)iProcMode,		// processing mode 0: default
					szRefFile,		// reference csv file to process
					szFilterRefIDFile, // exclude any RefIDs in this filter file
					szRelFile,		// relative csv file(s) to processs
					szRsltfile,  	// results file to generate
					iMinLen,		// minimum accepted ref length
					iMaxLen);		// maximum accepted ref length

	gStopWatch.Stop();
	Rslt = Rslt < 0 ? 1 : 0;
	gDiagnostics.DiagOut(eDLInfo,gszProcName,"Exit Code: %d Total processing time: %s",Rslt,gStopWatch.Read());
	exit(Rslt);
	}
else
	{
	arg_print_errors(stdout,end,gszProcName);
	arg_print_syntax(stdout,argtable,"\nend of help\n");
	exit(1);
	}
return 0;
}