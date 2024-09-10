void EndSignal(int sig){
	DB(fprintf(stderr,"EndSignal()\n"));
	CloseSocket();
	exit(0);
}