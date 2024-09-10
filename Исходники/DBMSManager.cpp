void
DBMSManager::InvalidatePublicAd() {
	ClassAd query_ad;
    SetMyTypeName(query_ad, QUERY_ADTYPE);
    SetTargetTypeName(query_ad, DBMSD_ADTYPE);

    MyString line;
    line.sprintf("%s = TARGET.%s == \"%s\"", ATTR_REQUIREMENTS, ATTR_NAME, m_name.Value());
    query_ad.Insert(line.Value());
	query_ad.Assign(ATTR_NAME,m_name.Value());

    m_collectors->sendUpdates(INVALIDATE_ADS_GENERIC, &query_ad, NULL, true);
	
	//TODO/FIXME - delete the ads of the databases we're advertising

	return;
}