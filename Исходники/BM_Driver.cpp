//---------------------------------------------------------------------------
// Attempt to open a com port.  Keep the handle in ComID.
// Set the starting baud rate to 115200.
//
// 'portnum'   - number 0 to MAX_PORTNUM-1.  This number provided will 
//               be used to indicate the port number desired when calling
//               all other functions in this library.
//
// 'port_zstr' - zero terminate port name.  For this platform
//               use format COMX where X is the port number.
//
//
// Returns: TRUE(1)  - success, COM port opened
//          FALSE(0) - failure, could not open specified port
//
bool OpenCOM(int portnum, char *port_zstr)
{
   char tempstr[80];
   short fRetVal;
   COMMTIMEOUTS CommTimeOuts;
   DCB dcb;

   // open COM device
   if ((ComID[portnum] =
      CreateFile( port_zstr, GENERIC_READ | GENERIC_WRITE,
                  0, 
                  NULL,                 // no security attrs
                  OPEN_EXISTING,
                  FILE_FLAG_OVERLAPPED, // overlapped I/O
                  NULL )) == (HANDLE) -1 )
   {
      ComID[portnum] = 0;
      return (FALSE) ;
   }
   else
   {
      // create events for detection of reading and write to com port 
      osRead[portnum].hEvent = CreateEvent(NULL,TRUE,FALSE,tempstr);  
      osWrite[portnum].hEvent = CreateEvent(NULL,TRUE,FALSE,tempstr); 

      // get any early notifications
      SetCommMask(ComID[portnum], EV_RXCHAR | EV_TXEMPTY | EV_ERR | EV_BREAK);

      // setup device buffers
      SetupComm(ComID[portnum], 2048, 2048);

      // purge any information in the buffer
      PurgeComm(ComID[portnum], PURGE_TXABORT | PURGE_RXABORT |
                           PURGE_TXCLEAR | PURGE_RXCLEAR );

      // set up for overlapped non-blocking I/O 
      CommTimeOuts.ReadIntervalTimeout = 0; 
      CommTimeOuts.ReadTotalTimeoutMultiplier = 20; 
      CommTimeOuts.ReadTotalTimeoutConstant = 40; 
      CommTimeOuts.WriteTotalTimeoutMultiplier = 20; 
      CommTimeOuts.WriteTotalTimeoutConstant = 40; 
      SetCommTimeouts(ComID[portnum], &CommTimeOuts);

      // setup the com port
      GetCommState(ComID[portnum], &dcb);

	  dcb.BaudRate = CBR_115200;             // current baud rate 
      dcb.fBinary = TRUE;                    // binary mode, no EOF check 
      dcb.fParity = FALSE;                   // enable parity checking 
      dcb.fOutxCtsFlow = FALSE;              // CTS output flow control 
      dcb.fOutxDsrFlow = FALSE;              // DSR output flow control 
      dcb.fDtrControl = DTR_CONTROL_ENABLE;  // DTR flow control type 
      dcb.fDsrSensitivity = FALSE;           // DSR sensitivity 
      dcb.fTXContinueOnXoff = TRUE;          // XOFF continues Tx 
      dcb.fOutX = FALSE;                     // XON/XOFF out flow control 
      dcb.fInX = FALSE;                      // XON/XOFF in flow control 
      dcb.fErrorChar = FALSE;                // enable error replacement 
      dcb.fNull = FALSE;                     // enable null stripping 
      dcb.fRtsControl = RTS_CONTROL_ENABLE;  // RTS flow control 
      dcb.fAbortOnError = FALSE;             // abort reads/writes on error 
      dcb.XonLim = 0;                        // transmit XON threshold 
      dcb.XoffLim = 0;                       // transmit XOFF threshold 
      dcb.ByteSize = 8;                      // number of bits/byte, 4-8 
      dcb.Parity = NOPARITY;                 // 0-4=no,odd,even,mark,space 
      dcb.StopBits = ONESTOPBIT;             // 0,1,2 = 1, 1.5, 2 
      dcb.XonChar = 0;                       // Tx and Rx XON character 
      dcb.XoffChar = 1;                      // Tx and Rx XOFF character 
      dcb.ErrorChar = 0;                     // error replacement character 
      dcb.EofChar = 0;                       // end of input character 
      dcb.EvtChar = 0;                       // received event character 

      fRetVal = SetCommState(ComID[portnum], &dcb);
   }

   // check if successfull
   if (!fRetVal)
   {
      CloseHandle(ComID[portnum]);
      ComID[portnum] = 0;
	  return false;
   }

   return true;
}