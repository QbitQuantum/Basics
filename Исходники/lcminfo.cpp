int main(int argc, char** argv) {
   Options opts;
   opts.process(argc, argv);

   ScorePageSet infiles(opts);

   int pages = infiles.getPageCount();
   int overlay = 0;
   int systems;
   int number;
   set<int> numbers;

   int i, j;
   for (i=0; i<pages; i++) {
      systems = infiles[i][overlay].getSystemCount();
      for (j=0; j<systems; j++) {
         cout << "P" << i+1 << "\tS" << j+1 << "\t";
         int number = infiles[i][overlay].getSystemLCMRhythm(j);
         numbers.insert(number);
         cout << number << endl;
      }
   }
   cout << "LCM of all rhythms: " << SU::lcm(numbers) << endl;

   return 0;
}