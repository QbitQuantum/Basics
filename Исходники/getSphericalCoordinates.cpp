Options setupOptions(int theArgc, char * theArgv[]){

	// Create the options
	Options opt;
	
	// Parse the options
	OptionParser OP;
	OP.readArgv(theArgc, theArgv);
	OP.setRequired(opt.required);	
	OP.setDefaultArguments(opt.defaultArgs); // the default argument is the --configfile option

	if (OP.countOptions() == 0){
		cout << "Usage: getSphericalCoordinates conf" << endl;
		cout << endl;
		cout << "\n";
		cout << "pdb PDB\n";
		cout << endl;
		exit(0);
	}

	opt.configFile = OP.getString("configfile");
	
	if (opt.configFile != "") {
		OP.readFile(opt.configFile);
		if (OP.fail()) {
			string errorMessages = "Cannot read configuration file " + opt.configFile + "\n";
			cerr << "ERROR 1111 "<<errorMessages<<endl;
		}
	}

	opt.pdb = OP.getString("pdb");
	if (OP.fail()){
		cerr << "ERROR 1111 no pdb specified."<<endl;
		exit(1111);
	}

	opt.resnum = OP.getInt("resnum");
	if (OP.fail()){
		cerr << "ERRROR 1111 no resnum\n";
		exit(1111);
	}

	opt.chain = OP.getString("chain");
	if (OP.fail()){
		cerr << "ERRROR 1111 no chain\n";
		exit(1111);
	}

	opt.negativeRes = OP.getBool("neg");
        if (OP.fail()){
                opt.negativeRes = false;
        }

        if (opt.negativeRes) {
                opt.resnum = -1*opt.resnum;
        }

	opt.printFrames = OP.getBool("printFrames");
	return opt;
}