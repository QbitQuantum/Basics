bool SearchInput::set ( TcpSocket *sock , HttpRequest *r , Query *q ) {

	// get coll rec
	long  collLen;
	char *coll = r->getString ( "c" , &collLen );
	//if (! coll){coll = g_conf.m_defaultColl; collLen = gbstrlen(coll); }
	if ( ! coll )
		coll = g_conf.getDefaultColl(r->getHost(), r->getHostLen());
	if ( ! coll ) { g_errno = ENOCOLLREC; return false; }
	collLen = gbstrlen(coll);
	CollectionRec *cr = g_collectiondb.getRec ( coll );
	if ( ! cr ) { 
		g_errno = ENOCOLLREC;
		g_msg = " (error: no such collection)";		
		return false;
	}

	// set all to 0 just to avoid any inconsistencies
	//long size = (char *)&m_END_TEST - (char *)&m_START;
	//memset ( this , 0x00 , size );
	setToDefaults( cr , 0 ); // niceness

	m_cr = cr;

	m_coll2    = m_cr->m_coll;
	m_collLen2 = gbstrlen(m_coll2);

	// from ::reset()
	m_languageWeightFactor = 0.33;

	// Set IP for language detection.
	// (among other things)
	if ( sock ) m_queryIP = sock->m_ip;
	else        m_queryIP = 0;
	m_hr = r;

	// keep ptr to the query class to use
	m_q        = q;

	// set this here since its size can be variable
	m_sq = r->getString("sq",&m_sqLen);
	// negative docids
	m_noDocIds = r->getString("nodocids",&m_noDocIdsLen);
	// negative sites
	m_noSiteIds = r->getString("nositeids",&m_noSiteIdsLen);

	// Msg5e calls Msg40 with this set to true in the searchInput
	// so it can analyze the entire pages of each search result so it
	// can find the article start/end tag sequence indicators
	m_getTitleRec = r->getLong("gettrs",0);

	m_getSitePops = r->getLong("getsitepops",0 );

        // does this collection ban this IP?
	/*
	long  encapIp = 0; 
m	if (! cr->hasSearchPermission ( sock, encapIp ) ) {
		g_errno = ENOPERM;
		g_msg = " (error: permission denied)";
		return false;
	}
	*/

	// set all search parms in SearchInput to defaults
	for ( long i = 0 ; i < g_parms.m_numSearchParms ; i++ ) {
		Parm *m = g_parms.m_searchParms[i];
		// sanity
		if ( m->m_soff < 0 ) { char *xx=NULL;*xx=0; }
		char *x = (char *)this + m->m_soff;
		// what is the def val ptr
		char *def = NULL;
		if      ( m->m_off >= 0 && m->m_obj == OBJ_COLL )
			def = ((char *)cr) + m->m_off;
		else if ( m->m_off >= 0 && m->m_obj == OBJ_CONF )
			def = ((char *)&g_conf) + m->m_off;
		// set it based on type
		if      ( m->m_type == TYPE_LONG ) {
			long v = 0;
			if ( def )
				v = *(long *)def;
			else if ( m->m_def ) 
				v = atol(m->m_def);
			*(long *)x = v;
		}
		else if ( m->m_type == TYPE_BOOL ) {
			long v = 0;
			if ( def ) 
				v = *(char *)def;
			else if ( m->m_def ) 
				v = atol(m->m_def);
			// sanity test!
			if ( v != 0 && v != 1 )
				log("query: got non-bool default "
				    "for bool parm %s",m->m_title);
			if ( v ) *(char *)x = 1;
			else     *(char *)x = 0;
		}
		else if ( m->m_type == TYPE_CHAR ) {
			if ( def )
				*(char *)x = *(char *)def;
			else if ( m->m_def ) 
				*(char *)x = atol(m->m_def);
		}
		else if ( m->m_type == TYPE_FLOAT ) {
			float v = 0;
			if ( def )
				v = *(float *)def;
			else if ( m->m_def ) 
				v = atof(m->m_def);
			*(float *)x = (float)v;
		}
		else if ( m->m_type == TYPE_STRING ||
			  m->m_type == TYPE_STRINGBOX ) {
			//if ( m->m_cgi && strcmp ( m->m_cgi, "erpc" ) == 0 )
			//	log("hey1");
			//if ( m->m_cgi && strcmp ( m->m_scgi, "q" ) == 0 )
			//	log("hey1");
			char *v = NULL;
			if ( def )
				v = (char *)def;
			else if ( m->m_def ) 
				v = m->m_def;
			*(char **)x = v;
			// set the length
			if ( ! v ) *(long *)(x-4) = 0;
			else       *(long *)(x-4) = gbstrlen(v);
		}
	}

	// this is just used to determine in PageResults.cpp if we should
	// show admin knobs next to each result...
	// default to off for now
	m_isAdmin = r->getLong("admin",0);
	//if ( m_isAdmin ) m_isAdmin = g_users.hasPermission ( r , PAGE_MASTER );
	// local ip?
	if ( ! r->isLocal() ) m_isAdmin = 0;

	// default set does not take into account g_conf,
	// so we will take care of that here ourselves...
	m_adFeedEnabled  = g_conf.m_adFeedEnabled;
	//m_excludeLinkText = g_conf.m_excludeLinkText;
	//m_excludeMetaText = g_conf.m_excludeMetaText;

	// we need to get some cgi values in order to correct the defaults
	// based on if we're doing an xml feed, have a site: query, etc.
	long  xml      = r->getLong ( "xml" , 0 ); // was "raw"
	long  siteLen  = 0; r->getString ("site",&siteLen);
	long  sitesLen = 0; 
	char *sites = r->getString ("sites",&sitesLen,NULL);

	// save it if there
	if ( sites && sitesLen > 0 && 
	     ( ! m_whiteListBuf.safeStrcpy(sites)||
	       ! m_whiteListBuf.nullTerm() ) )
		return log("query: unable to strcpy whitelist");
	
	// now override automatic defaults for special cases
	if ( xml > 0 ) {
		m_familyFilter            = 0;
		// this is causing me a headache when on when i dont know it
		m_restrictIndexdbForQuery   = false;
		// this is hackish
		if ( r->getLong("rt",0) ) m_restrictIndexdbForQuery=false;
		m_numTopicsToDisplay      = 0;
		m_doQueryHighlighting     = 0;
		m_spellCheck              = 0;
		m_refs_numToGenerate      = 0;
		m_refs_docsToScan         = 0;
	}
	else if ( m_siteLen > 0 ) {
		m_restrictIndexdbForQuery = false;
		m_doSiteClustering        = false;
		m_ipRestrictForTopics     = false;
	}
	else if ( m_whiteListBuf.length() > 0 ) {
		m_ipRestrictForTopics     = false;
	}

	m_doIpClustering          = false;
	//m_sitesQueryLen           = 0;

	// set the user ip, "uip"
	long uip = m_queryIP;
	char *uipStr = m_hr->getString ("uip" , NULL );
	long tmpIp = 0; if ( uipStr ) tmpIp = atoip(uipStr);
	if ( tmpIp ) uip = tmpIp;

	//
	//
	// BEGIN MAIN PARM SETTING LOOP
	//
	//

	// loop through all possible cgi parms to set SearchInput
	for ( long i = 0 ; i < g_parms.m_numSearchParms ; i++ ) {
		Parm *m = g_parms.m_searchParms[i];
		char *x = (char *)this + m->m_soff;
		// what is the parm's cgi name?
		char *cgi = m->m_scgi;
		if ( ! cgi ) cgi = m->m_cgi;
		// sanity check
		if ( ! m->m_sparm ) {
			log("query: Failed search input sanity check.");
			char *xx = NULL; *xx = 0;
		}
		// . break it down by type now
		// . get it from request and store it in SearchInput
		if ( m->m_type == TYPE_LONG ) {
			// default was set above
			long def = *(long *)x;
			// assume default
			long v = def;
			// but cgi parms override cookie
			v = r->getLong ( cgi , v );
			// but if its a privledged parm and we're not an admin
			// then do not allow overrides, but m_priv of 3 means
			// to not display for clients, but to allow overrides
			if ( ! m_isAdmin && m->m_priv && m->m_priv!=3) v = def;
			// bounds checks
			if ( v < m->m_smin ) v = m->m_smin;
			if ( v > m->m_smax ) v = m->m_smax;
			if ( m->m_sminc >= 0 ) {
				long vmin = *(long *)((char *)cr+m->m_sminc);
				if ( v < vmin ) v = vmin;
			}
			if ( m->m_smaxc >= 0 ) {
				long vmax = *(long *)((char *)cr+m->m_smaxc);
				if ( v > vmax ) v = vmax;
			}
			// set it
			*(long *)x = v;
			// do not print start result num (m->m_sprop is 0 for 
			// "s" now)
			//if ( cgi[0] == 's' && cgi[1] == '\0' ) continue;
			// should we propagate it? true by default
			//if ( ! m->m_sprop ) continue;
			// if it is the same as its default, and the default is
			// always from m_def and never from the CollectionRec, 
			// then do not both storing it in here! what's the 
			// point?
			if ( v == def && m->m_off < 0 ) continue;
			// if not default do not propagate
			if ( v == def ) continue;
			// . include for sure if explicitly provided
			// . vp will be NULL if "cgi" is not explicitly listed 
			//   as a cgi parm. otherwise, even if *vp == '\0', vp
			//   is non-NULL.
			// . crap, it can be in the cookie now
			//char *vp = r->getValue(cgi, NULL, NULL);
			// if not given at all, do not propagate
			//if ( ! vp ) continue;
			// store in up if different from default, even if
			// same as default ("def") because default may be
			// changed by the admin since m->m_off >= 0
			//if ( m->m_sprpg && up + gbstrlen(cgi) + 20 < upend ) 
			//	up += sprintf ( up , "%s=%li&", cgi , v );
			//if ( m->m_sprpp && pp + gbstrlen(cgi) + 80 < ppend )
			//	pp += sprintf ( pp , "<input type=hidden "
			//			"name=%s value=\"%li\">\n", 
			//			cgi , v );
		}
		else if ( m->m_type == TYPE_FLOAT ) {
			// default was set above
			float def = *(float *)x;
			// get overriding from http request, if any
			float v;
			// but if its a privledged parm and we're not an admin
			// then do not allow overrides
			if ( ! m_isAdmin && m->m_priv && m->m_priv!=3) v = def;
			else v = r->getFloat( cgi , def );
			// bounds checks
			if ( v < m->m_smin ) v = m->m_smin;
			if ( v > m->m_smax ) v = m->m_smax;
			if ( m->m_sminc >= 0 ) {
				float vmin = *(float *)((char *)cr+m->m_sminc);
				if ( v < vmin ) v = vmin;
			}
			if ( m->m_smaxc >= 0 ) {
				float vmax = *(float *)((char *)cr+m->m_smaxc);
				if ( v > vmax ) v = vmax;
			}
			// set it
			*(float *)x = v;
			// do not print start result num
			//if ( cgi[0] == 's' && cgi[1] == '\0' ) continue;

			// include for sure if explicitly provided
			char *vp = r->getValue(cgi, NULL, NULL);
			if ( ! vp ) continue;
			// unchanged from default?
			if ( v == def ) continue;
			// store in up different from default
			//if ((vp||v!= def) && up + gbstrlen(cgi)+20 < upend ) 
			//	up += sprintf ( up , "%s=%f&", cgi , v );
			//if ((vp||v!= def) && pp + gbstrlen(cgi)+20 < ppend )
			//	pp += sprintf ( pp , "<input type=hidden "
			//			"name=%s value=\"%f\">\n", 
			//			cgi , v );
		}

		else if ( m->m_type == TYPE_BOOL ) {
			// default was set above
			long def = *(char *)x;
			if ( def != 0 ) def = 1; // normalize
			// assume default
			long v = def;
			// cgi parms override cookie
			v = r->getBool ( cgi , v );
			// but if no perm, use default
			if ( ! m_isAdmin && m->m_priv && m->m_priv!=3) v = def;
			if ( v != 0 ) v = 1; // normalize
			*(char *)x = v;
			// don't propagate rcache
			//if ( ! strcmp(cgi,"rcache") ) continue;
			// should we propagate it? true by default
			//if ( ! m->m_sprop ) continue;
			// if it is the same as its default, and the default is
			// always from m_def and never from the CollectionRec, 
			// then do not both storing it in here! what's the 
			// point?
			if ( v == def && m->m_off < 0 ) continue;
			// if not default do not propagate
			if ( v == def ) continue;
			// . include for sure if explicitly provided
			// . vp will be NULL if "cgi" is not explicitly listed 
			//   as a cgi parm. otherwise, even if *vp == '\0', vp 
			//   is non-NULL.
			// . crap, it can be in the cookie now!
			//char *vp = r->getValue(cgi, NULL, NULL);
			// if not given at all, do not propagate
			//if ( ! vp ) continue;
			// store in up if different from default, even if
			// same as default ("def") because default may be
			// changed by the admin since m->m_off >= 0
			//if ( m->m_sprpg && up + gbstrlen(cgi) + 10 < upend )
			//	up += sprintf ( up , "%s=%li&", cgi , v );
			//if ( m->m_sprpp && pp + gbstrlen(cgi) + 80 < ppend )
			//	pp += sprintf ( pp , "<input type=hidden "
			//			"name=%s value=\"%li\">\n", 
			//			cgi , v );
		}
		else if ( m->m_type == TYPE_CHAR ) {
			// default was set above
			char def = *(char *)x;
			*(char *)x = r->getLong ( cgi, def );
			// use this
			long v = *(char *)x;
			// store in up if different from default, even if
			// same as default ("def") because default may be
			// changed by the admin since m->m_off >= 0. nah,
			// let's try to reduce cgi parm pollution...
			if ( v == def ) continue;
			//if ( m->m_sprpg && up + gbstrlen(cgi) + 10 < upend )
			//	up += sprintf ( up , "%s=%li&", cgi , v );
			//if ( m->m_sprpp && pp + gbstrlen(cgi) + 80 < ppend )
			//	pp += sprintf ( pp , "<input type=hidden "
			//			"name=%s value=\"%li\">\n", 
			//			cgi , v );
		}
		else if ( m->m_type == TYPE_STRING ||
			  m->m_type == TYPE_STRINGBOX ) {
			//if ( m->m_cgi && strcmp ( m->m_cgi, "qlang" ) == 0 )
			//	log("hey2");
			char *def = *(char **)x;
			// get overriding from http request, if any
			long len = 0;
			char *v = NULL;
			// . cgi parms override cookie
			// . is this url encoded?
			v = r->getString ( cgi , &len , v );
			// if not specified explicitly, default it and continue
			if ( ! v ) {
				// sanity
				if  ( ! def ) def = "";
				*(char **)x = def;
				// length preceeds char ptr in SearchInput
				*(long *)(x - 4) = gbstrlen(def);
				continue;
			}
			// if something was specified, override, it might
			// be length zero, too
			*(char **)x = v;
			// length preceeds char ptr in SearchInput
			*(long *)(x - 4) = len;
			// do not store if query, that needs to be last so
			// related topics can append to it
			//if ( cgi[0] == 'q' && cgi[1] == '\0' ) continue;
			// should we propagate it? true by default
			//if ( ! m->m_sprop ) continue;
			// if not given at all, do not propagate
			//if ( ! vp ) continue;
			// if it is the same as its default, and the default is
			// always from m_def and never from the CollectionRec, 
			// then do not both storing it in here! what's the 
			// point?
			//if ( v && v == def && !strcmp(def,v) && m->m_off < 0)
			//	continue;
			// Need to set qcs based on page encoding...
			// not propagated
			if (!strncmp(cgi, "qcs", 3))
				continue;
			// do not propagate defaults
			if ( v == def ) continue;
			// store in up if different from default, even if
			// same as default ("def") because default may be
			// changed by the admin since m->m_off >= 0
			//if( m->m_sprpg && up+gbstrlen(cgi)+len+6  < upend ) {
			//	up += sprintf ( up , "%s=", cgi );
			//	up  += urlEncode ( up , upend-up-2 , v , len );
			//	*up++ = '&';
			//}
			// propogate hidden inputs
			//if ( m->m_sprpp && up+gbstrlen(cgi)+len+80 < upend )
			//	pp += sprintf ( pp , "<input type=hidden "
			//			"name=%s value=\"%s\">\n", 
			//			cgi , v );
		}
	}

	// now add the special "qh" parm whose default value changes 
	// depending on if we are widget related or not
	long qhDefault = 1;
	m_doQueryHighlighting = r->getLong("qh",qhDefault);


	//
	// TODO: use Parms.cpp defaults
	//
	TopicGroup *tg = &m_topicGroups[0];

	//
	//
	// gigabits
	//
	//
	tg->m_numTopics = 50;
	tg->m_maxTopics = 50;
	tg->m_docsToScanForTopics = m_docsToScanForTopics;
	tg->m_minTopicScore = 0;
	tg->m_maxWordsPerTopic = 6;
	tg->m_meta[0] = '\0';
	tg->m_delimeter = '\0';
	tg->m_useIdfForTopics = false;
	tg->m_dedup = true;
	// need to be on at least 2 pages!
	tg->m_minDocCount = 2;
	tg->m_ipRestrict = true;
	tg->m_dedupSamplePercent = 80;
	tg->m_topicRemoveOverlaps = true;
	tg->m_topicSampleSize = 4096;
	// max sequential punct chars allowedin a topic
	tg->m_topicMaxPunctLen = 1;
	m_numTopicGroups = 1;

	// use "&dg=1" to debug gigabits
	m_debugGigabits = r->getLong("dg",0);


	// . omit scoring info from the xml feed for now
	// . we have to roll this out to gk144 net i think
	if ( xml > 0 )
		m_getDocIdScoringInfo = 0;

	// turn off by default!
	if ( ! r->getLong("gigabits",0) ) {
		m_numTopicGroups = 0;
	}


	//////////////////////////////////////
	//
	// transform input into classes
	//
	//////////////////////////////////////

	// USER_ADMIN, ...
	m_username = g_users.getUsername(r);
	// if collection is NULL default to one in g_conf
	if ( ! m_coll2 || ! m_coll2[0] ) { 
		//m_coll = g_conf.m_defaultColl; 
		m_coll2 = g_conf.getDefaultColl(r->getHost(), r->getHostLen());
		m_collLen2 = gbstrlen(coll); 
	}

	// reset this
	m_gblang = 0;

	// use gblang then!
	long gglen;
	char *gg = r->getString ( "clang" , &gglen , NULL );
	if ( gg && gglen > 1 )
		m_gblang = getLanguageFromAbbr(gg);

	// allow for "qlang" if still don't have it
	//long gglen2;
	//char *gg2 = r->getString ( "qlang" , &gglen2 , NULL );
	//if ( m_gblang == 0 && gg2 && gglen2 > 1 )
	//	m_gblang = getLanguageFromAbbr(gg2);
	
	// fix query by removing lang:xx from ask.com queries
	//char *end = m_query + m_queryLen -8;
	//if ( m_queryLen > 8 && m_query && end > m_query && 
	//     strncmp(end," lang:",6)==0 ) {
	//	char *asklang = m_query+m_queryLen - 2;
	//	m_gblang = getLanguageFromAbbr(asklang);
	//	m_queryLen -= 8;
	//	m_query[m_queryLen] = 0;
	//	
	//}

	// . returns false and sets g_errno on error
	// . sets m_qbuf1 and m_qbuf2
	if ( ! setQueryBuffers (r) ) return false;


	/* --- Virtual host language detection --- */
	if(r->getHost()) {
		bool langset = getLanguageFromAbbr(m_defaultSortLanguage);
		char *cp;
		if(!langset && (cp = strrchr(r->getHost(), '.'))) {
			uint8_t lang = getLanguageFromUserAgent(++cp);
			if(lang) {
				// char langbuf[128];
				// sprintf(langbuf, "qlang=%s\0", getLanguageAbbr(lang));
				//m_defaultSortLanguage = getLanguageAbbr(lang);
                                char *tmp = getLanguageAbbr(lang);
                                strncpy(m_defaultSortLanguage, tmp, 6);
				// log(LOG_INFO,
				//	getLanguageString(lang), r->getHost(), this);
			}
		}
	}
	/* --- End Virtual host language detection --- */

	char *qs1 = m_defaultSortLanguage;

	// this overrides though
	//long qlen2;
	//char *qs2 = r->getString ("qlang",&qlen2,NULL);
	//if ( qs2 ) qs1 = qs2;
	
	m_queryLang = getLanguageFromAbbr ( qs1 );

	if ( qs1 && qs1[0] && ! m_queryLang )
		log("query: qlang of \"%s\" is NOT SUPPORTED",qs1);





	// . the query to use for highlighting... can be overriden with "hq"
	// . we need the language id for doing synonyms
	if ( m_highlightQuery && m_highlightQuery[0] )
		m_hqq.set2 ( m_highlightQuery , m_queryLang , true );
	else if ( m_query && m_query[0] )
		m_hqq.set2 ( m_query , m_queryLang , true );

	// log it here
	log("query: got query %s",m_sbuf1.getBufStart());

	// . now set from m_qbuf1, the advanced/composite query buffer
	// . returns false and sets g_errno on error (ETOOMANYOPERANDS)
	if ( ! m_q->set2 ( m_sbuf1.getBufStart(), 
			   m_queryLang , 
			   m_queryExpansion ) ) {
		g_msg = " (error: query has too many operands)";
		return false;
	}

	if ( m_q->m_truncated && m_q->m_isBoolean ) {
		g_errno = ETOOMANYOPERANDS;
		g_msg = " (error: query has too many operands)";
		return false;
	}


	// do not allow querier to use the links: query operator unless they 
	// are admin or the search controls explicitly allow links:
	//if ( m_q->m_hasLinksOperator && ! m_isAdmin  &&
	//     !cr->m_allowLinksSearch ) {
	//	g_errno = ENOPERM;
	//	g_msg = " (error: permission denied)";
	//	return false;
	//}

	// miscellaneous
	m_showBanned = false;
	//if ( m_isAdmin ) m_showBanned = true;
	// admin can say &sb=0 explicitly to not show banned results
	if ( m_isAdmin ) m_showBanned = r->getLong("sb",m_showBanned);


	if ( m_q->m_hasUrlField  ) m_ipRestrictForTopics = false;
	if ( m_q->m_hasIpField   ) {
		m_ipRestrictForTopics = false;
		//if( m_isAdmin ) m_showBanned = true;
	}
	if ( m_q->m_hasPositiveSiteField ) {
		m_ipRestrictForTopics = false;
		m_doSiteClustering    = false;
	}
	if ( m_q->m_hasQuotaField ) {
		m_doSiteClustering    = false;
		m_doDupContentRemoval = false;
	}


	m_familyFilter = r->getLong("ff",0);

	long codeLen;
	char *code = r->getString ("code",&codeLen,NULL);
	// set m_endUser
	if ( ! codeLen || ! code || strcmp(code,"gbfront")==0 )
		m_endUser = true;
	else
		m_endUser = false;


	if(codeLen && !m_endUser) {
		m_maxResults = cr->m_maxSearchResultsForClients;
	}
	else {
		m_maxResults = cr->m_maxSearchResults;
	}
	// don't let admin bewilder himself
	if ( m_maxResults < 1 ) m_maxResults = 500;

	// we can't get this kind of constraint from generic Parms routines
	if ( m_firstResultNum + m_docsWanted > m_maxResults ) 
		m_firstResultNum = m_maxResults - m_docsWanted;
	if(m_firstResultNum < 0) m_firstResultNum = 0;

	// if useCache is -1 then pick a default value
	if ( m_useCache == -1 ) {
		// assume yes as default
		m_useCache = 1;
		// . if query has url: or site: term do NOT use cache by def.
		// . however, if spider is off then use the cache by default
		if ( g_conf.m_spideringEnabled ) {
			if      ( m_q->m_hasPositiveSiteField ) m_useCache = 0;
			else if ( m_q->m_hasIpField   ) m_useCache = 0;
			else if ( m_q->m_hasUrlField  ) m_useCache = 0;
			else if ( m_siteLen  > 0      ) m_useCache = 0;
			else if ( m_whiteListBuf.length() ) m_useCache = 0;
			else if ( m_urlLen   > 0      ) m_useCache = 0;
		}
	}
	// never use cache if doing a rerank (msg3b)
	//if ( m_rerankRuleset >= 0 ) m_useCache = 0;
	bool readFromCache = false;
	if ( m_useCache ==  1  ) readFromCache = true;
	if ( m_rcache   ==  0  ) readFromCache = false;
	if ( m_useCache ==  0  ) readFromCache = false;
	// if useCache is false, don't write to cache if it was not specified
	if ( m_wcache == -1 ) {
		if ( m_useCache ==  0 ) m_wcache = 0;
		else                    m_wcache = 1;
	}
	// save it
	m_rcache = readFromCache;

	/*
	m_language = 0;
	// convert m_languageCode to a number for m_language
	if ( m_languageCode ) {
		m_language = (unsigned char)atoi(m_languageCode);
		if ( m_language == 0 )
			m_language = getLanguageFromAbbr(m_languageCode);
	}
	*/

	// a hack for buzz for backwards compatibility
	//if ( strstr ( m_q->m_orig,"gbkeyword:r36p1" ) )
	//	m_ruleset = 36;

	//
	// . turn this off for now
	// . it is used in setClusterLevels() to use clusterdb to filter our
	//   search results via Msg39, so it is not the most efficient.
	// . plus i am deleting most foreign language pages from the index
	//   so we can just focus on english and that will give us more english
	//   pages that we could normally get. we don't have resources to
	//   de-spam the other languages, etc.
	// . turn it back on, i took out the setClusterLevels() use of that
	//   because we got the langid in the posdb keys now
	//
	//m_language = 0;

	// convert m_defaultSortCountry to a number for m_countryHint
	m_countryHint = g_countryCode.getIndexOfAbbr(m_defaultSortCountry);


	return true;
}