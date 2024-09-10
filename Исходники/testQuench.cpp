Options setupOptions(int theArgc, char * theArgv[]){
	Options opt;

	OptionParser OP;

	OP.readArgv(theArgc, theArgv);
	OP.setRequired(opt.required);
	OP.setAllowed(opt.optional);

	if (OP.countOptions() == 0){
		cout << "Usage:" << endl;
		cout << endl;
		cout << "testQuench --pdb PDB\n";
		exit(0);
	}

	opt.pdb  = OP.getString("pdb");
	if (OP.fail()){
		cerr << "ERROR 1111 pdb not specified.\n";
		exit(1111);
	}

	opt.topfile = OP.getString("topfile");
	if (OP.fail()){
		cerr << "WARNING no topfile specified, using default "<<SYSENV.getEnv("MSL_CHARMM_TOP")<<endl;
		opt.topfile = SYSENV.getEnv("MSL_CHARMM_TOP");
	}

	opt.parfile = OP.getString("parfile");
	if (OP.fail()){
		cerr << "WARNING no parfile specified, using default "<<SYSENV.getEnv("MSL_CHARMM_PAR")<<endl;
		opt.parfile = SYSENV.getEnv("MSL_CHARMM_PAR");
	}

	opt.rotlib = OP.getString("rotlib");
	if (OP.fail()){
		cerr << "WARNING no rotlib specified, using default "<<SYSENV.getEnv("MSL_ROTLIB")<<endl;
		opt.rotlib = SYSENV.getEnv("MSL_ROTLIB");
	}

	return opt;
}