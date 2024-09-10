    void SyncSourceFeedback::ensureMe(OperationContext* txn) {
        string myname = getHostName();
        {
            Lock::DBLock dlk(txn->lockState(), "local", MODE_X);
            WriteUnitOfWork wunit(txn);
            Client::Context ctx(txn, "local");

            // local.me is an identifier for a server for getLastError w:2+
            if (!Helpers::getSingleton(txn, "local.me", _me) ||
                !_me.hasField("host") ||
                _me["host"].String() != myname) {

                // clean out local.me
                Helpers::emptyCollection(txn, "local.me");

                // repopulate
                BSONObjBuilder b;
                b.appendOID("_id", 0, true);
                b.append("host", myname);
                _me = b.obj();
                Helpers::putSingleton(txn, "local.me", _me);
            }
            wunit.commit();
            // _me is used outside of a read lock, so we must copy it out of the mmap
            _me = _me.getOwned();
        }
    }