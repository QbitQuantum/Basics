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

    opt.required.push_back("pdb");
    opt.required.push_back("type");
    opt.required.push_back("atomNames");
    opt.required.push_back("value");
    opt.allowed.push_back("outputPdb");
    //opt.allowed.push_back("outputdir");
    opt.allowed.push_back("configfile");
    opt.allowed.push_back("version"); // --version
    opt.allowed.push_back("v"); // -v is equivalent to --version
    opt.allowed.push_back("help"); // --help
    opt.allowed.push_back("h"); // -h is equivalent to --help

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


    opt.pdb = OP.getString("pdb");
    if (OP.fail()) {
        opt.errorMessages = "Option name of first pdb file \"pdb\" not specified";
        opt.errorFlag = true;
    }

    opt.outputPdb = OP.getString("outputPdb");
    if (OP.fail()) {
        opt.warningMessages = "Option name of output edited pdb file \"outputPdb\" not specified";
        opt.warningFlag = true;
        string base = MslTools::pathTail(opt.pdb);
        base = MslTools::pathRoot(base);
        opt.outputPdb = base + (string)"-edited.pdb";
    }

    int index = 0;
    while (true) {
        DoF tmp;
        tmp.type = OP.getString("type", index);
        if (OP.fail()) {
            break;
        }
        tmp.atomNames = OP.getStringVector("atomNames", index);
        if (OP.fail()) {
            break;
        }
        tmp.value = OP.getDouble("value", index);
        if (OP.fail()) {
            break;
        }
        opt.edits.push_back(tmp);
        index++;
    }

    // return the Options structure
    return opt;

}