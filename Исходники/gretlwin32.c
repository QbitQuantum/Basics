static DWORD open_dde_conversation (LPCTSTR topic_name,
				    const char *exename,
				    const char *ddename,
				    HCONV *convp)
{
    DWORD session = 0;
    HCONV conversation = NULL;
    HSZ service, topic;
    UINT ret;
    int i, err = 0;
    
    ret = DdeInitialize(&session, (PFNCALLBACK) init_callback,
			APPCLASS_STANDARD | APPCMD_CLIENTONLY, 0);
    
    if (ret != DMLERR_NO_ERROR) {
	fprintf(stderr, "DDE: couldn't initialize session\n");
	return 0;
    }

    service = DdeCreateStringHandle(session, ddename, CP_WINANSI);
    topic   = DdeCreateStringHandle(session, topic_name, CP_WINANSI);

    if (!service || !topic) {
	fprintf(stderr, "DDE: string creation failed\n");
	DdeUninitialize(session);
	return 0;
    }
    
    conversation = DdeConnect(session, service, topic, 0);

    if (conversation == NULL) {
	err = start_dde_server(exename);
	if (!err) {
	    /* try to connect */
	    for (i=0; i<5 && !conversation; i++) {
		Sleep(CONNECT_DELAY);
		conversation = DdeConnect(session, service, topic, 0);
	    }
	}
	if (conversation == NULL && !err) {
	    fprintf(stderr, "DDE: couldn't contact server %s\n", ddename);
	    err = 1;
	}	
    }

    DdeFreeStringHandle(session, service);
    DdeFreeStringHandle(session, topic);

    if (err) {
	DdeUninitialize(session);
	session = 0;
    } else {
	*convp = conversation;
    }

    return session;
}