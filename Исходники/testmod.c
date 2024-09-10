APIRET LoadModulePerf(PSZ pszModuleName,
                      PHMODULE phModule)
{
  PERFSTRUCT TS_Start;
  PERFSTRUCT TS_End;
  ULONG      ulFreeStart;
  ULONG      ulFreeEnd;
  double     seconds;
  APIRET     rc;                                  /* operation return code */

  printf ("Loading %s ...\n",
          pszModuleName);

  ulFreeStart = QueryFreeMemory();
  ToolsPerfQuery (&TS_Start);                    /* exact time measurement */

  rc = LoadModule(pszModuleName,
                  phModule);

  ToolsPerfQuery (&TS_End);                      /* exact time measurement */
  seconds = TS_End.fSeconds - TS_Start.fSeconds;     /* calculate duration */
  ulFreeEnd = QueryFreeMemory();

  printf("%u kb used, %11.6f ms\n",                  /* print report */
         (ulFreeStart - ulFreeEnd) / 1024,
         seconds * 1000.0);

  return rc;                                                         /* OK */
}