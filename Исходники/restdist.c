int main(int argc, Char *argv[])
{  /* distances from restriction sites or fragments */
#ifdef MAC
  argc = 1;		/* macsetup("Restdist",""); */
  argv[0] = "Restdist";
#endif
#ifdef WIN32
  phySetConsoleAttributes();
  phyClearScreen();
#endif
  strcpy(progname,argv[0]);
  openfile(&infile,INFILE,"input data file","r",argv[0],infilename);
  openfile(&outfile,OUTFILE,"output file","w",argv[0],outfilename);
  ibmpc = IBMCRT;
  ansi = ANSICRT;
  mulsets = false;
  datasets = 1;
  firstset = true;
  doinit();
  for (ith = 1; ith <= datasets; ith++) {
    getinput();
    if (ith == 1)
      firstset = false;
    if (datasets > 1 && progress)
      printf("\nData set # %ld:\n\n",ith);
    makedists();
    writedists();
  }
  FClose(infile);
  FClose(outfile);
#ifdef MAC
  fixmacfile(outfilename);
#endif
  printf("Done.\n\n");
#ifdef WIN32
  phyRestoreConsoleAttributes();
#endif
  return 0;
}  /* distances from restriction sites or fragments */