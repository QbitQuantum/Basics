void SessionManagerTests::testSessionInfo()
{
	// Create an empty object store
#ifndef _WIN32
	ObjectStore store("./testdir");
#else
	ObjectStore store(".\\testdir");
#endif

	// Create the managers
	SlotManager slotManager(&store);
	SessionManager sessionManager;

	// Get a slot
	CK_SLOT_ID slotID = 0;
	Slot* slot = slotManager.getSlot(slotID);

	// Initialize the token
	ByteString soPIN((unsigned char*)"1234", 4);
	ByteString userPIN((unsigned char*)"1234", 4);
	CK_UTF8CHAR label[33] = "My test token                   ";
	CPPUNIT_ASSERT(slot->initToken(soPIN, label) == CKR_OK);
	CPPUNIT_ASSERT(slot->getToken()->loginSO(soPIN) == CKR_OK);
	CPPUNIT_ASSERT(slot->getToken()->initUserPIN(userPIN) == CKR_OK);
	slot->getToken()->logout();

	// Get a session
	CK_SESSION_HANDLE hSession;
	CK_RV rv = sessionManager.openSession(slot, CKF_SERIAL_SESSION, NULL_PTR, NULL_PTR, &hSession);
	CPPUNIT_ASSERT(rv == CKR_OK);

	// Get session info
	CK_SESSION_INFO info;
	rv = sessionManager.getSessionInfo(CK_INVALID_HANDLE, &info);
	CPPUNIT_ASSERT(rv == CKR_SESSION_HANDLE_INVALID);
	rv = sessionManager.getSessionInfo(hSession, NULL_PTR);
	CPPUNIT_ASSERT(rv == CKR_ARGUMENTS_BAD);
	rv = sessionManager.getSessionInfo(hSession, &info);
	CPPUNIT_ASSERT(rv == CKR_OK);

	// Public RO session info
	CPPUNIT_ASSERT(info.slotID == slotID);
	CPPUNIT_ASSERT(info.state == CKS_RO_PUBLIC_SESSION);
	CPPUNIT_ASSERT(info.flags == CKF_SERIAL_SESSION);

	rv = sessionManager.closeSession(hSession);
	CPPUNIT_ASSERT(rv == CKR_OK);

	// Public RW session info
	rv = sessionManager.openSession(slot, CKF_SERIAL_SESSION | CKF_RW_SESSION, NULL_PTR, NULL_PTR, &hSession);
	CPPUNIT_ASSERT(rv == CKR_OK);
	Session* session = sessionManager.getSession(CK_INVALID_HANDLE);
	CPPUNIT_ASSERT(session == NULL);
	session = sessionManager.getSession(hSession);
	CPPUNIT_ASSERT(session != NULL);
	rv = session->getInfo(&info);
	CPPUNIT_ASSERT(rv == CKR_OK);
	CPPUNIT_ASSERT(info.state == CKS_RW_PUBLIC_SESSION);
	CPPUNIT_ASSERT(info.flags == (CKF_SERIAL_SESSION | CKF_RW_SESSION));

	rv = sessionManager.closeSession(hSession);
	CPPUNIT_ASSERT(rv == CKR_OK);

	// User RO session info
	rv = slot->getToken()->loginUser(userPIN);
	CPPUNIT_ASSERT(rv == CKR_OK);
	rv = sessionManager.openSession(slot, CKF_SERIAL_SESSION, NULL_PTR, NULL_PTR, &hSession);
	CPPUNIT_ASSERT(rv == CKR_OK);
	rv = sessionManager.getSessionInfo(hSession, &info);
	CPPUNIT_ASSERT(rv == CKR_OK);
	CPPUNIT_ASSERT(info.state == CKS_RO_USER_FUNCTIONS);
	CPPUNIT_ASSERT(info.flags == CKF_SERIAL_SESSION);

	rv = sessionManager.closeSession(hSession);
	CPPUNIT_ASSERT(rv == CKR_OK);

	// User RW session info
	rv = slot->getToken()->loginUser(userPIN);
	CPPUNIT_ASSERT(rv == CKR_OK);
	rv = sessionManager.openSession(slot, CKF_SERIAL_SESSION | CKF_RW_SESSION, NULL_PTR, NULL_PTR, &hSession);
	CPPUNIT_ASSERT(rv == CKR_OK);
	rv = sessionManager.getSessionInfo(hSession, &info);
	CPPUNIT_ASSERT(rv == CKR_OK);
	CPPUNIT_ASSERT(info.state == CKS_RW_USER_FUNCTIONS);
	CPPUNIT_ASSERT(info.flags == (CKF_SERIAL_SESSION | CKF_RW_SESSION));

	rv = sessionManager.closeSession(hSession);
	CPPUNIT_ASSERT(rv == CKR_OK);

	// SO RW session info
	rv = slot->getToken()->loginSO(soPIN);
	CPPUNIT_ASSERT(rv == CKR_OK);
	rv = sessionManager.openSession(slot, CKF_SERIAL_SESSION | CKF_RW_SESSION, NULL_PTR, NULL_PTR, &hSession);
	CPPUNIT_ASSERT(rv == CKR_OK);
	rv = sessionManager.getSessionInfo(hSession, &info);
	CPPUNIT_ASSERT(rv == CKR_OK);
	CPPUNIT_ASSERT(info.state == CKS_RW_SO_FUNCTIONS);
	CPPUNIT_ASSERT(info.flags == (CKF_SERIAL_SESSION | CKF_RW_SESSION));

	rv = sessionManager.closeSession(hSession);
	CPPUNIT_ASSERT(rv == CKR_OK);
}