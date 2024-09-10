int testlistwords::execute()
{
	if (!MVTApp::startStore()) {mLogger.print("Failed to start store\n"); return RC_NOACCESS;}
	mSession = MVTApp::startSession();

	char *propName2;char lB[64]; sprintf(lB, "testlistwordsProp.");propName2=lB;
	mProp[0]=MVTUtil::getPropRand(mSession,propName2);
	
	createWords("abcd"); //single word scenario
	verifyListWords("a","abcd");
	verifyListWords("ab","abcd");
	verifyListWords("abc","abcd");
	verifyListWords("abcd","abcd");
	verifyListWords("abcde","abcd",true);

	createWords("abcd abeq bcfg"); //multiple words scenario
	verifyListWords("ab","abcd abeq");
	verifyListWords("ab bc","abcd abeq bcfg");
	
	createWords("qtvy dwqa iopl"); //multiple words scenario one of the items not found
	verifyListWords("dw hyretpo","dwqa");
	verifyListWords("hyretpo dw","dwqa");

	createWords("zio38"); //alpha numeric
	verifyListWords("zi","zio38");
	verifyListWords("zio3","zio38");
	verifyListWords("zio38","zio38");
	
	createWords("786blunders"); //numeric alpha
	verifyListWords("7","786");
	verifyListWords("786b","786blunders",true);
	verifyListWords("blu","blunders");

	createWords("impgo_kotre imhr-ghet grewqq#thge"); //special chars and delimiters
	verifyListWords("impg","impgo_kotre");
	verifyListWords("impg","impgo_kotre");
	verifyListWords("impgo_","impgo_kotre");
	verifyListWords("impgo_k","impgo_kotre");
	verifyListWords("imhr","imhr");
	verifyListWords("imhr-ghet","imhr ghet");
	verifyListWords("imhr-gh","imhr-ghet",true);

	mSession->terminate();
	MVTApp::stopStore();
	return RC_OK;
}