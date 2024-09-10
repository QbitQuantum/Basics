std::string get_http(const char *host, int port, const char *request)
{
	SocketHandler h;
	GetHttp sock(h, request);
	sock.Open( host, port );
	h.Add(&sock);
	while (h.GetCount()) {
		h.Select(1, 0);
	}
	return sock.Response();
}