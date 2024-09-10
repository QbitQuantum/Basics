int main(int argc, Char *argv[])
{  /* main program */
#ifdef MAC
  argc = 1;		/* macsetup("Neighbor","");		*/
  argv[0] = "Neighbor";
#endif
#ifdef WIN32
  phySetConsoleAttributes();
  phyClearScreen();
#endif
  openfile(&infile,INFILE,"input file", "r",argv[0],infilename);
  openfile(&outfile,OUTFILE,"output file", "w",argv[0],outfilename);
  ibmpc = IBMCRT;
  ansi = ANSICRT;
  mulsets = false;
  datasets = 1;
  doinit();
  if (trout)
    openfile(&outtree,OUTTREE,"output tree file", "w",argv[0],outtreename);
  ith = 1;
  while (ith <= datasets) {
    if (datasets > 1) {
      fprintf(outfile, "Data set # %ld:\n",ith);
      if (progress)
        printf("Data set # %ld:\n",ith);
    }
    getinput();
    maketree();
    if (eoln(infile)) {
      fscanf(infile, "%*[^\n]");
      getc(infile);
    }
    ith++;
  }
  FClose(infile);
  FClose(outfile);
  FClose(outtree);
#ifdef MAC
  fixmacfile(outfilename);
  fixmacfile(outtreename);
#endif
  printf("Done.\n\n");
#ifdef WIN32
  phyRestoreConsoleAttributes();
#endif
  return 0;
}