void qdah(char* motifFile, char* ditherFile,char* outputFile)
{

  Image motif;
  motif.readFile(motifFile);


  Image dither;
  dither.readFile(ditherFile);

  //  fprintf(dbgfp,"read dither ok\n");

  Image output;

  checkImageSizes(motif, dither);

  //  fprintf(dbgfp,"image sizes ok\n");

  qdah(motif, dither, output);;

  //  fprintf(dbgfp,"qdah succeeded\n");
  //  fflush(dbgfp);

  output.writeFile(outputFile);

  //  fprintf(dbgfp,"wrote output\n");
}