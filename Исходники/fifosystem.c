// fifoSetDatamsgHandler - Set a callback to receive incoming data sequences on a specific channel.
bool fifoSetDatamsgHandler(int channel, FifoDatamsgHandlerFunc newhandler, void * userdata) {
	if(channel<0 || channel>=FIFO_NUM_CHANNELS) return false;

	int oldIME = enterCriticalSection();

	fifo_datamsg_func[channel] = newhandler;
	fifo_datamsg_data[channel] = userdata;


	if(newhandler) {
		while(fifoCheckDatamsg(channel)) {
			int block = fifo_data_queue[channel].head;
			int n_bytes = FIFO_UNPACK_DATALENGTH(FIFO_BUFFER_DATA(block));
			newhandler(n_bytes, userdata);
			if (block == fifo_data_queue[channel].head) fifoGetDatamsg(channel,0,0);
		}
	}

	leaveCriticalSection(oldIME);

	return true;
}