int main(int argc,char *argv[])
{
	SocketHandler h;

	// enable socks4 client
#ifdef ENABLE_SOCKS4
	h.SetSocks4Host("somehost.com");
	h.SetSocks4Port(1080);
	h.SetSocks4Userid("myname.net");
	h.SetSocks4TryDirect(false);
#endif

	for (int i = 1; i < argc; i++)
	{
		Get(h,argv[i]);
	}
	h.Select(1,0);
	while (h.GetCount())
	{
		h.Select(1,0);
	}
}