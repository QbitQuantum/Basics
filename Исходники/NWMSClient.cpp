void NWNMSClient::RequestServerList(int roomId)
{
	fprintf(logFile, "Creating thread...\n");
	fflush(logFile);

	this->currentRoom = roomId;

	// params is virusman's struct for tracking client object and roomid :)
	// imo I would of thought malloc is better but I guess MS is smart enough enough not to delete 
	// at end of function when using their QueueUserWorkItem (a ref to the allocated memory)
	RequestThreadParams *params = new RequestThreadParams;
	params->client = this;
	params->roomId = roomId;
	// that last NULL parameter is the same as WT_EXECUTEDEFAULT... good grief..
	QueueUserWorkItem((LPTHREAD_START_ROUTINE) NWNMSClient::RequestThread, params, NULL);
}