main(int argc,char *argv[])
  {
  if (argc<2)
     {
     puts("Tento program vyzaduje jmeno souboru, ve kterem se naleza\n"
          "script pro popis dialogu pro hru BRANY SKELDALU v 1.0");
     exit(0);
     }
  puts("");
  puts("Prob�h� kompilace:");
  puts("   Spou�t�m program LEX_LIB.EXE\n");
  putenv("DOS4G=QUIET");
  create_include_list(argv[1]);
  if (spawnlp(P_WAIT,GetLexLibPath(),"lex_lib.exe",TEMP_NAME1,"temp.$$$",NULL))
     exit(1);
  if (errno || init("temp.$$$"))
     {
     puts("Nemohu spustit program lex_lib.exe");
     exit(1);
     }
  mlist=fopen(SCRIPT,"w");
  if (mlist==NULL)
     {
     printf("Nemohu otevrit soubor %s pro zapis.\n",SCRIPT);
     exit(0);
     }
  decode_program(f);
  fclose(f);
  remove("temp.$$$");
  remove(TEMP_NAME1);
  puts("Kompilace �sp��n�...");
  printf("Vytvoreno odstavcu: %d\nCelkem knihoven: %d\nCelkem Sentenci: %d\nD�lka k�du: %d\n",pgf_count,libs,sentencs,prog_pos);
  save_program();
  fclose(mlist);
  }