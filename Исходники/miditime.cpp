void checkOptions(Options& opts) {

   opts.define("author=b");
   opts.define("version=b");
   opts.define("example=b");
   opts.define("help=b");
   opts.define("o|on|onset=b");
   opts.process();

   if (opts.getBoolean("author")) {
      cout << "Written by Craig Stuart Sapp, "
           << "[email protected], July 2010" << endl;
      exit(0);
   }
   if (opts.getBoolean("version")) {
      cout << "midiextract version 1.0" << endl;
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

   onsetQ = opts.getBoolean("onset");
}