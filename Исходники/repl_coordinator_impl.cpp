    void ReplicationCoordinatorImpl::doMemberHeartbeat(ReplicationExecutor::CallbackData cbData,
                                                       const HostAndPort& hap) {

        if (cbData.status == ErrorCodes::CallbackCanceled) {
            return;
        }

        // Are we blind, or do we have a failpoint setup to ignore this member?
        bool dontHeartbeatMember = false; // TODO: replSetBlind should be here as the default

        MONGO_FAIL_POINT_BLOCK(rsHeartbeatRequestNoopByMember, member) {
            const StringData& stopMember = member.getData()["member"].valueStringData();
            HostAndPort ignoreHAP;
            Status status = ignoreHAP.initialize(stopMember);
            // Ignore
            if (status.isOK()) {
                if (hap == ignoreHAP) {
                    dontHeartbeatMember = true;
                }
            } else {
                log() << "replset: Bad member for rsHeartbeatRequestNoopByMember failpoint "
                       <<  member.getData() << ". 'member' failed to parse into HostAndPort -- "
                       << status;
            }
        }

        if (dontHeartbeatMember) {
            // Don't issue real heartbeats, just call start again after the timeout.
            ReplicationExecutor::CallbackFn restartCB = stdx::bind(
                                                &ReplicationCoordinatorImpl::doMemberHeartbeat,
                                                this,
                                                stdx::placeholders::_1,
                                                hap);
            CBHStatus status = _replExecutor->scheduleWorkAt(
                                        Date_t(curTimeMillis64() + heartbeatFrequencyMillis),
                                        restartCB);
            if (!status.isOK()) {
                log() << "replset: aborting heartbeats for " << hap << " due to scheduling error"
                       << " -- "<< status;
                return;
             }
            _trackHeartbeatHandle(status.getValue());
            return;
        }

        // Compose heartbeat command message
        BSONObj hbCommandBSON;
        {
            // take lock to build request
            boost::lock_guard<boost::mutex> lock(_mutex);
            BSONObjBuilder cmdBuilder;
            const MemberConfig me = _rsConfig.getMemberAt(_thisMembersConfigIndex);
            cmdBuilder.append("replSetHeartbeat", _rsConfig.getReplSetName());
            cmdBuilder.append("v", _rsConfig.getConfigVersion());
            cmdBuilder.append("pv", 1);
            cmdBuilder.append("checkEmpty", false);
            cmdBuilder.append("from", me.getHostAndPort().toString());
            cmdBuilder.append("fromId", me.getId());
            hbCommandBSON = cmdBuilder.done();
        }
        const ReplicationExecutor::RemoteCommandRequest request(hap, "admin", hbCommandBSON);

        ReplicationExecutor::RemoteCommandCallbackFn callback = stdx::bind(
                                       &ReplicationCoordinatorImpl::_handleHeartbeatResponse,
                                       this,
                                       stdx::placeholders::_1,
                                       hap,
                                       curTimeMillis64(),
                                       heartbeatRetries);


        CBHStatus status = _replExecutor->scheduleRemoteCommand(request, callback);
        if (!status.isOK()) {
            log() << "replset: aborting heartbeats for " << hap << " due to scheduling error"
                   << status;
            return;
         }
        _trackHeartbeatHandle(status.getValue());
    }