	inline crypthash_ptr_t create_crypthash_ptr(HCRYPTPROV hProv,	ALG_ID Algid,	HCRYPTKEY hKey,	DWORD dwFlags)
	{
		HCRYPTHASH tmp;
		
		if( !CryptCreateHash( hProv, Algid, hKey, dwFlags, &tmp ) )
		{
			DWORD const errc = GetLastError();
			STCRYPT_THROW_EXCEPTION( exception::cryptoapi_error() << exception::cryptoapi_einfo(errc) );
		}

		std::auto_ptr<HCRYPTHASH> hcrypthash_mem;
		try {
			hcrypthash_mem.reset(new HCRYPTHASH(tmp));
		}catch(...){
			BOOL const r = CryptDestroyHash(tmp); assert(r);
			throw;
		}

		return crypthash_ptr_t  ( hcrypthash_mem.release(), delete_HCRYPTHASH );
	}