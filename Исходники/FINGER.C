int main (int argc, char* argv[])
{
	int c, lastc;
	struct in_addr defaddr;
	struct hostent *hp, def;
	struct sockaddr_in sin;
	int s, i;
	char *alist[1], *host;
	char request[100];
	char input[80];
	char* name;

	if (argc >= 2)
		{
		name = argv[1];
		}
	else
		{
		printf("user@hostname? ");
		fflush(stdout);
		name = input;
		do 
			{
			c = getchar();
			if (c=='\b')		/* DIY backspace processing */
				{
				if (name > input)
					name--;
				continue;
				}
			if (c=='\n' || c=='\r')
				break;
			*name++ = c;
			}
		while (name < input+78);
		*name++ = '\0';
		name = input;
		}
	host = strrchr(name, '@');
	if (host==0)
		{
		printf("Usage: finger user@hostname\n");
		exit(-2);
		}
	*host++ = NULL;

	/* Step 1 - resolve the IP address */

	printf("\nLooking up IP address of %s...\n", host);

	if (isdigit(*host) && (defaddr.s_addr = inet_addr(host)) != INADDR_ANY) 
		{
		def.h_name = host;
		def.h_addr_list = alist;
		def.h_addr = (char *)&defaddr;
		def.h_length = sizeof(struct in_addr);
		def.h_addrtype = AF_INET;
		def.h_aliases = 0;
		hp = &def;
		} 
	else
		{
		hp = gethostbyname(host);
		if(!hp) 
			{
			(void)fprintf(stderr, "finger: unknown host: %s\n", host);
			exit(-3);
			}
		}
	sin.sin_family = hp->h_addrtype;
	memcpy((char *)&sin.sin_addr, hp->h_addr, hp->h_length);
	if ((s = socket(hp->h_addrtype, SOCK_STREAM, 0)) < 0) {
		perror("finger: socket");
		exit(-4);
	}

	(void)printf("\n    %s => %s\n", hp->h_name, inet_ntoa(sin.sin_addr));

	/* Step 2 - Connect to the finger port on the target host */

	printf("\nConnecting to %s...", host);
	fflush(stdout);

	sin.sin_port = htons(IPPORT_FINGER);
	if (connect(s, (struct sockaddr *)&sin, sizeof (sin))) {
		perror("finger: connect");
		exit(-5);
	}

	printf("OK\n");

	/* Step 3 - Finger the user and read the result... */

	printf("\nFinger %s@%s\n", name, host);

	/* send the name followed by <CR><LF> */
	sprintf(request, "%s\r\n", name);
	if (write(s, request, strlen(request)) < 0) {
		perror("finger: write");
		close(s);
		exit(-6);
	}

	/* Read from the remote system; once we're connected, we assume some
	 * data.  If none arrives, we hang until the user interrupts.
	 *
	 * If we see a <CR> or a <CR> with the high bit set, treat it as
	 * a newline; if followed by a newline character, only output one
	 * newline.
	 *
	 * Otherwise, all high bits are stripped; if it isn't printable and
	 * it isn't a space, we can simply set the 7th bit.  Every ASCII
	 * character with bit 7 set is printable.
	 */
	lastc = '\n';

	while (recv(s, &request[0], 1, 0) > 0) {
		c = request[0];
		if (c == 0x0d) {
			if (lastc == '\r')	/* ^M^M - skip dupes */
				continue;
			c = '\n';
			lastc = '\r';
		} else {
			if (!isprint(c) && !isspace(c)) {
				c &= 0x7f;
				c |= 0x40;
			}
			if (lastc != '\r' || c != '\n')
				lastc = c;
			else {
				lastc = '\n';
				continue;
			}
		}
		putchar(c);
	}
	if (lastc != '\n')
		putchar('\n');
	close(s);

	/* Step 4 - Check the time on the remote machine as well */

	if ((s = socket(hp->h_addrtype, SOCK_STREAM, 0)) < 0) {
		perror("finger: socket");
		exit(-7);
	}

	sin.sin_port = htons(IPPORT_DAYTIME);
	if (connect(s, (struct sockaddr *)&sin, sizeof (sin))) {
		perror("finger: connect");
		exit(-8);
	}

	i = recv(s, request, sizeof(request)-1, 0);
	if (i<0)
		{
		perror("finger: recv");
		exit(-9);
		}
	request[i] = '\0';

	printf("\nThe time on %s is %s\n", host, request);
	close(s);

	return 0;
}