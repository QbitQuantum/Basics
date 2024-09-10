/* -------------------------------------------------------------
   InitChannelDump
   ------------------------------------------------------------- */
void InitChannelDump(OPTIONSTRUCT *Options, CHANNEL * channel, 
					 char *DumpPath)
{
  char buffer[NAMESIZE];

  if (channel->streams != NULL) {
    sprintf(buffer, "%sStream.Flow", DumpPath);
    OpenFile(&(channel->streamout), buffer, "w", TRUE);
    sprintf(buffer, "%sStreamflow.Only", DumpPath);
    OpenFile(&(channel->streamflowout), buffer, "w", TRUE);
    /* output files for John's RBM model */
	if (Options->StreamTemp) {
      //inflow to segment
      sprintf(buffer, "%sInflow.Only", DumpPath);
      OpenFile(&(channel->streaminflow), buffer, "w", TRUE);
      // outflow ( redundant but it's a check
      sprintf(buffer, "%sOutflow.Only", DumpPath);
      OpenFile(&(channel->streamoutflow), buffer, "w", TRUE);
      // total incoming short wave
      sprintf(buffer, "%sISW.Only", DumpPath);
      OpenFile(&(channel->streamISW), buffer, "w", TRUE);
	  //net incoming short wave
      sprintf(buffer, "%sNSW.Only", DumpPath);
      OpenFile(&(channel->streamNSW), buffer, "w", TRUE);
      // total incoming long wave
      sprintf(buffer, "%sILW.Only", DumpPath);
      OpenFile(&(channel->streamILW), buffer, "w", TRUE);
	  // net incoming long wave
	  sprintf(buffer, "%sNLW.Only", DumpPath);
      OpenFile(&(channel->streamNLW), buffer, "w", TRUE);
      //Vapor pressure
      sprintf(buffer, "%sVP.Only", DumpPath);
      OpenFile(&(channel->streamVP), buffer, "w", TRUE);
      //wind speed
      sprintf(buffer, "%sWND.Only", DumpPath);
      OpenFile(&(channel->streamWND), buffer, "w", TRUE);
      //air temperature
      sprintf(buffer, "%sATP.Only", DumpPath);
      OpenFile(&(channel->streamATP), buffer, "w", TRUE);
	  //beam radiation
      sprintf(buffer, "%sBeam.Only", DumpPath);
      OpenFile(&(channel->streamBeam), buffer, "w", TRUE);
	  //diffuse radiation
      sprintf(buffer, "%sDiffuse.Only", DumpPath);
      OpenFile(&(channel->streamDiffuse), buffer, "w", TRUE);
	  //skyview
      sprintf(buffer, "%sSkyview.Only", DumpPath);
      OpenFile(&(channel->streamSkyView), buffer, "w", TRUE);
	}
  }
  if (channel->roads != NULL) {
    sprintf(buffer, "%sRoad.Flow", DumpPath);
    OpenFile(&(channel->roadout), buffer, "w", TRUE);
    sprintf(buffer, "%sRoadflow.Only", DumpPath);
    OpenFile(&(channel->roadflowout), buffer, "w", TRUE);

  }
}