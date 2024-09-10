    Status AuthzManagerExternalStateMongod::removePrivilegeDocuments(const string& dbname,
                                                                     const BSONObj& query) {
        try {
            string userNS = dbname + ".system.users";
            DBDirectClient client;
            {
                Client::GodScope gs;
                // TODO(spencer): Once we're no longer fully rebuilding the user cache on every
                // change to user data we should remove the global lock and uncomment the
                // WriteContext below
                Lock::GlobalWrite w;
                // Client::WriteContext ctx(userNS);
                client.remove(userNS, query);
            }

            // 30 second timeout for w:majority
            BSONObj res = client.getLastErrorDetailed(false, false, -1, 30*1000);
            string errstr = client.getLastErrorString(res);
            if (!errstr.empty()) {
                return Status(ErrorCodes::UserModificationFailed, errstr);
            }

            int numUpdated = res["n"].numberInt();
            if (numUpdated == 0) {
                return Status(ErrorCodes::UserNotFound,
                              mongoutils::str::stream() << "No users found on database \"" << dbname
                                      << "\" matching query: " << query.toString());
            }
            return Status::OK();
        } catch (const DBException& e) {
            return e.toStatus();
        }
    }