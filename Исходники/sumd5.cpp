void Md5::update(gcstring s)
	{
	if (! CryptHashData(hHash, (BYTE*) s.ptr(), s.size(), 0))
		except("Md5: CryptHashData failed");
	}