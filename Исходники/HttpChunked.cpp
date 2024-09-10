static void Server(String r)
{
	TcpSocket   server;
	if(server.Listen(4000, 10)) {

		TcpSocket socket;
		LOG("Waiting...");
		bool b = socket.Accept(server);
		if(b) {
			LOG("Connection accepted");
			HttpHeader http;
			http.Read(socket);
			socket.Put(r);
			socket.Close();
		}
	}
}