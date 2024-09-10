static void readf() {
	char msg[256];
	while (1) {
		receive (msg);
		kprint ("%s", msg);
		SEND("", 1, 1);
	}		
}