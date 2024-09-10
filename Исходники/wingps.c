int main(int argc,char *argv[])
{
    int             status;
    char            ch;
	const char     *port;
	int             baud;
	HANDLE          h;

	/* require both arguments */
	if (argc != 3) {
		printf("%s <comport> <baud>\n",argv[0]);
		return 1;
	}

	/* serial port argument */
	port = argv[1];

	/* baud rate argument */
	status = sscanf(argv[2],"%d",&baud);
	if (status != 1) {
		printf("%s <comport> <baud>\n",argv[0]);
		printf("invalid <baud> : %s\n",argv[2]);
		return 1;
	}

	/** open the serial port */
	h = openPort(port,baud);
	if (h == INVALID_HANDLE_VALUE) {
		printf("can't open port : %s\n",port);
		return 1;
	}
    
	/* ---------------------------------------*/
	/*STEP 2 : initialize the nmea context    */                                                
	/* ---------------------------------------*/
    status = nmeap_init(&nmea,(void *)&user_data);
    if (status != 0) {
        printf("nmeap_init %d\n",status);
        exit(1);
    }
    
	/* ---------------------------------------*/
	/*STEP 3 : add standard GPGGA parser      */                                                
	/* -------------------------------------- */
    status = nmeap_addParser(&nmea,"GPGGA",nmeap_gpgga,0,&gga);
    if (status != 0) {
        printf("nmeap_add %d\n",status);
        exit(1);
    }

	/* ---------------------------------------*/
	/*STEP 4 : add standard GPRMC parser      */                                                
	/* -------------------------------------- */
    status = nmeap_addParser(&nmea,"GPRMC",nmeap_gprmc,0,&rmc);
    if (status != 0) {
        printf("nmeap_add %d\n",status);
        exit(1);
    }

	/* ---------------------------------------*/
	/*STEP 5 : process input until done       */                                                
	/* -------------------------------------- */
    for(;;) {
		/* ---------------------------------------*/
		/*STEP 6 : get a byte at a time           */                                                
		/* -------------------------------------- */
        ch = readPort(h);
        if (ch <= 0) {
            break;
        }
        
		/* --------------------------------------- */
		/*STEP 7 : pass it to the parser           */
		/* status indicates whether a complete msg */
		/* arrived for this byte                   */
		/* NOTE : in addition to the return status */
		/* the message callout will be fired when  */
		/* a complete message is processed         */
		/* --------------------------------------- */
        status = nmeap_parse(&nmea,ch);
        
		/* ---------------------------------------*/
		/*STEP 8 : process the return code        */                                                
		/* -------------------------------------- */
        switch(status) {
        case NMEAP_GPGGA:
			/* GOT A GPGGA MESSAGE */
            printGps(&gga,&rmc);
            break;
        case NMEAP_GPRMC:
			/* GOT A GPRMC MESSAGE */
            printGps(&gga,&rmc);
            break;
        default:
            break;
        }
    }

	/* close and quit */
	closePort(h);
    
    return 0;
}