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
        cout << "fillInSideChains CONF\n";
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
	    cout << "outpdb /tmp/out.pdb"<<endl<<endl;
	    cout << "# Rotamer library"<<endl;
	    cout << "rotlib /library/rotlib/balanced/rotlib-balanced-200.txt"<<endl<<endl;
	    cout << "# CHARMM Topology"<<endl;
	    cout << "topfile /library/charmmTopPar/top_all27_prot_lipid.inp"<<endl<<endl;
	    cout << "# CHARMM Parameter"<<endl;
	    cout << "parfile /library/charmmTopPar/par_all27_prot_lipid.inp"<<endl<<endl;
	    exit(1);
    }


    opt.pdb = OP.getString("pdb");
    if (OP.fail()){
	    cerr << "ERROR 1111 no pdb file"<<endl;
    }

    opt.rotlib = OP.getString("rotlib");
    if (OP.fail()){
	    cerr << "ERROR 1111 no rotlib file"<<endl;
	    
    }

    opt.topfile = OP.getString("topfile");
    if (OP.fail()){
	    cerr << "ERROR 1111 no topfile file"<<endl;
    }
    opt.parfile = OP.getString("parfile");
    if (OP.fail()){
	    cerr << "ERROR 1111 no parfile file"<<endl;
    }

    opt.outpdb = OP.getString("outpdb");
    if (OP.fail()){
	    opt.outpdb = "/tmp/out.pdb";
	    cerr << "WARNING no outpdb file specifed will write to: "<<opt.outpdb<<endl;
    }

    opt.debug = OP.getBool("debug");
    if (OP.fail()){
	    opt.debug = false;
    }


    
    return opt;
}