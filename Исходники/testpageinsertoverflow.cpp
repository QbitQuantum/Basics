int TestPageInsertOverflow::execute()
{
	bool lSuccess = true; 
	if (MVTApp::startStore())
	{
		ISession * session =	MVTApp::startSession();
		Value val[sNumProps];PID pid1;IPIN *pin1;
        	MVTApp::mapURIs(session, "TestPageInsertOverflow.prop.", sNumProps, lPropIDs);
		TVERIFYRC(session->createPIN(NULL,0,&pin1,MODE_PERSISTENT));
		pid1 = pin1->getPID();
		if(pin1!=NULL) pin1->destroy();
		for (int i=0; i < 10; i++)
		{
			IPIN *pin;Tstring str;int k=0;int x=0;
			for (k=0; k < 10; k++)
			{
				MVTApp::randomString(str,1,30);
				val[k].set(str.c_str());val[k].setPropID(lPropIDs[k]);
			}
			TVERIFYRC(session->createPIN(val,k-1,&pin,MODE_PERSISTENT|MODE_COPY_VALUES));
			for (x =0; x < 10;x++,k++)
			{
				val[x].set(pid1);val[x].setPropID(lPropIDs[k]);
				val[x].op = OP_ADD;val[x].eid = STORE_FIRST_ELEMENT;
			}
			TVERIFYRC(pin->modify(val,x));
			for (x =0; x < 40;x++,k++)
			{
				val[x].set("a");val[x].setPropID(lPropIDs[k]);
			}
			TVERIFYRC(pin->modify(val,x));
			for (x =0; x < 10;x++,k++)
			{
				val[x].set(pid1);val[x].setPropID(lPropIDs[k]);
				val[x].op = OP_ADD;val[x].eid = STORE_FIRST_ELEMENT;
			}
			TVERIFYRC(pin->modify(val,x));
			for (x =0; x < 10;x++,k++)
			{
				val[x].set(pid1);val[x].setPropID(lPropIDs[k]);
			}
			session->startTransaction();
			TVERIFYRC(pin->modify(val,x));
			if(pin!=NULL) pin->destroy();
			session->rollback();
		}
		session->terminate();
		MVTApp::stopStore();
	}
	else { TVERIFY(!"could not open store") ; }
	return lSuccess ? 0 : 1;
}