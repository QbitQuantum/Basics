        virtual bool run(OperationContext* txn, const string&, 
                         BSONObj& cmdObj, 
                         int, 
                         string& errmsg, 
                         BSONObjBuilder& result, 
                         bool fromRepl) {
            Status status = getGlobalReplicationCoordinator()->checkReplEnabledForCommand(&result);
            if (!status.isOK())
                return appendCommandStatus(result, status);

            HostAndPort targetHostAndPort;
            status = targetHostAndPort.initialize(cmdObj["replSetSyncFrom"].valuestrsafe());
            if (!status.isOK())
                return appendCommandStatus(result, status);

            return appendCommandStatus(
                    result,
                    getGlobalReplicationCoordinator()->processReplSetSyncFrom(targetHostAndPort,
                                                                              &result));
        }