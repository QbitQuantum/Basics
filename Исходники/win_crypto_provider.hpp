		HCRYPTHASH duplicate(crypt_hash const& h)
		{
			HCRYPTHASH ret;
			if (CryptDuplicateHash(h.m_hash, 0, 0, &ret) == false)
			{
				throw_ex<system_error>(error_code(GetLastError(), system_category()));
			}
			return ret;
		}