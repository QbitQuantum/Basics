void ServerMessageProcessor::process_crack_request(LSP_Packet& packet)
{
	fprintf(stderr, "ServerMessageProcessor:: Processing crack Request from %s : %d\n", packet.getHostname(), packet.getPort());
	/*crack request to server comes from request and is of the format
	c sha len */
	/* Send ack to request */
	LSP_Packet ack_packet = create_ack_packet(packet);
	ConnInfo* connInfo = get_conn_info(packet.getConnId());
	connInfo->add_to_outMsgs(ack_packet);
	fprintf(stderr, "ServerMessageProcessor:: Pushing ACK packet to Outbox for conn_id: %u\n", packet.getConnId());

	if(testing) return;

	/* Parse and get appropriate entries about the request */
	uint8_t* bytes = packet.getBytes();
	string s((char*)bytes);
	stringstream iss(s);
	string ignore;
	iss >> ignore;
	string hash;
	iss >> hash;
	string startS;
	iss >> startS;
	string endS;
	iss >> endS;
	int length = strlen(startS.c_str());
	/* Get the least busy worker */
	vector<int> workers = get_least_busy_workers(1);
	/* Check some conditions before assigning to the worker */
	if(workers.empty() || hash.length() != 40)
	{
		LSP_Packet c_pkt(create_not_found_packet(connInfo));
		connInfo->add_to_outMsgs(c_pkt);
		return;
	}
	if(length == 0)
	{
		LSP_Packet c_pkt(create_not_found_packet(connInfo));
		connInfo->add_to_outMsgs(c_pkt);
		return;
	}
	if(length > MAX_PWD_LTH)
	{
		LSP_Packet c_pkt(create_not_found_packet(connInfo));
		connInfo->add_to_outMsgs(c_pkt);
		return;
	}

	if(length<4)
	{
		/*Assign only 1 worker. Sending message to more workers will take more time
		than processing by a single worker for 17576 entries.*/

		/* Get least busy worker and create an empty packet with that connId*/
		int worker = workers[0];
		ConnInfo *cInfo = get_conn_info(worker);

		int end = pow(26,length)-1;
		string startString = numToString(0,length);
        string endString = numToString(end,length);
	    string data = "c " + hash + " "+startString + " " +endString;
	    WorkerInfo w(cInfo->getConnectionId(), 0, hash, startString, endString);
	    /* Send crack request to worker. */
		send_crack_worker_request(packet, cInfo,w, data.c_str());
	}
	else if(length >= 4)
	{
		int start = 0;
		int numPoss = pow(26,length)-1;
		vector<int> workers = get_least_busy_workers(5);
		int workersCount = workers.size();
		int each = ceil(numPoss/workersCount);
		/* Split the work among the workers, update the request and worker information and send crack request to worker  */
		for(int i=0; i<workersCount; ++i)
		{
			ConnInfo* cInfo = get_conn_info(workers[i]);
			int last;
			if(start+each>numPoss)
				last = 	numPoss;
			else
				last = 	start+each;
			string startString = numToString(start,length);
			string endString = numToString(last,length);
			string data = "c " + hash + " "  + startString + " " +endString;
			WorkerInfo w(cInfo->getConnectionId(), 0, hash, startString, endString);
			send_crack_worker_request(packet, cInfo, w, data.c_str());
			start = start + each + 1;
		}
	}
}