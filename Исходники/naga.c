int main(int argc, char * argv[]) {
	printf("Naga Epic Control v%d\n", VERSION);

	int retry = 0;
	int count = 0;

	while ((retry == 1 && count < 3) || count == 0) {
		count++;

		if (init() != 0) return 1;

		// Verbose mode
		if (scanArgs("-v", argv, argc)) {
			verbose = 1;
		}
		
		// Brightness control
		unsigned char brightness = 255;
		int tmp = scanArgs("-l", argv, argc);
		if (tmp) {
			if (tmp < argc - 1) tmp++;
			// Looking for number after -l
			brightness = atoi(argv[tmp]);
			// If number not found, looking for on or off
			if (strcmp(argv[tmp], "on") == 0) {
				brightness = 255;
			} else if (strcmp(argv[tmp], "off") == 0) {
				brightness = 0;
			}
			if (verbose) printf("[Debug] Brightness: %d\n", brightness);

			// Building command for mouse
			Lights_Brightness[10] = brightness;
			Lights_Brightness[11] = brightness ^ 3;

			sendcmd(Lights_Brightness);

			// Receiving and checking data
			if (recvcmd()[0] != 1) {
				printf("[Error] Command failed!\n");
				retry = 1;
			} else {
				retry = 0;
			}
		}

		closeHandle();
	}
	return 0;
}