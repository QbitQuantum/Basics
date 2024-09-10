void UDPMulticastSender::send()
{
	try {
		UDPSocket sock;

		sock.setMulticastTTL(multicastTTL);
		//sock.setBroadcast();

		Sleep(7000); //Wait the Simulation Start

		// Repeatedly send the string to the server
		for (;;) {
 			buildSendMessage();

			sock.sendTo(sendBuffer, bufLen, servAddress, port);
			Sleep(1000./60.); //camera 60 fps
		}
	} catch (SocketException &e) {
		cerr << e.what() << endl;
		exit(1);
	}
}