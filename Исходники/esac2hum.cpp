void checkOptions(Options& opts, int argc, char* argv[]) {
	opts.define("debug=b",      "print debug information");
	opts.define("v|verbose=b",  "verbose output");
	opts.define("h|header=s:",  "Header filename for placement in output");
	opts.define("t|trailer=s:", "Trailer filename for placement in output");
	opts.define("s|split=s:file", "Split song info into separate files");
	opts.define("x|extension=s:.krn", "Split filename extension");
	opts.define("f|first=i:1",    "Number of first split filename");

	opts.define("author=b",  "author of program");
	opts.define("version=b", "compilation info");
	opts.define("example=b", "example usages");
	opts.define("help=b",  "short description");
	opts.process(argc, argv);

	// handle basic options:
	if (opts.getBoolean("author")) {
		cout << "Written by Craig Stuart Sapp, "
			  << "[email protected], March 2002" << endl;
		exit(0);
	} else if (opts.getBoolean("version")) {
		cout << argv[0] << ", version: 5 March 2002" << endl;
		cout << "compiled: " << __DATE__ << endl;
		cout << MUSEINFO_VERSION << endl;
		exit(0);
	} else if (opts.getBoolean("help")) {
		usage(opts.getCommand().c_str());
		exit(0);
	} else if (opts.getBoolean("example")) {
		example();
		exit(0);
	}

	debugQ      = opts.getBoolean("debug");
	verboseQ    = opts.getBoolean("verbose");

	if (opts.getBoolean("header")) {
		getFileContents(header, opts.getString("header").c_str());
	} else {
		header.resize(0);
	}
	if (opts.getBoolean("trailer")) {
		getFileContents(trailer, opts.getString("trailer").c_str());
	} else {
		trailer.resize(0);
	}

	if (opts.getBoolean("split")) {
		splitQ = 1;
	}
	strcpy(namebase, opts.getString("split").c_str());
	strcpy(fileextension, opts.getString("extension").c_str());
	firstfilenum = opts.getInteger("first");

}