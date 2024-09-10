void RegressionAnalysis::PrintScores()
   {
   int chr = 0;
   String tablename;
   FILE * tablefile = NULL;

   if (MerlinCore::tabulate)
      {
      chr = markers.Length() > 0 ? Pedigree::GetMarkerInfo(markers[0])->chromosome : 0;
      tablename.printf("%s-regress-chr%02d.tbl", (const char *) MerlinCore::filePrefix, chr > 0 ? chr : 0);
      tablefile = fopen(tablename, "wt");
      }

   if (tablefile != NULL)
      fprintf(tablefile, "CHR\tPOS\tPHENOTYPE\tH2\tSD\tINFO\tLOD\tPVALUE\n");

   for (int i = 0; i < modelCount; i++)
      regress[i].PrintScores(tablefile, chr, pdf, labels);

   if (tablefile != NULL)
      {
      printf("Linkage results stored in file [%s]\n\n", (const char *) tablename);

      fclose(tablefile);
      tablefile = NULL;
      }
   }