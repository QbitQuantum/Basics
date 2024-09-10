void checkOptions(Options& opts, int argc, char* argv[]) {
	opts.define("t|test=b", "check to see if there are tie errors in the file");
	opts.define("debug=b");           // determine bad input line num
	opts.define("author=b");          // author of program
	opts.define("version=b");         // compilation info
	opts.define("example=b");         // example usages
	opts.define("h|help=b");          // short description
	opts.process(argc, argv);

	// handle basic options:
	if (opts.getBoolean("author")) {
		cout << "Written by Craig Stuart Sapp, "
			  << "[email protected], May 2004" << endl;
		exit(0);
	} else if (opts.getBoolean("version")) {
		cout << argv[0] << ", version: 3 May 2018" << endl;
		cout << "compiled: " << __DATE__ << endl;
		cout << MUSEINFO_VERSION << endl;
		exit(0);
	} else if (opts.getBoolean("help")) {
		usage(opts.getCommand().data());
		exit(0);
	} else if (opts.getBoolean("example")) {
		example();
		exit(0);
	}

	testQ = opts.getBoolean("test");
}