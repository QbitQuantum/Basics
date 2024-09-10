int main(int argc, char** argv) {
   Options opts;
   opts.define("a|assign=b", "Assign part numbers to staves");
   opts.define("p|page=i:1", "Process only given page # (indexed from 1)");
   opts.define("t|test-assignment=b", "Test part assignment");
   opts.define("i|8|staff-items=b", "Extract staff items from page");
   opts.define("c|pecf|part-extractor-control-file=b",
         "file needed for part extraction");
   opts.process(argc, argv);
   ScorePageSet infiles(opts);

   if (opts.getBoolean("page")) {
      processPage(infiles, opts.getInteger("page")-1, opts);
   } else if (opts.getBoolean("part-extractor-control-file")) {
      generatePECF(infiles);
   } else {
      for (int i=0; i<infiles.getPageCount(); i++) {
         processPage(infiles, i, opts);
      }
   }

   if (opts.getBoolean("assign")) {
      cout << infiles;
   }

   return 0;
}