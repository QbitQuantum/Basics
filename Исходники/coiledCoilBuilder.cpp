Options parseOptions(int _argc, char * _argv[], Options defaults) {

	/******************************************
	 *  Pass the array of argument and the name of
	 *  a configuration file to the ArgumentParser
	 *  object.  Then ask for the value of the argument
	 *  and collect error and warnings.
	 *
	 *  This function returns a Options structure
	 *  defined at the head of this file 
	 ******************************************/
	
	Options opt;

	/******************************************
	 *  Set the allowed and required options:
	 *
	 *  Example of configuartion file:
	 *  
	 ******************************************/
	vector<string> required;
	vector<string> allowed;

	opt.required.push_back("sequence");
	opt.required.push_back("startPos");
	opt.required.push_back("startRegPos");

	opt.required.push_back("r0_start");
	opt.required.push_back("r0_end");
	opt.required.push_back("r0_step");
	opt.required.push_back("r1_start");
	opt.required.push_back("r1_end");
	opt.required.push_back("r1_step");
	opt.required.push_back("w1_start");
	opt.required.push_back("w1_end");
	opt.required.push_back("w1_step");
	opt.required.push_back("phi1_start");
	opt.required.push_back("phi1_end");
	opt.required.push_back("phi1_step");
	opt.required.push_back("rpr_start");
	opt.required.push_back("rpr_end");
	opt.required.push_back("rpr_step");
	opt.required.push_back("pitch_start");
	opt.required.push_back("pitch_end");
	opt.required.push_back("pitch_step");

	opt.required.push_back("nRes");
	opt.required.push_back("symmetry");
	opt.required.push_back("N");

	//opt.required.push_back("testNo");
	opt.allowed.push_back("setState");
	opt.allowed.push_back("rotamerStates");

	opt.allowed.push_back("rotamerSamplingSize");
	opt.allowed.push_back("seed");
	opt.required.push_back("rotamerLibrary"); //filename of rotamer library file
	opt.allowed.push_back("outputdir");
	opt.allowed.push_back("outputfile"); //filename of output file
	opt.allowed.push_back("version"); // --version
	opt.allowed.push_back("v"); // -v is equivalent to --version
	opt.allowed.push_back("help"); // --help
	opt.allowed.push_back("h"); // -h is equivalent to --help
	opt.allowed.push_back("configfile");

	opt.allowed.push_back("runDEE");
	opt.allowed.push_back("runEnum");
	opt.allowed.push_back("runSCMF");
	opt.allowed.push_back("runMCO");

	opt.equivalent.push_back(vector<string>());
	opt.equivalent.back().push_back("v");
	opt.equivalent.back().push_back("version");
	opt.equivalent.push_back(vector<string>());
	opt.equivalent.back().push_back("h");
	opt.equivalent.back().push_back("help");

	opt.defaultArgs.push_back("configfile");


	//OptionParser OP(_argc, _argv);
	OptionParser OP;
	OP.setShortOptionEquivalent(opt.equivalent);
	OP.readArgv(_argc, _argv);
	OP.setDefaultArguments(opt.defaultArgs); // a pdb file value can be given as a default argument without the --pdbfile option
	OP.setRequired(opt.required);
	OP.setAllowed(opt.allowed);
	OP.autoExtendOptions(); // if you give option "solvat" it will be autocompleted to "solvationfile"
	if (OP.countOptions() == 0) {
		usage();
		exit(0);
	}
	opt.configfile = OP.getString("configfile");
	if (opt.configfile != "") {
		OP.readFile(opt.configfile);
		if (OP.fail()) {
			opt.errorFlag = true;
			opt.errorMessages += "Cannot read configuration file " + opt.configfile + "\n";
			exit(1);
		}
	}

	/*****************************************
	 *  VERSION AND HELP
	 *
	 *  --version or -v arguments print the version number
	 *  --help prints the usage and help
	 *****************************************/
	opt.version = OP.getBool("version");
	//if (OP.fail()) {
	//	opt.version = OP.getBool("v");
	//}

	if (opt.version) {
		version();
		exit(0);
	}

	opt.help = OP.getBool("help");
//	if (OP.fail()) {
//		opt.help = OP.getBool("h");
//	}

	if (opt.help) {
		help(defaults);
		exit(0);
	}

	/*****************************************
	 *  CHECK THE GIVEN OPTIONS
	 *****************************************/
	if (!OP.checkOptions()) {
		opt.errorFlag = true;
		opt.OPerrors = OP.getErrors();
		return opt;
	}
	opt.errorFlag = false;
	opt.warningFlag = false;

	/*****************************************
	 *  OUTPUT DIR AND FILES
	 *****************************************/
	opt.outputdir = OP.getString("outputdir");
	if (OP.fail() || opt.outputdir == "") {
		opt.outputdir = defaults.outputdir;
	}
	
	opt.outputfile = OP.getString("outputfile");
	if (OP.fail()) {
		opt.outputfile = defaults.outputfile;
	}
	if (opt.outputfile != "" && opt.outputfile != "STDOUT") {
		opt.coutRedirected = true;
		opt.cout_fs = new ofstream();
		opt.cerr_fs = new ofstream();
	} else {
		opt.coutRedirected = false;
		opt.cout_fs = NULL;
		opt.cerr_fs = NULL;
	}


	/*****************************************
	 *  CHECK THE GIVEN OPTIONS
	 *****************************************/
	//opt.commandName = OP.getCommandName();
	//if (!OP.checkOptions()) {
	//	opt.errorFlag = true;
	//	opt.disallowed = OP.getDisallowedOptions();
	//	opt.missing = OP.getMissingOptions();
	//	opt.ambiguous = OP.getAmbiguousOptions();
	//	return opt;
	//}
	opt.errorFlag = false;
	opt.warningFlag = false;

	opt.sequence= OP.getString("sequence");
	if (OP.fail()) {
		opt.errorMessages = "sequence not specified";
		opt.errorFlag = true;
	}
	opt.startPos = OP.getStringVector("startPos");
	if (OP.fail()) {
		opt.errorMessages = "startPos not specified";
		opt.errorFlag = true;
	}
	opt.startRegPos = OP.getString("startRegPos");
	if (OP.fail()) {
		opt.errorMessages = "startRegPos not specified";
		opt.errorFlag = true;
	}
	opt.r0_start = OP.getDouble("r0_start");
	if (OP.fail()) {
		opt.errorMessages = "r0 not specified";
		opt.errorFlag = true;
	}
	opt.r0_end = OP.getDouble("r0_end");
	if (OP.fail()) {
		opt.errorMessages = "r0 not specified";
		opt.errorFlag = true;
	}
	opt.r0_step = OP.getDouble("r0_step");
	if (OP.fail()) {
		opt.errorMessages = "r0 not specified";
		opt.errorFlag = true;
	}
	opt.r1_start = OP.getDouble("r1_start");
	if (OP.fail()) {
		opt.errorMessages = "r1 not specified";
		opt.errorFlag = true;
	}
	opt.r1_end = OP.getDouble("r1_end");
	if (OP.fail()) {
		opt.errorMessages = "r1 not specified";
		opt.errorFlag = true;
	}
	opt.r1_step = OP.getDouble("r1_step");
	if (OP.fail()) {
		opt.errorMessages = "r1 not specified";
		opt.errorFlag = true;
	}
	opt.w1_start = OP.getDouble("w1_start");
	if (OP.fail()) {
		opt.errorMessages = "w1 not specified";
		opt.errorFlag = true;
	}
	opt.w1_end = OP.getDouble("w1_end");
	if (OP.fail()) {
		opt.errorMessages = "w1 not specified";
		opt.errorFlag = true;
	}
	opt.w1_step = OP.getDouble("w1_step");
	if (OP.fail()) {
		opt.errorMessages = "w1 not specified";
		opt.errorFlag = true;
	}
	opt.phi1_start = OP.getDouble("phi1_start");
	if (OP.fail()) {
		opt.errorMessages = "phi1 not specified";
		opt.errorFlag = true;
	}
	opt.phi1_end = OP.getDouble("phi1_end");
	if (OP.fail()) {
		opt.errorMessages = "phi1 not specified";
		opt.errorFlag = true;
	}
	opt.phi1_step = OP.getDouble("phi1_step");
	if (OP.fail()) {
		opt.errorMessages = "phi1 not specified";
		opt.errorFlag = true;
	}
	opt.rpr_start = OP.getDouble("rpr_start");
	if (OP.fail()) {
		opt.errorMessages = "rpr not specified";
		opt.errorFlag = true;
	}
	opt.rpr_end = OP.getDouble("rpr_end");
	if (OP.fail()) {
		opt.errorMessages = "rpr not specified";
		opt.errorFlag = true;
	}
	opt.rpr_step = OP.getDouble("rpr_step");
	if (OP.fail()) {
		opt.errorMessages = "rpr not specified";
		opt.errorFlag = true;
	}
	opt.pitch_start = OP.getDouble("pitch_start");
	if (OP.fail()) {
		opt.errorMessages = "pitch not specified";
		opt.errorFlag = true;
	}
	opt.pitch_end = OP.getDouble("pitch_end");
	if (OP.fail()) {
		opt.errorMessages = "pitch not specified";
		opt.errorFlag = true;
	}
	opt.pitch_step = OP.getDouble("pitch_step");
	if (OP.fail()) {
		opt.errorMessages = "pitch not specified";
		opt.errorFlag = true;
	}
	opt.nRes = OP.getInt("nRes");
	if (OP.fail()) {
		opt.errorMessages = "number of residues not specified";
		opt.errorFlag = true;
	}
	opt.symmetry = OP.getString("symmetry");
	if (OP.fail()) {
		opt.errorMessages = "symmetry not specified";
		opt.errorFlag = true;
	}
	opt.N = OP.getInt("N");
	if (OP.fail()) {
		opt.errorMessages = "N not specified";
		opt.errorFlag = true;
	}
	opt.rotamerLibrary = OP.getString("rotamerLibrary");
	if (OP.fail()) {
		opt.errorMessages = "rotamerLibrary not specified";
		opt.errorFlag = true;
	}
	opt.outputfile = OP.getString("outputfile");
	if (OP.fail()) {
		opt.errorMessages = "outputfile not specified";
		opt.errorFlag = true;
	}

	/*
	opt.testNo = OP.getInt("testNo");
	if (OP.fail()) {
		opt.errorMessages = "testNo not specified";
		opt.errorFlag = true;
	}
	*/

	opt.rotamerSamplingSize = OP.getString("rotamerSamplingSize");
	opt.seed = OP.getInt("seed");
	opt.runDEE = OP.getBool("runDEE");
	opt.runEnum = OP.getBool("runEnum");
	opt.runSCMF = OP.getBool("runSCMF");
	opt.runMCO = OP.getBool("runMCO");
	opt.setState = OP.getBool("setState");
	opt.rotamerStates = OP.getUnsignedIntVector("rotamerStates");

	opt.rerunConf = "########################################################\n";
	opt.rerunConf += "#  This configuration file was automatically generated,\n";
	opt.rerunConf += "#  it will rerun this job with the same options. Run as:\n";
	opt.rerunConf += "#\n";
	opt.rerunConf += "#  Run as:\n";
	opt.rerunConf += "#\n";
	opt.rerunConf += "#    % " + programName + " --configfile " + opt.rerunConfFile + "\n";
	opt.rerunConf += "#\n";
	opt.rerunConf += "#  Job started on " + (string)ctime(&start_time);
	opt.rerunConf += "#  on host " + opt.host + ", path " + opt.pwd + "\n";
	if (opt.seed == 0) {
		opt.rerunConf += "#  seed " + MslTools::intToString(opt.seed) + " (time based)\n";
	} else {
		opt.rerunConf += "#  seed " + MslTools::intToString(opt.seed) + "\n";
	} 
	opt.rerunConf += "########################################################\n";
	opt.rerunConf += "\n";
	opt.rerunConf += OP.getConfFile();

	// return the Options structure
	return opt;

}