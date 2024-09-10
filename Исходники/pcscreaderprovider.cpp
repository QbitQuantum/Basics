	PCSCReaderProvider::PCSCReaderProvider() :
		ReaderProvider()
	{
		d_scc = 0;
		long scres = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &d_scc);
		if (scres != SCARD_S_SUCCESS)
		{
			char tmpbuf[128];
			memset(tmpbuf, 0x00, sizeof(tmpbuf));
			sprintf(tmpbuf, "Can't establish the context for PC/SC service (%x).", static_cast<unsigned int>(scres));
			THROW_EXCEPTION_WITH_LOG(LibLogicalAccessException, tmpbuf);
		}
	}