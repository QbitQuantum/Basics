int main(int argc, char* argv[])
{
    int i = 0;
    msg_type messages[4];
    unsigned num_msg = sizeof(messages) / sizeof(messages[0]);
    struct timespec timeread;
    struct timespec timedelay;
    int fd = -1;
    char* port = "/dev/can1";
    char line[1024];
    char* read = NULL;
    int linenum = 0;
    uint8_t extended = 0;
    int nmax = 0;
    int opt = 0;
    int verbose = 0;

    // parse the command-line args
    while ((opt = getopt(argc, argv, "e:n:p:v:z")) != -1)
    {
	printf ("opt = %d\n", opt);
	switch (opt)
	{
	case 'e':
	    extended = 1;
	    break;
	case 'n':
	    nmax = atoi(optarg);
	    break;
	case 'p':
	    port = strdup(optarg);
	    break;
	case 'v':
	    verbose = 1;
	    break;
	}
    }

    memset(messages, 0, sizeof(messages));
    for (i = 0; i < num_msg; ++i)
    {
	messages[i].frequency = i * 10 + 10; // 10Hz, 20Hz, 30Hz, etc...
	messages[i].period = 1000 / messages[i].frequency;
    }

    // read 10 lines of messages from stdin
    read = fgets(line, sizeof(line), stdin);
    while ((int)read != EOF && read != NULL)
    {
	char* token = strtok(line, " \t");
	int num_msg_incoming = atoi(token);
	int id;

	// check number of messages matches the number we can store
	if (num_msg_incoming != num_msg)
	{
	    fprintf(stderr, "number of messages don't match: %d, %d\n",
		    num_msg_incoming, num_msg);
	    continue;
	}

	
	for (i = 0; i < num_msg_incoming; i++)
	{
	    msg_descriptor_t* p = NULL;
	    uint64_t msg_raw = 0;
	    
	    token = strtok(NULL, " \t");
	    id = atoi(token);
	    p = &msg_descriptors[id / 100 - 1];

	    if (messages[i].id != p->identifier)
	    {
		if (messages[i].id == 0)
		    messages[i].id = p->identifier;
		else
		{
		    fprintf(stderr, "identifers don't match.");
		    continue;
		}
	    }

	    msg_raw = parse_msg_input(p, NULL, NULL);
	    messages[i].data[linenum] = msg_raw;

	    if (verbose)
	    {
		printf ("msg parsed: ");
		print_data(msg_raw);
		putchar('\n');
	    }
	}

	linenum++;
	read = fgets(line, sizeof(line), stdin);
    }

    puts("input data correctly parsed.");

    // initialize the timedelay structure
    timedelay.tv_sec = 0;
    timedelay.tv_nsec = 10000000;   /* 10 millsecs */

    // open can port
    fd = can_open(port, O_WRONLY);
    if (fd == -1)
    {
	fprintf (stderr, "error opening %s\n", port);
	exit(1);
    }
    printf ("can port opened. fd = %d\n", fd);

    // keep on sending data until someone decides to press ctrl+C
    for (;;) 
    {
	unsigned now_ms;

	clock_gettime(CLOCK_REALTIME, &timeread);
	now_ms = timeread.tv_sec * 1000 + timeread.tv_nsec / 1000000;

	for (i = 0; i < num_msg; ++i)
	{
	    // see how long it has been since that message was last sent
	    unsigned long diff = now_ms - messages[i].lastsent;

	    // if longer than period, send again
	    if (diff >= messages[i].period)
	    {
		int rand_msg = rand() % 10;
		can_write(fd, 
			  messages[i].id, 
			  0, 
			  &messages[i].data[rand_msg], // pick random
			  8);
		
		if (verbose)
		{
		    printf ("msg sent: i=%d, id=%d, msg_index=%d, data= ",
			    i, messages[i].id,
			    rand_msg);
		    print_data(messages[i].data[rand_msg]);
		    putchar('\n');
		}
		    

		messages[i].lastsent = now_ms;
	    }
	}

	// sleep for 10 ms to avoid using all the cpu
//	nanosleep(&timedelay, NULL);
    }
    
    return 0;
}