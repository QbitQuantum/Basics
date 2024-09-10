void AGSPlatformDriver::ReadPluginsFromDisk(FILE *iii) {
  if (getw(iii) != 1)
    quit("ERROR: unable to load game, invalid version of plugin data");

  int numPlug = getw(iii), a, datasize;
  char buffer[80];

  for (a = 0; a < numPlug; a++) {
    // read the plugin name
    fgetstring (buffer, iii);
    datasize = getw(iii);
    fseek (iii, datasize, SEEK_CUR);
  }

}