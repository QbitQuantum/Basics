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
int Rslt = 0;   			// function result code >= 0 represents success, < 0 on failure

etPMode PMode;				// processing mode
etFMode FMode;				// format output mode

int TruncLength;			// truncate regions to be no longer than this length
int OfsLoci;				// offset region loci by this many bases
int DeltaLen;				// change region lengths by this many bases

int MovAvgFilter;			// apply this moving average window size filter
int BaselineFilter;			// use this window size when normalising for baseline
char szTrackTitle[cMaxDatasetSpeciesChrom];			// title to identify predicted nucleosome track
double Dyadratio;
double Dyad2ratio;
double Dyad3ratio;
char szRsltsFile[_MAX_PATH];
char szInConfFile[_MAX_PATH];
char szInGenomeFile[_MAX_PATH];

char szInclRegionFile[_MAX_PATH]; //  only report predicted nucleosomes if intersecting with regions in this file


// command line args
struct arg_lit  *help    = arg_lit0("hH","help",                "print this help and exit");
struct arg_lit  *version = arg_lit0("v","version,ver",			"print version information and exit");
struct arg_int *FileLogLevel=arg_int0("f", "FileLogLevel",		"<int>","Level of diagnostics written to logfile 0=fatal,1=errors,2=info,3=diagnostics,4=debug");
struct arg_file *LogFile = arg_file0("F","log","<file>",		"diagnostics log file");

struct arg_int *pmode = arg_int0("m","mode","<int>",		    "processing mode: 0 - predict from minor groove (default = 0)");
struct arg_file *inGenomefile = arg_file1("i","in","<file>",	"input from this bioseq genome file");
struct arg_file *inConfFile = arg_file1("I","conf","<file>",	"input conformation characteristics from this file");

struct arg_file *inclRegionFile = arg_file0("r","inclregions","<file>",	"only report predicted nucleosomes if intersecting with regions in this file");
struct arg_int  *trunclength = arg_int0("T","trunclength","<int>","truncate regions to be no longer than this length (default 147)");
struct arg_int  *ofsloci   = arg_int0("u","offset","<int>",	    "offset region loci by this many bases, -2048 to +2048 (default 0)");
struct arg_int  *deltalen  = arg_int0("U","deltalen","<int>",	"delta region lengths by this many bases, -2048 to +2048 (default 0)");

struct arg_dbl *dyadratio=arg_dbl0("d", "dyadratio",	"<double>","dyad minor grooves must be at least this ratio to background (default 1.020");
struct arg_dbl *dyad2ratio=arg_dbl0("D", "dyad2ratio",	"<double>","immediately flanking minor grooves must be at least this ratio to background (default 1.015");
struct arg_dbl *dyad3ratio=arg_dbl0("e", "dyad3ratio",	"<double>","remainder flanking minor grooves must be at least this ratio to background (default 1.010");

struct arg_int *movavgfilter = arg_int0("a","avgwindow","<int>","apply lowpass filter as a moving average window of this size, 0 if none else 5..100 (default: 10)");
struct arg_int *baselinefilter = arg_int0("A","basewindow","<int>","baseline normalisation window size, 0 if none else 25..5000 (default: 250)");

struct arg_file *outfile = arg_file1("o","out","<file>",		"output nucleosome predictions to this file");
struct arg_int *format = arg_int0("M","format","<int>",		    "output format: 0 - UCSC bedGraph dyads, 1 - UCSC BED dyads, 2 - CSV dyads,  3 - UCSC bedGraph nucleosomes, 4 - UCSC BED nucleosomes, 5 - CSV nucleosomes, 6 - CSV scores (default: 0)");
struct arg_str  *title = arg_str0("t","title","<string>",       "track title");

struct arg_end *end = arg_end(20);

