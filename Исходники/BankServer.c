int main(int argc, char *argv[])
{
    static struct sockaddr_in ZERO_SOCKADDR;

    WSADATA w;
    struct sockaddr_in client, server = ZERO_SOCKADDR;
    SOCKADDR *c = (SOCKADDR *)&client;
    int cLen = (int)sizeof(struct sockaddr_in);
    int sd = 0;
    char *dbPath = NULL;
    unsigned short port = 0;
    User *head = NULL;
	char doLogin = FALSE;
	char doShutDown = FALSE;
	time_t currTime;
	int option = 0;
	char ipAddr[MAX_IP_LEN];
	char initialized = FALSE;

    // Test for correct number of arguments
    if (argc != 3)
    {
       usage();
       exit(0);
    }

    dbPath = argv[1];
    port = atoi(argv[2]);

    // Validate port number
    if (!port || port < 256 || port > 65535)
    {
        fprintf(stderr, "Invalid port number.\n");
        usage();
        exit(0);
    }
    
    // Open and parse the database file
    head = readDatabase(dbPath);
    if (!head)
        DieWithError("Error reading database file.\n");

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 0), &w))
        DieWithError("WSAStartup() failed.");

    // Open a datagram socket
    sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sd == INVALID_SOCKET)
        DieWithError("Could not create socket.\n");

    // Clear out server struct
    server = ZERO_SOCKADDR;

    // Set family, port, and address
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind to the local address
    if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) == SOCKET_ERROR)
    {
        closesocket(sd);
        DieWithError("bind() failed");
    }

    printf("\nWaiting for connection...\n\n");

    for (;;) // Run forever
    {
		char buffer[BUFFER_SIZE];
		User *clientUser;

		// Shut down the server if the flag is set
		if (doShutDown == TRUE)
			break;

		// Wait for client to send initial packet to confirm connection
		if (!doLogin && recvDecrypt(sd, buffer, BUFFER_SIZE, c, &cLen) == SOCKET_ERROR)
		{
			fprintf(stderr, "recvfrom() failed.\n");
			continue;
		}

		// Login on initial connection and if flag is set
		if(!strcmp(buffer, "connect") || doLogin)
		{
			// Get IP address if first transmission
			if (!initialized)
			{	
				recvDecrypt(sd, buffer, BUFFER_SIZE, c, &cLen);
				sscanf(buffer, "%s", &ipAddr);
			}

			// Loop until successful login
			while (!(clientUser = login(sd, c, cLen, head, ipAddr)))
				sendEncrypt(sd, "\nInvalid credentials. Please try again.\n", BUFFER_SIZE, 0, c, cLen);
			initialized = TRUE;
		}

		// Display successful login
		currTime = time(NULL);
        printf("%.24s : %s %s has logged in from %s.\n", ctime(&currTime), clientUser->firstName,
            clientUser->lastName, clientUser->ipAddr);

        sprintf(buffer, "\n\nLogin successful. Welcome, %s %s!\n",
            clientUser->firstName, clientUser->lastName);
        sendEncrypt(sd, buffer, BUFFER_SIZE, 0, c, cLen);

        sprintf(buffer, "User type: %s\n", clientUser->userType == 'C' ? "Customer" : "Manager");
        sendEncrypt(sd, buffer, BUFFER_SIZE, 0, c, cLen);

        if ((long long)clientUser->lastLogin > 0)
		    sprintf(buffer, "Last login: %.24s\n", ctime(&clientUser->lastLogin)); 
	    else
		    sprintf(buffer, "Last login: N/A\n");
	    sendEncrypt(sd, buffer, BUFFER_SIZE, 0, c, cLen);

		sprintf(buffer, "Last IP address: %s\n\n", clientUser->ipAddr);
        sendEncrypt(sd, buffer, BUFFER_SIZE, 0, c, cLen);

        // Set the last login time to the current time
        clientUser->lastLogin = currTime;

        // Initialize login flag
		doLogin = FALSE;

        while (doLogin == FALSE && doShutDown == FALSE)
        {
            // Print menu for correct user type
            switch(clientUser->userType) {

            case 'M': // Manager
                sendEncrypt(sd, "\nRequest Code\t Action\n\n", BUFFER_SIZE, 0, c, cLen);
                sendEncrypt(sd, "1\t\t Report balance of a selected customer\n", BUFFER_SIZE, 0, c, cLen);
                sendEncrypt(sd, "2\t\t Transfer money between two accounts\n", BUFFER_SIZE, 0, c, cLen);
                sendEncrypt(sd, "3\t\t Add a new customer to the system\n", BUFFER_SIZE, 0, c, cLen);
                sendEncrypt(sd, "4\t\t See the list of customers and their account information\n", BUFFER_SIZE, 0, c, cLen);
                sendEncrypt(sd, "5\t\t Report customer accounts sorted by balance\n", BUFFER_SIZE, 0, c, cLen);
                sendEncrypt(sd, "6\t\t See the total balance of all customers\n", BUFFER_SIZE, 0, c, cLen);
                sendEncrypt(sd, "7\t\t Shut down the server\n", BUFFER_SIZE, 0, c, cLen);
                sendEncrypt(sd, "8\t\t Logout\n", BUFFER_SIZE, 0, c, cLen);
                break;

            case 'C': // Customer
                sendEncrypt(sd, "Request Code\t Action\n", BUFFER_SIZE, 0, c, cLen);
                sendEncrypt(sd, "1\t\t Report balance of the customer\n", BUFFER_SIZE, 0, c, cLen);
                sendEncrypt(sd, "2\t\t Transfer money to another customer account\n", BUFFER_SIZE, 0, c, cLen);
                sendEncrypt(sd, "3\t\t Change password\n", BUFFER_SIZE, 0, c, cLen);
                sendEncrypt(sd, "4\t\t Logout\n", BUFFER_SIZE, 0, c, cLen);
                break;

            default:    // Shouldn't reach here since it loops until successful login.
                break;
            }

            sendEncrypt(sd, "\nPlease enter a Request Code: ", BUFFER_SIZE, 0, c, cLen);
            sendDone(sd, c, cLen);

            // Blocking wait for menu option from client
            if(recvDecrypt(sd, buffer, BUFFER_SIZE, c, &cLen) == (BUFFER_SIZE+1)) { doLogin = TRUE; continue; }

			// Get user input
			if (sscanf(buffer, "%d", &option) != 1)
				option = -1;

            // Perform appropriate action
            if (clientUser->userType == 'M')  // Manager
            {
                switch(option) {
                    case 1: if(seeBalanceSelected(sd, c, cLen, head) == -1){ doLogin = TRUE;} break;
                    case 2: if(transferBetweenAccounts(sd, c, cLen, head) == -1){ doLogin = TRUE;} break;
                    case 3: if(addNewCustomer(sd, c, cLen, &head) == -1){ doLogin = TRUE;} break;
                    case 4: listCustomers(sd, c, cLen, head); break;
                    case 5: sortByBalance(sd, c, cLen, &head); listCustomers(sd, c, cLen, head); break;
                    case 6: totalBalanceOfAll(sd, c, cLen, head); break;
                    case 7: doShutDown = TRUE; break;	// Sets flag to shut down server
                    case 8: doLogin = TRUE; break;		// Sets flag to loop back to login state
                    default: sendEncrypt(sd, "\n\nInvalid input. Please enter a valid option.\n\n", BUFFER_SIZE, 0, c, cLen); break;
                }
            }
            else if (clientUser->userType == 'C') // Customer
            {
                switch(option) {
                    case 1: seeUserBalance(sd, c, cLen, clientUser); break;
                    case 2: if(transferToCustomer(sd, c, cLen, clientUser, head) == -1){ doLogin = TRUE;} break;
                    case 3: if(changePassword(sd, c, cLen, clientUser) == -1){ doLogin = TRUE;} break;
                    case 4: doLogin = TRUE; break; // Sets flag to loop back to login state
                    default: sendEncrypt(sd, "\n\nInvalid input. Please enter a valid option.\n\n", BUFFER_SIZE, 0, c, cLen); break;
                }
            }
            else{}
        }
		// Reached when log out OR shut down flag is set to true
		sendEncrypt(sd, "\n\nLogging out.", BUFFER_SIZE, 0, c, cLen);
		currTime=time(NULL);
		printf("%.24s : %s %s has logged out.\n\n", ctime(&currTime), clientUser->firstName, clientUser->lastName);
		writeDatabase(dbPath, head);

		if (doShutDown == FALSE)
			sendEncrypt(sd, BORDER, BUFFER_SIZE, 0, c, cLen);
    }
    // Reached when shut down flag is set to true
	sendEncrypt(sd, BORDER, BUFFER_SIZE, 0, c, cLen);
	sendEncrypt(sd, "\nThe server has shut down. Client is closing. Thank you.\n\n", BUFFER_SIZE, 0, c, cLen);
	sendEncrypt(sd, "close", BUFFER_SIZE, 0, c, cLen);	// message to close the client
	printf("Server is shutting down by client request.\n\n");
}