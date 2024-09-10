void TestFamilyOrder::queryFamily(DataEventID cid,int opt)
{
	IStmt *lQ = mSession->createStmt();
	Value paramVals;
	unsigned char lVar;
	SourceSpec cs ;
	ICursor *lR;
	OrderSeg os={NULL,mPropIDs[0],0,0,0};
	
	IPIN * pResult ;

	switch(opt)
	{
	case 0: 
		mLogger.out()<<"Query all the entries of the family"<<endl;	
		mLogger.out()<<"-----------------------------------------\n";

		cs.objectID = cid;
		cs.nParams = 0 ;
		cs.params = NULL;

		lVar = lQ->addVariable( &cs, 1 ) ;
		break;

	case 1:
		mLogger.out()<<"Query all the entries of the family ordered by the 1st propery in ASCENDING"<<endl;
		mLogger.out()<<"--------------------------------------------------------------------------------\n";

		cs.objectID = cid;
		cs.nParams = 0 ;
		cs.params = NULL;

		lVar = lQ->addVariable( &cs, 1 ) ;

		os.flags=0;
		lQ->setOrder(&os,1);
		break;

	case 2: 
		mLogger.out()<<"Query all the entries of the family ordered by the 1st property,in ASCENDING|NCASE order "<<endl;
		mLogger.out()<<"-----------------------------------------------------------------------------------------\n";

		cs.objectID = cid;
		cs.nParams = 0 ;
		cs.params = NULL;
	
		lVar = lQ->addVariable( &cs, 1 ) ;

		os.flags=ORD_NCASE;

		lQ->setOrder( &os,1);
		break;
	
	case 3: 
		mLogger.out()<<"Query all the entries of the family based on the parameter and ordered by prop1, in ASCENDING|NCASE order"<<endl;
		mLogger.out()<<"----------------------------------------------------------------------------------------------------------------\n";

		cs.objectID = cid;
		cs.nParams = 1 ;
		paramVals.set(valuestr[0].c_str());
		cs.params = &paramVals ;
		
		lVar = lQ->addVariable( &cs, 1 ) ;

		os.flags=ORD_NCASE;
		lQ->setOrder( &os, 1);
		break;

	case 4: 
		mLogger.out()<<"Query all the entries of the family ordered by the 2nd propery in ASCENDING"<<endl;
		mLogger.out()<<"--------------------------------------------------------------------------------\n";

		cs.objectID = cid;
		cs.nParams = 0 ;
		cs.params = NULL;

		lVar = lQ->addVariable( &cs, 1 ) ;

		os.pid=mPropIDs[1];
		lQ->setOrder( &os,1);
		break;

	case 5:
		mLogger.out()<<"Query all the entries of the family ordered by the 2nd property,in ASCENDING|NCASE order "<<endl;
		mLogger.out()<<"-----------------------------------------------------------------------------------------\n";

		cs.objectID = cid;
		cs.nParams = 0 ;
		cs.params = NULL;
		lVar = lQ->addVariable( &cs, 1 ) ;

		os.pid=mPropIDs[1]; os.flags=ORD_NCASE;
		lQ->setOrder( &os, 1);
		break;
	
	case 6: 
		mLogger.out()<<"Query all the entries of the family based on the parameter n ordered by prop2, in ASCENDING|NCASE order"<<endl;
		mLogger.out()<<"----------------------------------------------------------------------------------------------------------------\n";

		cs.objectID = cid;
		cs.nParams = 1 ;
		paramVals.set(valuestr[0].c_str());
		cs.params = &paramVals ;
		
		lVar = lQ->addVariable( &cs, 1 ) ;

		os.pid=mPropIDs[1]; os.flags=ORD_NCASE;
		lQ->setOrder( &os, 1);
		break;

	case 7: 
		mLogger.out()<<"Query all the entries of the family based on the parameter n ordered by prop2, in DESCENDING|NCASE order"<<endl;
		mLogger.out()<<"--------------------------------------------------------------------------------------------------------\n";

		cs.objectID = cid;
		cs.nParams = 1 ;
		paramVals.set(valuestr[0].c_str());
		cs.params = &paramVals ;

		lVar = lQ->addVariable( &cs, 1 ) ;

		os.pid=mPropIDs[1]; os.flags=ORD_NCASE|ORD_DESC;
		lQ->setOrder( &os, 1);
		break;	
	}
	TVERIFYRC(lQ->execute(&lR));

	mLogger.print("Family queries...\n\n");
	int cnt = 0;
	mCase = 0;

	while ( NULL != ( pResult = lR->next() ) )
	{
		const Value *pIndex[2];
		pIndex[0] = pResult->getValue(mPropIDs[0]) ;
		if(isVerbose()) mLogger.print("Prop1:%s\n",pIndex[0]->str);

		pIndex[1] = pResult->getValue(mPropIDs[1]) ;
		if(isVerbose()) mLogger.print("Prop2:%s\n",pIndex[1]->str);

		if(opt == 6)
			vPIDS1[cnt++]=pResult->getPID();

		if(opt == 7)
		{
				vPIDS2[cnt++]=pResult->getPID();
				mCase++;
		}
		if(isVerbose()) mLogger.out() << "PIN ID " << pResult->getPID().pid << std::endl;
	
		if ( pIndex == NULL ) { TVERIFY(!"No index prop") ; pResult->destroy() ; continue ; }
		pResult->destroy() ;
	}	
	lQ->destroy();
}