void checkOptions(Options& opts, int argc, char** argv) {
	opts.define("d|debug=b",    "Debugging information");
	opts.define("r|remove=b",   "Remove stems");
	opts.define("R|removeall=b","Remove all stems including explicit beams");
	opts.define("o|overwrite|replace=b","Overwrite non-explicit stems in input");
	opts.define("O|overwriteall|replaceall=b",  "Overwrite all stems in input");
	opts.define("L|no-long|not-long|not-longs=b", "Do not put stems one whole notes or breves");
	opts.define("u|up=b",       "Middle note on staff has stem up");
	opts.define("p|pos=b",     "Display only note vertical positions on staves");
	opts.define("v|voice=b",    "Display only voice/layer information");

	opts.define("author=b",     "Program author");
	opts.define("version=b",    "Program version");
	opts.define("example=b",    "Program examples");
	opts.define("h|help=b",     "Short description");
	opts.process(argc, argv);

	// handle basic options:
	if (opts.getBoolean("author")) {
		cout << "Written by Craig Stuart Sapp, "
				  << "[email protected], December 2010" << endl;
		exit(0);
	} else if (opts.getBoolean("version")) {
		cout << argv[0] << ", version: 26 December 2010" << endl;
		cout << "compiled: " << __DATE__ << endl;
		cout << MUSEINFO_VERSION << endl;
		exit(0);
	} else if (opts.getBoolean("help")) {
		usage(opts.getCommand());
		exit(0);
	} else if (opts.getBoolean("example")) {
		example();
		exit(0);
	}

	debugQ        = opts.getBoolean("debug");
	removeQ       = opts.getBoolean("remove");
	removeallQ    = opts.getBoolean("removeall");
	noteposQ      = opts.getBoolean("pos");
	voiceQ        = opts.getBoolean("voice");
	overwriteQ    = opts.getBoolean("overwrite");
	overwriteallQ = opts.getBoolean("overwriteall");
	notlongQ      = opts.getBoolean("no-long");
	if (opts.getBoolean("up")) {
		Middle = 4;
		Borderline = 1;
	}
	removeallQ = opts.getBoolean("removeall");
	if (removeallQ) {
		removeQ = 1;
	}
	if (overwriteallQ) {
		overwriteQ = 1;
	}

}