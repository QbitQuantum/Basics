void TestUndelete::quickTest()
{
	// Delete a PIN
	int lPINIndex;
	uint64_t lBefDelCount = 0, lAftDelCount = 0;
	uint64_t lAftUndeleteCount = 0;
	PID lPID;
	Value lV[1]; 
	IStmt *lQ;
	IPIN * lPIN = NULL;

	lPINIndex = MVTRand::getRange(0 , (int)(mPIDs.size()-1));
	lPID = mPIDs[lPINIndex];

	// lPID exists
	lPIN = mSession->getPIN(lPID, 0);
	if(!lPIN) TVERIFY(!"Cannot retrieve PIN that is not deleted");
	else 
	{
		TVERIFY( (lPIN->getFlags()&PIN_DELETED)==0 ) ;
		lPIN->destroy();
	}

	lPIN = mSession->getPIN(lPID, MODE_DELETED);
	if(!lPIN) TVERIFY(!"Cannot retrieve PIN");
	else 
	{
		// Retrieving same PIN with MODE_DELETED says that it is deleted 
		TVERIFY( (lPIN->getFlags()&PIN_DELETED)==0 ) ;
		lPIN->destroy();
	}

	lV[0].set(lPINIndex); 
	lQ = getQuery(4, mPropIDs[1], lV); 
	
	lQ->count(lBefDelCount); deletePINs(2, &lPID, 1);
	lQ->count(lAftDelCount, NULL, 0, ~0, MODE_DELETED);
	TVERIFY(lBefDelCount == lAftDelCount && "Deleted PIN not returned in query");
	lQ->destroy();

	// By default you can't get a deleted PIN
	lPIN = mSession->getPIN(lPID);	
	TVERIFY(lPIN==NULL);

	// MODE_DELETED says to get the PIN even if it is deleted
	lPIN = mSession->getPIN(lPID, MODE_DELETED);	
	if(!lPIN) TVERIFY(false && "Deleted pin cannot be retrieved with MODE_DELETED");
	else
	{
		TVERIFY( (lPIN->getFlags()&PIN_DELETED)!=0 ) ;
		lPIN->destroy();
	}

	undeletePINs(0, &lPID, 1);

	// Check with PIN was undeleted
	// Get PIN usign ISessin::getPIN()
	lPIN = mSession->getPIN(lPID);
	if(!lPIN) TVERIFY(false && "PIN is still marked as deleted after an undelete");
	else lPIN->destroy();
	
	// Passing MODE_DELETED causes no trouble to retrieve undeleted pins
	lPIN = mSession->getPIN(lPID, MODE_DELETED);
	if(!lPIN) TVERIFY(false && "undeleted PIN cannot be retrieved");
	else 
	{
		TVERIFY( (lPIN->getFlags()&PIN_DELETED)==0 ) ;
		lPIN->destroy();
	}

	/*
	// FT Query
	lV[0].set(getPINStr(lPINIndex));
	lAftUndeleteCount = 0;
	IStmt *lQ1 = getQuery(0, mPropIDs[0], lV);	lQ1->count(lAftUndeleteCount);
	TVERIFY(lAftDelCount == lAftUndeleteCount && "Undeleted PIN not returned in FT query");
	lQ1->destroy();
	*/

	if(!MVTApp::isRunningSmokeTest())
	{
		// Full Scan Query on VT_STR
		lV[0].set(getPINStr(lPINIndex));
		lAftUndeleteCount = 0;
		IStmt *lQ2 = getQuery(1, mPropIDs[0], lV);	lQ2->count(lAftUndeleteCount);
		TVERIFY(lAftDelCount == lAftUndeleteCount && "Undeleted PIN not returned in Full Scan query");
		lQ2->destroy();
	}

	// Family Query
	lV[0].set(getPINStr(lPINIndex));
	lAftUndeleteCount = 0;
	IStmt *lQ3 = getQuery(3, mPropIDs[0], lV);	lQ3->count(lAftUndeleteCount);
	TVERIFY(lAftDelCount == lAftUndeleteCount && "Undeleted PIN not returned in Family query");
	lQ3->destroy();

	// Family with PIN Index
	lV[0].set(lPINIndex);
	lAftUndeleteCount = 0;
	IStmt *lQ4 = getQuery(4, mPropIDs[1], lV);	lQ4->count(lAftUndeleteCount);
	TVERIFY(lAftDelCount == lAftUndeleteCount && "Undeleted PIN not returned in Class query");
	lQ4->destroy();
	
	if(!MVTApp::isRunningSmokeTest())
	{
		// Full Scan Query with VT_INT
		lV[0].set(lPINIndex);
		lAftUndeleteCount = 0;
		IStmt *lQ5 = getQuery(5, mPropIDs[1], lV);	lQ5->count(lAftUndeleteCount);
		TVERIFY(lAftDelCount == lAftUndeleteCount && "Undeleted PIN not returned in Full Scan query");
		lQ5->destroy();
	}

	undeletePINs(2, &mPIDs[0], sNumPINs);

	//Create pin, soft delete and then purge.
	{
		Value val[1];Tstring str;PID delPid;IPIN *pin;
		MVTRand::getString(str,10,0);
		val[0].set(str.c_str());val[0].setPropID(mPropIDs[3]);
		TVERIFYRC(mSession->createPIN(val,1,&pin,MODE_PERSISTENT|MODE_COPY_VALUES));
		delPid = pin->getPID();
		//softdelete the pin
		TVERIFYRC(mSession->deletePINs(&pin,1));
		pin =  mSession->getPIN(delPid, MODE_DELETED);
		//Purge the deleted pin
		TVERIFYRC(mSession->deletePINs(&pin,1,MODE_PURGE));
		//verify if the pin is really purged
		pin =  mSession->getPIN(delPid, MODE_DELETED);
		if (NULL != pin){
			mLogger.out()<<"Got a purged pin!!!"<<std::endl;
			TVERIFY(false);
		}
	}
}