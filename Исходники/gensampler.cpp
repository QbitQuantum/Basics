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

int iMode;
char szOutputFile[_MAX_PATH];
char szInputFile[_MAX_PATH];
char szInSeqFile[_MAX_PATH];
char szInputBiobedFile[_MAX_PATH];
int iRegionsIn;
int iRegionsOut;
char szRegionsIn[128];		// regions to retain
char szRegionsOut[128];		// regions to exclude
int iRegLen;

// command line args
struct arg_lit  *help    = arg_lit0("hH","help",                "print this help and exit");
struct arg_lit  *version = arg_lit0("v","version,ver",			"print version information and exit");
struct arg_int *FileLogLevel=arg_int0("f", "FileLogLevel",		"<int>","Level of diagnostics written to logfile 0=fatal,1=errors,2=info,3=diagnostics,4=debug");
struct arg_int *ScreenLogLevel=arg_int0("S", "ScreenLogLevel",	"<int>","Level of diagnostics written to logfile 0=fatal,1=errors,2=info,3=diagnostics,4=debug");
struct arg_file *LogFile = arg_file0("F","log","<file>",	"diagnostics log file");

struct arg_int  *Mode = arg_int0("m","procmode","<int>",	"processing mode 0:default");
struct arg_int  *RegLen = arg_int0("L","updnstream","<int>",	"length of 5'up or 3'down  stream regulatory region length (default = 2000) 0..1000000");
struct arg_file *InFile = arg_file1("i",NULL,"<file>",			"input from loci csv file");
struct arg_file *OutFile = arg_file1("o",NULL,"<file>",			"output to multifasta file");
struct arg_file *InSeqFile = arg_file1("a","assemb","<file>","get sequences fron this file");
struct arg_file *InBedFile = arg_file1("b","bed","<file>",		"characterise regions from biobed file");
struct arg_str  *RegionsOut = arg_str0("R","regionsout","<string>","Filter out random samples in any of these regions (space or comma delimit), 1: Intergenic, 2: US, 3: 5'UTR, 4: CDS, 5: Intron, 6: 3'UTR, 7: DS");
struct arg_str  *RegionsIn = arg_str0("r","regionsin","<string>","Accept random samples in any of these exclusive regions (space or comma delimit), 1: Intergenic, 2: US, 3: 5'UTR, 4: CDS, 5: Intron, 6: 3'UTR, 7: DS");

struct arg_end *end = arg_end(20);

void *argtable[] = {help,version,FileLogLevel,ScreenLogLevel,LogFile,
					Mode,RegLen,InFile,OutFile,InSeqFile,InBedFile,RegionsIn,RegionsOut,
					end};

char **pAllArgs;
int argerrors;
argerrors = CUtility::arg_parsefromfile(argc,(char **)argv,&pAllArgs);
if(argerrors >= 0)
	argerrors = arg_parse(argerrors,pAllArgs,argtable);

    /* special case: '--help' takes precedence over error reporting */
if (help->count > 0)
        {
		printf("Usage: %s ", gszProcName);
        arg_print_syntax(stdout,argtable,"\n");
        arg_print_glossary(stdout,argtable,"  %-25s %s\n");
		exit(1);
        }

    /* special case: '--version' takes precedence error reporting */
if (version->count > 0)
        {
		printf("\n%s: Version: %d.%2.2d\n",gszProcName,cProgVer/100,cProgVer%100);
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

	iMode = Mode->count ? Mode->ival[0] : eProcModeStandard;
	if(iMode < eProcModeStandard || iMode > eProcModeStandard)
		{
		printf("\nError: Requested processing mode '-x%d' not supported",iMode);
		exit(1);
		}

	if(RegionsIn->count)
		{
		strcpy(szRegionsIn,RegionsIn->sval[0]);
		TrimQuotes(szRegionsIn);
		if((iRegionsIn = ParseRegions(szRegionsIn)) < 0)
			{
			printf("Error: unable to parse '-r%s' into regions to retain",szRegionsIn);
			exit(1);
			}
		}
	else
		{
		szRegionsIn[0] = '\0';
		iRegionsIn = (cFeatBitIG | cFeatBitUpstream | cFeatBit5UTR | cFeatBitCDS | cFeatBitIntrons | cFeatBit3UTR | cFeatBitDnstream);
		}

	if(RegionsOut->count)
		{
		strcpy(szRegionsOut,RegionsOut->sval[0]);
		TrimQuotes(szRegionsOut);
		if((iRegionsOut = ParseRegions(szRegionsOut)) < 0)
			{
			printf("Error: unable to parse '-R%s' into regions to remove",szRegionsOut);
			exit(1);
			}
		}
	else
		{
		szRegionsOut[0] = '\0';
		iRegionsOut = 0;
		}
	iRegionsIn &= ~iRegionsOut;
	if(!iRegionsIn)
		{
		printf("Error: no regions to retain");
		exit(1);
		}

	iRegLen = RegLen->count ? RegLen->ival[0] : cDfltRegLen;
	if(iRegLen < cMinRegLen)
		{
		printf("\nRegulatory region length '-L%d' less than minimum %d, assuming you meant to use '-L%d'",iRegLen,cMinRegLen,cMinRegLen);
		iRegLen = cMinRegLen;
		}
	else
		{
		if(iRegLen > cMaxRegLen)
			{
			printf("\nRegulatory region length '-L%d' more than maximum %d, assuming you meant to use '-L%d'",iRegLen,cMaxRegLen,cMaxRegLen);
			iRegLen = cMaxRegLen;
			}
		}

	strcpy(szInputFile,InFile->filename[0]);
	strcpy(szOutputFile,OutFile->filename[0]);
	strcpy(szInputBiobedFile,InBedFile->filename[0]);
	strcpy(szInSeqFile,InSeqFile->filename[0]);

		// now that command parameters have been parsed then initialise diagnostics log system
	if(!gDiagnostics.Open(szLogFile,(etDiagLevel)iScreenLogLevel,(etDiagLevel)iFileLogLevel,true))
		{
		printf("\nError: Unable to start diagnostics subsystem.");
		if(szLogFile[0] != '\0')
			printf(" Most likely cause is that logfile '%s' can't be opened/created",szLogFile);
		exit(1);
		}

	gDiagnostics.DiagOut(eDLInfo,gszProcName,"Version: %d.%2.2d Processing parameters:",cProgVer/100,cProgVer%100);
	gDiagnostics.DiagOutMsgOnly(eDLInfo,"Loci file (.csv) file to process: '%s'",szInputFile);
	gDiagnostics.DiagOutMsgOnly(eDLInfo,"bio assembly (.seq) file to process: '%s'",szInSeqFile);
	gDiagnostics.DiagOutMsgOnly(eDLInfo,"where to write out fasta with random sequences: '%s'",szOutputFile);
	gDiagnostics.DiagOutMsgOnly(eDLInfo,"biobed file containing regional features: '%s'",szInputBiobedFile);
	gDiagnostics.DiagOutMsgOnly(eDLInfo,"Processing mode: %s",iMode == eProcModeStandard ? "standard" : iMode == eProcModeStandard ? "extended" : "summary");
	gDiagnostics.DiagOutMsgOnly(eDLInfo,"Accept random samples in any of these regions: '%s'",Regions2Txt(iRegionsIn));

#ifdef _WIN32
	SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);
#endif

	Rslt = Process(iMode,iRegionsIn,iRegLen,szInputFile,szInputBiobedFile,szInSeqFile,szOutputFile);
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
}