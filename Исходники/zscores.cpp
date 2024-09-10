void checkOptions(Options& opts, int argc, char* argv[]) {
	opts.define("m|mean=d:0.0", "use this mean rather than calculated one");
	opts.define("d|sd=d:0.0",   "use this SD rather than calculated one");
	opts.define("a|append=b",   "append output data to input");
	opts.define("p|prepend=b",  "prepend output data to input");
	opts.define("r|raw=b",      "raw output display");
	opts.define("sample=b",     "use sample rather than population SD");
	opts.define("replace=b",    "raw output display");
	opts.define("s|stat=b",     "display analyzed statistics");
	opts.define("S|suppress=b", "suppress display of statistics in output");
	opts.define("reverse=b",    "reverse z-score calculation process");
	opts.define("f|field=i:0",  "spine number to process");
	opts.define("i|input=b",    "display only extract values");
	opts.define("full=b",       "display only extract values with locations");

	opts.define("author=b",  "author of program");
	opts.define("version=b", "compilation info");
	opts.define("example=b", "example usages");
	opts.define("help=b",  "short description");
	opts.process(argc, argv);

	// handle basic options:
	if (opts.getBoolean("author")) {
			cout << "Written by Craig Stuart Sapp, "
			     << "[email protected], Jan 2008" << endl;
			exit(0);
	} else if (opts.getBoolean("version")) {
			cout << argv[0] << ", version: 12 Jan 2002" << endl;
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

	field     = opts.getInteger("field");
	inputQ    = opts.getBoolean("input");
	fullQ     = opts.getBoolean("full");
	statQ     = opts.getBoolean("stat");
	rawQ      = opts.getBoolean("raw");
	appendQ   = opts.getBoolean("append");
	prependQ  = opts.getBoolean("prepend");
	replaceQ  = opts.getBoolean("replace");
	suppressQ = opts.getBoolean("suppress");
	reverseQ  = opts.getBoolean("reverse");
	sampleQ   = opts.getBoolean("sample");
	meanQ     = opts.getBoolean("mean");
	myMean    = opts.getDouble("mean");
	sdQ       = opts.getBoolean("sd");
	mySd      = opts.getDouble("sd");
}