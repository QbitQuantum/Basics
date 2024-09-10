void checkOptions(Options& opts) {
   opts.define("r|reverse=b", "Reverse the order of notes");

   opts.define("author=b",    "Author of the program");
   opts.define("version=b",   "Print version of the program");
   opts.define("example=b",   "Display example use of the program");
   opts.define("help=b",      "Dispay help for the program");
   opts.process();

   if (opts.getBoolean("author")) {
      cout << "Written by Craig Stuart Sapp, "
           << "[email protected], 2 December 1999" << endl;
      exit(0);
   }
   if (opts.getBoolean("version")) {
      cout << "midimixup version 2.0" << endl;
      cout << "compiled: " << __DATE__ << endl;
   }
   if (opts.getBoolean("help")) {
      usage(opts.getCommand().data());
      exit(0);
   }
   if (opts.getBoolean("example")) {
      example();
      exit(0);
   }

   reverseQ = opts.getBoolean("reverse");
}