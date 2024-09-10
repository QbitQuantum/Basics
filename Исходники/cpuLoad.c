void dataPush()
{
	float cpuLoad=(1000-idle)*0.1;
	intToChar(cpuLoad,cpuLoadBuffer[myQueue.end]);
	if(isQueueFull(&myQueue)!=1)
	{
		enqQueue(&myQueue,(void *)cpuLoadBuffer[myQueue.end]);
	}
	else
	{
		deqQueue(&myQueue);
		enqQueue(&myQueue,(void *)cpuLoadBuffer[myQueue.end]);
	}

}