/**
 * Updates the remote cached version on the remote shard host (primary, in the case of replica
 * sets) if needed with a fully-qualified shard version for the given namespace:
 *   config server(s) + shard name + shard version
 *
 * If no remote cached version has ever been set, an initial shard version is sent.
 *
 * If the namespace is empty and no version has ever been sent, the config server + shard name
 * is sent to the remote shard host to initialize the connection as coming from mongos.
 * NOTE: This initialization is *best-effort only*.  Operations which wish to correctly version
 * must send the namespace.
 *
 * Config servers are special and are not (unless otherwise a shard) kept up to date with this
 * protocol.  This is safe so long as config servers only contain unversioned collections.
 *
 * It is an error to call checkShardVersion with an unversionable connection (isVersionableCB).
 *
 * @return true if we contacted the remote host
 */
bool checkShardVersion(DBClientBase* conn_in,
                       const string& ns,
                       ChunkManagerPtr refManager,
                       bool authoritative,
                       int tryNumber) {
    // TODO: cache, optimize, etc...

    // Empty namespaces are special - we require initialization but not versioning
    if (ns.size() == 0) {
        return initShardVersionEmptyNS(conn_in);
    }

    auto status = grid.catalogCache()->getDatabase(nsToDatabase(ns));
    if (!status.isOK()) {
        return false;
    }

    shared_ptr<DBConfig> conf = status.getValue();

    DBClientBase* conn = getVersionable(conn_in);
    verify(conn);  // errors thrown above

    unsigned long long officialSequenceNumber = 0;

    ShardPtr primary;
    ChunkManagerPtr manager;
    if (authoritative)
        conf->getChunkManagerIfExists(ns, true);

    conf->getChunkManagerOrPrimary(ns, manager, primary);

    if (manager) {
        officialSequenceNumber = manager->getSequenceNumber();
    }

    const auto shard = grid.shardRegistry()->getShard(conn->getServerAddress());
    uassert(ErrorCodes::ShardNotFound,
            str::stream() << conn->getServerAddress() << " is not recognized as a shard",
            shard);

    // Check this manager against the reference manager
    if (manager) {
        if (refManager && !refManager->compatibleWith(*manager, shard->getId())) {
            const ChunkVersion refVersion(refManager->getVersion(shard->getId()));
            const ChunkVersion currentVersion(manager->getVersion(shard->getId()));

            string msg(str::stream()
                       << "manager (" << currentVersion.toString() << " : "
                       << manager->getSequenceNumber() << ") "
                       << "not compatible with reference manager (" << refVersion.toString()
                       << " : " << refManager->getSequenceNumber() << ") "
                       << "on shard " << shard->getId() << " (" << shard->getConnString().toString()
                       << ")");

            throw SendStaleConfigException(ns, msg, refVersion, currentVersion);
        }
    } else if (refManager) {
        string msg(str::stream() << "not sharded ("
                                 << ((manager.get() == 0) ? string("<none>") : str::stream()
                                             << manager->getSequenceNumber())
                                 << ") but has reference manager ("
                                 << refManager->getSequenceNumber() << ") "
                                 << "on conn " << conn->getServerAddress() << " ("
                                 << conn_in->getServerAddress() << ")");

        throw SendStaleConfigException(
            ns, msg, refManager->getVersion(shard->getId()), ChunkVersion::UNSHARDED());
    }

    // Do not send setShardVersion to collections on the config servers - this causes problems
    // when config servers are also shards and get SSV with conflicting names.
    // TODO: Make config servers regular shards
    if (primary && primary->getId() == "config") {
        return false;
    }

    // Has the ChunkManager been reloaded since the last time we updated the shard version over
    // this connection?  If we've never updated the shard version, do so now.
    unsigned long long sequenceNumber = 0;
    if (connectionShardStatus.getSequence(conn, ns, &sequenceNumber)) {
        if (sequenceNumber == officialSequenceNumber) {
            return false;
        }
    }

    ChunkVersion version = ChunkVersion(0, 0, OID());
    if (manager) {
        version = manager->getVersion(shard->getId());
    }

    LOG(1) << "setting shard version of " << version << " for " << ns << " on shard "
           << shard->toString();

    LOG(3) << "last version sent with chunk manager iteration " << sequenceNumber
           << ", current chunk manager iteration is " << officialSequenceNumber;

    BSONObj result;
    if (setShardVersion(*conn,
                        ns,
                        grid.catalogManager()->connectionString().toString(),
                        version,
                        manager.get(),
                        authoritative,
                        result)) {
        LOG(1) << "      setShardVersion success: " << result;
        connectionShardStatus.setSequence(conn, ns, officialSequenceNumber);
        return true;
    }

    LOG(1) << "       setShardVersion failed!\n" << result << endl;

    if (result["need_authoritative"].trueValue())
        massert(10428, "need_authoritative set but in authoritative mode already", !authoritative);

    if (!authoritative) {
        // use the original connection and get a fresh versionable connection
        // since conn can be invalidated (or worse, freed) after the failure
        checkShardVersion(conn_in, ns, refManager, 1, tryNumber + 1);
        return true;
    }

    if (result["reloadConfig"].trueValue()) {
        if (result["version"].timestampTime() == Date_t()) {
            warning() << "reloading full configuration for " << conf->name()
                      << ", connection state indicates significant version changes";

            // reload db
            conf->reload();
        } else {
            // reload config
            conf->getChunkManager(ns, true);
        }
    }

    const int maxNumTries = 7;
    if (tryNumber < maxNumTries) {
        LOG(tryNumber < (maxNumTries / 2) ? 1 : 0)
            << "going to retry checkShardVersion shard: " << shard->toString() << " " << result;
        sleepmillis(10 * tryNumber);
        // use the original connection and get a fresh versionable connection
        // since conn can be invalidated (or worse, freed) after the failure
        checkShardVersion(conn_in, ns, refManager, true, tryNumber + 1);
        return true;
    }

    string errmsg = str::stream() << "setShardVersion failed shard: " << shard->toString() << " "
                                  << result;
    log() << "     " << errmsg << endl;
    massert(10429, errmsg, 0);
    return true;
}