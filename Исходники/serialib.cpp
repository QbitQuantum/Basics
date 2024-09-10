/*!
     \brief Open the serial port
     \param Device : Port name (COM1, COM2, ... for Windows ) or (/dev/ttyS0, /dev/ttyACM0, /dev/ttyUSB0 ... for linux)
     \param Bauds : Baud rate of the serial port.

                \n Supported baud rate for Windows :
                        - 110
                        - 300
                        - 600
                        - 1200
                        - 2400
                        - 4800
                        - 9600
                        - 14400
                        - 19200
                        - 38400
                        - 56000
                        - 57600
                        - 115200
                        - 128000
                        - 256000

               \n Supported baud rate for Linux :\n
                        - 110
                        - 300
                        - 600
                        - 1200
                        - 2400
                        - 4800
                        - 9600
                        - 19200
                        - 38400
                        - 57600
                        - 115200

     \return 1 success
     \return -1 device not found
     \return -2 error while opening the device
     \return -3 error while getting port parameters
     \return -4 Speed (Bauds) not recognized
     \return -5 error while writing port parameters
     \return -6 error while writing timeout parameters
  */
char serialib::Open(const char *Device,const unsigned int Bauds)
{
#if defined (_WIN32) || defined( _WIN64)

    // Open serial port
    hSerial = CreateFileA(  Device,GENERIC_READ | GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    if(hSerial==INVALID_HANDLE_VALUE) {
        if(GetLastError()==ERROR_FILE_NOT_FOUND)
            return -1;                                                  // Device not found
        return -2;                                                      // Error while opening the device
    }

    // Set parameters
    DCB dcbSerialParams = {0};                                          // Structure for the port parameters
    dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))                       // Get the port parameters
        return -3;                                                      // Error while getting port parameters
    switch (Bauds)                                                      // Set the speed (Bauds)
    {
    case 110  :     dcbSerialParams.BaudRate=CBR_110; break;
    case 300  :     dcbSerialParams.BaudRate=CBR_300; break;
    case 600  :     dcbSerialParams.BaudRate=CBR_600; break;
    case 1200 :     dcbSerialParams.BaudRate=CBR_1200; break;
    case 2400 :     dcbSerialParams.BaudRate=CBR_2400; break;
    case 4800 :     dcbSerialParams.BaudRate=CBR_4800; break;
    case 9600 :     dcbSerialParams.BaudRate=CBR_9600; break;
    case 14400 :    dcbSerialParams.BaudRate=CBR_14400; break;
    case 19200 :    dcbSerialParams.BaudRate=CBR_19200; break;
    case 38400 :    dcbSerialParams.BaudRate=CBR_38400; break;
    case 56000 :    dcbSerialParams.BaudRate=CBR_56000; break;
    case 57600 :    dcbSerialParams.BaudRate=CBR_57600; break;
    case 115200 :   dcbSerialParams.BaudRate=CBR_115200; break;
    case 128000 :   dcbSerialParams.BaudRate=CBR_128000; break;
    case 256000 :   dcbSerialParams.BaudRate=CBR_256000; break;
    default : return -4;
}
    dcbSerialParams.ByteSize=8;                                         // 8 bit data
    dcbSerialParams.StopBits=ONESTOPBIT;                                // One stop bit
    dcbSerialParams.Parity=NOPARITY;                                    // No parity
    if(!SetCommState(hSerial, &dcbSerialParams))                        // Write the parameters
        return -5;                                                      // Error while writing

    // Set TimeOut
    timeouts.ReadIntervalTimeout=0;                                     // Set the Timeout parameters
    timeouts.ReadTotalTimeoutConstant=MAXDWORD;                         // No TimeOut
    timeouts.ReadTotalTimeoutMultiplier=0;
    timeouts.WriteTotalTimeoutConstant=MAXDWORD;
    timeouts.WriteTotalTimeoutMultiplier=0;
    if(!SetCommTimeouts(hSerial, &timeouts))                            // Write the parameters
        return -6;                                                      // Error while writting the parameters
    return 1;                                                           // Opening successfull

#endif
#ifdef __linux__
    struct termios options;                                             // Structure with the device's options


    // Open device
    fd = open(Device, O_RDWR | O_NOCTTY | O_NDELAY);                    // Open port
    if (fd == -1) return -2;                                            // If the device is not open, return -1
    fcntl(fd, F_SETFL, FNDELAY);                                        // Open the device in nonblocking mode

    // Set parameters
    tcgetattr(fd, &options);                                            // Get the current options of the port
    bzero(&options, sizeof(options));                                   // Clear all the options
    speed_t         Speed;
    switch (Bauds)                                                      // Set the speed (Bauds)
    {
    case 110  :     Speed=B110; break;
    case 300  :     Speed=B300; break;
    case 600  :     Speed=B600; break;
    case 1200 :     Speed=B1200; break;
    case 2400 :     Speed=B2400; break;
    case 4800 :     Speed=B4800; break;
    case 9600 :     Speed=B9600; break;
    case 19200 :    Speed=B19200; break;
    case 38400 :    Speed=B38400; break;
    case 57600 :    Speed=B57600; break;
    case 115200 :   Speed=B115200; break;
    default : return -4;
}
    cfsetispeed(&options, Speed);                                       // Set the baud rate at 115200 bauds
    cfsetospeed(&options, Speed);
    options.c_cflag |= ( CLOCAL | CREAD |  CS8);                        // Configure the device : 8 bits, no parity, no control
    options.c_iflag |= ( IGNPAR | IGNBRK );
    options.c_cc[VTIME]=0;                                              // Timer unused
    options.c_cc[VMIN]=0;                                               // At least on character before satisfy reading
    tcsetattr(fd, TCSANOW, &options);                                   // Activate the settings
    return (1);                                                         // Success
#endif
}