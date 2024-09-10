int main(int argc, char* argv[])
{
    Cmt3 serial;
    Packet reply(1,0); /* 1 item, not xbus */
    (void) signal(SIGINT, ctrlchandler);
    atexit(exitFunc);
        
    char portname[32];
    if(argc > 1)
	strcpy(portname, argv[1]);

    if (strlen(portname) == 0)
        sprintf(portname, "/dev/ttyUSB0");

    if (serial.openPort(portname, B115200) != XRV_OK)
        EXIT_ERROR("open");
    printf("MT now in config mode\n");
    
	 //set the measurement timeout to 100ms (default is 16ms)
	int timeOut = 100;
	if (serial.setTimeoutMeasurement(timeOut) != XRV_OK)
		EXIT_ERROR("set timeout");
	printf("Measurement timeout set to %d ms\n", timeOut);
	
    CmtDeviceMode mode(CMT_OUTPUTMODE_ORIENT | CMT_OUTPUTMODE_CALIB, CMT_OUTPUTSETTINGS_TIMESTAMP_SAMPLECNT | CMT_OUTPUTSETTINGS_COORDINATES_NED | CMT_OUTPUTSETTINGS_ORIENTMODE_MATRIX | CMT_OUTPUTSETTINGS_CALIBMODE_ACCGYR, 100);
    if (serial.setDeviceMode(mode, false, CMT_DID_BROADCAST))
        EXIT_ERROR("set device mode");
    printf("Device modes set\n");

    

    if (serial.gotoMeasurement())
        EXIT_ERROR("goto measurement");
    printf("Now in measurement mode\n");

    FILE *fp;
    if(argc > 2) { fp = fopen(argv[2],"w"); }
    else { fp = fopen("./data.imu","w"); }

    if (fp == NULL) {
        perror("Failed to open file!");
        return EXIT_FAILURE;
    }

    long msgCount = 0;

struct timeval lasttime, newtime;

gettimeofday(&lasttime,NULL);
gettimeofday(&newtime,NULL);

double xpos = 0;
double xvel = 0;

CmtMatrix matrix_data;

    while (!quit)
    {
        if (serial.waitForDataMessage(&reply) != XRV_OK)
        {
            printf("\n");
            EXIT_ERROR("read data message");
        }

        msgCount++;

	matrix_data = reply.getOriMatrix();

//	long double cos_roll = cosl((long double)reply.getOriEuler().m_roll*2*M_PI/360);
//	long double cos_pitch = cosl((long double)reply.getOriEuler().m_pitch*2*M_PI/360);
//	long double sin_roll = sinl((long double)reply.getOriEuler().m_roll*2*M_PI/360);
//	long double sin_pitch = sinl((long double)reply.getOriEuler().m_pitch*2*M_PI/360);

	long double xacc = (long double) reply.getCalData().m_acc.m_data[0];
	long double yacc = (long double) reply.getCalData().m_acc.m_data[1];
	long double zacc = (long double) reply.getCalData().m_acc.m_data[2];

	long double xacc_comp = (long double) matrix_data.m_data[0][0]*xacc + matrix_data.m_data[1][0]*yacc + matrix_data.m_data[2][0]*zacc;
	long double yacc_comp = (long double) matrix_data.m_data[0][1]*xacc + matrix_data.m_data[1][1]*yacc + matrix_data.m_data[2][1]*zacc;
	long double zacc_comp = (long double) matrix_data.m_data[0][2]*xacc + matrix_data.m_data[1][2]*yacc + matrix_data.m_data[2][2]*zacc;

	long double yaw;

	if(matrix_data.m_data[0][1] < 0 && matrix_data.m_data[1][1] < 0) { yaw = 360*asinl(matrix_data.m_data[1][0])/2/M_PI; }
	else if(matrix_data.m_data[1][1] > 0) { yaw = 180 - 360*asinl(matrix_data.m_data[1][0])/2/M_PI; }
	else { yaw = 360 + 360*asinl(matrix_data.m_data[1][0])/2/M_PI; }
	

//	long double xacc_comp = (long double) cos_pitch*xacc + sin_pitch*zacc;
//	long double yacc_comp = (long double) sin_pitch*sin_roll*xacc + cos_roll*yacc - sin_roll*cos_pitch*zacc;
//	long double zacc_comp = (long double) -cos_roll*sin_pitch*xacc + sin_roll*yacc + cos_roll*cos_pitch*zacc;


       // fprintf(fp,"%3ld,%hu,%llu,%u,%f,%f,%f,%f,%f,%f\n",
	printf("%3ld \t %hu \t %lu \t %u  \t %f %f Yaw %Lf \t x %Lf \t y%Lf \t z %Lf \t x' %Lf \t y' %Lf \t z' %Lf %f \t %f\n",
            	msgCount,
            	reply.getSampleCounter(),              // sample counter
            	reply.m_rtc,                           // Time Of Arrival / Real-Time Clock
            	getTimeOfDay(),                         // timestamp

		matrix_data.m_data[1][1],matrix_data.m_data[0][1],
            	yaw ,      // yaw ps
	    	xacc ,
	    	yacc   ,
	    	zacc	,
	    
		xacc_comp ,
	    	yacc_comp   ,
	    	zacc_comp,

		xvel, xpos	

            );



xvel += xacc*10/1000;
xpos += xvel*10/1000;

//gettimeofday(&newtime,NULL);
//printf("Time %f\n",(double)(newtime.tv_usec - lasttime.tv_usec)/1000);
//lasttime = newtime;






    }

    fclose(fp);
    printf("\n\nDone reading\n");
    return 0;
}