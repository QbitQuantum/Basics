    OID ReplicationCoordinatorExternalStateImpl::ensureMe(OperationContext* txn) {
        std::string myname = getHostName();
        OID myRID;
        {
            ScopedTransaction transaction(txn, MODE_IX);
            Lock::DBLock lock(txn->lockState(), meDatabaseName, MODE_X);

            BSONObj me;
            // local.me is an identifier for a server for getLastError w:2+
            // TODO: handle WriteConflictExceptions below
            if (!Helpers::getSingleton(txn, meCollectionName, me) ||
                    !me.hasField("host") ||
                    me["host"].String() != myname) {

                myRID = OID::gen();

                // clean out local.me
                Helpers::emptyCollection(txn, meCollectionName);

                // repopulate
                BSONObjBuilder b;
                b.append("_id", myRID);
                b.append("host", myname);
                Helpers::putSingleton(txn, meCollectionName, b.done());
            } else {
                myRID = me["_id"].OID();
            }
        }
        return myRID;
    }