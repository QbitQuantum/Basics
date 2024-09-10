void Thread(void* arg) {
	int* i = (int*) arg;
	PutChar('T');
	PutInt(*i);
	PutChar('\n');
	(*i)--;
	if (*i > 0) {
		int tid = UserThreadCreate(Thread, arg);
		UserThreadJoin(tid);
	}
	UserThreadExit();
}