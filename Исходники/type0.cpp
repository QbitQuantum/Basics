void checkOptions(Options& opts) {
   opts.define("author=b",   "Author of the program");
   opts.define("version=b",  "Version of the program");
   opts.define("example=b",  "Example useage of the program");
   opts.define("h|help=b",   "List of options for the program");
   opts.process();

   if (opts.getBoolean("author")) {
      cout << "Written by Craig Stuart Sapp, "
              "[email protected], February 2015" << endl;
      exit(0);
   } else if (opts.getBoolean("version")) {
      cout << "tobinary, version 1.0 (18 Feb 2015)\n"
              "compiled: " << __DATE__ << endl;
      exit(0);
   } else if (opts.getBoolean("help")) {
      usage(opts.getCommand());
      exit(0);
   } else if (opts.getBoolean("example")) {
      example();
      exit(0);
   }

   if (opts.getArgCount() > 2) {
      cerr << "Error: Too many filenames given." << endl;
      exit(1);
   }
   if (opts.getArgCount() == 0) {
      cerr << "Error: Too few filenames given." << endl;
      exit(1);
   }

}