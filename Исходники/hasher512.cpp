	hasher512& hasher512::operator=(hasher512 const& h)
	{
		if (this == &h) return *this;
		CryptDestroyHash(m_context);
		if (CryptDuplicateHash(h.m_context, 0, 0, &m_context) == false)
		{
#ifndef BOOST_NO_EXCEPTIONS
			throw system_error(error_code(GetLastError(), system_category()));
#else
			std::terminate();
#endif
		}
		return *this;
	}