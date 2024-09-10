int XHCP_server (node_t* argXmlConfig)
{
	static const int zero=0;
	
    static int listener;
	static int conn;
    static pid_t  pid;
    //static struct sockaddr_in servaddr;
    static struct sockaddr_storage servaddr;
	
	static struct timeval time_conn, time_resp;
	
    static char *additionalDataBuffer=NULL;
    static int argc = 0;
    static char *argv[MAX_CMD_ARGS+1];
   
    static char	buffer[MAX_REQ_LINE] = {0};
	
	int		status, nbCar;
	// Variables non persistantes
	int sockV4, sockV6;
	struct addrinfo hints,  *list_addr, *p_adresse, *aiv4, *aiv6, *choix_ai;
	
	switch (XHCP_running_status)
	{
		/* ------------------------------------------------------------------------ */
		case (XHCPstate_init):

			XHCP_loadConfig(argXmlConfig);
    
    
			/*  Create socket  */
		//	if ( (listener = socket (AF_INET, SOCK_STREAM, 0)) < 0 )
		//		Error_Quit ("Couldn't create listening socket.");
			
			
			/*  Populate socket address structure  */
			memset (&hints, 0, sizeof(hints));
			hints.ai_family      = AF_UNSPEC;
			hints.ai_socktype     = SOCK_STREAM;
			hints.ai_flags        = AI_PASSIVE;
			if ( (getaddrinfo(NULL, XHCP_SERVER_PORT, &hints, &list_addr)) < 0 )
			{
				//printf("getaddrinfo: %s\n",gai_strerroe(flags));
				perror("getaddrinfo");
				exit(1);
			}
			
			sockV4=-1; sockV6=-1;
			p_adresse = list_addr;
			
			// Vérification des protocoles en testant l'ouverture d'une socket
			while (p_adresse)
			{
				if ( p_adresse->ai_family == AF_INET6)
				{
					if ( sockV6 < 0 )
					{
						printf("Scanning IPV6...");
						if ( (sockV6=socket(p_adresse->ai_family, p_adresse->ai_socktype, p_adresse->ai_protocol)) >= 0 )
						{
							aiv6 = p_adresse;
							printf(" found");
						}
						printf("\n");
					}
				}
				else if ( p_adresse->ai_family == AF_INET)
				{
					if ( sockV4 < 0 )
					{
						printf("Scanning IPV4...");
						if ( (sockV4=socket(p_adresse->ai_family, p_adresse->ai_socktype, p_adresse->ai_protocol)) >= 0 )
						{
							aiv4 = p_adresse;
							printf(" found");
						}
						printf("\n");
					}
				}
			p_adresse = p_adresse->ai_next;
			}

			// Selection de la socket
			if ( sockV6 >= 0 )
			{
				choix_ai = aiv6;
				listener = sockV6;
				// Tentative d'activation de la traduction IPV6->IPV4
				if ( setsockopt(sockV6, IPPROTO_IPV6, IPV6_V6ONLY, &zero, sizeof(zero)) < 0 )
				{
					perror("notice : setsockopt(IPV6_ONLY)");
					printf("IPV6 ONLY ! Tentative de passer en IPV4...\n");
					
					if (sockV4 >=0)
					{
						close(sockV6);
						sockV6 = -1;
					}
				}
				else
				{	//Traduction possible, on ferme l'ipv4
					if (sockV4 >= 0)
					{
						printf("IPV4 over IPV6 => close IPV4\n");
						close(sockV4);
						sockV4=-1;
					}
				}
			}
			
			if ( sockV4 >= 0 )
			{
				choix_ai = aiv4;
				listener = sockV4;
			}
			else if ( sockV6 < 0 )
			{
				Error_Quit ("Aucun protocole IPV4 ou IPV6 possible.");
			}
			
			
				
			
			/* "Address already in use" error message killer !!!! */
			int tr=1;
			if (setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&tr,sizeof(int)) == -1)
			{
				perror("setsockopt");
				exit(1);
			}
			
			/*  Assign socket address to socket  */
			if ( bind (listener, choix_ai->ai_addr, choix_ai->ai_addrlen) < 0 )
			{
				perror("Bind");
				Error_Quit ("Couldn't bind listening socket.");
			}
			
			/*  Make socket a listening socket  */
			if ( listen (listener, LISTENQ) < 0 )
				Error_Quit ("Call to listen failed.");
			
			int flags = fcntl(listener, F_GETFL );
			fcntl(listener, F_SETFL, flags | O_NONBLOCK );
			
			freeaddrinfo(list_addr);
			
			/* Diverses initialisations */
			XHCP_customWelcomeMessage ();
		
			/* L'initialisation est terminée, on passe à la suite */
			XHCP_running_status = XHCPstate_waitConnect;
			
			/* No break, we continue !!!*/
			
		/* ------------------------------------------------------------------------ */
		case (XHCPstate_waitConnect):
		
			/*  Wait for connection  */
			if ( (conn = accept (listener, NULL, NULL)) < 0 )
			{
				if ( (errno == EWOULDBLOCK) || (errno == EAGAIN) )
				{
					return XHCP_running_status;
				}
				else
					Error_Quit ("Error calling accept()");
			
			}
			//Gestion du timeout pour la bascule en mode commande
			gettimeofday(&time_conn, NULL);
			
			//XHCP_running_status = XHCPstate_waitCommand;
			XHCP_running_status = XHCPstate_waitHTTPRequest;
		
			/* No break, we continue !!!*/
			
		/* ------------------------------------------------------------------------ */
		case (XHCPstate_waitHTTPRequest):
		
			if ( (nbCar = recv(conn, buffer, MAX_REQ_LINE - 1, MSG_DONTWAIT)) <0 )
			{
				if ( (errno == EWOULDBLOCK) || (errno == EAGAIN) )
				{
					//TODO Gestion du timeout
					gettimeofday(&time_resp, NULL);
					if ( timerdiff(&time_conn, &time_resp) > 100000 )
					{
						// On passe en mode "Commande"
						XHCP_running_status = XHCPstate_waitCommand;
						XHCP_printXHCPResponse (conn, RES_HALWELCOM );  // Petit message de bienvenue
					}
					return XHCP_running_status;
				}
				else
					Error_Quit ("Error calling accept()");
			
			}
		
			buffer[nbCar]='\0';

			/* We suppress all extra characters */
			Trim (buffer, 0);

			
			processHttpRequest(conn, buffer);


			
			if ( close (conn) < 0 )
				Error_Quit ("Error closing connection socket in parent.");

			
			XHCP_running_status = XHCPstate_waitConnect;
			return  XHCP_running_status;

		/* ------------------------------------------------------------------------ */
		case (XHCPstate_waitCommand):
		
			if ( (nbCar = recv(conn, buffer, MAX_REQ_LINE - 1, MSG_DONTWAIT)) <0 )
			{
				if ( (errno == EWOULDBLOCK) || (errno == EAGAIN) )
				{
					//TODO Gestion du timeout
					return XHCP_running_status;
				}
				else
					Error_Quit ("Error calling accept()");
			
			}
			
			buffer[nbCar]='\0';

            Trim (buffer, 0); // We suppress all extra characters
                
			if ( buffer[0] == '\0' )
				return XHCP_running_status; // We continue....

			printf ("Ligne lue : %s\n", buffer);

			cut_Line (buffer, &argc, argv);

			printf ("%d arguments :\n", argc);
			int i;
			for ( i=0; i<argc; i++ )
				printf ( "%d - %s\n", i, argv[i]);

			status = exec_Line (conn, argc, argv ); // We compute the line...
			printf("Ligne executee, statut = %d\n",status);
			switch (status)
			{
				case -1:  // deconnexion
					XHCP_running_status = XHCPstate_endConnect;
					return XHCP_running_status;
					break;
				case 0:   // Fin de la commande
					return XHCP_running_status;
					break;
				// default : // On continue
			}

			XHCP_running_status = XHCPstate_waitData;
			
			/* No break, we continue !!!*/

		/* ------------------------------------------------------------------------ */
		case (XHCPstate_waitData):
			
			if ( (nbCar = recv(conn, buffer, MAX_REQ_LINE - 1, MSG_DONTWAIT)) <0 )
			{
				if ( (errno == EWOULDBLOCK) || (errno == EAGAIN) )
				{
					//TODO Gestion du timeout
					return XHCP_running_status;
				}
				else
					Error_Quit ("Error calling accept()");
			
			}

			buffer[nbCar]='\0';
			/* We suppress all extra characters on the right except '.' and '>' */
			Trim (buffer, 1);

			/* The handler is activate, so all lignes are added in buffer */
			if ( buffer[0] == '.' &&  buffer[1] == '\0')
			{
				additionalDataHandler (conn, argc, argv, additionalDataBuffer );
				additionalDataHandler = NULL;
				free (additionalDataBuffer);
				additionalDataBuffer = NULL;

				XHCP_running_status = XHCPstate_waitCommand;
			}
			else
			{
				additionalDataBuffer = addBuffer (additionalDataBuffer, buffer);
			}

			
			break;
			
		/* ------------------------------------------------------------------------ */
		case (XHCPstate_endConnect):
		
			XHCP_printXHCPResponse (conn, RES_CLOCONBYE ); 
			 
		    if ( close (conn) < 0 )
				Error_Quit ("Error closing connection socket in parent.");

			XHCP_running_status = XHCPstate_waitConnect;

			
		//default :  /* (XHCPstate_death) */
			/* Do nothing ... */
			
	}
	
	return XHCP_running_status;
}