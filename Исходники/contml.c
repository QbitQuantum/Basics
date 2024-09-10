int main(int argc, Char *argv[])
{  /* main program */
  long i;

#ifdef MAC
  argc = 1;                /* macsetup("Contml","");                */
  argv[0] = "Contml";
#endif
  init(argc, argv);
  progname = argv[0];
  openfile(&infile,INFILE,"input file", "r",argv[0],infilename);
  openfile(&outfile,OUTFILE,"output file", "w",argv[0],outfilename);
  ibmpc = IBMCRT;
  ansi = ANSICRT;
  mulsets = false;
  firstset = true;
  datasets = 1;
  doinit();
  if (trout)
    openfile(&outtree,OUTTREE,"output tree file", "w",argv[0],outtreename);
  for (ith = 1; ith <= datasets; ith++) {
    getinput();
    if (ith == 1)
      firstset = false;
    if (datasets > 1) {
      fprintf(outfile, "Data set # %ld:\n\n", ith);
      if (progress)
        printf("\nData set # %ld:\n", ith);
    }
    for (jumb = 1; jumb <= njumble; jumb++)
      maketree();
    if (usertree)
      for (i = 0; i < MAXSHIMOTREES; i++)
        free(l0gf[i]);
  }
  FClose(outfile);
  FClose(outtree);
  FClose(infile);
#ifdef MAC
  fixmacfile(outfilename);
  fixmacfile(outtreename);
#endif
  printf("\nDone.\n\n");
#ifdef WIN32
  phyRestoreConsoleAttributes();
#endif
  return 0;
}