int main(int argc, char** argv) {
   Options opts;
   opts.define("r|remove|hide=b",  "hide courtesy/cautionary accidentals");
   opts.define("R|replace|show=b", "show courtesy/cautionary accidentals");
   opts.define("p|paren=b",   "put parentheses around courtesy accidentals");
   opts.define("P|no-paren=b","remove parentheses around courtesy accidentals");
   opts.define("k|keep=b",      "keep courtey accidental note states");
   opts.define("m|mark=b",      "mark courtesy accidentals (no highlighting)");
   opts.define("lj|LJ=b",       "Add LJ commands for changed systems");
   opts.define("a|analysis=b",  "Include pitch analysis data in output");
   opts.define("e|editorial=b", "put editorial accs. on all non-natural notes");
   opts.process(argc, argv);

   ScorePage infile;

   int argcount = opts.getArgCount();
   for (int i=0; i<argcount || i==0; i++) {
      if (argcount == 0) {
        infile.read(cin);
      } else  {
         infile.read(opts.getArg(i+1));
      }
      if (argcount > 1) {
         cout << "###FILE:\t" << infile.getFilename() << endl;
      }
      processData(infile, opts);
   }

   return 0;
}