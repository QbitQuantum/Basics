void TestFTStreams::testFTStreams(ISession *session)
{
	const bool bWords = false ; // No words in the search string, because FT search matches with each and short random words can appear anywhere

	Value val[5];
	unsigned long streamlen = 20 + rand() % 40;
	Tstring serstr; // Random Search String
	MVTRand::getString(serstr,5,0,bWords);
	streamlen+=6;
#define	NUM_PROPS 10
	PropertyID lPropIDs[NUM_PROPS];
	MVTApp::mapURIs(session,"TestFTStreams.testFTStreams",NUM_PROPS,lPropIDs);

	//case 1: Short Stream and search string at the begining.(create)
	val[0].set(MVTApp::wrapClientStream(session, new testStream(streamlen,97/*start character*/,VT_STRING,serstr,0)));
	val[0].setPropID(lPropIDs[0]);
	val[0].meta = META_PROP_FTINDEX;
	TVERIFYRC(session->createPIN(val,1,NULL, MODE_PERSISTENT|MODE_COPY_VALUES));
	testExpectedFT( session, lPropIDs[0], serstr.c_str(),"case 1: Short Stream and search string at the begining.(create) failed");

	//case 2: Short stream collection and search string at the begining (create).
	streamlen = 40 + rand() % 60;
	MVTRand::getString(serstr,7,0,bWords);
	streamlen+=8;
	val[0].set(MVTApp::wrapClientStream(session, new testStream(streamlen,97,VT_STRING,serstr,0)));
	val[0].setPropID(lPropIDs[1]);
	val[0].op = OP_ADD; val[0].eid = STORE_LAST_ELEMENT;

	streamlen = 10 + rand()% 20;
	MVTRand::getString(serstr,4,0,bWords);
	streamlen+=6;
	val[1].set(MVTApp::wrapClientStream(session, new testStream(streamlen,97,VT_STRING,serstr,0)));
	val[1].setPropID(lPropIDs[1]);
	val[1].op = OP_ADD; val[1].eid = STORE_LAST_ELEMENT;

	streamlen = 10 + rand()% 30;
	MVTRand::getString(serstr,9,0,bWords);
	streamlen+=10;
	val[2].set(MVTApp::wrapClientStream(session, new testStream(streamlen,97,VT_STRING,serstr,0)));
	val[2].setPropID(lPropIDs[1]);
	val[2].op = OP_ADD; val[2].eid = STORE_LAST_ELEMENT;
	val[0].meta = val[1].meta = val[2].meta = META_PROP_FTINDEX;
	TVERIFYRC(session->createPIN(val,3,NULL, MODE_PERSISTENT|MODE_COPY_VALUES));
	testExpectedFT( session, lPropIDs[1], serstr.c_str(),"case 2: Short stream collection and search string at the begining (create) failed");
	
	//case 3: large stream with search string somewhere in between
	streamlen = 10000 + rand() % 20000;
	MVTRand::getString(serstr,35,0,bWords); 
	streamlen+=36;
	val[0].set(MVTApp::wrapClientStream(session, new testStream(streamlen,97,VT_STRING,serstr,5612)));
	val[0].setPropID(lPropIDs[1]);
	val[0].meta = META_PROP_FTINDEX;
	TVERIFYRC(session->createPIN(val,1,NULL, MODE_PERSISTENT|MODE_COPY_VALUES));

	testExpectedFT( session, lPropIDs[1], serstr.c_str(),"case 3: large stream with search string somewhere in between (create) failed");

	//case 4: big stream collection (25000,30000,15000 fails: investigate)
	//Assertion failed: ulong(sht)==pin->stamp, file c:\software\eclipse\workspace\pinto\mvstore\commitpins.cpp, line 208
	streamlen = 35000 + rand()%30000;
	MVTRand::getString(serstr,16,0,bWords);
	streamlen+=17;
	val[0].set(MVTApp::wrapClientStream(session, new testStream(streamlen,97,VT_STRING,serstr,9534)));
	val[0].setPropID(lPropIDs[2]);
	val[0].op = OP_ADD; val[0].eid = STORE_FIRST_ELEMENT;
	
	streamlen  = 40000 + rand() % 30000;
	MVTRand::getString(serstr,20,0,bWords);
	streamlen+=21;
	val[1].set(MVTApp::wrapClientStream(session, new testStream(streamlen,97,VT_STRING,serstr,12567)));
	val[1].setPropID(lPropIDs[2]);
	val[1].op = OP_ADD; val[1].eid = STORE_FIRST_ELEMENT;
	
	streamlen = 25000 + rand() % 30000;
	MVTRand::getString(serstr,6,0,bWords);
	streamlen+=7;
	val[2].set(MVTApp::wrapClientStream(session, new testStream(streamlen,97,VT_STRING,serstr,666)));
	val[2].setPropID(lPropIDs[2]);
	val[2].op = OP_ADD; val[2].eid = STORE_LAST_ELEMENT;
	val[0].meta = val[1].meta = val[2].meta = META_PROP_FTINDEX;
	TVERIFYRC(session->createPIN(val,3,NULL, MODE_PERSISTENT|MODE_COPY_VALUES));

	testExpectedFT( session, lPropIDs[2], serstr.c_str(),"case 4: big stream collection (create) failed");
	
	//case 5: Modify pin with a short stream
	streamlen = 40 + rand()% 100;
	MVTRand::getString(serstr,6,0,bWords);
	streamlen+=7;
	val[0].set(MVTApp::wrapClientStream(session, new testStream(streamlen,97,VT_STRING,serstr,0)));
	val[0].setPropID(lPropIDs[3]);
	val[0].meta = META_PROP_FTINDEX;
	IPIN *pin;
	TVERIFYRC(session->createPIN(val,1,&pin, MODE_PERSISTENT|MODE_COPY_VALUES));
	
	streamlen = 40 + rand() % 200;
	MVTRand::getString(serstr,4,0,bWords);
	streamlen+=5;
	val[0].set(MVTApp::wrapClientStream(session, new testStream(streamlen,97,VT_STRING,serstr,0)));
	val[0].setPropID(lPropIDs[3]);
	val[0].meta = META_PROP_FTINDEX;
	TVERIFYRC(pin->modify(val,1,0));
	pin->destroy();
	testExpectedFT( session, lPropIDs[3], serstr.c_str(),"case 5: Modify pin with a short stream failed");
	
	//case 6: collection modify of short stream
	streamlen = 60 + rand() % 40;
	streamlen+=7;
	val[0].set(MVTApp::wrapClientStream(session, new testStream(streamlen,97,VT_STRING," junk ",0)));
	val[0].setPropID(lPropIDs[5]);
	streamlen = 50 + rand() % 70;
	MVTRand::getString(serstr,9,0,bWords);
	streamlen+=10;
	val[1].set(MVTApp::wrapClientStream(session, new testStream(streamlen,97,VT_STRING,serstr,0)));
	val[1].setPropID(lPropIDs[5]);
	val[0].meta = val[1].meta = META_PROP_FTINDEX;
	TVERIFYRC(session->createPIN(val,2,&pin,MODE_PERSISTENT|MODE_COPY_VALUES));

	streamlen = 40 + rand() % 60;
	MVTRand::getString(serstr,5,0,bWords);
	streamlen+=6;
	val[0].set(MVTApp::wrapClientStream(session, new testStream(streamlen,97,VT_STRING,serstr,0)));
	val[0].setPropID(lPropIDs[5]);
	streamlen = 100 + rand() % 100;
	streamlen+=5;
	val[1].set(MVTApp::wrapClientStream(session, new testStream(streamlen,97,VT_STRING,"junk",0)));
	val[1].setPropID(lPropIDs[6]);
	val[0].meta = val[1].meta = META_PROP_FTINDEX;
	pin->modify(val,2,0);

	if ( MVTApp::bVerbose )
		MVTApp::output(*pin,mLogger.out(),session);

	testExpectedFT( session, lPropIDs[6], serstr.c_str(),"case 6: Modify pin with a short stream collection failed");
	pin->destroy();

	//case 7: modifypin with a long stream
	val[0].set("this will converted to streams");val[0].setPropID(lPropIDs[7]);
	val[1].set(123445);val[1].setPropID(lPropIDs[8]);
	val[2].set("http://www.f1.com");val[2].setPropID(lPropIDs[9]);
	val[0].meta = val[2].meta = META_PROP_FTINDEX;
	TVERIFYRC(session->createPIN(val,3,&pin,MODE_PERSISTENT|MODE_COPY_VALUES));
	
	streamlen = 900000 + rand() % 30000;
	MVTRand::getString(serstr,8,0,bWords);
	streamlen+=9;
	val[0].set(MVTApp::wrapClientStream(session, new testStream(streamlen,97,VT_STRING,serstr,0)));
	val[0].setPropID(lPropIDs[7]);
	val[0].meta = META_PROP_FTINDEX;
	TVERIFYRC(session->modifyPIN(pin->getPID(),val,1,0));
	testExpectedFT( session, lPropIDs[7], serstr.c_str(),"case 7: Modify pin with a long stream failed");
	pin->destroy();

	MVTApp::sReporter.enable(false); // Hide full scan query noise
	for ( int i = 0 ; i < NUM_PROPS ; i++ )
		purgeTestPins( session, lPropIDs[i] ) ; // Avoid future iterations failing
	MVTApp::sReporter.enable(true); 
}