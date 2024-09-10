Options setupOptions(int theArgc, char * theArgv[]){
  Options opt;

  OptionParser OP;


  OP.setRequired(opt.required);
  OP.setAllowed(opt.optional);
  OP.setDefaultArguments(opt.defaultArgs); // a pdb file value can be given as a default argument without the --pdbfile option
  OP.autoExtendOptions(); // if you give option "solvat" it will be autocompleted to "solvationfile"
  OP.readArgv(theArgc, theArgv);

  if (OP.countOptions() == 0){
    cout << "Usage:" << endl;
    cout << endl;
    cout << "addSequenceConservation --pdb PDB --fasta FASTA_FILE --refCounts REF_COUNTS_FILE\n";
    exit(0);
  }


  opt.configfile = OP.getString("configfile");
  if (opt.configfile != "") {
    OP.readFile(opt.configfile);
    if (OP.fail()) {
      cerr << "ERROR couldn't read : "<<opt.configfile<<endl;
      exit(1);
    }
  }

  opt.fasta = OP.getString("fasta");
  if (OP.fail()){
    cerr << "ERROR 1111 fasta not specified.\n";
    exit(1111);
  }

  opt.refSeqName = OP.getString("refSeqName");
  if (OP.fail()){
    cerr << "WARNING 1111 refSeqName not specified.\n";
    opt.refSeqName = "";
  } 

  opt.seq = OP.getString("seq");
  if (OP.fail()){
    opt.seq = "";
  }

  if (opt.seq == ""){
    opt.pdb = OP.getString("pdb");
    if (OP.fail()){
      cerr << "ERROR 1111 pdb not specified.\n";
      exit(1111);
    }


    opt.refAACounts = OP.getString("refAACounts");
    if (OP.fail()){
      cerr << "ERROR 1111 refAACounts not specified.\n";
      exit(1111);
    }

    opt.sel = OP.getString("sel");
    if (OP.fail()){
      cerr << "ERROR 1111 sel not specified.\n";
      exit(1111);
    }




    opt.refSeqOffset = OP.getInt("refSeqOffset");
    if (OP.fail()){
      cerr << "WARNING 1111 refSeqOffset not specified.\n";
      opt.refSeqOffset = 0;
    }
    opt.freq = OP.getBool("freq");
    if (OP.fail()){
      opt.freq = false;
    }

    opt.applyToAllChains = OP.getBool("applyToAllChains");
    if (OP.fail()){
      opt.applyToAllChains = false;
    }

    opt.regexForFasta = OP.getString("regexForFasta");
    if (OP.fail()){
      opt.regexForFasta = "";
    }

    opt.outPdb = OP.getString("outPdb");
    if (OP.fail()){
      opt.outPdb = MslTools::stringf("%s_seqcons.pdb",MslTools::getFileName(opt.pdb).c_str());
      cerr << "WARNING --outPdb is set to : "<<opt.outPdb<<endl;
    }

  }



  return opt;
}