int OpenComport(int comport_number, int baudrate)
{
    int baudr;

    if((comport_number>21)||(comport_number<0))
    {
        printf("illegal comport number\n");
        return(1);
    }

    switch(baudrate)
    {
    case      50 :
        baudr = B50;
        break;
    case      75 :
        baudr = B75;
        break;
    case     110 :
        baudr = B110;
        break;
    case     134 :
        baudr = B134;
        break;
    case     150 :
        baudr = B150;
        break;
    case     200 :
        baudr = B200;
        break;
    case     300 :
        baudr = B300;
        break;
    case     600 :
        baudr = B600;
        break;
    case    1200 :
        baudr = B1200;
        break;
    case    1800 :
        baudr = B1800;
        break;
    case    2400 :
        baudr = B2400;
        break;
    case    4800 :
        baudr = B4800;
        break;
    case    9600 :
        baudr = B9600;
        break;
    case   19200 :
        baudr = B19200;
        break;
    case   38400 :
        baudr = B38400;
        break;
    case   57600 :
        baudr = B57600;
        break;
    case  115200 :
        baudr = B115200;
        break;
    case  230400 :
        baudr = B230400;
        break;
    case  460800 :
        baudr = B460800;
        break;
    case  500000 :
        baudr = B500000;
        break;
    case  576000 :
        baudr = B576000;
        break;
    case  921600 :
        baudr = B921600;
        break;
    case 1000000 :
        baudr = B1000000;
        break;
    default      :
        printf("invalid baudrate\n");
        return(1);
        break;
    }

    Cport[comport_number] = open(comports[comport_number], O_RDWR | O_NOCTTY | O_NDELAY);
    if(Cport[comport_number]==-1)
    {
        perror("unable to open comport ");
        return(1);
    }

    error = tcgetattr(Cport[comport_number], old_port_settings + comport_number);
    if(error==-1)
    {
        close(Cport[comport_number]);
        perror("unable to read portsettings ");
        return(1);
    }
    memset(&new_port_settings, 0, sizeof(new_port_settings));  /* clear the new struct */

    new_port_settings.c_cflag = baudr | CS8 | CLOCAL | CREAD;
    new_port_settings.c_iflag = IGNPAR;
    new_port_settings.c_oflag = 0;
    new_port_settings.c_lflag = 0;
    new_port_settings.c_cc[VMIN] = 0;      /* block untill n bytes are received */
    new_port_settings.c_cc[VTIME] = 0;     /* block untill a timer expires (n * 100 mSec.) */
    error = tcsetattr(Cport[comport_number], TCSANOW, &new_port_settings);
    if(error==-1)
    {
        close(Cport[comport_number]);
        perror("unable to adjust portsettings ");
        return(1);
    }

    return(0);
}