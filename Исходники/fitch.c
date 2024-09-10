int main(int argc, Char *argv[])
{
  int i;
#ifdef MAC
  argc = 1;		/* macsetup("Fitch","");	*/
  argv[0]="Fitch";
#endif
#ifdef WIN32
  phySetConsoleAttributes();
  phyClearScreen();
#endif
  strcpy(progname,argv[0]);
  openfile(&infile,INFILE,"input file","r",argv[0],infilename);
  openfile(&outfile,OUTFILE,"output file","w",argv[0],outfilename);

  ibmpc = IBMCRT;
  ansi = ANSICRT;
  mulsets = false;
  datasets = 1;
  firstset = true;
  doinit();
  if (trout)
    openfile(&outtree,OUTTREE,"output tree file","w",argv[0],outtreename);
  for (i=0;i<spp;++i){
    enterorder[i]=0;}
  for (ith = 1; ith <= datasets; ith++) {
    if (datasets > 1) {
      fprintf(outfile, "Data set # %ld:\n\n",ith);
      if (progress)
        printf("\nData set # %ld:\n\n",ith);
    }
    fitch_getinput();
    for (jumb = 1; jumb <= njumble; jumb++)
        maketree();
    firstset = false;
    if (eoln(infile)) {
      fscanf(infile, "%*[^\n]");
      getc(infile);
    }
  }
  if (trout)
    FClose(outtree);
  FClose(outfile);
  FClose(infile);
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