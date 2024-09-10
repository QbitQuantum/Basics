// MAIN --------------------------------------------------------------
int main(int argc, char* argv[]) {
	if (argc < 4) {
		printf("Usage:\n\t%s <0 or 1 (server==1)> <test count> <roundtrip count> <server hostname>\n", argv[0]);
		exit(1);
	}
	bool isServer = false;
	if (atoi(argv[1]) == 1)
		isServer = true;
	int testCnt = atoi(argv[2]);
	int roundtripCount = atoi(argv[3]);

	int n;
    int msgSize;
    char* msgBody;

    // Set make a connection object
    Connection* pipe;
    pipe = new Connection();

	if (isServer)
	{
		pipe->initI(isServer, 54321, "");
		sleep(1);
        
        for (int test = 0; test < testCnt; test++) {
			for (int j = 0; j < 21; j++) {
				// Make msg
				msgSize = (int) pow(2,j);
				msgBody = (char*) malloc(msgSize + 1);
				if (msgBody == NULL) {
					printf("Couldn't malloc msgBody\n");
					exit(1);
				}
				memset(msgBody, 'a', msgSize);
				msgBody[msgSize + 1] = '\0';

				// Run test
				for (int i = 0; i < roundtripCount; i++) {
					int msgSizeRec = 0;
					char* recvMsg = (char*) pipe->receive(msgSizeRec);
					if (msgSizeRec != msgSize) {
						printf("Message of incorrect size received\n");
						return -1;
					}
					free(recvMsg);
					n = pipe->send(msgBody, msgSizeRec);
				}
			}
        }
	}
	else
	{
		timespec begin, end;
        unsigned long elapsed;
        double latency;

        // Perhaps, to get rid of busy sockets, we can inc the port num on each run?
		pipe->initI(isServer, 54321, argv[4]);
		sleep(1);

        for (int test = 0; test < testCnt; test++) {
			printf("Test %d\nMessage Size (Bytes),Average RTT/2 (us)\n", test);
			for (int j = 0; j < 21; j++) {
				// Make msg
				msgSize = (int) pow(2,j);
				msgBody = (char*) malloc(msgSize + 1);
				if (msgBody == NULL) {
					printf("Couldn't malloc msgBody\n");
					exit(1);
				}
				memset(msgBody, 'a', msgSize);
				msgBody[msgSize + 1] = '\0';

				// Run test
				long totElapsed = 0;
				for (int i = 0; i < roundtripCount; i++) {
                                        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin); 
					int msgSizeSend = 0;
					n = pipe->send(msgBody, msgSize);
					char* recvMsg = (char*) pipe->receive(msgSizeSend);
					if (msgSizeSend != msgSize) {
						printf("Message of incorrect size sent\n");
						// ^^ Error msg that make you look like an idiot if is pops up
						return -1;
					}
					free(recvMsg);
					clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
					timespec ts_elapsed = diff(end, begin);
					elapsed = (long)ts_elapsed.tv_sec*1000000 + (long)ts_elapsed.tv_nsec/1000;
					totElapsed += elapsed;
				}

				// Return test metrics
				latency = (double) totElapsed/(roundtripCount * 2); 
				printf("%d,%.2f\n", msgSize, (double) latency);
				sleep(1);
			}
                }
	}
    delete(pipe);
	free(msgBody);
	return 0;
}