int main2()
{
	SocketHandler h;
	ListenSocket<ServerSocket> ll(h);
	if (ll.Bind(443))
	{
		return -1;
	}
	h.Add(&ll);
	h.Select(1,0);
	while (h.GetCount())
	{
		h.Select(1,0);
	}
}