//-------------------------------------------------------------------
//  Change Port Settings
//
static int NT_ChangePortSettings (HANDLE hPort, unsigned int Speed, t_uchar DataBits, t_uchar Parity,
            t_uchar StopBits)
{
  int             Error      = 0;
  t_uchar      ParityEnable    = ( Parity == UART_PARITY_NONE ) ? ( FALSE ) : ( TRUE );
  DCB        ControlBlock;
  int             BaudRate    = 0;//  {  CBR_110,   CBR_300,   CBR_600,    CBR_1200,   CBR_2400,
                    //    CBR_4800,  CBR_9600,  CBR_14400,  CBR_19200,  CBR_38400,  
                    //    CBR_56000, CBR_57600, CBR_115200, CBR_128000, CBR_256000 };

  //Get current com port settings
  if ( (GetCommState( hPort, &ControlBlock )) == 0 ) //0 if fails
  {
    Error = GetLastError();
//    PrintError( "NT_ChangePortSettings:", "There was ERROR:", Error );
    return( Error );    
  }//end if 


//Convert Parity
  if ( Parity == UART_PARITY_ODD )
    Parity = ODDPARITY;    //1
  else if ( Parity == UART_PARITY_EVEN )
    Parity = EVENPARITY;  //2
  else
    Parity = NOPARITY;    //0

//Convert Baud Rate
  switch ( Speed )
  {
  case 4800:
    BaudRate = CBR_4800;
    break;
  case 9600:
    BaudRate = CBR_9600;
    break;
  case 115200:
    BaudRate = CBR_115200;
    break;
  default:
    BaudRate = CBR_4800;
    break;
  }//end switch

//Convert Stop Bits
  switch ( StopBits )
  {
  case 1:
    StopBits = ONESTOPBIT;
    break;
  case 2:
    StopBits = TWOSTOPBITS;
    break;
  default:
    StopBits = ONESTOPBIT;
    break;
  }//end switch

////////////////////////////////////////////////////////////////////////////////////
//            Change port settings
////////////////////////////////////////////////////////////////////////////////////
//    ControlBlock.DCBlength;                        // sizeof(DCB) 
    ControlBlock.BaudRate           = BaudRate;      // current baud rate 
//    ControlBlock.fBinary: 1;                      // binary mode, no EOF check 
    ControlBlock.fParity           = ParityEnable;  // enable parity checking 
    ControlBlock.fOutxCtsFlow      = 0;              // CTS output flow control 
    ControlBlock.fOutxDsrFlow      = 0;              // DSR output flow control 
    ControlBlock.fDtrControl       = DTR_CONTROL_ENABLE;// DTR flow control type 
    ControlBlock.fDsrSensitivity   = 0;              // DSR sensitivity 
    ControlBlock.fTXContinueOnXoff = 0;              // XOFF continues Tx 
    ControlBlock.fOutX             = 0;              // XON/XOFF out flow control
    ControlBlock.fInX              = 0;              // XON/XOFF in flow control 
//    ControlBlock.fErrorChar: 1;                    // enable error replacement 
//    ControlBlock.fNull: 1;                        // enable null stripping 
    ControlBlock.fRtsControl       = RTS_CONTROL_ENABLE;// RTS flow control 
//    ControlBlock.fAbortOnError:1;                  // abort reads/writes on error 
//    ControlBlock.fDummy2:17;                      // reserved 
//    ControlBlock.wReserved;                        // not currently used 
//    ControlBlock.XonLim;                          // transmit XON threshold 
//    ControlBlock.XoffLim;                          // transmit XOFF threshold 
    ControlBlock.ByteSize           = DataBits;      // number of bits/t_uchar, 4-8 
    ControlBlock.Parity             = Parity;        // 0-4=no,odd,even,mark,space 
    ControlBlock.StopBits           = StopBits;      // 0,1,2 = 1, 1.5, 2 
//    ControlBlock.XonChar;                          // Tx and Rx XON character 
//    ControlBlock.XoffChar;                        // Tx and Rx XOFF character 
//    ControlBlock.ErrorChar;                        // error replacement character 
//    ControlBlock.EofChar;                          // end of input character 
//    ControlBlock.EvtChar;                          // received event character 
//    ControlBlock.wReserved1;                      // reserved; do not use 

  //Set com port settings
  if ( (SetCommState( hPort, &ControlBlock )) == 0 ) // 0 if fails
  {
    Error = GetLastError();
//    PrintError( "SetCommState:", "There was ERROR:", Error );
  }//end if

return( Error );
}//end NT_ChangePortSettings