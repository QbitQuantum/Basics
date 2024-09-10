static
void GenerateGiantSteps(const GF2EX& f, const GF2EX& h, long l, long verbose)
{

   double t;

   if (verbose) { cerr << "generating giant steps..."; t = GetTime(); }

   GF2EXModulus F;
   build(F, f);

   GF2EXArgument H;

#if 0
   double n2 = sqrt(double(F.n));
   double n4 = sqrt(n2);
   double n34 = n2*n4;
   long sz = long(ceil(n34/sqrt(sqrt(2.0))));
#else
   long sz = 2*SqrRoot(F.n);
#endif

   build(H, h, F, sz);

   GF2EX h1;

   h1 = h;

   long i;

   long HexOutput = GF2X::HexOutput; 
   GF2X::HexOutput = 1;

   if (!use_files) {
      GiantStepFile.kill();
      GiantStepFile.SetLength(l);
   }

   for (i = 1; i <= l-1; i++) {
      if (use_files) {
         ofstream s;
         OpenWrite(s, FileName(GF2EX_stem, "giant", i));
         s << h1 << "\n";
         s.close();
      }
      else
         GiantStepFile(i) = h1;

      CompMod(h1, h1, H, F);
      if (verbose) cerr << "+";
   }

   if (use_files) {
      ofstream s;
      OpenWrite(s, FileName(GF2EX_stem, "giant", i));
      s << h1 << "\n";
      s.close();
   }
   else
      GiantStepFile(i) = h1;

   if (verbose)
      cerr << (GetTime()-t) << "\n";

   GF2X::HexOutput = HexOutput;
}