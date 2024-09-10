void ConnectionListener::FoundAdvertisedName(const char* name, TransportMask transport, const char* namePrefix)
{

		printf("FoundAdvertisedName(name='%s', transport = 0x%x, prefix='%s')\n", name, transport, namePrefix);

		const char* convName = name + strlen(mPrefix.c_str());
		printf("Discovered chat conversation: \"%s\"\n", convName);

		/* Join the conversation */
		/* Since we are in a callback we must enable concurrent callbacks before calling a synchronous method. */
		mBus->EnableConcurrentCallbacks();
		SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, true, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
		QStatus status = mBus->JoinSession(name, mPort, this, *(mSessionUser->getSessionId()), opts);
		if (ER_OK == status) {
			printf("Joined conversation \"%s\"\n", convName);
			mSessionUser->setJoined(true);

		}
		else {
			printf("JoinSession failed (status=%s)\n", QCC_StatusText(status));
		}
		if (!mSessionUser->isJoined())
		{
		uint32_t timeout = 20;
		status = mBus->SetLinkTimeout(*(mSessionUser->getSessionId()), timeout);
		if (ER_OK == status) {
			printf("Set link timeout to %d\n", timeout);
		}
		else {
			printf("Set link timeout failed\n");
		}
	}
}