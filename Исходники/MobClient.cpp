QStatus CMobClient::Connect()
{
	QStatus status = CAlljoynMob::Connect();

	if (ER_OK == status) {
		/* Begin discovery on the well-known name of the service to be called */
		status = m_pBus->FindAdvertisedName(m_sSvrName.data());

		if (status == ER_OK) {
			printf("org.alljoyn.Bus.FindAdvertisedName ('%s') succeeded.\n", m_sSvrName.data());
		}
		else {
			printf("org.alljoyn.Bus.FindAdvertisedName ('%s') failed (%s).\n", m_sSvrName.data(), QCC_StatusText(status));
		}
	}

	if (ER_OK == status) {
		unsigned int count = 0;

		while (!m_bJoinComplete && !s_interrupt) {
			if (0 == (count++ % 100)) {
				printf("Waited %u seconds for JoinSession completion.\n", count / 100);
			}

#ifdef _WIN32
			Sleep(10);
#else
			usleep(10 * 1000);
#endif
		}
	}

	return (m_bJoinComplete && !s_interrupt ? ER_OK : ER_ALLJOYN_JOINSESSION_REPLY_CONNECT_FAILED);
}