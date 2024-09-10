void handle_request_NOTIFY(CLIENT_t *ptC, CONN_SESSION *ptSession)
{
    CONN_SESSION   *ptResp;
    BYTE           *pbMsg;

    do
    {
        // each NOTIFY message will be considered to KEEP-ALIVE message.
        ptC->n32TimeGotKA = time( (time_t *)NULL );

        // if state already inactive | x | x ..., then we need resume media plane.
        if (ptC->eState == eCLIENT_STATE_INACTIVE) {
            ptC->eState = eCLIENT_STATE_CONNECTED;

            // resume media plane
            sdp_process_type_t eClientType = (ptC == &patClient[0]) ? SDP_F : SDP_C;
            data_plane_suspend(eClientType, ptC->tMedia, SUSPEND_OFF);

        }

        // keep-alive NOTIFY. simply break-out.
        if (0 == ptSession->bMap[EVENT_SEQ_NUM]) {
            break;
        }

        BYTE *pbEvName   = &ptSession->tEvent.bName[0];
        BYTE *pbEvParams = NULL;

        // get name & params
        {
            BYTE   bLocation = 0;
            while(pbEvName[bLocation] != '\0')
            {
                bLocation++;
                if (pbEvName[bLocation] == ' ') {
                    pbEvName[bLocation++]  = '\0';
                    pbEvParams = &pbEvName[bLocation];
                    break;
                }
            }
        }

        // client request for self-state
        //if (StrICmp(ptSession->tEvent.bName, (BYTE *)"logon-state")) {
        if (StrICmp(pbEvName, (BYTE *)"logon-state")) {
            BYTE   *pbMsg = &ptSession->bBody[0];

            WriteString(&pbMsg, (BYTE *)"State: ", MAX_BODY_LTH);
            WriteString(&pbMsg, abClientState[ptC->eState], MAX_BODY_LTH);
            //&pbMsg++ = '\0';

            ptSession->wBdyLth = pbMsg - &ptSession->bBody[0];

            break;
        }

        // F request for C-list
        //else if (StrICmp(ptSession->tEvent.bName, (BYTE *)"listener-list")) {
        else if (StrICmp(pbEvName, (BYTE *)"listener-list")) {
            BYTE   *pbMsg = &ptSession->bBody[0];
            BYTE    i;
            BYTE    bString[COMMEN_LTH];

            if (ptC != &patClient[0]) {
                /* requirement update: C CAN request F'state, F CAN request C state-list.  */
                WriteString(&pbMsg, (BYTE *)"1:", COMMEN_LTH);
                WriteString(&pbMsg, (BYTE *)&patClient[0].aName[0], USER_LTH);
                if ('\0' != patClient[0].aID[0]) {
                    WriteString(&pbMsg, (BYTE *)"<", 2);
                    WriteString(&pbMsg, (BYTE *)&patClient[0].aID[0], USER_LTH);
                    WriteString(&pbMsg, (BYTE *)">", 2);
                }
                *pbMsg++ = ':';
                WriteString(&pbMsg, (BYTE *)inet_ntoa( *((struct in_addr *)&patClient[0].tAddrRemoteSignal.ip_addr) ), HOST_NAME_LTH);

                *pbMsg++ = '\r';
                *pbMsg++ = '\n';

                ptSession->wBdyLth = pbMsg - &ptSession->bBody[0];

                break;
            }

            // Now, F request C-list.

            if (!pbEvParams) {
                // only get total number

                BYTE bCnt = 0;
                for (i=1; i<MAX_CONNECT_CLIENT; i++) {
                    if (patClient[i].eState == eCLIENT_STATE_NONE) {
                        continue;
                    }

                    bCnt++;
                }

                // format as:
                //    Total: xx
                WriteString(&pbMsg, (BYTE *)"Total: ", 8);
                sprintf((char*)bString, "%d", bCnt);
                WriteString(&pbMsg, &bString[0], COMMEN_LTH);

                *pbMsg++ = '\r';
                *pbMsg++ = '\n';

            } else {
                // get No.x detail info

                BYTE bIndex = atoi((const char*)pbEvParams);
                if ( (bIndex < 1) || (bIndex >= MAX_CONNECT_CLIENT)) {
                    bIndex = 1;   // No.0 is F self.
                }

                BYTE bCnt = 0;
                BOOL8 blFound = FALSE_B8;

                for (i=1; i<MAX_CONNECT_CLIENT; i++) {
                    if (patClient[i].eState == eCLIENT_STATE_NONE) {
                        continue;
                    }

                    if (++bCnt < bIndex) {
                        continue;
                    }

                    // found
                    blFound = TRUE_B8;
                    break;

                }

                if (blFound) {
                    //     format as: "slot-No.:Name<ID>:IP"
                    // OR: format as: "index-No.:Name<ID>:IP"
                    sprintf((char*)bString, "%d", i);
                    WriteString(&pbMsg, &bString[0], COMMEN_LTH);
                    *pbMsg++ = ':';
                    WriteString(&pbMsg, (BYTE *)&patClient[i].aName[0], USER_LTH);
                    if ('\0' != patClient[i].aID[0]) {
                        WriteString(&pbMsg, (BYTE *)"<", 2);
                        WriteString(&pbMsg, (BYTE *)&patClient[i].aID[0], USER_LTH);
                        WriteString(&pbMsg, (BYTE *)">", 2);
                    }
                    *pbMsg++ = ':';
                    WriteString(&pbMsg, (BYTE *)inet_ntoa( *((struct in_addr *)&patClient[i].tAddrRemoteSignal.ip_addr) ), HOST_NAME_LTH);

                    *pbMsg++ = '\r';
                    *pbMsg++ = '\n';

                } else {
                    // index error, return
                    sendMgrResponse(&ptC->tAddrRemoteSignal, ptSession, 400, reinterpret_cast<const unsigned char *>("Index not found."));
                    return;
                }

            }

            ptSession->wBdyLth = pbMsg - &ptSession->bBody[0];

            break;

        }

        else {
            // NOT supported event.
            sendMgrResponse(&ptC->tAddrRemoteSignal, ptSession, 400, reinterpret_cast<const unsigned char *>("Unknown event type."));
            return;
        }
    } while(0);

    // send out response
    ptResp = ptSession;

    memset(&ptResp->bMap[0], 0, sizeof(ptResp->bMap));

    ptResp->bMap[CALLID_SEQ_NUM] = 1;
    ptResp->bMap[CSEQ_SEQ_NUM] = 1;

    // content-length: Automatic done.
    //

    // send response to peer.
    sendResponse(&ptC->tAddrRemoteSignal, ptResp, 200, reinterpret_cast<const unsigned char *>("OK"));

    return;
}