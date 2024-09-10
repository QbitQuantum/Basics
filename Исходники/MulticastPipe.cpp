void MulticastPipe::broadcastRaw(void* data,size_t size)
	{
	/* Write or read data depending on whether this is the master node or a slave node: */
	if(master)
		{
		/* Write the data: */
		writeRaw(data,size);
		}
	else
		{
		/* Read the data: */
		readRaw(data,size);
		}
	}