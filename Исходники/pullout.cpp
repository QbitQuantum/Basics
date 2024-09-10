void checkOptions(Options& opts, int argc, char* argv[]) {
   opts.define("c|count=b", "count number of segments");
   opts.define("r|range=b", "print a range for the count");
   opts.define("n|nth=i:0", "print a particular segment");

   opts.define("debug=b");              // determine bad input line num
   opts.define("author=b");             // author of program
   opts.define("version=b");            // compilation info
   opts.define("example=b");            // example usages
   opts.define("h|help=b");             // short description
   opts.process(argc, argv);
   
   // handle basic options:
   if (opts.getBoolean("author")) {
      cout << "Written by Craig Stuart Sapp, "
           << "[email protected], Sept 2011" << endl;
      exit(0);
   } else if (opts.getBoolean("version")) {
      cout << argv[0] << ", version: 18 Sept 2011" << endl;
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

   countQ = opts.getBoolean("count");
   rangeQ = opts.getBoolean("range");
   nth    = opts.getInteger("nth");
}