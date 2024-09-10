int main (int argc, char const *argv[])
{
	// Get args
	filename = getArg("-f", argv);
	port = atoi(getArg("-p", argv).c_str());
	host = getMyIP();
	
	if(filename.empty()) {
		cout << "Need to specify a filename" << endl;
		exit(0);
	} else if(port < 1024 || port > 65535) {
		cout << "Invalid port" << endl;
		exit(0);
	}
	
	// Parse and generate topology
	readtopology();
	
	// Get my Node representation from Topology
	me = topology.get(host, port);
	
	
	Socket sock = Socket();
	sock.block(false);
	
	// Start the timer.
	int messageNeighborsWait = 4000;
	timer.add("messageNeighbors", messageNeighborsWait);
	timer.add("updateLSP", 20000);
	timer.add("decrementTTL", 1000);
	while(1) {
		string response = sock.listen(port);
		if(!response.empty()) {
			forwardpacket(response);
			response = string("");
		}

		if(timer.isDone("messageNeighbors")) {
			stringstream ss;
			acksNeededFromNeighbors = me.neighbors();

			for(unsigned int i = 0; i < acksNeededFromNeighbors.size(); i++) {
				Node n = acksNeededFromNeighbors.at(i);
				// Create the ack packet
				HSPacket ack = HSPacket().type('A').sourceIP(host).sourcePort(port).destinationIP(n.host()).destinationPort(n.port());
				
				// Create the timer
				ss.str("");
				ss << "A|" << n.host() << ":" << n.port();
				// Set the timer
				ackTimer.add(ss.str(), 500);
				
				// Send the ack packet to our neighbor
				sock.send(n.host(), n.port(), ack.toString());
			}
			timer.add("messageNeighbors", messageNeighborsWait);
		}
		
		// Check to see if expiration up on acksNeededFromNeighbors
		stringstream key;
		for(unsigned int i = 0; i < acksNeededFromNeighbors.size(); i++) {
			Node n = acksNeededFromNeighbors.at(i);
			key.str("");
			key << "A|" << n.host() << ":" << n.port();
			
			if(ackTimer.isDone(key.str())) {
				// This node did not respond. Disable in topology
				topology.disable(n.host(), n.port());
				
				stringstream write;
				string neighbors = topology.getNeighborsForLSP(me);
				write << "Something has changed. Send emulators LS information: " << neighbors << " to neighbors.";
				cout << colorize(write.str(), "yellow");

				// Then trigger reliable flooding algorithm to update node topologies
				createroutes(me.neighbors(), 10);
			}
 		}
		
		if(timer.isDone("updateLSP")) {
			cout << colorize("Occasional update... flood topology", "blue");
			createroutes(me.neighbors(), 10);
			timer.add("updateLSP", 20000);
		}
		
		// if(timer.isDone("decrementTTL")) {
		// 	decrementTTL();
		// 	timer.add("decrementTTL", 10000);
		// }
		
		// ---- OK I THINK I FIGURED IT OUT:
		
		/* Every little bit we send out "hello" (acks. perhaps..)
		   packets to our neighbors
			
			IF we don't get a response from the neighbor we declare that its offline and 
			send out the LSPacket from the node that found out theres an offline node. 
			The Neighbors field in the LSPacket should contain which node is OFFLINE.
			
			EVERY ONCE IN A WHILE we send out LSPackets, but just to make sure "nothing has changed"
		*/
		
		// Run createroutes on its own say.. 20 seconds
		
		
		// cout << "exit out of loop for now" << endl;
		// 		exit(1);
	}
	
	
	
	return 0;
}