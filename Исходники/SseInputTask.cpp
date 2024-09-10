//
// routine: receive and send on incoming messages
//
// Notes:
//		No analysis of the message is performed - that is left
//		to the command processor task.  Instead, the local copy
//		of the header
//		is demarshalled to determined whether or not there
//		is associated data; if there is, space is allocated to
//		contain it.
void *
SseInputTask::routine()
{
    extractArgs();

    Timer timer;
    if (cmdArgs->noSSE()) {
        processIpFromFile();
        while (1)
            timer.sleep(3000);
    };

    // run forever, waiting for messages from the SSE
    bool stopIssued = false;
    bool done = false;
    uint32_t lastCode = MESSAGE_CODE_UNINIT;
    int32_t lastLen = 0;
    uint32_t lastTime = 0;
    while (!done) {
        // if there's no connection, request that it be
        // established, then wait for that to happen
        if (!sse->isConnected()) {
            requestConnection();
            while (!sse->isConnected())
                timer.sleep(3000);
        }
        stopIssued = false;

        // got a connection - wait for data to come in
        SseInterfaceHeader hdr;
        Error err = sse->recv((void *) &hdr, sizeof(hdr));
        if (err) {
            switch (err) {
            case EAGAIN:
            case EINTR:
            case ENOTCONN:
            case ECONNRESET:
                stopAllActivities(stopIssued);
                continue;
            default:
                Fatal(err);
                break;
            }
        }
        // demarshall the header
        hdr.demarshall();

        if (cmdArgs->logSseMessages()) {
            LogWarning(ERR_NE, hdr.activityId,
                       "bad msg from Sse, code = %d, len = %d", hdr.code,
                       hdr.dataLength);
        }

        // allocate a message to hold the incoming message
        Msg *msg = msgList->alloc();
        msg->setHeader(hdr);
        msg->setUnit((sonata_lib::Unit) UnitSse);

        // if there's data associated with the message,
        // allocate space and retrieve it, demarshall it
        // based on the message type,
        // then send it on to the command processor
        void *data = 0;
        int32_t len = hdr.dataLength;
        timeval tv;
        gettimeofday(&tv, NULL);
        if (len > 10000) {
            LogWarning(ERR_NE, hdr.activityId,
                       "msg code = %d, len = %d, t = %u, last msg = %d, last len = %d, last t = %u",
                       hdr.code, len, tv.tv_sec, lastCode, lastLen, lastTime);
            Timer t;
            t.sleep(100);
        }
        else {
            lastCode = hdr.code;
            lastLen = len;
            lastTime = tv.tv_sec;
        }
        if (len) {
            MemBlk *blk = partitionSet->alloc(len);
            Assert(blk);
            if (!blk)
                Fatal(ERR_MAF);
            data = blk->getData();
            err = sse->recv(data, len);
            if (err) {
                switch (err) {
                case EAGAIN:
                case EINTR:
                case ENOTCONN:
                case ECONNRESET:
                    blk->free();
                    Assert(msgList->free(msg));
                    stopAllActivities(stopIssued);
                    continue;
                default:
                    Fatal(err);
                    break;
                }
            }
            msg->setData(data, len, blk);
        }

        // demarshall the data of the message depending on
        // the message type
        switch (hdr.code) {
        case REQUEST_INTRINSICS:
            break;
        case CONFIGURE_DX:
            (static_cast<DxConfiguration *> (data))->demarshall();
            break;

        case PERM_RFI_MASK:
        case BIRDIE_MASK:
        case RCVR_BIRDIE_MASK:
        case TEST_SIGNAL_MASK:
            demarshallFrequencyMask(data);
            break;
        case RECENT_RFI_MASK:
            demarshallRecentRFIMask(data);
            break;
        case REQUEST_DX_STATUS:
            break;
        case SEND_DX_ACTIVITY_PARAMETERS:
            (static_cast<DxActivityParameters *> (data))->demarshall();
            break;
        case DX_SCIENCE_DATA_REQUEST:
            (static_cast<DxScienceDataRequest *> (data))->demarshall();
            break;
#ifdef notdef
        case SEND_DOPPLER_PARAMETERS:
            (static_cast<DopplerParameters *> (data))->demarshall();
            break;
#endif
        case BEGIN_SENDING_FOLLOW_UP_SIGNALS:
            (static_cast<Count *> (data))->demarshall();
            break;
        case SEND_FOLLOW_UP_CW_SIGNAL:
            (static_cast<FollowUpCwSignal *> (data))->demarshall();
            break;
        case SEND_FOLLOW_UP_PULSE_SIGNAL:
            (static_cast<FollowUpPulseSignal *> (data))->demarshall();
            break;
        case DONE_SENDING_FOLLOW_UP_SIGNALS:
            break;
        case START_TIME:
            (static_cast<StartActivity *> (data))->demarshall();
            break;
        case BEGIN_SENDING_CANDIDATES:
            (static_cast<Count *> (data))->demarshall();
            break;
        case SEND_CANDIDATE_CW_POWER_SIGNAL:
            (static_cast<CwPowerSignal *> (data))->demarshall();
            break;
        case SEND_CANDIDATE_PULSE_SIGNAL:
            demarshallPulseSignal(data);
            break;
        case DONE_SENDING_CANDIDATES:
            break;
        case BEGIN_SENDING_CW_COHERENT_SIGNALS:
            break;
        case SEND_CW_COHERENT_SIGNAL:
            (static_cast<CwCoherentSignal *> (data))->demarshall();
            break;
        case DONE_SENDING_CW_COHERENT_SIGNALS:
            break;
        case REQUEST_ARCHIVE_DATA:
            (static_cast<ArchiveRequest *> (data))->demarshall();
            break;
        case DISCARD_ARCHIVE_DATA:
            (static_cast<ArchiveRequest *> (data))->demarshall();
            break;
        // the following commands arrive with no data
        case STOP_DX_ACTIVITY:
        case SHUTDOWN_DX:
        case RESTART_DX:
            Debug(DEBUG_CONTROL, hdr.activityId,
                  "STOP_DX_ACTIVITY, act");
            break;
        default:
            LogError(ERR_IMT, hdr.activityId, "activity %d, type %d",
                     hdr.activityId, hdr.code);
            Err(ERR_IMT);
            ErrStr(hdr.code, "msg code");
            Assert(msgList->free(msg));
            continue;
        }

        // at this point, the entire marshalled message is in
        // a generic Msg; send the message on for processing,
        // then go back to waiting
        cmdQ->send(msg);
    }
    return (0);
}