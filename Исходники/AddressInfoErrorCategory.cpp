	std::string AddressInfoErrorCategory_t::message(int ev) const
	{
#ifdef _WIN32
		return gai_strerrorA(ev);
#else
		return gai_strerror(ev);
#endif
	}