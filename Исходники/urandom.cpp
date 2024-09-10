		void generate(void *ptr,unsigned len)
		{
			if(CryptGenRandom(provider_,len,static_cast<BYTE *>(ptr)))
				return;
			std::ostringstream ss;
			ss<<"CryptGenRandom failed with code 0x"<<std::hex<<GetLastError();
			throw cppcms_error(ss.str());
		}