// . delete a collection
// . this uses blocking unlinks, may make non-blocking later
bool Collectiondb::deleteRec ( char *coll , bool deleteTurkdb ) {
	// force on for now
	deleteTurkdb = true;
	// no spiders can be out. they may be referencing the CollectionRec
	// in XmlDoc.cpp... quite likely.
	if ( g_conf.m_spideringEnabled ||
	     g_spiderLoop.m_numSpidersOut > 0 ) {
		log("admin: Can not delete collection while "
		    "spiders are enabled or active.");
		return false;
	}
	// do not allow this if in repair mode
	if ( g_repairMode > 0 ) {
		log("admin: Can not delete collection while in repair mode.");
		return false;
	}
	// ensure it's not NULL
	if ( ! coll ) {
		log(LOG_LOGIC,"admin: Collection name to delete is NULL.");
		return false;
	}
	// find the rec for this collection
	collnum_t collnum = getCollnum ( coll );
	// bitch if not found
	if ( collnum < 0 ) {
		g_errno = ENOTFOUND;
		return log(LOG_LOGIC,"admin: Collection \"%s\" not found, "
			   "delete failed.",coll);
	}
	CollectionRec *cr = m_recs [ collnum ];
	if ( ! cr ) return log("admin: Collection id problem. Delete failed.");
	// we need a save
	m_needsSave = true;
	// nuke it on disk
	char oldname[1024];
	sprintf(oldname, "%scoll.%s.%li/",g_hostdb.m_dir,cr->m_coll,
		(long)cr->m_collnum);
	char newname[1024];
	sprintf(newname, "%strash/coll.%s.%li.%lli/",g_hostdb.m_dir,cr->m_coll,
		(long)cr->m_collnum,gettimeofdayInMilliseconds());
	//Dir d; d.set ( dname );
	// ensure ./trash dir is there
	char trash[1024];
	sprintf(trash, "%strash/",g_hostdb.m_dir);
	::mkdir ( trash, 
		  S_IRUSR | S_IWUSR | S_IXUSR | 
		  S_IRGRP | S_IWGRP | S_IXGRP | 
		  S_IROTH | S_IXOTH ) ;
	// move into that dir
	::rename ( oldname , newname );
	// debug message
	logf ( LOG_INFO, "admin: deleted collection \"%s\" (%li).",
	       coll,(long)collnum );

	// nuke doleiptable and waintree and waitingtable
	/*
	SpiderColl *sc = g_spiderCache.getSpiderColl ( collnum );
	sc->m_waitingTree.clear();
	sc->m_waitingTable.clear();
	sc->m_doleIpTable.clear();
	g_spiderLoop.m_lockTable.clear();
	g_spiderLoop.m_lockCache.clear(0);
	sc->m_lastDownloadCache.clear(collnum);
	*/

	// remove from spider cache, tell it to sync up with collectiondb
	//g_spiderCache.reset1();
	// . TODO: remove from g_sync
	// . remove from all rdbs
	//g_indexdb.getRdb()->delColl    ( coll );
	g_posdb.getRdb()->delColl    ( coll );
	//g_datedb.getRdb()->delColl     ( coll );

	g_titledb.getRdb()->delColl    ( coll );
	//g_revdb.getRdb()->delColl      ( coll );
	//g_sectiondb.getRdb()->delColl  ( coll );
	g_tagdb.getRdb()->delColl ( coll );
	// let's preserve the tags... they have all the turk votes in them
	if ( deleteTurkdb ) {
	}
	//g_catdb.getRdb()->delColl      ( coll );
	//g_checksumdb.getRdb()->delColl ( coll );
	g_spiderdb.getRdb()->delColl   ( coll );
	g_doledb.getRdb()->delColl     ( coll );
	//g_tfndb.getRdb()->delColl      ( coll );
	g_clusterdb.getRdb()->delColl  ( coll );
	g_linkdb.getRdb()->delColl     ( coll );
	// free it
	mdelete ( m_recs[(long)collnum], sizeof(CollectionRec), 
		  "CollectionRec" ); 
	delete ( m_recs[(long)collnum] );
	m_recs[(long)collnum] = NULL;
	// dec counts
	m_numRecsUsed--;
	while ( ! m_recs[m_numRecs-1] ) m_numRecs--;
	// update the time
	updateTime();
	// done
	return true;
}