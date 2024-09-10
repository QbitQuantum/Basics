void TestBig::bigCollection(ISession *session, unsigned int cntElements, unsigned int sizeElement )
{
	PropertyID lProps[2]; 
	MVTApp::mapURIs(session, "TestBig.bigCollection", 2, lProps ) ;
	PropertyID propid = lProps[0], propid1 = lProps[1] ;

	// Prepare pool of random strings
	unsigned int i;
	vector<string> strCollItems(cntElements) ;
	for (i=0; i<cntElements; i++){
		MVTRand::getString(strCollItems[i],sizeElement,0,true,true);
	}

	// Give warning about potential pin size
	mLogger.out() << "Generating pins with collection size " << ( cntElements * ( sizeElement + 1 + sizeof(Value) ) ) / ( 1024.) << "(KB) (or more)" << endl ;

	//case 1: build big collection on uncommited pin
	Value * const val = (Value *)session->malloc(sizeof(Value) * cntElements);
	Tstring str;
	IPIN *pin;
	PID pid;
	RC rc;

	session->createPIN(NULL,0,&pin,MODE_PERSISTENT);
	reportRunningCase("uncommited pin collection.");
	for (i=0; i<cntElements; i++){
		// two properties so double the size
		val[0].set(strCollItems[i].c_str());val[0].setPropID(propid);
		val[0].op = OP_ADD; /*val[0].eid = STORE_LAST_ELEMENT;*/
		val[1].set(strCollItems[i].c_str());val[1].setPropID(propid1);
		val[1].op = OP_ADD; /*val[1].eid = STORE_LAST_ELEMENT;*/
		pin->modify(val,2,MODE_COPY_VALUES);
	}


	verifyExpectedCollection(session,pin,propid,strCollItems,"case1.prop0.beforecommit") ;
	verifyExpectedCollection(session,pin,propid1,strCollItems,"case1.prop1.beforecommit") ;

	//TVERIFYRC(session->commitPINs(&pin,1));
		// REVIEW: this fails in case of small collection with huge elements
		// is that by design?
	TVERIFY(pin->getValue(propid)->type == VT_COLLECTION) ;

	verifyExpectedCollection(session,pin,propid,strCollItems,"case1.prop0") ;
	verifyExpectedCollection(session,pin,propid1,strCollItems,"case1.prop1") ;

	pid = pin->getPID() ;

	pin->destroy();
	pin = NULL;

	// Sanity check with fresh PIN
	pin = session->getPIN(pid) ;

	if (isVerbose())
		mLogger.out() << "\t\tNew pid: " << std::hex << pid.pid << std::dec << endl ;

	//Review:	
	TVERIFY(pin->getValue(propid)->type == VT_COLLECTION) ;

	verifyExpectedCollection(session,pin,propid,strCollItems,"case1.prop0") ;
	verifyExpectedCollection(session,pin,propid1,strCollItems,"case1.prop1") ;

	pin->destroy();
	pin = NULL;


	//case 2: Commited pin with large collection elements.
	reportRunningCase("big collection at creation time");

	for (i=0;i<cntElements; i++){
		val[i].set(strCollItems[i].c_str());val[i].setPropID((unsigned)propid);
		val[i].op = OP_ADD; val[i].eid = STORE_LAST_ELEMENT;
	}
	TVERIFYRC(session->createPIN(val,cntElements,&pin,MODE_NO_EID | MODE_COPY_VALUES | MODE_PERSISTENT));
	pid= pin->getPID();
	verifyExpectedCollection(session,pin,propid,strCollItems,"case2") ;
	pin->destroy();
	pin = NULL;

	//case 3: uncommited pin with MODE_COPY_VALUES
	reportRunningCase("uncommitted MODE_COPY_VALUES");
	for (i =0; i < cntElements; i ++){
		// We don't need to allocate string memory because MODE_COPY_VALUES
		// means store will do the copy
		val[i].set(strCollItems[i].c_str());val[i].setPropID((unsigned)propid);
		val[i].op = OP_ADD_BEFORE; val[i].eid = STORE_LAST_ELEMENT;
	}
	TVERIFYRC(session->createPIN(val,cntElements,&pin,MODE_COPY_VALUES|MODE_PERSISTENT));TVERIFY(pin!=NULL) ;
	verifyExpectedCollection(session,pin,propid,strCollItems,"case3") ;

	//case 3a: modify this pin and elements.
	val[0].set(strCollItems[0].c_str());val[0].setPropID((unsigned)propid);
	val[0].eid = STORE_LAST_ELEMENT;val[0].op = OP_ADD_BEFORE;
	TVERIFYRC(pin->modify(val,1));
	TVERIFY2( MVTApp::getCollectionLength(*pin->getValue(propid)) == cntElements+1, "case 3a" ) ;

	//case 4: clone a big collection pin with overwrite values
	reportRunningCase("clone with more collection items");
	IPIN *clpin;
	Value cval[200];
	TVERIFY( pin!=NULL );

	// 200 integer values added to the same property
	for (i=0;i<200;i++){
		cval[i].set(i);cval[i].setPropID(propid);
		cval[i].op = OP_ADD_BEFORE; cval[i].eid = STORE_LAST_ELEMENT;
	}
	clpin = pin->clone(cval,200,MODE_PERSISTENT);

	TVERIFY2( MVTApp::getCollectionLength(*clpin->getValue(propid)) == (cntElements+1+200), "case 4" ) ;
	// Sanity check that original PIN is ok
	TVERIFY( MVTApp::getCollectionLength(*pin->getValue(propid)) == (cntElements+1) ) ;
	
	clpin->destroy();
	clpin=NULL;

	//case 5: Reload of a big collection pin.
	reportRunningCase("pin refresh");
	TVERIFY( pin!=NULL );
	TVERIFYRC(pin->refresh());
	TVERIFY( MVTApp::getCollectionLength(*pin->getValue(propid)) == (cntElements+1) ) ;
	pin->destroy(); pin=NULL;

	//case 6: Modify of a big collection
	reportRunningCase("modify big collection");
	
	// First element added at creation time
	val[0].set(strCollItems[0].c_str());val[0].setPropID(propid);
	val[0].op = OP_ADD; val[0].eid = STORE_COLLECTION_ID;
	TVERIFYRC(session->createPIN(val,1,&pin,MODE_PERSISTENT | MODE_COPY_VALUES));

	// Add remaining elements
	Value * val1 = (Value *)session->malloc(sizeof(Value) * (cntElements-1));

	for (i=0;i<cntElements-1; i++){
		val1[i].set(strCollItems[i+1].c_str());
		val1[i].setPropID(propid);val1[i].op=OP_ADD;val1[i].eid = STORE_LAST_ELEMENT;
	}
#if 1	
	//Workaround - create VT_COLLECTION value pointing to elements
	Value valArrayWrapper[1];
	valArrayWrapper[0].set(val1,cntElements-1);
	valArrayWrapper[0].setPropID(propid);valArrayWrapper[0].op=OP_ADD;valArrayWrapper[0].eid = STORE_COLLECTION_ID;
	TVERIFYRC(pin->modify(valArrayWrapper,1));	   
#else
	TVERIFYRC(pin->modify(val1,cntElements-1));
#endif
	verifyExpectedCollection(session,pin,propid,strCollItems,"case6") ;

	session->free(val1);

	//case b: Modify of a big collection

	/*MVTRand::getString(str,100,150,true,true);
	val[0].set(str.c_str());val[0].setPropID(propid);
	val[0].op = OP_ADD; val[0].eid = STORE_COLLECTION_ID;
	rc = session->createPINAndCommit(pid,val,1);
	pin = session->getPIN(pid);
	if (NULL != pin){
		for (i=0;i<cntElements; i++){
			MVTRand::getString(str,10,150,true,true);
			val[0].set(str.c_str());val[0].setPropID(propid);
			val[0].op=OP_ADD;val[0].eid = STORE_COLLECTION_ID;
			rc = pin->modify(val,1);
			if (RC_OK != rc)
				std::cout<<"Modify failed at element: "<<i<<std::endl;
		}
	}*/

	//case 6 b: modify a big c again.
	reportRunningCase("add many more elements");

	MVTRand::getString(str,100,150,true,true);
	for (unsigned int z =0; z < (2*cntElements); z ++){ 
		val[0].set(str.c_str());val[0].setPropID(propid);
		val[0].op = OP_ADD; val[0].eid = STORE_LAST_ELEMENT;
		TVERIFYRC(pin->modify(val,1));
	}

	//case 7: Delete of a big collection pin:
	reportRunningCase("delete pin");
	if (NULL != pin){
		TVERIFYRC(session->deletePINs(&pin,1,MODE_PURGE));
	}
	TVERIFY(pin==NULL) ;

	//case 8: delete a multiple elements at random places.
	reportRunningCase("delete random pin elements");
	Value *vals = (Value *)session->malloc(sizeof(Value) * cntElements);
	TVERIFY(vals!=NULL);
	for (i=0;i<cntElements; i++){
		vals[i].set(strCollItems[i].c_str());vals[i].setPropID(propid);
		vals[i].op = OP_ADD; vals[i].eid=STORE_COLLECTION_ID;
	}
	TVERIFYRC(session->createPIN(vals,cntElements,&pin,MODE_COPY_VALUES|MODE_PERSISTENT));
	session->free(vals);
	//pin->refresh();//to force VT_COLLECTION
			
	const Value *tmpVal = pin->getValue(propid);	
	const unsigned int cntElementsToDelete = cntElements / 10 ;

	if (VT_COLLECTION == tmpVal->type) {
		if (tmpVal->isNav()) {
			for (i=0; i < cntElementsToDelete && NULL != tmpVal; i++){
				const Value * candidate = tmpVal->nav->navigate(i+1==cntElementsToDelete?
												GO_LAST :
												GO_FIRST );
				if ( candidate == NULL ) {
					break ;
				}

				ElementID elid=tmpVal->nav->getCurrentID();

				if (i!=0 && i+1!=cntElementsToDelete){
					// Skip ahead
					for (int z=0,n=rand()%10; z < n; z++) {
						elid = tmpVal->nav->navigate(GO_NEXT)->eid;
					}				
				}

				if (isVerbose())
					mLogger.out() << "\t\tDelete 0x" << std::hex << elid << std::dec << endl ;

				val[0].setDelete(propid,elid);
				TVERIFYRC(rc = pin->modify(val,1));
				if (RC_OK != rc) break;
				tmpVal = pin->getValue(propid); // Get updated navigator
			}
		}
		else {
			for (i=0; i < cntElementsToDelete && tmpVal && tmpVal->type == VT_COLLECTION && !tmpVal->isNav() ; i++){
				int randElement = MVTRand::getRange(0,tmpVal->length-1) ;
				ElementID elid = tmpVal->varray[randElement].eid;
				char buf[100]; sprintf(buf,"Del: %08X\n",elid); 
				#ifdef WIN32
					OutputDebugString(buf);
				#endif
				if (isVerbose()) mLogger.out() << buf ;
				val[0].setDelete(propid,elid);
				TVERIFYRC(rc = pin->modify(val,1));
				if (RC_OK != rc) break;
				tmpVal = pin->getValue(propid);
			}
		}
	}
	TVERIFY( MVTApp::getCollectionLength(*pin->getValue(propid)) == (cntElements - cntElementsToDelete) ) ;
	pin->destroy();
	pin = NULL;

	//case 9: transaction effect on big collections
	//case a: commit transaction
	reportRunningCase(" transaction a ");
	testTransaction( session, propid, strCollItems, false/*rollback*/ ) ;

	//case b: rollback transaction.
#if TEST_ROLLBACK_BIGCOLLECTION
	reportRunningCase(" transaction b");
	testTransaction( session, propid, strCollItems, true/*rollback*/ ) ;
#endif


	//case 10: ssv big collections
	//(See linux bug #3823)
	reportRunningCase("SSV");
	vals = (Value *)session->malloc(sizeof(Value) * cntElements);
	TVERIFY(vals!=NULL);
	for (i =0; i < cntElements; i++){
		unsigned long len = 1 + rand() % 15000;
		vals[i].set(MVTApp::wrapClientStream(session, new MyStream(len)));vals[i].setPropID(propid);
		vals[i].op=OP_ADD;val[i].eid = STORE_LAST_ELEMENT;
	}
	TVERIFYRC(session->createPIN(vals,cntElements,&pin,MODE_COPY_VALUES|MODE_PERSISTENT));
	session->free(vals);
	if(MVTApp::getCollectionLength(*pin->getValue(propid)) != (cntElements))
		TVERIFY(!"Case 10: SSV BIG PIN ");
	pin->destroy();
	pin = NULL;


	//case 11: OP_MOVE and OP_MOVE_BEFORE of big collections

	//case 12: replication big pins
	//REVIEW: without checking notifications etc this isn't really
	//a very deep test!
	reportRunningCase("Replication BIG PIN");
	const int oldmode = session->getInterfaceMode();
	session->setInterfaceMode(ITF_REPLICATION | ITF_DEFAULT_REPLICATION);
	
	for (i=0; i<cntElements; i++){
		val[i].set(strCollItems[i].c_str());val[i].setPropID(propid);
		val[i].op = OP_ADD; /*val[0].eid = STORE_LAST_ELEMENT;*/
	}
	TVERIFYRC(session->createPIN(val,cntElements,&pin,MODE_PERSISTENT|MODE_COPY_VALUES));
	verifyExpectedCollection(session,pin,propid,strCollItems,"case12.prop0.beforecommit") ;
	//TVERIFYRC(session->commitPINs(&pin,1));
	verifyExpectedCollection(session,pin,propid,strCollItems,"case12.prop0") ;

	pin->destroy();
	pin = NULL;
	
	//case 13: remote big pins and refresh
	reportRunningCase("Remote pin");
	string identity ;
	MVTRand::getString(str,5,0,false,false) ;
	identity="testbig.identity.bigcollection"+str;
	IdentityID const iid = session->storeIdentity(identity.c_str(), NULL, 0);
	ushort const storeid = 0x1002;  // fake remote pin
	PID rpid;
	rpid.ident = iid;
	LOCALPID(rpid) = (uint64_t(storeid) << STOREID_SHIFT) + 5;
	IPIN *rpin;

	TVERIFYRC(session->createPIN(NULL, 0, &rpin, PIN_REPLICATED|MODE_PERSISTENT, &rpid));

	for (i =0; i < cntElements; i ++){
		val[0].set(strCollItems[i].c_str());val[0].setPropID((unsigned)propid);
		val[0].op = OP_ADD;
		TVERIFYRC(rpin->modify(val,1,MODE_COPY_VALUES));
	}

	verifyExpectedCollection(session,rpin,propid,strCollItems,"case13") ;

	//case 14: remote pin refresh

	TVERIFYRC(rpin->refresh());
	verifyExpectedCollection(session,rpin,propid,strCollItems,"case14") ;
	rpin->destroy();
	rpin = NULL;

	//case 14b: retrieve remote pin again
	rpin = session->getPIN(rpid);
	verifyExpectedCollection(session,rpin,propid,strCollItems,"case14b") ;
	rpin->destroy();
	rpin = NULL;

	//case 15 : Add collection elemtns one by one (look at testCustom24) will add here later.
	session->setInterfaceMode(oldmode);	
	session->free(val);
}