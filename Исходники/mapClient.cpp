void handleGetMap(ArNetPacket *packet)
{
  char buffer[512];

  if (packet->getDataReadLength() == packet->getDataLength())
  {
    printf("Empty packet signifying end of map (for central forward)\n");
    return;
  }
  
  packet->bufToStr(buffer, sizeof(buffer));
  // if we got an end of line char instead of a line it means the map is over
  if (buffer[0] == '\0')
  {
    printf("Map took %g seconds\n", start.mSecSince() / 1000.0);
    arMap.parsingComplete();
    arMap.writeFile("mapExample.map");
    //client.disconnect();
    //exit(0);
  }
  else
  {
    //printf("line '%s'\n", buffer);
    arMap.parseLine(buffer);
  }

}