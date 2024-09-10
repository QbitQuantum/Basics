main(int argc,char *argv[])
{
  if (argc != 2) {
    fprintf(stderr,"usage: %s name-for-package\n", argv[0]);
    exit(1);
  }
  NEWLINE();
  PUTS("package "); PUTS(argv[1]); PUTS(" : Cc_Info =\n");
  PUTS("\tstruct\n");
  PUTS("\t\t");COMMENT("all sizes in bytes");
  NEWLINE();
  PUTVAL("intSzB", sizeof(int));
  PUTVAL("shortSzB", sizeof(short));
  PUTVAL("longSzB", sizeof(long));
  NEWLINE();
  PUTVAL("charSzB", sizeof(char));
  NEWLINE();
  PUTVAL("floatSzB", sizeof(float));
  PUTVAL("doubleSzB", sizeof(double));
  NEWLINE();
  PUTVAL("ptrSzB", sizeof(int *));
  NEWLINE();
  PUTVAL("unionAlign", sizeof(int *));
  PUTVAL("structAlign", sizeof(int *));
  NEWLINE();
  PUTS("\tend "); PUTS("/* package "); PUTS(argv[1]); PUTS(" */\n");
  exit(0);
}