void *argtable[] = {help,version,FileLogLevel,LogFile,
					pmode,format,movavgfilter,baselinefilter,title,dyadratio,dyad2ratio,dyad3ratio,inGenomefile,inConfFile,outfile,
					inclRegionFile,trunclength,ofsloci,deltalen,
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
	if(FileLogLevel->count && !LogFile->count)
		{
		printf("\nError: FileLogLevel '-f%d' specified but no logfile '-F<logfile>'",FileLogLevel->ival[0]);
		exit(1);
		}

	iScreenLogLevel = iFileLogLevel = FileLogLevel->count ? FileLogLevel->ival[0] : eDLInfo;
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

	PMode = (etPMode)(pmode->count ? pmode->ival[0] : 0);
	if(PMode < 0 || PMode >= ePMplaceholder)
		{
		printf("\nError: Processing mode '-m%d' specified outside of range %d..%d",PMode,0,(int)ePMplaceholder-1);
		exit(1);
		}

	FMode = (etFMode)(format->count ? format->ival[0] : eFMbedGraphDyads);
	if(FMode < eFMbedGraphDyads || FMode >= eFMplaceholder)
		{
		printf("\nError: Output format mode '-m%d' specified outside of range %d..%d",FMode,eFMbedGraphDyads,(int)eFMplaceholder-1);
		exit(1);
		}

		MovAvgFilter = movavgfilter->count ? movavgfilter->ival[0] : 10;
	if(MovAvgFilter != 0 && (MovAvgFilter < 5 || MovAvgFilter > 100))
		{
		printf("\nError: Moving average filter width '-a%d' specified outside of range 0 or 5..100",MovAvgFilter);
		exit(1);
		}


	BaselineFilter = baselinefilter->count ? baselinefilter->ival[0] : 250;
	if(BaselineFilter != 0 && (BaselineFilter < 25 || MovAvgFilter > 5000))
		{
		printf("\nError: Baseline normalisation window width '-A%d' specified outside of range 0 or 25..5000",BaselineFilter);
		exit(1);
		}

	Dyadratio = dyadratio->count ? dyadratio->dval[0] : cDfltDyadratio;
	Dyad2ratio = dyad2ratio->count ? dyad2ratio->dval[0] : cDfltDyad2ratio;
	Dyad3ratio = dyad3ratio->count ? dyad3ratio->dval[0] : cDfltDyad3ratio;
	if(Dyadratio < 1.0f || Dyad2ratio < 1.0f || Dyad3ratio < 1.0f)
		{
		printf("\nError: All dyad and flanking threshold ratios must be at least 1.0");
		exit(1);
		}


	if(!title->count)
		{
		printf("\nError: no track title has been specified with '-t<title>' option");
		exit(1);
		}
	if(strlen(title->sval[0]) >= cMaxDatasetSpeciesChrom)
		{
		printf("\nError: track title '%s' is too long, must be shorter than %d chars",title->sval[0],cMaxDatasetSpeciesChrom-1);
		exit(1);
		}
	strncpy(szTrackTitle,title->sval[0],sizeof(szTrackTitle));
	szTrackTitle[sizeof(szTrackTitle)-1] = '\0';
	CUtility::TrimQuotedWhitespcExtd(szTrackTitle);
	CUtility::ReduceWhitespace(szTrackTitle);
	if(szTrackTitle[0] == '\0')
		{
		printf("\nError: specified track title is empty or whitespace only");
		exit(1);
		}

	strcpy(szInGenomeFile,inGenomefile->filename[0]);
	strcpy(szInConfFile,inConfFile->filename[0]);
	strcpy(szRsltsFile,outfile->filename[0]);

	if(inclRegionFile->count)
		{
		strncpy(szInclRegionFile,inclRegionFile->filename[0],_MAX_PATH);
		szInclRegionFile[_MAX_PATH-1] = '\0';

		OfsLoci = ofsloci->count ? ofsloci->ival[0] : 0;
		if(abs(OfsLoci) > 1024)
			{
			printf("Error: loci offset '-u%d' must be in the range -2048 to +2048",OfsLoci);
			exit(1);
			}

		DeltaLen = deltalen->count ? deltalen->ival[0] : 0;
		if(abs(DeltaLen) > 1024)
			{
			printf("Error: delta length '-U%d' must be in the range -2048 to +2048",DeltaLen);
			exit(1);
			}

		TruncLength = trunclength->count ? trunclength->ival[0] : 147;
		if(TruncLength < 147)
			{
			printf("Error: regions truncation length '-T%d' must be at least 147",TruncLength);
			exit(1);
			}
		}
	else
		{
		szInclRegionFile[0] = '\0';
		OfsLoci = 0;
		DeltaLen = 0;
		TruncLength = 0;
		}
	


		// now that command parameters have been parsed then initialise diagnostics log system
	if(!gDiagnostics.Open(szLogFile,(etDiagLevel)iScreenLogLevel,(etDiagLevel)iFileLogLevel,true))
		{
		printf("\nError: Unable to start diagnostics subsystem.");
		if(szLogFile[0] != '\0')
			printf(" Most likely cause is that logfile '%s' can't be opened/created",szLogFile);
		exit(1);
		}

// show user current resource limits
#ifndef _WIN32
	gDiagnostics.DiagOut(eDLInfo, gszProcName, "Resources: %s",CUtility::ReportResourceLimits());
#endif

	gDiagnostics.DiagOut(eDLInfo,gszProcName,"Version: %d.%2.2d Processing parameters:",cProgVer/100,cProgVer%100);
	const char *pszDescr;
	switch(PMode) {
		case ePMdefault:				
			pszDescr = "Default - predict from minor groove";
			break;
		}

	gDiagnostics.DiagOutMsgOnly(eDLInfo,"processing mode is : '%s'",pszDescr);

	switch(FMode) {
		case eFMbedGraphDyads:				
			pszDescr = "UCSC bedGraph dyads";
			break;
		case eFMbedDyads:					
			pszDescr = "UCSC BED dyads";
			break;
		case eFMcsvDyads:					
			pszDescr = "CSV dyads";
			break;
		case eFMbedGraphNucs:					
			pszDescr = "UCSC bedGraph nucleosomes";
			break;
		case eFMbedNucs:					
			pszDescr = "UCSC BED nucleosomes";
			break;
		case eFMcsvNucs:					
			pszDescr = "CSV nucleosomes";
			break;
		case eFMMcsvScores:					
			pszDescr = "CSV dyad scores along genome";
			break;

		}
	gDiagnostics.DiagOutMsgOnly(eDLInfo,"output format is : '%s'",pszDescr);

	gDiagnostics.DiagOutMsgOnly(eDLInfo,"moving average filter width : %d",MovAvgFilter);
	gDiagnostics.DiagOutMsgOnly(eDLInfo,"baseline noramlisation width : %d",BaselineFilter);

	gDiagnostics.DiagOutMsgOnly(eDLInfo,"dyad name: '%s'",szTrackTitle);

	gDiagnostics.DiagOutMsgOnly(eDLInfo,"dyad minor groove threshold: %1.4f",Dyadratio);
	gDiagnostics.DiagOutMsgOnly(eDLInfo,"dyad immediately flanking minor groove threshold: %1.4f",Dyad2ratio);
	gDiagnostics.DiagOutMsgOnly(eDLInfo,"dyad remainder flanking minor groove threshold: %1.4f",Dyad3ratio);

	gDiagnostics.DiagOutMsgOnly(eDLInfo,"input genome file: '%s'",szInGenomeFile);
	gDiagnostics.DiagOutMsgOnly(eDLInfo,"input conformation file: '%s'",szInConfFile);

	gDiagnostics.DiagOutMsgOnly(eDLInfo,"output predicted nucleosomes file: '%s'",szRsltsFile);
	
	if(szInclRegionFile[0] != '0')
		{
		gDiagnostics.DiagOutMsgOnly(eDLInfo,"Offset region start loci by : %d",OfsLoci);
		gDiagnostics.DiagOutMsgOnly(eDLInfo,"Delta region length by : %d",DeltaLen);
		gDiagnostics.DiagOutMsgOnly(eDLInfo,"Truncate region length: %d",TruncLength);
		gDiagnostics.DiagOutMsgOnly(eDLInfo,"include regions file: '%s'",szInclRegionFile);
		}
#ifdef _WIN32
	SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);
#endif
	gStopWatch.Start();
	Rslt = Process(PMode,FMode,MovAvgFilter,BaselineFilter,szTrackTitle,Dyadratio,Dyad2ratio,Dyad3ratio,szInGenomeFile,szInConfFile,szRsltsFile,
									szInclRegionFile,OfsLoci,DeltaLen,TruncLength);
	gStopWatch.Stop();
	Rslt = Rslt >=0 ? 0 : 1;
	gDiagnostics.DiagOut(eDLInfo,gszProcName,"Exit code: %d Total processing time: %s",Rslt,gStopWatch.Read());
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