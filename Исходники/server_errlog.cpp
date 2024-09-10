int main()
{
	SocketHandler h;
	ListenSocket<DisplaySocket> l(h);
	StdoutLog log;

	h.RegStdLog(&log);

	if (l.Bind(9001))
	{
		exit(-1);
	}
	h.Add(&l);
	h.Select(1,0);
	while (!quit)
	{
		h.Select(1,0);
	}
}