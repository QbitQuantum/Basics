int main(int argc, char *argv[])
{
	SocketHandler h;
	ListenSocket<IOSocket> l(h);
	l.Bind(12344);
	h.Add(&l);
	IOSocket sock(h);
	sock.Open("192.168.7.4", 12344);
	h.Add(&sock);
	while (!quit)
	{
		h.Select(1, 0);
	}
}