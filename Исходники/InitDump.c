 /*******************************************************************************
   Function name: InitDump()

   Purpose      : Read the model output information from the options file, and
                  organize what to output when.  This information is in the
          [OUTPUT] section

   Required     :
     LISTPTR Input         - Linked list with input strings
     OPTIONSTRUCT *Options - Mode options
     MAPSIZE *Map          - Information about basin area
     int MaxSoilLayers     - Maximum number of soil layers
     int MaxVegLayers      - Maximum number of vegetation layers
     int Dt                - Time step in seconds
     TOPOPIX **TopoMap     - Information about terrain characteristics
     DUMPSTRUCT *Dump      - Information on what to output when

   Returns      : void

   Modifies     : Members of Dump

   Comments     :
 *****************************************************************************/
void InitDump(LISTPTR Input, OPTIONSTRUCT *Options, MAPSIZE *Map, int MaxSoilLayers, 
  int MaxVegLayers, int Dt, TOPOPIX **TopoMap, DUMPSTRUCT *Dump, int *NGraphics,
  int **which_graphics)
{
  char *Routine = "InitDump";
  int i;
  int x;			/* counter */
  int y;			/* counter */
  int NImageVars;		/* Number of different variables for which to
                   dump images */
  int NMapVars;			/* Number of different variables for which to
                   dump maps */
  int temp_count;
  uchar **BasinMask;
  char sumoutfile[100];


  STRINIENTRY StrEnv[] = {
    {"OUTPUT", "OUTPUT DIRECTORY", "", ""},
    {"OUTPUT", "INITIAL STATE DIRECTORY", "", ""},
    {"OUTPUT", "NUMBER OF OUTPUT PIXELS", "", ""},
    {"OUTPUT", "NUMBER OF MODEL STATES", "", ""},
    {"OUTPUT", "NUMBER OF MAP VARIABLES", "", ""},
    {"OUTPUT", "NUMBER OF IMAGE VARIABLES", "", ""},
    {"OUTPUT", "NUMBER OF GRAPHICS", "", ""},
    {NULL, NULL, "", NULL},
  };

  printf("Initializing dump procedures\n");

  /* Get the key-entry pairs from the input file */
  for (i = 0; StrEnv[i].SectionName; i++)
    GetInitString(StrEnv[i].SectionName, StrEnv[i].KeyName, StrEnv[i].Default,
      StrEnv[i].VarStr, (unsigned long)BUFSIZE, Input);

  /* Assign the entries to the variables */
  if (IsEmptyStr(StrEnv[output_path].VarStr))
    ReportError(StrEnv[output_path].KeyName, 51);
  strcpy(Dump->Path, StrEnv[output_path].VarStr);

  // delete any previous failure_summary.txt file
  sprintf(sumoutfile, "%sfailure_summary.txt", Dump->Path);
  if (remove(sumoutfile) != -1)
    printf(" - removed old version of failure_summary.txt\n");

  if (IsEmptyStr(StrEnv[initial_state_path].VarStr))
    strcpy(Dump->InitStatePath, Dump->Path);
  strcpy(Dump->InitStatePath, StrEnv[initial_state_path].VarStr);

  if (IsEmptyStr(StrEnv[npixels].VarStr))
    Dump->NPix = 0;
  else if (!CopyInt(&(Dump->NPix), StrEnv[npixels].VarStr, 1) || Dump->NPix < 0)
    ReportError(StrEnv[npixels].KeyName, 51);

  if (IsEmptyStr(StrEnv[nstates].VarStr))
    Dump->NStates = 0;
  else if (!CopyInt(&(Dump->NStates), StrEnv[nstates].VarStr, 1))
    ReportError(StrEnv[nstates].KeyName, 51);

  if (IsEmptyStr(StrEnv[nmapvars].VarStr))
    NMapVars = 0;
  else if (!CopyInt(&NMapVars, StrEnv[nmapvars].VarStr, 1) || NMapVars < 0)
    ReportError(StrEnv[nmapvars].KeyName, 51);

  if (IsEmptyStr(StrEnv[nimagevars].VarStr))
    NImageVars = 0;
  else if (!CopyInt(&NImageVars, StrEnv[nimagevars].VarStr, 1) ||
    NImageVars < 0)
    ReportError(StrEnv[nimagevars].KeyName, 51);

  if (IsEmptyStr(StrEnv[ngraphics].VarStr))
    *NGraphics = 0;
  else if (!CopyInt(NGraphics, StrEnv[ngraphics].VarStr, 1) || *NGraphics < 0)
    ReportError(StrEnv[ngraphics].KeyName, 51);

  if (Options->Extent == POINT)
    *NGraphics = 0;

  Dump->NMaps = NMapVars + NImageVars;

  // Open file for recording aggregated values for entire basin
  sprintf(Dump->Aggregate.FileName, "%sAggregated.Values", Dump->Path);
  OpenFile(&(Dump->Aggregate.FilePtr), Dump->Aggregate.FileName, "w", TRUE);

  // Open file for recording mass balance for entire basin
  sprintf(Dump->Balance.FileName, "%sMass.Balance", Dump->Path);
  OpenFile(&(Dump->Balance.FilePtr), Dump->Balance.FileName, "w", TRUE);

  sprintf(Dump->FinalBalance.FileName, "%sMass.Final.Balance", Dump->Path);
  OpenFile(&(Dump->FinalBalance.FilePtr), Dump->FinalBalance.FileName, "w", TRUE);

  if (Options->Extent != POINT) {
    /* Read remaining information from dump info file */
    if (Dump->NStates > 0)
      InitStateDump(Input, Dump->NStates, &(Dump->DState));

    /* if Dump->NStates < 0, the state will be dumped every time step, this is
       done directly in ExecDump */
    if (!(BasinMask = (uchar **)calloc(Map->NY, sizeof(uchar *))))
      ReportError(Routine, 1);
    for (y = 0; y < Map->NY; y++)
      if (!(BasinMask[y] = (uchar *)calloc(Map->NX, sizeof(uchar))))
        ReportError(Routine, 1);

    for (y = 0; y < Map->NY; y++)
      for (x = 0; x < Map->NX; x++)
        BasinMask[y][x] = TopoMap[y][x].Mask;

    if (Dump->NPix > 0) {
      temp_count = InitPixDump(Input, Map, BasinMask, Dump->Path, Dump->NPix,
        &(Dump->Pix), Options);

      if (temp_count == 0) {
        Dump->NPix = 0;
        printf("no candidate dump pixels accepted \n");
      }
      else {
        Dump->NPix = temp_count;
        printf("total number of accepted dump pixels %d \n", Dump->NPix);
      }
    }
    for (y = 0; y < Map->NY; y++)
      free(BasinMask[y]);
    free(BasinMask);

    if (Dump->NMaps > 0)
      InitMapDump(Input, Map, MaxSoilLayers, MaxVegLayers, Dump->Path,
        Dump->NMaps, NMapVars, &(Dump->DMap));
    if (NImageVars > 0)
      InitImageDump(Input, Dt, Map, MaxSoilLayers, MaxVegLayers, Dump->Path,
        Dump->NMaps, NImageVars, &(Dump->DMap));

    if (*NGraphics > 0)
      InitGraphicsDump(Input, *NGraphics, &which_graphics);

    /* if no network open unit hydrograph file */
    if (!(Options->HasNetwork)) {
      sprintf(Dump->Stream.FileName, "%sStream.Flow", Dump->Path);
      OpenFile(&(Dump->Stream.FilePtr), Dump->Stream.FileName, "w", TRUE);
    }
  }
}