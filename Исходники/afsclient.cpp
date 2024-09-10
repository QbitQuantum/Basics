int main (int argc, char * const argv[]) 
{
	// allocate a struct for storing our state
	MyData* myData = (MyData*)calloc(1, sizeof(MyData));
	
	// initialize a mutex and condition so that we can block on buffers in use.
	pthread_mutex_init(&myData->mutex, NULL);
	pthread_cond_init(&myData->cond, NULL);
	pthread_cond_init(&myData->done, NULL);
	
	// get connected
	int connection_socket = MyConnectSocket();
	if (connection_socket < 0) return 1;
	printf("connected\n");

	// allocate a buffer for reading data from a socket
	const size_t kRecvBufSize = 40000;
	char* buf = (char*)malloc(kRecvBufSize * sizeof(char));

	// create an audio file stream parser
	OSStatus err = AudioFileStreamOpen(myData, MyPropertyListenerProc, MyPacketsProc, 
							kAudioFileAAC_ADTSType, &myData->audioFileStream);
	if (err) { PRINTERROR("AudioFileStreamOpen"); return 1; }
	
	while (!myData->failed) {
		// read data from the socket
		printf("->recv\n");
		ssize_t bytesRecvd = recv(connection_socket, buf, kRecvBufSize, 0);
		printf("bytesRecvd %d\n", bytesRecvd);
		if (bytesRecvd <= 0) break; // eof or failure
		
		// parse the data. this will call MyPropertyListenerProc and MyPacketsProc
		err = AudioFileStreamParseBytes(myData->audioFileStream, bytesRecvd, buf, 0);
		if (err) { PRINTERROR("AudioFileStreamParseBytes"); break; }
	}

	// enqueue last buffer
	MyEnqueueBuffer(myData);

	printf("flushing\n");
	err = AudioQueueFlush(myData->audioQueue);
	if (err) { PRINTERROR("AudioQueueFlush"); return 1; }	

	printf("stopping\n");
	err = AudioQueueStop(myData->audioQueue, false);
	if (err) { PRINTERROR("AudioQueueStop"); return 1; }	
	
	printf("waiting until finished playing..\n");
	pthread_mutex_lock(&myData->mutex); 
	pthread_cond_wait(&myData->done, &myData->mutex);
	pthread_mutex_unlock(&myData->mutex);
	
	
	printf("done\n");
	
	// cleanup
	free(buf);
	err = AudioFileStreamClose(myData->audioFileStream);
	err = AudioQueueDispose(myData->audioQueue, false);
	close(connection_socket);
	free(myData);
	
    return 0;
}