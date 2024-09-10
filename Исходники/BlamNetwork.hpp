			unsigned long ToInAddr() const
			{
				return _byteswap_ulong(Address.IPv4);
			}