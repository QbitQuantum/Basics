char * getKey(void) {
	int i = 0;
	char * ret = (char *) Malloc(MAX_BUFFER);
	if (terminals[getTTY()].insertShellBuffer == 0) {
		if (getPID() == terminals[getTTY()].foregroundProcess) {
			terminals[getTTY()].blockedPID = getPID();
		}
		block();
	}
	for (; i < terminals[tty].insertShellBuffer; i++) {
		ret[i] = terminals[tty].shellBuffer[i];
	}
	ret[i] = '\0';
	cleanShellBuffer();
	return ret;
}