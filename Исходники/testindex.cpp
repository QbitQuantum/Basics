int testindex::execute()
{
	size_t mVerifyCnt = 0;
	size_t bSuccess = 0;

	if(!MVTApp::startStore()) {
		mLogger.out()<<"failed to start store...\n";
		return -1;
	}

	if((lsession = MVTApp::startSession())==NULL){
		mLogger.out()<<"failed to create session....\n";
		return -1;
	}
	
	CStoreInfo indexInfo_bef(lsession),indexInfo_aft(lsession);
	std::stringstream ft_bef,ft_aft; 
	
	//get class details before rebuild
	mLogger.out()<<"Store Scan in progress....\n";
	indexInfo_bef.storeScan();
	mLogger.out()<<"DONE..\n\n";

	mLogger.out()<<"FT scan in progress.....\n";
	indexInfo_bef.ftScan(ft_bef);
	mLogger.out()<<"DONE...\n\n";

	//rebuild ALL classes and ftindex.
	mLogger.out()<<"Store rebuild in progres....\n";
	TVERIFYRC(updateClass(lsession,NULL,NULL));
	TVERIFYRC(lsession->rebuildIndexFT());
	mLogger.out()<<"DONE...\n\n";

	//get class details before rebuild
	mLogger.out()<<"Store Scan in progress....\n";
	indexInfo_aft.storeScan();
	mLogger.out()<<"DONE..\n\n";

	mLogger.out()<<"FT scan in progress.....\n";
	indexInfo_aft.ftScan(ft_aft);
	mLogger.out()<<"DONE..\n\n";

	//compare class results
	mLogger.out()<<"Validating results.....\n";
	for(size_t i=0;i<indexInfo_bef.mClasses.size();i++)
	{
		TVERIFY(indexInfo_bef.mClasses[i]->mClassID == indexInfo_aft.mClasses[i]->mClassID);
		//mLogger.out()<<"DataEventID:"<<indexInfo_bef.mClasses[i]->mClassID<<"\t";

		TVERIFY(indexInfo_bef.mClasses[i]->mClassName == indexInfo_aft.mClasses[i]->mClassName);
		//mLogger.out()<<"ClassName:"<<indexInfo_bef.mClasses[i]->mClassName<<"\t";

		TVERIFY(indexInfo_bef.mClasses[i]->mFamily == indexInfo_aft.mClasses[i]->mFamily);
		//mLogger.out()<<"IsFamily:"<<indexInfo_bef.mClasses[i]->mFamily<<"\t";

		TVERIFY(indexInfo_bef.mClasses[i]->mPinCnt == indexInfo_aft.mClasses[i]->mPinCnt);
		//mLogger.out()<<"PIN count:"<<indexInfo_bef.mClasses[i]->mPinCnt<<"\t";

		TVERIFY(indexInfo_bef.mClasses[i]->mIndexedProp == indexInfo_aft.mClasses[i]->mIndexedProp);
		//mLogger.out()<<"IndexedPropID:"<<indexInfo_bef.mClasses[i]->mIndexedProp<<"\n";
		mLogger.out()<<"DataEventID:"<<indexInfo_bef.mClasses[i]->mClassID<<"\t"<<"verified successfully..."<<i+1<<endl;
		mVerifyCnt++;
	}

	//compare ft results
	if(ft_aft.str()== ft_bef.str())
	{
		bSuccess = 1;
		mLogger.out()<<ft_aft.str()<<endl;
		mLogger.out()<<"Ft validation is successful..\n";
	}

	lsession->terminate();
	MVTApp::stopStore();
	return bSuccess&(indexInfo_bef.mClasses.size() == mVerifyCnt?0:-1);
}	