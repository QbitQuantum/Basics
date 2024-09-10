void checkOptions(Options& opts) {
   opts.define("a|auto|automatic=b");
   opts.define("c|const|constant=b");
   opts.define("t|tempo|tempo-average=i:1");
   opts.define("m|max|max-amplitude=i:64");
   opts.define("p|port|out-port=i:0");
   opts.define("i|inport|in-port=i:0");
   opts.define("1|z|channel-collapse=b");
   opts.define("improv-author=b");
   opts.define("improv-version=b");
   opts.define("example=b");
   opts.define("improv-help=b");
   opts.process();              

   if (opts.getBoolean("improv-author")) {
      cout << "Written by Craig Stuart Sapp, "
           << "[email protected], Nov 1999" << endl;
      exit(0);
   }
   if (opts.getBoolean("improv-version")) {
      cout << "midiperform version 1.0" << endl;
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

   // can only have one output filename
   if (opts.getArgCount() != 1) {
      cout << "Error: need one input MIDI file for performance." << endl;
      usage(opts.getCommand().data());
      exit(1);
   } 

   // figure out the tempo performance method
   if (opts.getBoolean("automatic")) {
      tempoMethod = TEMPO_METHOD_AUTOMATIC;
   } else if (opts.getBoolean("constant")) {
      tempoMethod = TEMPO_METHOD_CONSTANT;
   } else {
      switch (opts.getInteger("tempo-average")) {
         case 1:  tempoMethod = TEMPO_METHOD_ONEBACK;   break;
         case 2:  tempoMethod = TEMPO_METHOD_TWOBACK;   break;
         case 3:  tempoMethod = TEMPO_METHOD_THREEBACK; break;
         case 4:  tempoMethod = TEMPO_METHOD_FOURBACK;  break;
         default: tempoMethod = TEMPO_METHOD_ONEBACK;   break;
      }
   }

   outport = opts.getInteger("out-port");
   inport = opts.getInteger("in-port");
   maxamp = opts.getInteger("max-amplitude");
   performance.channelCollapse(opts.getBoolean("channel-collapse"));
}