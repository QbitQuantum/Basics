/* Start a new race. */
static void
newrace(int index, tCarElt* car, tSituation *s)
{

    total_tics[index]=0;

    /***********************************************************************************
    ************************* UDP client identification ********************************
    ***********************************************************************************/

    bool identified=false;
    char line[UDP_MSGLEN];

    // Set timeout
    if (getTimeout()>0)
    	UDP_TIMEOUT = getTimeout();

    //Set sensor range
    if (strcmp(getVersion(),"2009")==0)
    {
    	__SENSORS_RANGE__ = 100;
    	printf("*****2009*****\n");
    }
    else if (strcmp(getVersion(),"2010")==0 || strcmp(getVersion(),"2011")==0)
        __SENSORS_RANGE__ = 200;
    else
    {
    	printf("%s is not a recognized version",getVersion());
    	exit(0);
    }

    listenSocket[index] = socket(AF_INET, SOCK_DGRAM, 0);
    if (listenSocket[index] < 0)
    {
        std::cerr << "Error: cannot create listenSocket!";
        exit(1);
    }

    srand(time(NULL));

    // Bind listen socket to listen port.
    serverAddress[index].sin_family = AF_INET;
    serverAddress[index].sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress[index].sin_port = htons(getUDPListenPort()+index);

    if (bind(listenSocket[index],
             (struct sockaddr *) &serverAddress[index],
             sizeof(serverAddress[index])) < 0)
    {
        std::cerr << "cannot bind socket";
        exit(1);
    }

    // Wait for connections from clients.
    listen(listenSocket[index], 5);

    std::cout << "Waiting for request on port " << getUDPListenPort()+index << "\n";

    // Loop until a client identifies correctly
    while (!identified)
    {

        clientAddressLength[index] = sizeof(clientAddress[index]);

        // Set line to all zeroes
        memset(line, 0x0, UDP_MSGLEN);
        if (recvfrom(listenSocket[index], line, UDP_MSGLEN, 0,
                     (struct sockaddr *) &clientAddress[index],
                     &clientAddressLength[index]) < 0)
        {
            std::cerr << "Error: problem in receiving from the listen socket";
            exit(1);
        }

#ifdef __UDP_SERVER_VERBOSE__
        // show the client's IP address
        std::cout << "  from " << inet_ntoa(clientAddress[index].sin_addr);

        // show the client's port number.
        std::cout << ":" << ntohs(clientAddress[index].sin_port) << "\n";

        // Show the line
        std::cout << "  Received: " << line << "\n";
#endif

        // compare received string with the ID
        if (strncmp(line,UDP_ID,3)==0)
        {
#ifdef __UDP_SERVER_VERBOSE__
            std::cout << "IDENTIFIED" << std::endl;
#endif
            std::string initStr(line);
            if (SimpleParser::parse(initStr,std::string("init"),trackSensAngle[index],19)==false)
            {
            	for (int i = 0; i < 19; ++i) {
            		trackSensAngle[index][i] =-90 + 10*i;
				}
            }
//            char line[UDP_MSGLEN];
            sprintf(line,"***identified***");
            // Sending the car state to the client
            if (sendto(listenSocket[index], line, strlen(line) + 1, 0,
                       (struct sockaddr *) &clientAddress[index],
                       sizeof(clientAddress[index])) < 0)
                std::cerr << "Error: cannot send identification message";
            identified=true;
        }
    }

	focusSens[index] = new Sensors(car, 5);//ML
	for (int i = 0; i < 5; ++i) {//ML
		focusSens[index]->setSensor(i,(car->_focusCmd)+i-2,200);//ML
	}//ML

    // Initialization of track sensors
    trackSens[index] = new Sensors(car, 19);
    for (int i = 0; i < 19; ++i) {
    	trackSens[index]->setSensor(i,trackSensAngle[index][i],__SENSORS_RANGE__);
#ifdef __UDP_SERVER_VERBOSE__
    	std::cout << "Set Track Sensors " << i+1 << " at angle " << trackSensAngle[index][i] << std::endl;
#endif
	}
    // Initialization of opponents sensors
    oppSens[index] = new ObstacleSensors(36, curTrack, car, s, __SENSORS_RANGE__);

    prevDist[index]=-1;
}