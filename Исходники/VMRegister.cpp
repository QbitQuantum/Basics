void
VMRegister::requestHostClassAds(void)
{
	// find host startd daemon
	if( !m_vm_host_daemon )
		m_vm_host_daemon = vmapi_findDaemon( m_vm_host_name, DT_STARTD);

	if( !m_vm_host_daemon ) {
		dprintf( D_FULLDEBUG, "Can't find host(%s) Startd daemon\n", m_vm_host_name );
		return;
	}

	ClassAd query_ad;
	query_ad.SetMyTypeName(QUERY_ADTYPE);
	query_ad.SetTargetTypeName(STARTD_ADTYPE);
	query_ad.Assign(ATTR_REQUIREMENTS, true);

	char *addr = m_vm_host_daemon->addr();
	Daemon hstartd(DT_STARTD, addr);
	ReliSock ssock;

	ssock.timeout( VM_SOCKET_TIMEOUT );
	ssock.encode();

	if( !ssock.connect(addr) ) {
		dprintf( D_FULLDEBUG, "Failed to connect to host startd(%s)\n to get host classAd", addr);
		return;
	}

	if(!hstartd.startCommand( QUERY_STARTD_ADS, &ssock )) {
		dprintf( D_FULLDEBUG, "Failed to send QUERY_STARTD_ADS command to host startd(%s)\n", addr);
		return;
	}

	if( !query_ad.put(ssock) ) {
		dprintf(D_FULLDEBUG, "Failed to send query Ad to host startd(%s)\n", addr);
	}

	if( !ssock.end_of_message() ) {
		dprintf(D_FULLDEBUG, "Failed to send query EOM to host startd(%s)\n", addr);
	}

	// Read host classAds
	ssock.timeout( VM_SOCKET_TIMEOUT );
	ssock.decode();
	int more = 1, num_ads = 0;
	ClassAdList adList;
	ClassAd *ad;

	while (more) {
		if( !ssock.code(more) ) {
			ssock.end_of_message();
			return;
		}

		if(more) {
			ad = new ClassAd;
			if( !ad->initFromStream(ssock) ) {
				ssock.end_of_message();
				delete ad;
				return;
			}

			adList.Insert(ad);
			num_ads++;
		}
	}

	ssock.end_of_message();

	dprintf(D_FULLDEBUG, "Got %d classAds from host\n", num_ads);

	// Although we can get more than one classAd from host machine, 
	// we use only the first one classAd
	adList.Rewind();
	ad = adList.Next();

#if !defined(WANT_OLD_CLASSADS)
	ad->AddTargetRefs( TargetJobAttrs );
#endif

	// Get each Attribute from the classAd
	// added "HOST_" in front of each Attribute name
	const char *name;
	ExprTree *expr;

	ad->ResetExpr();
	while( ad->NextExpr(name, expr) ) {
		MyString attr;
		attr += "HOST_";
		attr += name;

		// Insert or Update an attribute to host_classAd in a VMRegister object
		ExprTree * pTree = expr->Copy();
		host_classad->Insert(attr.Value(), pTree, true);
	}
}