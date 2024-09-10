main(int argc,char *argv[])
  {
  int codesize;
  char *z;
  printf("%d\n",sizeof(TKOUZLO));
  if (argc<2)
     {
     puts("Tento program vyzaduje jmeno souboru, ve kterem se nalezaji\n"
          "platne definice kouzel pro hru BRANY SKELDALU v 1.0");
     exit(0);
     }
  puts("");
  puts("Prob¡h  kompilace:");
  puts("   Spouçt¡m program LEX_LIB.EXE\n");
//  putenv("DOS4G=QUIET");
  z=(char *)malloc(strlen(argv[1])+10);
  sprintf(z,"\"%s\"",argv[1]);
  if (_spawnlp(P_WAIT,GetLexLibPath(),"lex_lib.exe",z,"temp.$$$",NULL))
     exit(1);
  free(z);
  if (errno)
     {
     puts("Nemohu spustit program lex_lib.exe");
     exit(1);
     }
  puts("Byla kompilov na tato kouzla:");
  puts("¬¡slo, zaŸ tek, jmeno:");
  puts("======================");
  memset(kouzla_tab,0,sizeof(kouzla_tab));
  init("temp.$$$");
  codesize=build_tables();
  add_prog_command(0xff);
  fclose(source);
  save_tab("kouzla.dat");
  remove("temp.$$$");
  puts("Kompilace £spØçn ...");
  printf("D‚lka k¢du: %d (+%d)",codesize,sizeof(kouzla_tab));
  }