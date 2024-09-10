int main(int argc, char **argv)
{
	UDPSocket sock;
	SocketAddress localadr("145.89.98.137", 2222, SocketAddress::UDP_SOCKET);
	sock.bind(localadr);
	SocketAddress remoteadr;
	sock.setTimeOut(2);

	int count = 0;
	while(true){
		try{
			cout << "waiting" << endl;

			sock.recvFrom(&count, sizeof(int), remoteadr);

			cout << "recieved: " << count << endl;
			cout << "from: " << remoteadr.getAddress() << ":" << remoteadr.getPort() << endl;

			count++;
			sock.sendTo(&count, sizeof(int), remoteadr );

		}catch(SocketTimedOutException e){continue;}
	}
}