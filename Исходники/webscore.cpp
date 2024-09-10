void processOptions(Options& opts, int argc, char** argv) {
   opts.define("sep|separator=s",
         "Separator between file name and system enumertor");
   opts.define("a|abbreviated=b", "Embed only note ids into font 99 text");
   opts.define("aa|all-abbreviated=b", "Embed ids for all items");
   opts.define("r|replace=b", "print replacement expressions");
   opts.define("i|index=b", "include item index serial numbers");
   opts.define("F|plain-fonts=b", "Remove specialzed fonts");
   opts.define("A|no-articulation=b", "do not label note articulations");
   opts.define("s|system-offset=i:0", "index of first system");
   opts.define("p|part=b", "indicate part number in class tags");
   opts.define("R|no-round=b", "do not round quarter-note timestamps");
   opts.process(argc, argv);

   Separator     =  opts.getString("separator");
   indexQ        =  opts.getBoolean("index");
   abbreviatedQ  =  options.getBoolean("abbreviated");
   allabbrQ      =  options.getBoolean("all-abbreviated");
   if (allabbrQ) {
      abbreviatedQ = 1;
   }
   replaceQ      =  options.getBoolean("replace");
   articulationQ = !options.getBoolean("no-articulation");
   systemOffset  =  options.getInteger("system-offset");
   partQ         =  options.getBoolean("part");
   roundQ        = !options.getBoolean("no-round");
   fixfontQ      = !options.getBoolean("plain-fonts");
}