__uint CEvtAswThread::run()
{
	CEvtAswPkt &aswPkt = *((CEvtAswPkt *)heap);
	int count = 0;

	switch(qryPkt.eClass){
	case AC_Alarm:
	case AC_AckAlarm:
	case AC_CancelAlarm:
	case AC_Online:
	case AC_Offline:
		count = alarms->getRecord(qryPkt.stm, qryPkt.etm, qryPkt.count, events);
		break;
	case AC_WriteDevice:
		count = operates->getRecord(qryPkt.stm, qryPkt.etm, qryPkt.count, events);
		break;
	}

	int pcount;
	CMulticastSocket sck;
	RTK_TIME	t1, t2;
	
	sck.Socket();
	
	int length=65535;
	sck.SetSockOpt(SO_RCVBUF, (void *)&length, sizeof(length));
	sck.SetSockOpt(SO_SNDBUF, (void *)&length, sizeof(length));

	utils_debug(
		"Answering query from %s:%d of class %d with %d entries.\n", 
		src,
		port,
		qryPkt.eClass,
		count
		);

	rtk_time_mark(&t1);
	aswPkt.gid = qryPkt.gid;
	aswPkt.id = 0;
	aswPkt.count = COUNT_IN_ONE_PKT;
	pcount = 0;
	CPMCEvent * pEvent = events;
	while(count >= COUNT_IN_ONE_PKT){
		memcpy(
			// aswPkt.events, 
			EVT_ARRAY_OF(aswPkt),
			pEvent,
			COUNT_IN_ONE_PKT * sizeof(CPMCEvent)
			);
		sck.SendTo(
			&aswPkt, 
			sizeof(CEvtAswPkt) + COUNT_IN_ONE_PKT * sizeof(CPMCEvent),
			port, 
			src
			);
		pEvent += COUNT_IN_ONE_PKT;
		aswPkt.id += COUNT_IN_ONE_PKT;
		pcount++;
		count -= COUNT_IN_ONE_PKT;
		Sleep(100);
	}
	if(count){
		aswPkt.count = count;
		memcpy(
			// aswPkt.events, 
			EVT_ARRAY_OF(aswPkt),
			pEvent,
			count * sizeof(CPMCEvent)
			);
		pcount++;
		sck.SendTo(
			&aswPkt, 
			sizeof(CEvtAswPkt) + count * sizeof(CPMCEvent),
			port, 
			src
			);
	}
	rtk_time_mark(&t2);

	utils_debug(
		"%d packets sent in %.3f seconds.\n", 
		pcount,
		rtk_time_diff(&t2, &t1) 
		);

	Sleep(1000);

	delete this;

	return 1;
}