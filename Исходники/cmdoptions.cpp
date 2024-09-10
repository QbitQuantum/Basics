// parse command line options
void parsecmdoptions(int argc, char *argv[], Cmdopt* cmdopt) {


  if (argc < 7) {                              // no enough arguments
    buildcontighelp();
    exit(1);
  }


  bool tag = false;
  for (int i = 1; i < argc; i += 2) {        // read each option
    
    if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--mapfile") == 0) {          // read mapping file
      cmdopt->mapfile = argv[i+1];
      cmdopt->filetype = "map";
    }
    
    else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--samfile") == 0) {          // read mapping file
      cmdopt->mapfile = argv[i+1];
      cmdopt->filetype = "sam";
    }
    
    else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--refseq") == 0)     // ref seq file
      cmdopt->reffile = argv[i+1];
    
    else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--prefix") == 0)     // output prefix
      cmdopt->outprefix = argv[i+1];

    else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--mincov") == 0) {   // min depcov for outputing contigs
      if (atoi(argv[i+1]) < 1)
	tag = true;
      cmdopt->mindepcov = atoi(argv[i+1]);
    }

    else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--minlen") == 0) {   // min length for outputing contigs
      if (atoi(argv[i+1]) < 1)
	tag = true;
      cmdopt->minlen = atoi(argv[i+1]);
    }

    else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--thread") == 0) {   // min length for outputing contigs
      if (atoi(argv[i+1]) < 1)
	tag = true;
      cmdopt->nump = atoi(argv[i+1]);
    }

    else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--prof") == 0) {   // print .baseprof file or not
      if (argv[i+1][0] == 'T') 
	cmdopt->printbaseprof = true;
      else if (argv[i+1][0] == 'F') 
	cmdopt->printbaseprof = false;
      else
	tag = true;
    }

    else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--newref") == 0) {   // print .newref file or not
      if (argv[i+1][0] == 'T') 
	cmdopt->printnewref = true;
      else if (argv[i+1][0] == 'F') 
	cmdopt->printnewref = false;
      else
	tag = true;
    }

    else if (strcmp(argv[i], "-u") == 0 || strcmp(argv[i], "--usedmap") == 0) {   // print .usedmap file or not
      if (argv[i+1][0] == 'T') 
	cmdopt->printusedmap = true;
      else if (argv[i+1][0] == 'F') 
	cmdopt->printusedmap = false;
      else
	tag = true;
    }

    else if (strcmp(argv[i], "-k") == 0 || strcmp(argv[i], "--pickref") == 0) {   // how to pick ref seq
      if (strcmp(argv[i+1], "all") == 0) 
	cmdopt->pickref = "all";
      else if (strcmp(argv[i+1], "breadth") == 0) 
	cmdopt->pickref = "breadth";
      else if (strcmp(argv[i+1], "random") == 0) 
	cmdopt->pickref = "random";
      else if (strcmp(argv[i+1], "depth") == 0) 
	cmdopt->pickref = "depth";
      else
	tag = true;
    }
    
    else                                     // does not match, then something goes wrong
      tag = true;
  }


  // these parameters must be specified
  if (cmdopt->mapfile == "" || cmdopt->reffile == "" || cmdopt->outprefix == "")
    tag = true;

  if (tag) {
    buildcontighelp();
    exit(1);
  }
}