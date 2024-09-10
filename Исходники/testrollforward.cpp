void TestRollforward::insertDataPhase1()
{	
	// Insert first chunk of data

	// REVIEW: This could become more sophisticated 
	// to cover more aspects of rollforward recovery.
	// But normal recovery testing should touch on some 
	// of the same ground
	mLogger.out() << "** Insert phase 1" << std::endl;
	IPIN *pin;
	TVERIFYRC(mSession->createPIN (NULL,0,&pin,MODE_PERSISTENT));
	mPid1 = pin->getPID();
	if(pin!=NULL) pin->destroy();
}