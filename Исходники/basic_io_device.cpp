bool basic_io_device::would_block(system::error_code const &e)
{
	int code = e.value();
	bool block = 0
	#ifdef EAGAIN
	|| code==EAGAIN
	#endif
	#ifdef EINPROGRESS
	|| code == EINPROGRESS
	#endif
	#ifdef EWOULDBLOCK
	|| code == EWOULDBLOCK
	#endif
	#ifdef WSAEAGAIN
	|| code==WSAEAGAIN
	#endif
	#ifdef WSAEINPROGRESS
	|| code == WSAEINPROGRESS
	#endif
	#ifdef WSAEWOULDBLOCK
	|| code == WSAEWOULDBLOCK
	#endif
	;
	return block;
}