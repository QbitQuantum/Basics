void SimpleThread(void* which) {
    char* ch = (char*) which;
    int i;
    for (i = 0; i < 10; i++) {
        PutChar(*ch);
        PutInt(i);
        PutChar('\n');
    }
    UserThreadExit();
}