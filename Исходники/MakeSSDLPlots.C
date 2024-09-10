//_____________________________________________________________________________________
int main(int argc, char* argv[]) {
// Default options
	TString outputdir = "SSDLPlots/";
	TString datacard  = "DataCard_SSDL.dat";
	int verbose = 0;
	TString configfile;
	bool cfg = false;
	TString region = "";

// Parse options
	char ch;
	while ((ch = getopt(argc, argv, "d:c:v:m:s:p:lh?")) != -1 ) {
		switch (ch) {
			case 'd': outputdir = TString(optarg); break;
			case 'v': verbose = atoi(optarg); break;
			case 'c': datacard = TString(optarg); break;
			case 'p': configfile = TString(optarg); break;
			case 's': region = TString(optarg); break; 
			case '?':
			case 'h': usage(0); break;
			default:
			cerr << "*** Error: unknown option " << optarg << std::endl;
			usage(-1);
		}
	}

	if(configfile.Length() > 0) {
		cfg = true;
		cout << "Using specified config file: " << configfile << endl;
	}
	else cout << "Using default configuration file: " << outputdir << "/dumperconfig.cfg"<< endl;

	cout << "--------------" << endl;
	cout << "OutputDir is:      " << outputdir << endl;
	cout << "Verbose level is:  " << verbose << endl;
	cout << "--------------" << endl;

	SSDLPlotter *tA;
	if (cfg) tA = new SSDLPlotter(configfile);
	else tA = new SSDLPlotter(outputdir+"/dumperconfig.cfg");
	tA->setOutputDir(outputdir);
	tA->setVerbose(verbose);
	tA->init(datacard);
	tA->doAnalysis();
	if (region != "")	
	  tA->doSMSscans(region);

	delete tA;
	return 0;
}