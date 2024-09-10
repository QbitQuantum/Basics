void checkOptions(Options& opts, int argc, char** argv) {
   opts.define("H|humdrum=b", "Display original Humdrum data in tandem with output data.");
   opts.define("L|no-labels=b",   "Suppress fuction labels");
   opts.define("C|no-comments=b", "Suppress reference record printing");
   opts.define("debug=b",     "Debugging flag");
   opts.define("author=b",    "Program author");
   opts.define("version=b",   "Program version");
   opts.define("example=b",   "Program examples");
   opts.define("h|help=b",    "Short description");
   opts.process(argc, argv);

   // handle basic options:
   if (opts.getBoolean("author")) {
      cout << "Written by Craig Stuart Sapp, "
           << "[email protected], March 2013" << endl;
      exit(0);
   } else if (opts.getBoolean("version")) {
      cout << argv[0] << ", version: 19 March 2013" << endl;
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

   debugQ        =  opts.getBoolean("debug");
   humdrumQ      =  opts.getBoolean("humdrum");
   labelQ        = !opts.getBoolean("no-labels");
   commentQ      = !opts.getBoolean("no-comments");
}