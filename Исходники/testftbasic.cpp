	unsigned long search(
		size_t pLineNo,
		char* inSearch, 
		unsigned long inExpected, 
		unsigned int flags = 0  /* for example MODE_ALL_WORDS*/)
	{
		PropertyID props[1] ; int cnt = 1 ;
		props[0] = mProp ;

		TV_R(inSearch!=NULL&&strlen(inSearch)>0,mTest);

		uint64_t cntResults = 0 ;
		CmvautoPtr<IStmt> ftQ(mSession->createStmt()) ;
		unsigned char v = ftQ->addVariable() ;

		string strFlags;
		if ( flags & QFT_FILTER_SW ) strFlags.append( "QFT_FILTER_SW ");
		if ( flags & MODE_ALL_WORDS ) strFlags.append( "MODE_ALL_WORDS ");

		// For testing convenience two different flag args jammed into one
		// but if any value overlap happens in future this will have to split
		unsigned int flagsToAddConditionFT = 0;
		if (flags&QFT_FILTER_SW)
		{
			flagsToAddConditionFT |= QFT_FILTER_SW;
			flags &= ~QFT_FILTER_SW ;
		}

		// NOTE: This isn't a "Full scan" query even though no class is specified
		TVRC_R( ftQ->addConditionFT( v, 
					inSearch, 
					flagsToAddConditionFT /*WARNING THIS IS NOT THE PLACE FOR MODE_ALL_WORDS*/, 
					props, 
					cnt ), mTest ) ;

		// Verify conversion from string back to query
#if TEST_FTQ_AS_STRING_9084
		char * strQ = ftQ->toString() ;
		CmvautoPtr<IStmt> ftQ2(mSession->createStmt(strQ));
		if ( ftQ2.IsValid() )
		{
			char * strQ2 = ftQ2->toString() ;

			if ( mTest->isVerbose() )
			{
				mTest->getLogger().out() << "Q1" << endl << strQ << endl << "Q2" << endl << strQ2 << endl ;
			}
			mSession->free(strQ2);

			ftQ.Attach(ftQ2.Detach());
		}
		else
		{
			TV_R(!"Failure to convert FT query from string",mTest) ;
		}
		mSession->free(strQ);
#endif

		TVRC_R( ftQ->count( cntResults, NULL, 0, ~0, flags ), mTest );
		ICursor* lC = NULL;
		ftQ->execute(&lC,NULL,0,~0,0,flags);
		CmvautoPtr<ICursor> res(lC);
		IPIN * pin ;
		unsigned long cntCheck = 0 ;
		while( pin = res->next() )
		{
			cntCheck++ ;
			pin->destroy() ;
		}
		TV_R(cntCheck == inExpected, mTest) ;
		TV_R(cntCheck == cntResults, mTest) ;

		if (mTest->isVerbose())
			printResults( inSearch, flags ) ;

		if ( cntCheck != inExpected || cntResults != inExpected )
		{
			if ( cntCheck == 0 )
			{
				mTest->getLogger().out() << "No matches for \"" << inSearch << "\" " << strFlags << " Prop: " << mProp ;
				mTest->getLogger().out() << " (line " << pLineNo << ")" << endl ;
			}
			else
			{
				mTest->getLogger().out() << strFlags << " Expected " << inExpected << " got " << cntCheck << " Prop: " << mProp;
				mTest->getLogger().out() << " (line " << pLineNo << ")" << endl ;
				printResults( inSearch, flags );
			}
			
			// Full scan print properties and show what is there
			mTest->getLogger().out() << "-------------Dump of strings on Properties--------------" << endl;
			CmvautoPtr<IStmt> qFullScan(mSession->createStmt());
			TVRC_R(qFullScan->setPropCondition(qFullScan->addVariable(),&mProp,1),mTest);
			ICursor* lC = NULL;
			qFullScan->execute(&lC);
			CmvautoPtr<ICursor> rFullScan(lC);
			IPIN* pin;
			while(NULL!=(pin=rFullScan->next()))
			{
				mTest->getLogger().out() << "Pin: " << hex << pin->getPID().pid << dec ;
				const Value * indexedStr = pin->getValue(mProp); TV_R(indexedStr!=NULL,mTest);
				if ( indexedStr->type==VT_STRING)
					mTest->getLogger().out() << " " << indexedStr->str << endl;
				else if ( indexedStr->type==VT_STREAM )
					mTest->getLogger().out() << " (stream)" << endl;
				else
					TV_R(false,mTest);
				pin->destroy();
			}
		}

		return (unsigned long)cntResults ;
	}