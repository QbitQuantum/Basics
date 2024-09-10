s32 cellSslCertificateLoader(u64 flag, vm::ptr<char> buffer, u32 size, vm::ptr<u32> required)
{
	cellSsl.trace("cellSslCertificateLoader(flag=%llu, buffer=0x%x, size=%zu, required=0x%x)", flag, buffer, size, required);

	const std::bitset<58> flagBits(flag);
	const std::string certPath = vfs::get("/dev_flash/") + "data/cert/";

	if (required)
	{
		*required = 0;
		for (int i = 1; i <= flagBits.size(); i++)
		{
			if (!flagBits[i-1])
				continue;
			// If we're loading cert 6 (the baltimore cert), then we need set that we're loading the 'normal' set of certs.
			*required += (u32)(getCert(certPath, i, flagBits[BaltimoreCert-1]).size());
		}
	}
	else
	{
		std::string final;
		for (int i = 1; i <= flagBits.size(); i++)
		{
			if (!flagBits[i-1])
				continue;
			// If we're loading cert 6 (the baltimore cert), then we need set that we're loading the 'normal' set of certs.
			final.append(getCert(certPath, i, flagBits[BaltimoreCert-1]));
		}

		memset(buffer.get_ptr(), '\0', size - 1);
		memcpy(buffer.get_ptr(), final.c_str(), final.size());
	}