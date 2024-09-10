// Writes image data to a file on the non-temporary storage (ie. HDD or flash
// memory) of the device running this sofware.
void* writeImageContentToFile(void* args)
{
	struct threadArgs* 	inputs = (struct threadArgs*)args;
	int 				nodeCtr = 0;
	struct lstnode* 	node = inputs->cNode;
	pthread_mutex_t* 	mutex = inputs->mutex;
	free(args);
	int fd = openPort(); 		        // open the serial port
	while(TRUE)
	{
		byte* buf = (byte*)malloc(6); // allocate buffer for meta data
		if(read(fd, buf, 6) == 6) // read meta data
		{
			pthread_mutex_lock(mutex); // lock so other thread can't change ptrs
			printf("Received: %s\n", buf);
			struct telpkt* tp = decode(buf, 5); // create telemetry pkt
			if(node->size > 0) node = writeDataToSerial(tp, fd, node, nodeCtr);
			free(tp);
			pthread_mutex_unlock(mutex);
		}
		free(buf);
	}
	free(inputs);
	pthread_exit(NULL);
}