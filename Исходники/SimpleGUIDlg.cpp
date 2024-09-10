void myThreadFunc(LPVOID lpvThreadParam) {
	int i;
	char message[100];
    char cTime[9];
	for (i = 0; i < 10; i++) {
		count++;
		strcpy(message, "Integer changed to ");
		strcat(message, itoa(count, cTime,10));
		strcat(message, " by thread ");
		strcat(message,  (char*) lpvThreadParam);
		strcat(message, " at ");
        _strtime( cTime );
		strcat(message, cTime);
		strcat(message, RETURN);
		PostMessage(winHandle, UPDATE_DATA, 0, (long)message);
		Sleep(500);
	}
	threadcount--;
	strcpy(message, "Thread ");
	strcat(message, (char*) lpvThreadParam);
	strcat(message, " exited!!!!!!!!!!!!!");
	PostMessage(winHandle, UPDATE_DATA, 0, (long)message);
	Sleep(100);
	PostMessage(winHandle, UPDATE_DATA, 0, (long)message);
	ExitThread(0);

}