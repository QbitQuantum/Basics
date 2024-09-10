int
main(int argc, char *argv[])
{

	SSRC *ssrc = NULL;
	ARC *arc = NULL;
	char *url, *user, *pass, *capath;

	Identifier *ars[4];
	int i;
	PublishRequest *pr1, *pr2;
	list<PublishElement *> pulist, pdlist;
	SubscribeRequest *sr;
	SubscribeUpdate *su;
	XmlMarshalable *ipmac;
	PollResult *pres;
	
	checkAndLoadParameters(argc, argv, 0, usage, &url, &user,
			&pass, &capath);

	// create ssrc object which is used for synchronous communication
	ssrc = SSRC::createSSRC(url, user, pass, capath);
	arc = ssrc->getARC();

	for (i = 0; i < 4; i++) {
		stringstream ss;
		ss << "AR" << i;
		ars[i] = Identifiers::createAr(ss.str(), user);
	}

	ipmac = Metadata::createIpMac();
	
	pulist.push_back(Requests::createPublishUpdate(ipmac->clone(),
				ars[0]->clone(), ars[1]->clone()));
	pulist.push_back(Requests::createPublishUpdate(ipmac->clone(),
				ars[1]->clone(), ars[2]->clone()));
	pulist.push_back(Requests::createPublishUpdate(ipmac->clone(),
				ars[2]->clone(), ars[3]->clone()));
	

	pdlist.push_back(Requests::createPublishDelete(FILTER_MATCH_ALL,
			ars[0]->clone(), ars[1]->clone()));
	pdlist.push_back(Requests::createPublishDelete(FILTER_MATCH_ALL,
			ars[2]->clone(), ars[3]->clone()));
	pdlist.push_back(Requests::createPublishUpdate(ipmac->clone(),
				ars[0]->clone(), ars[3]->clone()));
	pdlist.push_back(Requests::createPublishUpdate(ipmac,
				ars[3]->clone(), ars[1]->clone()));
	
	pr1 = Requests::createPublishReq(pulist);
	pr2 = Requests::createPublishReq(pdlist);
	pr1->addXmlNamespaceDefinition(TCG_META_NSPAIR);
	pr2->addXmlNamespaceDefinition(TCG_META_NSPAIR);
	
	su = Requests::createSubscribeUpdate(
			"sub1",
			FILTER_MATCH_ALL,
			4,
			FILTER_MATCH_ALL,
			SEARCH_NO_MAX_RESULT_SIZE,
			ars[0]->clone());
	
	sr = Requests::createSubscribeReq(su);

	try {	
		ssrc->newSession();
		ssrc->publish(pr1);
		ssrc->subscribe(sr);
		pres = arc->poll();

		checkContainsOnly(pres, SEARCH, "first poll", 1);

		for (i = 0; i < 4; i++)
			if (cntRi(pres, ars[i], SEARCH) != 1)
				cerr << "unexpected RI# for AR" << i << endl;
		
		if (cntRi(pres, ars[0], ars[1], SEARCH, 1) != 1)
				cerr << "unexpected LINK 0 1" << endl;

		if (cntRi(pres, ars[1], ars[2], SEARCH, 1) != 1)
				cerr << "unexpected LINK 1 2" << endl;

		if (cntRi(pres, ars[2], ars[3], SEARCH, 1) != 1)
				cerr << "unexpected LINK 2 3" << endl;

		delete pres;

		ssrc->publish(pr2);

		pres = arc->poll();

		checkRiCnt(pres, UPDATE, "second poll", 2);
		checkRiCnt(pres, DELETE, "second poll", 2);
		
		if (cntRi(pres, ars[0], ars[3], UPDATE, 1) != 1)
				cerr << "unexpected LINK 0 3" << endl;
		
		if (cntRi(pres, ars[1], ars[3], UPDATE, 1) != 1)
				cerr << "unexpected LINK 0 3" << endl;
		
		if (cntRi(pres, ars[0], ars[1], DELETE, 1) != 1)
			cerr << "LINK 0 2 not there?" << endl;
		
		if (cntRi(pres, ars[2], ars[3], DELETE, 1) != 1)
			cerr << "LINK 2 3 not there?" << endl;

		delete pres;
		ssrc->endSession();
	} catch (XmlCommunicationError e) {
		cerr << e << endl;
	} catch (ErrorResult e) {
		cerr << e << endl;
	}

	for (i = 0; i < 4; i++)
		delete ars[i];

	delete sr;
	delete pr1;
	delete pr2;
	delete arc;
	delete ssrc;
	return 0;
}