void checkOptions(Options& opts, int argc, char* argv[]) {
   opts.define("p|pause=d:2.0",  "Pause given number of secs after each file");
   opts.define("a|ascii=b",  "Display MIDI output as ASCII text");

   opts.define("author=b",  "author of program");
   opts.define("version=b", "compilation info");
   opts.define("example=b", "example usages");
   opts.define("h|help=b",  "short description");
   opts.process(argc, argv);

   // handle basic options:
   if (opts.getBoolean("author")) {
      cout << "Written by Craig Stuart Sapp, "
           << "[email protected], 16 October 2012" << endl;
      exit(0);
   } else if (opts.getBoolean("version")) {
      cout << argv[0] << ", version: October 2012" << endl;
      cout << "compiled: " << __DATE__ << endl;
      exit(0);
   } else if (opts.getBoolean("help")) {
      usage(opts.getCommand().data());
      exit(0);
   } else if (opts.getBoolean("example")) {
      example();
      exit(0);
   }

   if (opts.getArgCount() <= 1) {
      usage(opts.getCommand().data());
      exit(1);
   }

   seconds     =  opts.getDouble("pause");
   binaryQ     = !opts.getBoolean("ascii");
}