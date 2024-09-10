void TestACLsInfer::testJoinACLs(ISession *pSession)
{
	TVERIFY(pSession != NULL);
	CmvautoPtr<IStmt> lQ(pSession->createStmt());
	Value lParam[3];
	lParam[0].setError(mPropIDs[2]); lParam[1].setError(mPropIDs[2]); lParam[2].setRange(lParam);
	SourceSpec lCS[2] = {{mCLSID, 0, NULL}, {mCLSID2, 1, &lParam[2]}};
	unsigned char lVar1 = lQ->addVariable(&lCS[0], 1);
	unsigned char lVar2 = lQ->addVariable(&lCS[1], 1);
	IExprNode *lET;
	{
		Value lV[2];
		lV[0].setVarRef(lVar1,mPropIDs[1]);
		lV[1].setVarRef(lVar2,mPropIDs[2]);		
		lET = pSession->expr(OP_EQ, 2, lV);
	}
	lQ->join(lVar1, lVar2, lET);
	uint64_t lCount = 0;
	TVERIFYRC(lQ->count(lCount));
	TVERIFY(lCount == uint64_t(mExpectedCount));
	unsigned long lResultCount = 0;
	ICursor* lC = NULL;
	TVERIFYRC(lQ->execute(&lC));
	CmvautoPtr<ICursor> lR(lC);
	if(lR.IsValid())
	{
		for(IPIN *lPIN = lR->next(); lPIN != NULL; lPIN = lR->next(), lResultCount++)
		{
			PID lPID = lPIN->getPID();
			lPIN->destroy(); lPIN = NULL;
			lPIN = pSession->getPIN(lPID); TVERIFY(lPIN != NULL);
			lPIN->destroy();
		}
	}
	TVERIFY(lResultCount == (unsigned long)mExpectedCount);
}