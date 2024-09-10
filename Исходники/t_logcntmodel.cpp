LOCAL_D void TestFailGetContactStringL(CLogCntModel* aCntModel, TLogContactItemId aContactId)
	{
	// Read back the text information into a buffer too small to hold it using the plugin interface
	if(!OomTesting)
		theTest.Next(_L("@SYMTESTCaseID:PIM-APPENG-CNTMODEL-EC021-CIT-0012 Read back the text information into a buffer too small to hold it using the plugin interface"));

	// Setup buffer to contain concatenated result
	TBuf<1> overflow;
	TRAPD(err, aCntModel->ReadContactNameL(aContactId, overflow, ELogWesternFormat));
	if(OomTesting && err==KErrNoMemory)
		User::Leave(KErrNoMemory);	
	TEST(KErrNone==err);
	
	// Read back the text information for a non-existent Id using the plugin interface
	if(!OomTesting)
		theTest.Next(_L("Check no string read back for a non-existent Id using contact matching plugin"));

	// Set id1 to a non-existent Id
	aContactId=100;
	// Re-initialise buffer
	// Setup buffer to contain concatenated result
	TBuf<128> buf;
	// Initialise buffer
	buf=_L("");
	TRAP(err, aCntModel->ReadContactNameL(aContactId, buf, ELogWesternFormat));
	if(OomTesting && err==KErrNoMemory)
		User::Leave(KErrNoMemory);
	TEST(KErrNotFound==err);
	TEST(buf.Length()==0);

	// Read back the text information for an existing Id when making a call with an incorrect format parameter using the plugin interface
	if(!OomTesting)
		theTest.Next(_L("Check that correct string for an existing Id ( Western Format ) read back when making a call with an incorrect format parameter using contact matching plugin"));

	// Set id1 to a existing Id
	TLogContactItemId contactId=1;
	buf=_L("");
	TRAP(err, aCntModel->ReadContactNameL(contactId, buf, static_cast<TLogContactNameFormat>(100)));
	if(OomTesting && err==KErrNoMemory)
		User::Leave(KErrNoMemory);
	TEST(KErrNone==err);
	::CheckContactName(buf, KFirstName1, KLastName1, ELogWesternFormat);
	}