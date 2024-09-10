void Debug_Dump_LMLA_hastab(DecoderInst *dec)
{
   int i, n;
   LMLACacheEntry *e;

   FILE *debugFile;
   Boolean isPipe;
   static char *debug_net_fn = "lmla_cache.dump";

   debugFile = FOpen (debug_net_fn, NoOFilter, &isPipe);
   if (!debugFile) {
      printf ("fopen failed\n");
      return;
   }

   for (i = 0; i < dec->nLMLACacheBins; ++i) {
      n = 0;
      for (e = dec->lmlaCache[i]; e; e = e->next)
         ++n;
      fprintf (debugFile, "LMLA %d %d\n", i, n);
   }

   FClose (debugFile, isPipe);
}