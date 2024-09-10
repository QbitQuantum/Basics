/*!
  @param aDevName [in] Serial port device file name
  @return Sesnor's communication handler
  Returns NULL if failed
*/
tPort* scipConnect(char *aDevName)
{
  tPort *port;
  int ret;

  fprintf(stdout,"Connecting at 19200 bps ...\n");
  port=openPort(aDevName,19200);
  ret=scipTryComm(port);
  switch(ret){
    case 1:
    case 2:
      fprintf(stdout,"Connected at 19200 bps\n\n");
      return port;
    default:
      fprintf(stdout,"Could not connect at 19200 bps\n\n");
      break;
  }

  fprintf(stdout,"Connecting at 57600 bps ...\n");
  if(setupPort(fileno(port->dev),57600)!=EXIT_SUCCESS){
    perror("Could not set terminal parameters ");
    return NULL;
  }
  ret=scipTryComm(port);
  switch(ret){
    case 1:
    case 2:
      fprintf(stdout,"Connected at 57600 bps\n\n");
      return port;
    default:
      fprintf(stdout,"Could not connect at 57600 bps\n\n");
      break;
  }

  fprintf(stdout,"Connecting at 115200 bps ...\n");
  if(setupPort(fileno(port->dev),115200)!=EXIT_SUCCESS){
    perror("Could not set terminal parameters ");
    return NULL;
  }
  ret=scipTryComm(port);
  switch(ret){
    case 1:
    case 2:
      fprintf(stdout,"Connected at 115200 bps\n\n");
      return port;
    default:
      fprintf(stdout,"Could not connect at 115200 bps\n\n");
      break;
  }

  return NULL;
}