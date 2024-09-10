void FceApplication::ReceivePacket(Ptr<Socket> socket) {

	Address neighborMacAddress;
    Ptr<Packet> packet = socket->RecvFrom(neighborMacAddress);

    try {
    	OvnisPacket ovnisPacket(packet);
    	Vector position = mobilityModel->GetPosition();

		double distance = ovnisPacket.computeDistance(position.x, position.y);

		double packetDate = ovnisPacket.getTimeStamp();
		double packetAge = Simulator::Now().GetSeconds() - packetDate;
		string senderId = ovnisPacket.getSenderId();
//		long packetId = ovnisPacket.getPacketId();

		if (ovnisPacket.getPacketType() == CHANGED_EDGE_PACKET_ID) {
			string lastEdge = ovnisPacket.readString();
			double travelTime = ovnisPacket.readDouble();
			string currentEdge = ovnisPacket.readString();
			double numberOfVehiclesOnTheLastEdge = vanetsKnowledge.substractNumberOfVehicles(lastEdge);
			double numberOfVehiclesOnTheCurrentEdge = vanetsKnowledge.addNumberOfVehicles(currentEdge);
			Data data;
			data.date = packetDate;
			data.edgeId = lastEdge;
			data.travelTime = travelTime;
			vanetsKnowledge.record(data);

		}
		if (ovnisPacket.getPacketType() == TRAFFICINFO_PACKET_ID) {
			vector<Data> data = ovnisPacket.ReadTrafficInfoPacket();
			vanetsKnowledge.record(data);
//			for (vector<Data>::iterator it = data.begin(); it != data.end(); ++it) {
//				if (it->edgeId == "main_3b") {
//					Log::getInstance().getStream("main_3b_recording") << Simulator::Now().GetSeconds() << "\t" << decisionTaken << "\t";
//					vanetsKnowledge.record(*it);
//					Log::getInstance().getStream("main_3b_recording") << endl;
//				}
//				else {
//					vanetsKnowledge.record(*it);
//				}
//			}
		}

		Log::getInstance().packetReceived();
		Log::getInstance().addDistance(distance);
    }
    catch (exception & e) {
		cerr << "receive packet not recognized by ovnis" << endl;
	}
}