void RaceStandingsPlugin::Log(const char *msg)
{
  FILE *fo;
  time_t curtime;
  struct tm localtime;
  char timestamp[26];

  fo = fopen( RACE_STANDINGS_LOG_FILENAME, "a" );
  if( fo != NULL )
  {
	curtime = time(NULL);
	localtime_s(&localtime, &curtime);
	asctime_s(timestamp, 26, &localtime);
	timestamp[24] = 0;
    fprintf( fo, "[%s] %s\n", timestamp, msg );
    fclose( fo );
  }
}