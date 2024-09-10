int serveur_tcp (const char * nom_service)
{
	int err;
	int sock_serveur;
	int sock_connectee;
	struct addrinfo  hints;
	struct addrinfo *results;

	struct sockaddr_in * addr_in;
	socklen_t length = 0;
	char hostname [NI_MAXHOST];
	char servname [NI_MAXSERV];

	// Creer la socket serveur et lui attribuer un numero de service.
	if ((sock_serveur = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket");
		return -1;
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((err = getaddrinfo(NULL, nom_service,  &hints, &results)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
		close(sock_serveur);
		return -1;
	}

	err = bind(sock_serveur, results->ai_addr, results->ai_addrlen);
	freeaddrinfo(results);
	if (err < 0) {
		perror("bind");
		close(sock_serveur);
		return -1;
	}

	// Afficher notre adresse locale.
	fprintf(stdout, "Mon adresse >> ");
	length = sizeof(struct sockaddr_in);
	if (getsockname(sock_serveur, (struct sockaddr *) &addr_in, &length) < 0) {
		perror ("getsockname");
		return -1;
	}
	if (getnameinfo((struct sockaddr *) &addr_in, length,
	                hostname, NI_MAXHOST,
	                servname, NI_MAXSERV,
	                NI_NUMERICHOST | NI_NUMERICSERV) == 0) 
		fprintf (stdout, "IP = %s, Port = %s \n", hostname, servname);

	listen(sock_serveur, 5);

	while (! quitter_le_serveur()) {
		sock_connectee = accept(sock_serveur, NULL, NULL);
		if (sock_connectee < 0) {
			perror("accept");
			return -1;
		}
		switch (fork()) {
			case 0 : // fils
				close(sock_serveur);
				traite_connexion(sock_connectee);
				exit(EXIT_SUCCESS);
			case -1 :
				perror("fork");
				return -1;
			default : // pere
				close(sock_connectee);
		}
	}
	return 0;
}