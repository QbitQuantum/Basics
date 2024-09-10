void TestLeftJoin::executeQuery(SourceSpec *pLHSCS, SourceSpec *pRHSCS, IExprNode *pET, unsigned pMode)
{
	IStmt * lQ = mSession->createStmt();		
	unsigned char lVar1 = lQ->addVariable(pLHSCS, 1);
	unsigned char lVar2 = lQ->addVariable(pRHSCS, 1);
	Value lV[2];
	lV[1].setVarRef(lVar1,mRefPropID);
	lV[0].setVarRef(lVar2,mPINPropID);
	CmvautoPtr<IExprNode> lJoinET(mSession->expr(OP_EQ,2,lV));

	lQ->join(lVar1, lVar2, lJoinET, QRY_LEFT_OUTER_JOIN);
	uint64_t lCount = 0;
	TVERIFYRC(lQ->count(lCount, 0, 0, ~0));
	TVERIFY(lCount == (uint64_t)mLHSPINs.size());

	OrderSeg lOrder = {NULL,mRHSPropID,ORD_DESC,0,0};
	lQ->setOrder(&lOrder, 1); 
	Afy::ICursor *lR = NULL;
	lQ->execute(&lR, NULL, 0, ~0, 0, pMode);
	int lResultCount = 0;
	if(lR)
	{		
		for(IPIN *lPIN = lR->next(); lPIN != NULL; lPIN = lR->next())
		{
			lResultCount++;
			PID lResultPID = lPIN->getPID();
			if(isVerbose()) mLogger.out() << std::hex << lResultPID.pid << std::endl;
			TVERIFY(lResultPID.pid != STORE_INVALID_PID && "Junk PIN returned in the result set");
			bool lFound = false;
			size_t j = 0;
			for(j = 0; j < mLHSPINs.size(); j++)
			{
				PID lPID = mLHSPINs[j];
				if(lPID.pid == lResultPID.pid)
				{
					lFound = true; break;
				}
			}
			if(!lFound) TVERIFY(false && "PIN belonging to Family1 wasn't returned in LEFT JOIN");					
		}
		lR->destroy();
	}
	TVERIFY(lResultCount == (int)mLHSPINs.size() && "Not all PINs were returned");
	lQ->destroy();
}