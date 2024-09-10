// Open the serial port
ser_handler ser_open( const char* sername )
{
  char portname[ WIN_MAX_PORT_NAME + 1 ];
  HANDLE hComm;

  portname[ 0 ] = portname[ WIN_MAX_PORT_NAME ] = '\0';
  _snprintf( portname, WIN_MAX_PORT_NAME, "\\\\.\\%s", sername );
  hComm = CreateFile( portname, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0 );
  if( hComm == INVALID_HANDLE_VALUE )
    return WIN_ERROR;
  if( !SetupComm( hComm, 2048, 2048 ) )
    return WIN_ERROR;
  if( !FlushFileBuffers( hComm ) || 
      !PurgeComm( hComm, PURGE_TXABORT | PURGE_RXABORT |
                         PURGE_TXCLEAR | PURGE_RXCLEAR ) )
    return WIN_ERROR; 
  
  return hComm;
}