int InitSerialPort(PortType Port, BaudrateType BaudRate, ParityType Parity,
					                int Bits, int Stopbits)
{
   /* Method data declaration      */
   char *PortId = "";
   COMMTIMEOUTS   NewTimeout = {0};
   DCB            DeviceControlBlock;

   /* Method code declaration      */

   /*check for correct port */
   switch (Port) {
      case COM1:
        PortId = "COM1";
	    break;

      case COM2 :
        PortId = "COM2";
	    break;

      case COM3 :
        PortId = "COM3";
        break;

      case COM4 :
        PortId = "COM4";
      	break;

      case COM5 :
        PortId = "COM5";
      	break;

      case COM6 :
        PortId = "COM6";
      	break;

      case COM7 :
        PortId = "COM7";
      	break;

      default:
	    return -1;
	    break;
   }

   /* Open the selected port */
   ComPort = CreateFile( PortId,
                         GENERIC_READ | GENERIC_WRITE,
                         0,
                         0,
                         OPEN_EXISTING,
                         0,
                         0);

   /* check if port could be openend */
   if(ComPort != INVALID_HANDLE_VALUE) {

      /* Set the comm timeouts such, that read returns immediately */
      /* independent if any bytes are availlable or not            */
      GetCommTimeouts(ComPort,&OldTimeout);
      NewTimeout.ReadIntervalTimeout = MAXDWORD;
      SetCommTimeouts(ComPort, &NewTimeout);

      /* Setup the device controlblock (Baudrate and other parameters) */
      DeviceControlBlock.DCBlength = sizeof(DCB);
      GetCommState(ComPort, &DeviceControlBlock);
      BuildCommDCB("baud=1200 parity=N data=8 stop=1", &DeviceControlBlock);
      switch (BaudRate) {
		case Bd600 :
           DeviceControlBlock.BaudRate = CBR_600;
		   break;

		case Bd1200 :
           DeviceControlBlock.BaudRate = CBR_1200;
		   break;

		case Bd2400 :
           DeviceControlBlock.BaudRate = CBR_2400;
	       break;

		case Bd4800 :
           DeviceControlBlock.BaudRate = CBR_4800;
	       break;

		case Bd9600 :
           DeviceControlBlock.BaudRate = CBR_9600;
	       break;

		case Bd19200 :
           DeviceControlBlock.BaudRate = CBR_19200;
	       break;

        default:
	       /* illegal baudrate... */
           ShutdownSerialPort();
	       return -2;
	       break;
      }
      switch (Bits) {
         case 5:
         case 6:
         case 7:
         case 8:
            DeviceControlBlock.ByteSize = Bits;
            break;

         default:
            ShutdownSerialPort();
	        return -3;
	        break;
      }
      switch (Stopbits) {
         case 1: DeviceControlBlock.StopBits = 0; break;  // 1 = 1.5
         case 2: DeviceControlBlock.StopBits = 2; break;
         default: ShutdownSerialPort(); return -4; break;
      }
      switch (Parity) {
         case P_NONE:  DeviceControlBlock.fParity = 0;
                     DeviceControlBlock.Parity  = 0;
                     break;
         case P_EVEN:  DeviceControlBlock.fParity = 1;
                     DeviceControlBlock.Parity  = 2;
                     break;
         case P_ODD:   DeviceControlBlock.fParity = 1;
                     DeviceControlBlock.Parity  = 1;
                     break;
         case P_MARK:  DeviceControlBlock.fParity = 1;
                     DeviceControlBlock.Parity  = 3;
                     break;
         case P_SPACE: DeviceControlBlock.fParity = 1;
                     DeviceControlBlock.Parity  = 4;
                     break;
         default:    ShutdownSerialPort();
                     return -5;
                     break;
      }
      SetCommState(ComPort, &DeviceControlBlock);
   }
   return 0;
}