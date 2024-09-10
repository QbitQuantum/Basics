void TestExternalSort::doTest(int newpins)
{
	// Sorting massive strings bloats the 
	// memory usage so that external sort boundary is easier to
	// hit
	static const int strlen=0x10; 

	char baseStr[strlen+1];
	memset(baseStr,'a',strlen); baseStr[strlen]=0;

	if (newpins>0)
	{
		// Create store
		mLogger.out() << "Generation phase" << endl ;
		mSession->startTransaction();
		for ( int i = 0 ; i < newpins ; i++ )
		{
			Value v[2];

			// Although huge string, only the first character will
			// differ so we will have lots of duplicates
			baseStr[0]='a'+MVTRand::getRange(0,25);

			v[0].set(baseStr); 
			v[0].property=mProp1;

			ulong cntProps=1;
			if (MVTRand::getRange(1,100)>20)
			{
				// Most pins have a second sorting property
				cntProps=2;
#if TEST_VT_IDENTITY
				//BUG REPRO
				v[1].setIdentity(STORE_OWNER) ; 
				v[1].property = PROP_SPEC_CREATEDBY ; 
#else
				v[1].set(MVTRand::getRange(0,RAND_MAX-1));
				v[1].property=mProp2;
#endif
			}

			TVERIFYRC(mSession->createPIN(v,cntProps,NULL,MODE_PERSISTENT|MODE_COPY_VALUES));
		}
		mSession->commit(true);
	}

	// query
	mLogger.out() << "Order by" << endl ;
	CmvautoPtr<IStmt> lQ(mSession->createStmt());	
	unsigned char var = lQ->addVariable() ;
	TVERIFYRC(lQ->setPropCondition(var,&mProp1,1));
#if TEST_VT_IDENTITY
	const OrderSeg sortProps[2] = {{NULL,PROP_SPEC_CREATEDBY,0,0,0},{NULL,mProp1,ORD_DESC,0,0}}; 
#else
	const OrderSeg sortProps[2] = {{NULL,mProp1,0,0,0},{NULL,mProp2,ORD_DESC,0,0}}; 
#endif
	TVERIFYRC(lQ->setOrder(sortProps,2));

	// Complete Pass
	ICursor* lC = NULL;
	TVERIFYRC(lQ->execute(&lC));
	CmvautoPtr<ICursor> lR(lC);
	ulong cntEnum=0;
	PID p5 ; // Remember for later comparison
	INITLOCALPID(p5); p5.pid = STORE_INVALID_PID;
	int iPrev = INT_MAX ;
#if TEST_VT_IDENTITY
	char cPrev = 'z'; 
#else
	char cPrev = '\0'; 
#endif
	IPIN *p = NULL;
	while(p = lR->next())
	{
		if (cntEnum==5) p5=p->getPID();
		cntEnum++;

		const Value * v1 = p->getValue(mProp1);
		TVERIFY(v1->type == VT_STRING);
		char cThis=v1->str[0];// Only first character varies in each string

#if TEST_VT_IDENTITY
		// Treat identity as integer
		//
		// Some pins don't have the primary ordering key
		// Give them a HIGH value because they will come after the others 
		const Value * v2 = p->getValue(PROP_SPEC_CREATEDBY);
		int iThis=(v2==NULL)?9999:v2->i;  

		TVERIFY( iThis>=iPrev);
		if ( iThis<iPrev)
		{
			mLogger.out() << "iThis " << iThis << " versus " << iPrev << endl;
		}
		if(iThis==iPrev)
		{
			TVERIFY( cThis<=cPrev ); 
			if (cThis>cPrev) 
				mLogger.out() << "cThis " << cThis << " versus " << cPrev << endl;
		}
#else

		const Value * v2 = p->getValue(mProp2);
		int iThis=(v2==NULL)?-1:v2->i;

		// Prove that the sorting worked
		TVERIFY( cThis>=cPrev ); // Ascending
		if(cThis==cPrev) TVERIFY( iThis<=iPrev ); // Descending
#endif

		if (isVerbose())
			mLogger.out() << cThis << "," << ((v2==NULL)?-1:v2->i) << endl ;

		cPrev=cThis;
		iPrev=iThis;

		p->destroy();
	}
	TVERIFY2(cntEnum>15,"Test expects at least 15 pins generated");

	uint64_t cnt;
	TVERIFYRC(lQ->count(cnt)) ; // Count with no sorting 
	TVERIFY(cnt==cntEnum);

	// Try skip/pagination
	CmvautoPtr<ICursor> lR2;

	if ( cntEnum > 15 )
	{
		mLogger.out() << "Retrieve first chunk of pins" << endl << endl ;
		ICursor* lC = NULL;
		TVERIFYRC(lQ->execute(&lC,NULL, 0,10/*nReturn*/, 5/*nSkip*/));
		CmvautoPtr<ICursor> lR(lC);
		lR2.Attach(lC);
		ulong cntEnum2=0;
		while(p = lR2->next())
		{
			if(cntEnum2==0)
			{
				TVERIFY(p->getPID()==p5);
			}

			cntEnum2++;
			p->destroy();
		}
		TVERIFY(cntEnum2==10);
	}

#if 1
	if ( cntEnum > 25 )
	{
		mLogger.out() << endl << endl << "Retrieve second chunk of pins" << endl ;
	
		// PERFORMANCE REVIEW: To get the next 10 results like this results 
		// in complete regeneration of the sort,
		// so it is more efficient to paginate yourself with single ICursor
		ICursor* lC = NULL;
		TVERIFYRC(lQ->execute(&lC, NULL,0,10/*nReturn*/, 15/*nSkip*/));
		lR2.Attach(lC);
		ulong cntEnum2=0;
		while(p = lR2->next())
		{
			cntEnum2++;
			p->destroy();
		}
		TVERIFY(cntEnum2==10);
	}
#endif
}