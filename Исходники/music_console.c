/*****************************************************************************
 * Function: main()
 *****************************************************************************/
int main()
{
    struct timespec start,end,diff,cycle;
    unsigned char buf[SEND_SIZE];
    int fd_file = -1;
    int fd_serie = -1;
    int ret = 0;
    
	// Uncomment to test on the Arduino
    //fd_serie = initSerialMod_WIN_115200 ();

	// Uncomment to test on the PC
	iniciarAudio_Windows ();

	/* Open music file */
	printf("open file %s begin\n",FILE_NAME);
	fd_file = open (FILE_NAME, O_RDONLY, 0644);
	if (fd_file < 0) {
		printf("open: error opening file\n");
		return -1;
	}

    // loading cycle time
    cycle.tv_sec=PERIOD_TASK_SEC;
    cycle.tv_nsec=PERIOD_TASK_NSEC;
    
    clock_gettime(CLOCK_REALTIME,&start);
	while (1) {
	
		// read from music file
		ret=read(fd_file,buf,SEND_SIZE);
		if (ret < 0) {
			printf("read: error reading file\n");
			return NULL;
		}
		
		// write to serial port  		
		// Uncomment to test on the Arduino
		//ret = writeSerialMod_256 (buf);

		// Uncomment to test on the PC
		ret = reproducir_1bit_4000 (buf);
		if (ret < 0) {
			printf("write: error writting serial\n");
			return NULL;
		}
		
		// get end time, calculate lapso and sleep
	    clock_gettime(CLOCK_REALTIME,&end);
	    diffTime(end,start,&diff);
	    if (0 >= compTime(cycle,diff)) {
			printf("ERROR: lasted long than the cycle\n");
			return NULL;
	    }
	    diffTime(cycle,diff,&diff);
		nanosleep(&diff,NULL);   
	    addTime(start,cycle,&start);
	}
}