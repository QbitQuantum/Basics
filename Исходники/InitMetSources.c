/*******************************************************************************
  Function name: InitStations()

  Purpose      : Read the station information from the options file.  This 
                 information is in the [METEOROLOGY] section

  Required     : 
    LISTPTR Input       - Linked list with input strings
    MAPSIZE *Map        - Information about the basin area
    int NDaysSteps      - Number of time steps in a day
    int *NStats         - Number of met stations
    METLOCATION **Stat  - Information about each met station

  Returns      : void

  Modifies     : NStats, Stat and members of Stat

  Comments     :
*****************************************************************************/
void InitStations(LISTPTR Input, MAPSIZE * Map, int NDaySteps,
		  OPTIONSTRUCT * Options, int *NStats, METLOCATION ** Stat)
{
  int i;
  int j;
  int k;
  char tempfilename[BUFSIZE + 1];
  char KeyName[station_file + 1][BUFSIZE + 1];
  char *KeyStr[] = {
    "STATION NAME",
    "NORTH COORDINATE",
    "EAST COORDINATE",
    "ELEVATION",
    "STATION FILE"
  };
  char *SectionName = "METEOROLOGY";
  char VarStr[station_file + 1][BUFSIZE + 1];
  float East;
  float North;
  FILE *PrismStatFile;

  /* Get the number of different stations */
  GetInitString(SectionName, "NUMBER OF STATIONS", "", VarStr[0],
		(unsigned long) BUFSIZE, Input);
  if (!CopyInt(NStats, VarStr[0], 1))
    ReportError("NUMBER OF STATIONS", 51);

  if (*NStats <= 0)
    ReportError("Input Options File", 6);

  printf("\nEvaluating %d Met stations for inclusion\n", *NStats);

  /* Allocate memory for the stations */
  if (!(*Stat = (METLOCATION *) calloc(*NStats, sizeof(METLOCATION))))
    ReportError("Input Options File", 1);

  /* Read key-entry pairs for each station from the input file */
  /* for each potential station, up to NStats, read in the data and */
  /* determine if it is in the current model bounding box */
  /* If it is then put it into memory, otherwise, forget about it */
  /* unless Outside option is TRUE, then include it anyway */
  /* use temp counter k to track number of valid stations */
  k = 0;
  for (i = 0; i < *NStats; i++) {

    for (j = 0; j <= station_file; j++) {
      sprintf(KeyName[j], "%s %d", KeyStr[j], i + 1);
      GetInitString(SectionName, KeyName[j], "", VarStr[j],
		    (unsigned long) BUFSIZE, Input);
    }

    /* Assign the entries to the variables */
    if (IsEmptyStr(VarStr[station_name]))
      ReportError(KeyName[number_of_maps], 51);
    strcpy((*Stat)[k].Name, VarStr[station_name]);

    if (!CopyFloat(&North, VarStr[station_north], 1))
      ReportError(KeyName[station_north], 51);

    if (!CopyFloat(&East, VarStr[station_east], 1))
      ReportError(KeyName[station_east], 51);

    (*Stat)[k].Loc.N = Round(((Map->Yorig - 0.5 * Map->DY) - North) / Map->DY);
    (*Stat)[k].Loc.E = Round((East - (Map->Xorig + 0.5 * Map->DX)) / Map->DX);

    if (!CopyFloat(&((*Stat)[k].Elev), VarStr[station_elev], 1))
      ReportError(KeyName[station_elev], 51);

    if (IsEmptyStr(VarStr[station_file]))
      ReportError(KeyName[station_file], 51);
    strcpy((*Stat)[k].MetFile.FileName, VarStr[station_file]);

    OpenFile(&((*Stat)[k].MetFile.FilePtr), (*Stat)[k].MetFile.FileName,
	     "r", FALSE);

    /* check to see if the stations are inside the bounding box */
    if (((*Stat)[k].Loc.N > Map->NY || (*Stat)[k].Loc.N < 0 ||
	 (*Stat)[k].Loc.E > Map->NX || (*Stat)[k].Loc.E < 0)
	&& Options->Outside == FALSE)
      /*      ReportError((*Stat)[i].Name,10); */
      printf("Station %d outside bounding box: %s ignored\n",
	     i + 1, (*Stat)[k].Name);
    else
      k = k + 1;
  }
  if (Options->Outside == FALSE)
    printf("Final number of stations in bounding box is %d \n\n", k);
  else
    printf("Forced to include all %d stations \n", k);
  *NStats = k;

  if (Options->Outside == TRUE && Options->Prism == TRUE) {

    for (i = 0; i < *NStats; i++) {
      sprintf(tempfilename, "%s.prism", (*Stat)[i].MetFile.FileName);
      /* Options->PrismDataExt); */
      OpenFile(&PrismStatFile, tempfilename, "rt", FALSE);
      for (k = 0; k < 12; k++) {
	fscanf(PrismStatFile, "%f ", &(*Stat)[i].PrismPrecip[k]);
      }
      fclose(PrismStatFile);
    }
  }
}