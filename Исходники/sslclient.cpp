int main(int argc,char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <-hostname> <-port>\n", *argv);
		exit(-1);
	}
	SocketHandler h;
	MyClient sock(h);
	port_t port = atoi(argv[2]);
	if (port == 2222)
	{
		sock.EnableSSL();
	}
	sock.Open(argv[1], port);
	h.Add(&sock);
	while (h.GetCount())
	{
		h.Select();
	}
}