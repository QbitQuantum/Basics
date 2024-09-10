void ABI_Collab_Export::slaveInit(const UT_UTF8String& docUUID, UT_sint32 iRemoteRev)
{
	UT_DEBUGMSG(("ABI_Collab_Export::slaveInit() - docUUID: %s, iRev: %d\n", docUUID.utf8_str(), iRemoteRev));

	// NOTE: it's important that this function resets all state, as it can be
	// called in the middle of an already running collaboration session
	// (eg. when a session takeover happens)

	_cleanup();
	_init();

	// initialize the adjustment stack
	ChangeRecordSessionPacket voidPacket;
	voidPacket.setDocUUID(docUUID);
	voidPacket.setRev(iRemoteRev);
	m_pAbiCollab->addChangeAdjust(new ChangeAdjust(voidPacket, static_cast<PT_DocPosition>(0), docUUID));
}