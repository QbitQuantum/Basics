int main(int argc, char *argv[])
{
	std::string host = argc > 1 ? argv[1] : "www.alhem.net";
	int port = argc > 2 ? atoi(argv[2]) : 80;
	SocketHandler h;
	for (int i = 1; i < 255; i++)
	{
		char host[40];
		sprintf(host, "10.170.23.%d", i);
		tSocket *p = new tSocket(h, host, 23);
		h.Add(p);
	}
	while (h.GetCount())
	{
		h.Select(1, 0);
	}
}