void checkOptions(Options& opts) {
   opts.define("author=b",   "author of the program");
   opts.define("version=b",  "version of the program");
   opts.define("example=b",  "example useage of the program");
   opts.define("h|help=b",   "list of options for the program");
   opts.process();

   if (opts.getBoolean("author")) {
      cout << "Written by Craig Stuart Sapp, "
              "[email protected], February 2015" << endl;
      exit(0);
   } else if (opts.getBoolean("version")) {
      cout << "80off, version 1.0 (10 Feb 2015)\n"
              "compiled: " << __DATE__ << endl;
      exit(0);
   } else if (opts.getBoolean("help")) {
      usage(opts.getCommand());
      exit(0);
   } else if (opts.getBoolean("example")) {
      example();
      exit(0);
   }

   if (opts.getArgCount() == 0) {
      cerr << "Error: One or more input file is required." << endl;
      exit(1);
   }

}