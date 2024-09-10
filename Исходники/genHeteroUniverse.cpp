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

	opt.required.push_back("pdbFile");
	opt.required.push_back("helicalAxisPdbFile");
	opt.required.push_back("output");

	opt.required.push_back("xShiftStart");
	opt.required.push_back("xShiftEnd");
	opt.required.push_back("xShiftSteps");

	opt.required.push_back("zShiftAStart");
	opt.required.push_back("zShiftAEnd");
	opt.required.push_back("zShiftASteps");

	opt.required.push_back("zShiftBStart");
	opt.required.push_back("zShiftBEnd");
	opt.required.push_back("zShiftBSteps");

	opt.required.push_back("axialRotAStart");
	opt.required.push_back("axialRotAEnd");
	opt.required.push_back("axialRotASteps");

	opt.required.push_back("axialRotBStart");
	opt.required.push_back("axialRotBEnd");
	opt.required.push_back("axialRotBSteps");

	opt.required.push_back("crossingAngleStart");
	opt.required.push_back("crossingAngleEnd");
	opt.required.push_back("crossingAngleSteps");

	//opt.required.push_back("rotCount");

	opt.required.push_back("topFile");
	opt.required.push_back("parFile");
	opt.required.push_back("solvFile");
	opt.required.push_back("hBondFile");

	//opt.equivalent.push_back(vector<string>());
	//opt.equivalent.back().push_back("v");
	//opt.equivalent.back().push_back("version");
	//opt.equivalent.push_back(vector<string>());
	//opt.equivalent.back().push_back("h");
	//opt.equivalent.back().push_back("help");

	//opt.defaultArgs.push_back("configfile");


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


	/*****************************************
	 *  CHECK THE GIVEN OPTIONS
	 *****************************************/
	opt.errorFlag = false;
	opt.warningFlag = false;

	opt.pdbFile = OP.getString("pdbFile");
	if (OP.fail()) {
		opt.errorMessages = "pdb file not specified";
		opt.errorFlag = true;
	}
	opt.helicalAxisPdbFile = OP.getString("helicalAxisPdbFile");
	if (OP.fail()) {
		opt.errorMessages = "helicalAxisPdbFile file not specified";
		opt.errorFlag = true;
	}
	opt.output = OP.getString("output");
	if (OP.fail()) {
		opt.errorMessages = "output not specified";
		opt.errorFlag = true;
	}
	opt.xShiftStart = OP.getDouble("xShiftStart");
	if (OP.fail()) {
		opt.errorMessages = "xShiftStart not specified";
		opt.errorFlag = true;
	}
	opt.xShiftEnd = OP.getDouble("xShiftEnd");
	if (OP.fail()) {
		opt.errorMessages = "xShiftEnd not specified";
		opt.errorFlag = true;
	}
	opt.xShiftSteps = OP.getDouble("xShiftSteps");
	if (OP.fail()) {
		opt.errorMessages = "xShiftSteps not specified";
		opt.errorFlag = true;
	}

	opt.zShiftAStart = OP.getDouble("zShiftAStart");
	if (OP.fail()) {
		opt.errorMessages = "zShiftAStart not specified";
		opt.errorFlag = true;
	}
	opt.zShiftAEnd = OP.getDouble("zShiftAEnd");
	if (OP.fail()) {
		opt.errorMessages = "zShiftAEnd not specified";
		opt.errorFlag = true;
	}
	opt.zShiftASteps = OP.getDouble("zShiftASteps");
	if (OP.fail()) {
		opt.errorMessages = "zShiftASteps not specified";
		opt.errorFlag = true;
	}

	opt.zShiftBStart = OP.getDouble("zShiftBStart");
	if (OP.fail()) {
		opt.errorMessages = "zShiftBStart not specified";
		opt.errorFlag = true;
	}
	opt.zShiftBEnd = OP.getDouble("zShiftBEnd");
	if (OP.fail()) {
		opt.errorMessages = "zShiftBEnd not specified";
		opt.errorFlag = true;
	}
	opt.zShiftBSteps = OP.getDouble("zShiftBSteps");
	if (OP.fail()) {
		opt.errorMessages = "zShiftBSteps not specified";
		opt.errorFlag = true;
	}

	opt.axialRotAStart = OP.getDouble("axialRotAStart");
	if (OP.fail()) {
		opt.errorMessages = "axialRotAStart not specified";
		opt.errorFlag = true;
	}
	opt.axialRotAEnd = OP.getDouble("axialRotAEnd");
	if (OP.fail()) {
		opt.errorMessages = "axialRotAEnd not specified";
		opt.errorFlag = true;
	}
	opt.axialRotASteps = OP.getDouble("axialRotASteps");
	if (OP.fail()) {
		opt.errorMessages = "axialRotASteps not specified";
		opt.errorFlag = true;
	}

	opt.axialRotBStart = OP.getDouble("axialRotBStart");
	if (OP.fail()) {
		opt.errorMessages = "axialRotBStart not specified";
		opt.errorFlag = true;
	}
	opt.axialRotBEnd = OP.getDouble("axialRotBEnd");
	if (OP.fail()) {
		opt.errorMessages = "axialRotBEnd not specified";
		opt.errorFlag = true;
	}
	opt.axialRotBSteps = OP.getDouble("axialRotBSteps");
	if (OP.fail()) {
		opt.errorMessages = "axialRotBSteps not specified";
		opt.errorFlag = true;
	}

	opt.crossingAngleStart = OP.getDouble("crossingAngleStart");
	if (OP.fail()) {
		opt.errorMessages = "crossingAngleStart not specified";
		opt.errorFlag = true;
	}
	opt.crossingAngleEnd = OP.getDouble("crossingAngleEnd");
	if (OP.fail()) {
		opt.errorMessages = "crossingAngleEnd not specified";
		opt.errorFlag = true;
	}
	opt.crossingAngleSteps = OP.getDouble("crossingAngleSteps");
	if (OP.fail()) {
		opt.errorMessages = "crossingAngleSteps not specified";
		opt.errorFlag = true;
	}

	opt.topFile = OP.getString("topFile");
	if (OP.fail()) {
		opt.errorMessages = "topFile not specified";
		opt.errorFlag = true;
	}
	opt.parFile = OP.getString("parFile");
	if (OP.fail()) {
		opt.errorMessages = "parFile not specified";
		opt.errorFlag = true;
	}
	opt.solvFile = OP.getString("solvFile");
	if (OP.fail()) {
		opt.errorMessages = "solvFile not specified";
		opt.errorFlag = true;
	}
	opt.hBondFile = OP.getString("hBondFile");
	if (OP.fail()) {
		opt.errorMessages = "hBondFile not specified";
		opt.errorFlag = true;
	}
	// return the Options structure
	return opt;

}