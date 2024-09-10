//-------------------------------------------------------------------------
// Initialize TRK connection over a serial port.
// Returns success.
bool metrotrk_t::init(int port)
{
  sseq = 0;

  if ( port == DEBUGGER_PORT_NUMBER )
  {
    int p = find_smartphone_port();
    if ( p > 0 )
    {
      port = p;
      msg("Using COM%d: to communicate with the smartphone...\n", port);
    }
    else
    {
      warning("Could not autodetect the smartphone port.\n"
              "Please specify it manually in the process options");
    }
  }

  char name[32];
  qsnprintf(name, sizeof(name), "\\\\.\\COM%d", port);

  qstring friendly_name;
  if ( !is_serial_port_present(port, &friendly_name) )
  {
      if ( askyn_c(0,
                   "HIDECANCEL\n"
                   "Serial port COM%d seems to be unavailable. Do you want to proceed?",
                   port ) <= 0 )
      {
        SetLastError(ERROR_DEVICE_NOT_CONNECTED);
        return false;
      }
  }
  msg("Opening serial port %s: (%s)...\n", &name[4], friendly_name.c_str());

  // port exists, open it
  hp = CreateFile(name, GENERIC_READ|GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
  if ( hp == INVALID_HANDLE_VALUE )
    return false;
  DCB dcb;
  memset(&dcb, 0, sizeof(dcb));
  dcb.DCBlength = sizeof(dcb);
  dcb.BaudRate = CBR_115200;
  dcb.fBinary = true;
  dcb.ByteSize = 8;
  dcb.Parity = NOPARITY;
  dcb.StopBits = ONESTOPBIT;
  if ( !SetCommState(hp, &dcb) )
  {
    CloseHandle(hp);
    return false;
  }
  GetCommTimeouts(hp, &ct);
  return true;
}