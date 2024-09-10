AuthRepositoryPatch AuthRepositoryServer::sync (
	const AuthRepositoryPatch& clientSync )
{
//	throw std::runtime_error("test error");

	//LogConfig::logger()->debug("repo input: %s %s", clientSync.oldCommit.c_str(), clientSync.diffJson.c_str());

	authrepo::DBDataSource src;


	if ( clientSync.get_diffJson() == "{}" && clientSync.get_oldCommit() == src.getTaggedCommit ( "head" ) ) {
		//no changes on both sides
		AuthRepositoryPatch result;
		result.set_diffJson("{}");
		result.set_newCommit(clientSync.get_oldCommit());
		result.set_oldCommit(clientSync.get_oldCommit());

		return result;
	}

	authrepo::PPatch patch = authrepo::JsonPatch::parseString ( clientSync.get_diffJson() );

	//load current head
	authrepo::PCommitNode currentHead ( new authrepo::CommitNode ( &m_dbStructure, src.getTaggedCommit ( "head" ) ) );
	currentHead->load ( &src );

	try {
		currentHead->setUserPermissions ( m_userStaticId );

		//apply user patch
		authrepo::GeneralPatcher p ( currentHead.getAddr(), patch );
		p.apply();

		//all ok store results
		DBSession s = DBSessionFactory::getSession();

		s.BeginTransaction();
		authrepo::DBDataCollector coll ( s );
		currentHead->storeUpdates ( &coll );
		coll.writeTag ( "head", currentHead->getId() );

		ActiveDevicesList::update ( s );

		s.CommitTransaction();
	} catch ( authrepo::util::runtime_error &ue ) {
		LogConfig::logger()->error ( "client patch problem: %s", ue.what() );

		//return full patch
		authrepo::PCommitNode cleanHead ( new authrepo::CommitNode ( &m_dbStructure, src.getTaggedCommit ( "head" ) ) );
		cleanHead->load ( &src );

		currentHead = cleanHead;
	}

	//fast forward case
// 	if (fastForwardFlag)
// 	{
// 		AuthRepositoryPatch result;
// 		result.diffJson = "{}";
// 		result.newCommit = currentHead->getId();
// 		result.oldCommit = clientSync.oldCommit;
//
// 		LogConfig::logger()->info("repo fast forward: %s %s", result.diffJson.c_str(), result.newCommit.c_str());
// 		return result;
// 	}

	//default
	authrepo::PCommitNode clientSyncedCommit ( new authrepo::CommitNode ( &m_dbStructure, "initial" ) );

	//try load client
	try {
		authrepo::PCommitNode realClientSynced ( new authrepo::CommitNode ( &m_dbStructure, clientSync.get_oldCommit() ) );
		realClientSynced->load ( &src );
		clientSyncedCommit = realClientSynced;
	} catch ( authrepo::util::runtime_error &ue ) {
		LogConfig::logger()->error ( "client commit loading problem:\r\n %s\r\n %s", clientSync.get_oldCommit().c_str(), ue.what() );
	}

	authrepo::DiffCalculator dc ( clientSyncedCommit, currentHead );

	AuthRepositoryPatch result;
	result.set_diffJson(authrepo::JsonPatch::stringify ( dc.diff ( m_userStaticId ) ));
	result.set_newCommit(currentHead->getId());
	result.set_oldCommit(clientSyncedCommit->getId());

	//LogConfig::logger()->debug("repo output: %s", result.newCommit.c_str());

	return result;
}