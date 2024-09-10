void Thread2(void* arg) {
	int tid = *(int*) arg;
	int i;
	for (i = 0; i < 500; i++) {
		PutChar('d');
	}
	PutChar('Q');
	UserThreadJoin(tid);
	PutChar('Z');
	UserThreadExit();
}