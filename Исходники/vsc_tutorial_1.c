int main(int argc, char *argv[]) {
	struct timespec lastSent, timeNow, lastReceived, timeDiff;
	struct timeval timeout;
	int max_fd, vsc_fd, retval;
	fd_set input;

	/* Verify Arguments */
	if (argc != 3) {
		printf("Usage - program SerialPort BaudRate\n");
		printf("\t%s /dev/ttyUSB0 115200\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Catch CTRL-C */
	signal(SIGINT, signal_handler);

	/* Open VSC Interface */
	vscInterface = vsc_initialize(argv[1], atoi(argv[2]));
	if (vscInterface == NULL) {
		printf("Opening VSC Interface failed.\n");
		exit(EXIT_FAILURE);
	}

	/* Initialize the input set */
	vsc_fd = vsc_get_fd(vscInterface);
	FD_ZERO(&input);
	FD_SET(vsc_fd, &input);
	max_fd = vsc_fd + 1;

	/* Reset timing values to the current time */
	clock_gettime(CLOCK_REALTIME, &lastSent);
	clock_gettime(CLOCK_REALTIME, &lastReceived);

	/* Send Heartbeat Message to VSC */
	vsc_send_heartbeat(vscInterface, ESTOP_STATUS_NOT_SET);

	/* Loop Forever */
	while (1) {
		/* Get current clock time */
		clock_gettime(CLOCK_REALTIME, &timeNow);

		/* Send Heartbeat messages every 50 Milliseconds (20 Hz) */
		if (diffTime(lastSent, timeNow, &timeDiff) > 50000) {
			/* Get current clock time */
			lastSent = timeNow;

			/* Send Heartbeat */
			vsc_send_heartbeat(vscInterface, ESTOP_STATUS_NOT_SET);
		}

		/* Initialize the timeout structure for 50 milliseconds*/
		timeout.tv_sec = 0;
		timeout.tv_usec = (50000 - (diffTime(lastSent, timeNow, &timeDiff) * .001));

		/* Perform select on serial port or Timeout */
		FD_ZERO(&input);
		FD_SET(vsc_fd, &input);
		max_fd = vsc_fd + 1;

		retval = select(max_fd, &input, NULL, NULL, &timeout);

		/* See if there was an error */
		if (retval < 0) {
			fprintf(stderr, "vsc_example: select failed");
		} else if (retval == 0) {
			/* No data received - Check to see when we last recieved data from the VSC */
			clock_gettime(CLOCK_REALTIME, &timeNow);
			diffTime(lastReceived, timeNow, &timeDiff);

			if(timeDiff.tv_sec > 0) {
				printf("vsc_example: WARNING: No data received from VSC in %li.%09li seconds!\n",
						timeDiff.tv_sec, timeDiff.tv_nsec);
			}
		} else {
			/* Input received, check to see if its from the VSC */
			if (FD_ISSET(vsc_fd, &input)) {
				/* Read from VSC */
				readFromVsc();

				/* Record the last time input was recieved from the VSC */
				clock_gettime(CLOCK_REALTIME, &lastReceived);
			} else {
				fprintf(stderr, "vsc_example: invalid fd set");
			}
		}

	}

	/* Clean up */
	printf("Shutting down.\n");
	vsc_cleanup(vscInterface);

	return 0;
}