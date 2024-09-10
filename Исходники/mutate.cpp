Options setupOptions(int theArgc, char * theArgv[]){

    // Create the options
    Options opt;
    

    // Parse the options
    OptionParser OP;
    OP.readArgv(theArgc, theArgv);
    OP.setRequired(opt.required);    
    OP.setAllowed(opt.optional);
    //    OP.setShortOptionEquivalent(opt.equivalent);
    OP.setDefaultArguments(opt.defaultArgs); // the default argument is the --configfile option
    OP.autoExtendOptions(); // if you give option "solvat" it will be autocompleted to "solvationfile"


    if (OP.countOptions() == 0){
        cout << "Usage:" << endl;
        cout << endl;
        cout << "mutate CONF\n";
        exit(0);
    }

    opt.configfile = OP.getString("configfile");
    
    if (opt.configfile != "") {
        OP.readFile(opt.configfile);
        if (OP.fail()) {
            string errorMessages = "Cannot read configuration file " + opt.configfile + "\n";
            cerr << "ERROR 1111 "<<errorMessages<<endl;
        }
    }

    if (OP.getBool("help")){

	    cout << "# PDB "<<endl;	
	    cout << "pdb foo.pdb"<<endl<<endl;
	    cout << "# Output pdb" <<endl;
	    cout << "outpdb /tmp/out"<<endl<<endl;
	    cout << "# Rotamer library"<<endl;
	    cout << "rotlib /library/rotlib/balanced/rotlib-balanced-200.txt"<<endl<<endl;
	    cout << "# Position"<<endl;
	    cout << "position B,2"<<endl;
	    cout << "# New residue"<<endl;
	    cout << "newRes PHE"<<endl<<endl;
	    cout << "# Number of rotamers"<<endl;
	    cout << "numRot 10"<<endl<<endl;
	    exit(1);
    }


    opt.pdb = OP.getString("pdb");
    if (OP.fail()){
	    cerr << "ERROR 1111 no pdb file"<<endl;
    }

    opt.rotlib = OP.getString("rotlib");
    if (OP.fail()){
	    cerr << "ERROR 1111 no rotlib file"<<endl;
	    exit(1111);
    }

    opt.position = OP.getString("position");
    if (OP.fail()){
	    cerr << "ERROR 1111 no position"<<endl;
	    exit(1111);
    }
    opt.newRes = OP.getString("newRes");
    if (OP.fail()){
	    cerr << "ERROR 1111 no new residue (newRes)"<<endl;
	    exit(1111);
    }

    opt.outpdb = OP.getString("outpdb");
    if (OP.fail()){
	    opt.outpdb = "/tmp/out";
	    cerr << "WARNING no outpdb file specifed will write to: "<<opt.outpdb<<endl;
    }

    opt.numRot = OP.getInt("numRot");
    if (OP.fail()){
	    cerr << "numRot defaults to 10"<<endl;
	    opt.numRot = 10;
    }
    opt.debug = OP.getBool("debug");
    if (OP.fail()){
	    opt.debug = false;
    }


    
    return opt;
}