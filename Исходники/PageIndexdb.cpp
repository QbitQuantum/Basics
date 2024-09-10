// . make a web page from results stored in msg40
// . send it on TcpSocket "s" when done
// . returns false if blocked, true otherwise
// . sets g_errno on error
bool gotIndexList ( void *state ) {
	// the state
	State10 *st = (State10 *) state;
	// launch more
	if ( ! launchRequests ( st ) ) return false;
	/*
	// get the date list
	//fprintf(stderr,"termId now=%lli\n",st->m_termId);
	//fprintf(stderr,"should be=%lli\n",(st->m_termId & TERMID_MASK));
	// . now get the indexList for this termId
	// . date is complemented, so start with bigger one first
	key128_t startKey = g_datedb.makeStartKey ( st->m_termId ,0xffffffff);
	key128_t endKey   = g_datedb.makeEndKey   ( st->m_termId ,0x0);
	// get the rdb ptr to titledb's rdb
	//Rdb *rdb = g_indexdb.getRdb();
	// -1 means read from all files in Indexdb
	long numFiles = -1;
	// make it zero if caller doesn't want to hit the disk
	if ( ! st->m_useDisk ) numFiles = 0;
	// get the title rec at or after this docId
	if ( ! st->m_msg0.getList ( -1 ,
				    0  ,
				    0  ,
				    0  ,    // max cache age
				    false , // add to cache?
				    RDB_DATEDB  , // rdbId of 2 = indexdb
				    st->m_coll ,
				    &st->m_list2  ,
				    (char *)&startKey  ,
				    (char *)&endKey    ,
				    st->m_numRecs * sizeof(key128_t),//recSizes
				    //st->m_useTree   , // include tree?
				    //st->m_useCache  , // include cache?
				    //false     , // add to cache?
				    //0         , // startFileNum
				    //numFiles  , // numFiles
				    st        , // state
				    gotIndexListWrapper2 ,
				    0  ) )  // niceness
		return false;
	// otherwise call gotResults which returns false if blocked, true else
	// and sets g_errno on error
	return gotIndexList2 ( (void *) st , NULL );
}


void gotIndexListWrapper2 ( void *state , RdbList *list ) {
	gotIndexList2 ( state , list );
}

void addedKeyWrapper ( void *state ) {
	gotIndexList2 ( state, NULL );
}

// . make a web page from results stored in msg40
// . send it on TcpSocket "s" when done
// . returns false if blocked, true otherwise
// . sets g_errno on error
bool gotIndexList2 ( void *state , RdbList *list ) {
	// the state
	State10 *st = (State10 *) state;
	*/
	// get the socket
	TcpSocket *s = st->m_socket;
	// don't allow pages bigger than 128k in cache
	//char  buf [ 64*1024 ];
	// a ptr into "buf"
	//char *p    = buf;
	//char *pend = buf + 64*1024;
	/*
	// get termId
	key_t k = *(key_t *)st->m_list.getStartKey();
	long long termId = g_indexdb.getTermId ( k );
	// get groupId from termId
	//unsigned long groupId = k.n1 & g_hostdb.m_groupMask;
	unsigned long groupId = g_indexdb.getGroupIdFromKey ( &k );
	long hostnum = g_hostdb.makeHostId ( groupId );
	*/
	// check box " checked" strings
	char *ubs = "";
	char *uts = "";
	char *uds = "";
	char *ucs = "";
	char *add = "";
	char *del = "";
	if ( st->m_useDatedb) ubs = " checked";
	if ( st->m_useTree  ) uts = " checked";
	if ( st->m_useDisk  ) uds = " checked";
	if ( st->m_useCache ) ucs = " checked";
	if ( st->m_add      ) add = " checked";
	if ( st->m_del      ) del = " checked";

	SafeBuf *pbuf = &st->m_pbuf;

	g_pages.printAdminTop ( pbuf , st->m_socket , &st->m_r );

	// get base, returns NULL and sets g_errno to ENOCOLLREC on error
	RdbBase *base; 
	if (!(base=getRdbBase((uint8_t)RDB_INDEXDB,st->m_collnum)))return true;

	// print the standard header for admin pages
	pbuf->safePrintf ( 
		  "<center>\n"
		  "<table cellpadding=2><tr><td colspan=4>"
		  "useDatedb:<input type=checkbox value=1 name=ub%s> "
		  "useTree:<input type=checkbox value=1 name=ut%s> "
		  "useDisk:<input type=checkbox value=1 name=ud%s> "
		  "useCache:<input type=checkbox value=1 name=uc%s> "
		  "ADD:<input type=checkbox value=1 name=add%s> "
		  "DELETE:<input type=checkbox value=1 name=del%s>"
		  "</td></tr><tr><td>"
		  "query:"
		  "</td><td>"
		  "<input type=text name=q value=\"%s\" size=20>"
		  "</td><td>"
		  "collection:"
		  "</td><td>"
		  "<input type=text name=c value=\"%s\" size=10>"
		  "</td></tr><tr><td>"
		  "termId:"
		  "</td><td>"
		  "<input type=text name=t value=%lli size=20>"
		  "</td><td>"
		  "numRecs:"
		  "</td><td>"
		  "<input type=text name=numRecs value=%li size=10> "
		  "</td></tr><tr><td>"
		  "docId:"
		  "</td><td>"
		  "<input type=text name=d value=%lli size=20> "
		  "</td><td>"
		  "score:"
		  "</td><td>"
		  "<input type=text name=score value=%li size=10> "
		  "</td><td>"
		  "<input type=submit value=ok border=0>"
		  "</td></tr>"
		  "<tr><td colspan=2>"
		  "term appears in about %lli docs +/- %li"
		  "</td></tr>"
		  //"<tr><td colspan=2>"
		  //"this indexlist held by host #%li and twins"
		  //"</td></tr>"
		  "</table>"
		  "</form><br><br>" ,
		  ubs, uts, uds, ucs, add, del,
		  st->m_query , st->m_coll , st->m_termId  , 
		  st->m_numRecs  ,
		  st->m_docId , (long)st->m_score ,
		  st->m_termFreq ,
		  2 * (long)GB_INDEXDB_PAGE_SIZE / 6 * 
		  base->getNumFiles() );
		  //hostnum );

	if ( g_errno || (st->m_list.isEmpty() ) ) {//&&st->m_list2.isEmpty())){
		if (g_errno)pbuf->safePrintf("Error = %s",mstrerror(g_errno));
		else        pbuf->safePrintf("List is empty");
		pbuf->safePrintf("</center>");
		// erase g_errno for sending
		g_errno = 0;
		// now encapsulate it in html head/tail and send it off
		bool status = g_httpServer.sendDynamicPage(s , 
							   pbuf->getBufStart(),
							   pbuf->length() );
		// delete it
		mdelete ( st , sizeof(State10) , "PageIndexdb" );
		delete (st);
		return status;
	}

	pbuf->safePrintf ( 
		  "<table cellpadding=1 border=1>" 
		  "<tr><td>#</td><td>score</td>"
		  "<td>docId</td><td>domHash</td></tr>");

	//if ( searchingEvents

	// now print the score/docId of indexlist
	long i = 0;
	for (   st->m_list.resetListPtr () ;
	      ! st->m_list.isExhausted  () ;
		st->m_list.skipCurrentRecord () ) {
		// break if buf is low
		//if ( p + 1024 >= pend ) break;
		// but set the ip/port to a host that has this titleRec
		// stored locally!
		long long     docId   = st->m_list.getCurrentDocId () ;
		//unsigned long groupId = getGroupIdFromDocId ( docId );
		long shardNum = getShardNumFromDocId ( docId );
		// get the first host's hostId in this groupId
		//Host *h = g_hostdb.getFastestHostInGroup ( groupId );
		Host *hosts = g_hostdb.getShard ( shardNum );
		// just pick a host now...
		Host *h = &hosts[0];
		// . pick the first host to handle the cached titleRec request
		// . we assume it has the best time and is up!! TODO: fix!
		// . use local ip though if it was an internal request
		// . otherwise, use the external ip
		//unsigned long  ip   = h->m_externalIp;
		unsigned long  ip   = h->m_ip;
		// use the NAT mapped port
		unsigned short port = h->m_externalHttpPort;
		// log the first docid so we can blaster url: queries
		// to PageIndexdb and see if they are in indexdb
		if ( i == 0 ) 
			logf(LOG_INFO,"indexdb: %llu %s",docId,st->m_query);
		// adjust ip/port if local
		if ( st->m_isLocal ) {
			ip   = h->m_ip;
			port = h->m_httpPort;
		}
		unsigned long date = 0;
		if ( st->m_useDatedb )
			date = (unsigned long)st->m_list.getCurrentDate();
		uint8_t dh = g_titledb.getDomHash8FromDocId ( docId );
		char ds[32];
		ds[0]=0;
		if ( st->m_useDatedb ) sprintf (ds,"%lu/",date);
		pbuf->safePrintf ( 
			  "<tr><td>%li.</td>"
			  "<td>%s%i</td>"
			  "<td>"
			  //"<a href=http://%s:%hu/admin/titledb?d=%llu>"
			  "<a href=/admin/titledb?c=%s&d=%llu>"
			  "%llu"
			  //"<td><a href=/cgi/4.cgi?d=%llu>%llu"
			  "</td>"
			  "<td>"
			  "0x%02lx"
			  "</td>"
			  "</tr>\n" ,
			  i++,
			  ds, (int)st->m_list.getCurrentScore() ,
			  //iptoa(ip) , port ,
			  st->m_coll,
			  docId , 
			  docId ,
			  (long)dh );
	}	
	pbuf->safePrintf ( "</table>" );

	/*
	if ( ! st->m_list2.isEmpty() ) 
		p += sprintf ( p ,
			       "<br>"
			       "<br>"
			       "<table cellpadding=1 border=1>" 
			       "<tr><td>#</td><td>termId</td>"
			       "<td>date</td><td>score</td>"
			       "<td>docId</td></tr>");

	// now print the score/docId of datedb list
	i = 0;
	for (   st->m_list2.resetListPtr () ;
	      ! st->m_list2.isExhausted  () ;
		st->m_list2.skipCurrentRecord () ) {
		// break if buf is low
		if ( p + 1024 >= pend ) break;
		// but set the ip/port to a host that has this titleRec
		// stored locally!
		long long     docId   = st->m_list2.getCurrentDocId () ;
		unsigned long groupId = g_titledb.getGroupId ( docId );
		// get the first host's hostId in this groupId
		Host *h = g_hostdb.getFastestHostInGroup ( groupId );
		// . pick the first host to handle the cached titleRec request
		// . we assume it has the best time and is up!! TODO: fix!
		// . use local ip though if it was an internal request
		// . otherwise, use the external ip
		//unsigned long  ip   = h->m_externalIp;
		unsigned long  ip   = h->m_ip;
		// use the NAT mapped port
		unsigned short port = h->m_externalHttpPort;
		// adjust ip/port if local
		if ( st->m_isLocal ) {
			ip   = h->m_ip;
			port = h->m_httpPort;
		}
		// debug
		char kb[16];
		st->m_list2.getCurrentKey(kb);
		//log(LOG_INFO,"debug: n1=%016llx n0=%016llx",
		//    *(long long *)(kb+8),*(long long *)(kb+0));
		//if ( (unsigned long)st->m_list2.getCurrentDate() == 0 )
		//	log("STOP");
		sprintf ( p , 
			  "<tr><td>%li.</td>"
			  "<td>%llu</td>"
			  "<td>%lu</td><td>%i</td>"
			  "<td>"
			  //"<a href=http://%s:%hu/admin/titledb?d=%llu>"
			  "<a href=/admin/titledb?c=%s&d=%llu>"
			  "%llu"
			  //"<td><a href=/cgi/4.cgi?d=%llu>%llu"
			  "</td></tr>\n" ,
			  i++,
			  st->m_list2.getTermId16(kb) ,
			  (unsigned long)st->m_list2.getCurrentDate() ,
			  (int)st->m_list2.getCurrentScore() ,
			  //iptoa(ip) , port ,
			  st->m_coll,
			  docId , 
			  docId );
		p += gbstrlen ( p );
	}	
	*/
	if ( ! st->m_list.isEmpty() ) 
		pbuf->safePrintf ( "</table>" );


	// print msg if we could fit all into buf
	//if ( p + 1024 >= pend ) {
	//	sprintf ( p ,"... truncated ... no mem" );
	//	p += gbstrlen ( p );		
	//}
	// print the final tail
	//p += g_httpServer.printTail ( p , pend - p );
	pbuf->safePrintf ( "</center>\n");
	// now encapsulate it in html head/tail and send it off
	bool status = g_httpServer.sendDynamicPage ( s , 
						     pbuf->getBufStart() ,
						     pbuf->length() );
	// delete the state
	mdelete ( st , sizeof(State10) , "PageIndexdb" );
	delete (st) ;
	return status;
}