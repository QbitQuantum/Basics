void checkOptions(Options& opts, int argc, char* argv[]) {
	opts.define("p|parens=b", "print parentheses around dittox data");
	opts.define("r|rhythm=b", "print keeping kern data rhythm parseable");
	opts.define("c|char|chars=s:[rA-Ga-g#-]",
	                            "print only characters in list when dittoing");
	opts.define("C|xchar|xchars=s", "remove characters in list when dittoing");
	opts.define("k|kern|pitches=b", "print only pitch names in **kern data");

	opts.define("author=b");                     // author of program
	opts.define("version=b");                    // compilation info
	opts.define("example=b");                    // example usages
	opts.define("h|help=b");                     // short description
	opts.process(argc, argv);

	// handle basic options:
	if (opts.getBoolean("author")) {
		cout << "Written by Craig Stuart Sapp, "
			  << "[email protected], Nov 2000" << endl;
		exit(0);
	} else if (opts.getBoolean("version")) {
		cout << argv[0] << ", version: 14 Nov 2000" << endl;
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

	parensQ  = opts.getBoolean("parens");
	rhythmQ  = opts.getBoolean("rhythm");

	PerlRegularExpression pre;
	charQ    = opts.getBoolean("char");
	if (charQ) {
		charString = opts.getString("char");
		if (!pre.search(charString, "^\\[")) {
			pre.sar(charString, "^", "[");
			pre.sar(charString, "$", "]");
		}
		pre.sar(charString, "^\\[", "[^");
	}

	xcharQ    = opts.getBoolean("xchar");
	if (xcharQ) {
		xcharString = opts.getString("xchar");
		if (!pre.search(xcharString, "^\\[")) {
			pre.sar(xcharString, "^", "[");
			pre.sar(xcharString, "$", "]");
		}
	}

	if (opts.getBoolean("kern")) {
		charString = "[^rA-Ga-g#-]";
		charQ = 1;
	}
}