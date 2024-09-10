void * wfa_wmm_thread(void *thr_param)
{
    int myId = ((tgThrData_t *)thr_param)->tid;
    tgWMM_t *my_wmm = &wmm_thr[myId];
    tgStream_t *myStream = NULL;
    int myStreamId, i=0,rttime=0,difftime=0, rcvCount=0,sendCount=0;
    int mySock = -1, status, respLen = 0, nbytes = 0, ret=0, j=0;
    tgProfile_t *myProfile;
    pthread_attr_t tattr;
#ifdef WFA_WMM_PS_EXT
    tgThrData_t *tdata =(tgThrData_t *) thr_param;
    StationProcStatetbl_t  curr_state;
#endif

//#ifdef WFA_VOICE_EXT
    struct timeval lstime, lrtime;
    int asn = 1;  /* everytime it starts from 1, and to ++ */
//#endif

    wPT_ATTR_INIT(&tattr);
    wPT_ATTR_SETSCH(&tattr, SCHED_RR);

    while(1)
    {
        int sleepTotal=0,sendFailCount=0;
        DPRINT_INFO(WFA_OUT, "wfa_wmm_thread::begin while loop for each send/rcv before mutex lock\n");
        pthread_mutex_lock(&my_wmm->thr_flag_mutex);
        /* it needs to reset the thr_flag to wait again */
        while(my_wmm->thr_flag == 0)
        {
            printf("Mutex wait\n");
            /*
             * in normal situation, the signal indicates the thr_flag changed to
             * a valid number (stream id), then it will go out the loop and do
             * work.
             */
            wPT_COND_WAIT(&my_wmm->thr_flag_cond, &my_wmm->thr_flag_mutex);
        }
        wPT_MUTEX_UNLOCK(&my_wmm->thr_flag_mutex);
        myStreamId = my_wmm->thr_flag;
        my_wmm->thr_flag=0;

        /* use the flag as a stream id to file the profile */
        myStream = findStreamProfile(myStreamId);
        myProfile = &myStream->profile;

        if(myProfile == NULL)
        {
            status = STATUS_INVALID;
            wfaEncodeTLV(WFA_TRAFFIC_AGENT_SEND_RESP_TLV, 4, (BYTE *)&status, respBuf);
            respLen = WFA_TLV_HDR_LEN+4;
            /*
             * send it back to control agent.
             */
            continue;
        }

        DPRINT_INFO(WFA_OUT, "wfa_wmm_thread::Mutex unlocked\n");
        switch(myProfile->direction)
        {
        case DIRECT_SEND:
            mySock = wfaCreateUDPSock(myProfile->sipaddr, myProfile->sport);
            if (mySock < 0)
            {
               DPRINT_INFO(WFA_OUT, "wfa_wmm_thread SEND ERROR failed create UDP socket! \n");
               break;
            }

            mySock = wfaConnectUDPPeer(mySock, myProfile->dipaddr, myProfile->dport);
            sendThrId = myId;
            /*
             * Set packet/socket priority TOS field
             */
            wfaTGSetPrio(mySock, myProfile->trafficClass);

            /*
             * set a proper priority
             */
            wfaSetThreadPrio(myId, myProfile->trafficClass);

            /* if delay is too long, it must be something wrong */
            if(myProfile->startdelay > 0 && myProfile->startdelay<100)
            {
                wSLEEP(myProfile->startdelay);
            }

            /*
             * set timer fire up
             */
            if(myProfile->maxcnt == 0)
            {
                wSIGNAL(SIGALRM, tmout_stop_send);
                wALARM(myProfile->duration );
                DPRINT_INFO(WFA_OUT, "wfa_wmm_thread SEND set stop alarm for %d sec \n", myProfile->duration);
            }

            if(myProfile->profile == PROF_MCAST)
            {
                wfaSetSockMcastSendOpt(mySock);
            }

            if (myProfile->profile == PROF_IPTV || myProfile->profile == PROF_FILE_TX || myProfile->profile == PROF_MCAST)
            {
                int iOptVal, iOptLen;

                getsockopt(mySock, SOL_SOCKET, SO_SNDBUF, (char *)&iOptVal, (socklen_t *)&iOptLen);
                iOptVal = iOptVal * 16;
                setsockopt(mySock, SOL_SOCKET, SO_SNDBUF, (char *)&iOptVal, (socklen_t )iOptLen);

              if ( (myProfile->rate != 0 ) /* WFA_SEND_FIX_BITRATE_MAX_FRAME_RATE)*/ && 
                   (myProfile->pksize * myProfile->rate * 8 < WFA_SEND_FIX_BITRATE_MAX) )
                 wfaSendBitrateData(mySock, myStreamId, respBuf, &respLen);
              else
              {
                 wfaSendLongFile(mySock, myStreamId, respBuf, &respLen);
              }

              /* wfaSendLongFile(mySock, myStreamId, respBuf, &respLen); */
                if(mySock != -1)
                {
                    wCLOSE(mySock);
                    mySock = -1;
                }
            }
            else if(myProfile->profile == PROF_TRANSC || myProfile->profile == PROF_START_SYNC || myProfile->profile == PROF_CALI_RTD)
            {
#if 0
                struct timeval nxtime, curtime;
                int ioflags = wFCNTL(mySock, F_GETFL, 0);
#endif
                struct timeval tmout;

                gtgTransac = myStreamId;
                sentTranPkts = 0;

#if 0
                gettimeofday(&nxtime, NULL);
                nxtime.tv_usec += 20000;   /* fixed 20 min sec timeout */
                if(nxtime.tv_usec >= 1000000)
                {
                    nxtime.tv_sec +=1;
                    nxtime.tv_usec -= 1000000;
                }
                wFCNTL(mySock, F_SETFL, ioflags | O_NONBLOCK);
#endif
                gettimeofday(&lstime,0);
                DPRINT_INFO(WFA_OUT, "Start sending traffic,at sec %d usec %d\n", (int )lstime.tv_sec, (int)lstime.tv_usec);


                tmout.tv_sec = 0;
                tmout.tv_usec = 15000;     // set for 15000 microsec timeout for rcv              
                ret = setsockopt(mySock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tmout, (socklen_t) sizeof(tmout)); 
                
                rcvCount=0; sendFailCount=0;
                j=0;  sendCount=0;
                sleepTotal = 0;
                while(gtgTransac != 0)
                {
					gettimeofday(&lstime, NULL);
#ifdef WFA_VOICE_EXT  					
                    /*
                     * If your device is BIG ENDIAN, you need to
                     * modify the the function calls
                     */
                    int2BuffBigEndian(asn++, &((tgHeader_t *)trafficBuf)->hdr[8]);
                    int2BuffBigEndian(lstime.tv_sec, &((tgHeader_t *)trafficBuf)->hdr[12]);
                    int2BuffBigEndian(lstime.tv_usec, &((tgHeader_t *)trafficBuf)->hdr[16]);
#else
                    j++;
                    i=0;
                    do
                    {

#endif /* WFA_VOICE_EXT */

                        if(gtgTransac != 0/* && nbytes <= 0 */)
                        {
                            if(respBuf == NULL)
                            {
                                DPRINT_INFO(WFA_OUT, "wfa_wmm_thread SEND,PROF_TRANSC::a Null respBuf\n");
                            }
                            memset(respBuf, 0, WFA_RESP_BUF_SZ);
                            respLen = 0;
                            memset(trafficBuf  ,0, MAX_UDP_LEN + 1);
                            if(wfaSendShortFile(mySock, myStreamId,
                                trafficBuf, 0, respBuf, &respLen) == DONE)
                            {
                                if(wfaCtrlSend(gxcSockfd, respBuf, respLen) != respLen)
                                {
                                    DPRINT_INFO(WFA_OUT, "wfa_wmm_thread SEND,PROF_TRANSC::wfaCtrlSend Error for wfaSendShortFile\n");
                                }
                                sendFailCount++;
                                i--;
                                usleep(1000);
                            }
                            else
                            {
                                i++;
                                sendCount++;
                            }

                            //sentTranPkts++; /* send routine already incresed this counter  */

                            if((myProfile->maxcnt>0) &&(sendCount == myProfile->maxcnt))
                            {
                                DPRINT_INFO(WFA_OUT, "wfa_wmm_thread SEND,PROF_TRANSC::meet maxcnt=%d; end loop\n",myProfile->maxcnt);
                                gtgTransac = 0; /* break snd/rcv wile loop  */
                                break;
                            }

                            nbytes = wfaRecvFile(mySock, myStreamId, (char  *)trafficBuf);
                            if(nbytes <= 0)
                            {/* Do not print any msg it will slow down process on snd/rcv  */
                            //setsockopt(mySock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tmout, (socklen_t) sizeof(tmout)); 
                            //printf("PROF_TRANSC::time out event, wfaRecvFile failed,resend a new packet ...\n");

                            //tmout.tv_sec = 0;
                            //tmout.tv_usec = 3000;    // set for 20 minlsec timeout              
                            //setsockopt(mySock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tmout, (socklen_t) sizeof(tmout)); 
#if 0  /* if your socket APIs does not support "recvfrom" timeout, this is the way to loop the descriptor */
                        gettimeofday(&curtime, NULL);
                        if(((curtime.tv_sec - nxtime.tv_sec) * 1000000 + (curtime.tv_usec -  nxtime.tv_usec)) < 20000)
                        {
                            continue;
                        }

                        nxtime.tv_usec = curtime.tv_usec += 20000;
                        if(nxtime.tv_usec >= 1000000)
                        {
                            nxtime.tv_sec = curtime.tv_sec +=1;
                            nxtime.tv_usec -= 1000000;
                        }
#endif
                              //continue;
                            }
                            else
                            {
                               rcvCount++;
                               nbytes = 0;
                            }
                        } /*  if gtgTransac != 0 */
#ifdef WFA_VOICE_EXT 
                        /*
                        * Roundtrip time delay:
                        *   1. retrieve the timestamp
                        *   2. calculate the Trt(1) roundtrip delay
                        *   3. store the minimum Trt(1)
                        *   4. store Cdut(t1) and Ctm(2)
                        */
                        gettimeofday(&lrtime, NULL);

                    /* get a round trip time */
                    rttime = wfa_ftime_diff(&lstime, &lrtime);

                    if(min_rttime > rttime)
                    {

                        min_rttime = rttime;
                        if(gtgCaliRTD != 0)
                        {
                            gtgPktRTDelay = min_rttime;
                        }
                    }

                        if(gtgCaliRTD != 0 )
                        {
                            usleep(20000); /* wait a few min seconds before retrying the next calibration */
                        }
#else
                        /*  not voice case  */ 
                        /*  for do-while loop for frame rate per sec */ 
 
                    }while ((i <= myProfile->rate + myProfile->rate/3) && (myProfile->rate !=0) && (gtgTransac != 0 )); 

					if(myProfile->maxcnt == 0)
                    {
	                    gettimeofday(&lrtime, NULL);
	                    rttime = wfa_itime_diff(&lstime, &lrtime);
	                    /*  we cover frame rate = 0 case without any sleep to continue push data */
	                    if (((difftime = 1000000 - rttime) > 0) && (myProfile->rate != 0))
	                    {
	                        if ( j < myProfile->duration)
	                        {
	                           usleep (difftime);
	                           sleepTotal = sleepTotal + difftime/1000;
	                        }
	                    }
	                    if (j > myProfile->duration + 2)
	                    {	/* avoid infinite loop  */
	                        DPRINT_INFO(WFA_OUT, "wfa_wmm_thread SEND over time %d sec, stop sending\n",myProfile->duration);
	                        break;
	                    }
					}
#endif /* WFA_VOICE_EXT */
                } /* while */

                if(mySock != -1)
                {
                    wCLOSE(mySock);
                    mySock = -1;
                }
                DPRINT_INFO(WFA_OUT, "wfa_wmm_thread SEND::Sending stats back, sendCount=%d rcvCount=%d sleepTotal in mil-sec=%d sendFailCount=%d frmRate=%d do count=%d\n", sendCount,rcvCount,sleepTotal,sendFailCount, myProfile->rate, j);

            }/* else if(myProfile->profile == PROF_TRANSC || myProfile->profile == PROF_START_SYNC || myProfile->profile == PROF_CALI_RTD) */

            wMEMSET(respBuf, 0, WFA_RESP_BUF_SZ);
            wSLEEP(1);

            /*
             * uses thread that is saved at last to pack the items and ships
             * it to CA.
             */

            if(myId == sendThrId)
            {
                wfaSentStatsResp(gxcSockfd, respBuf);
                printf("done stats\n");
                sendThrId = 0;
            }

            break;

        case DIRECT_RECV:
            /*
             * Test WMM-PS
             */
            if(myProfile->profile == PROF_UAPSD)
            {
#ifdef WFA_WMM_PS_EXT /* legacy code not used now  */
                wmmps_info.sta_test = B_D;
                wmmps_info.ps_thread = myId;
                wmmps_info.rcv_state = 0;
                wmmps_info.tdata = tdata;
                wmmps_info.dscp = wfaTGSetPrio(psSockfd, TG_WMM_AC_BE);
                tdata->state_num=0;
                /*
                 * default timer value
                 */

                while(gtgWmmPS>0)
                {
                    if(resetsnd)
                    {
                        tdata->state_num = 0;
                        resetsnd = 0;
                    }
                    if (wmmps_info.sta_test > LAST_TEST)
                        break;

                    tdata->state =  stationProcStatetbl[wmmps_info.sta_test];
                    curr_state = tdata->state[tdata->state_num];
                    curr_state.statefunc(curr_state.pw_offon,curr_state.sleep_period,&(tdata->state_num));
                }
#endif /* WFA_WMM_PS_EXT */
            }
            else if (myProfile->profile == PROF_IPTV || myProfile->profile == PROF_FILE_TX || myProfile->profile == PROF_MCAST)
            {
                char recvBuf[MAX_RCV_BUF_LEN+1];
                int iOptVal, iOptLen;
                struct timeval tmout;

#ifdef WFA_VOICE_EXT
                struct timeval currtime;
                FILE *e2eoutp = NULL;
                char e2eResults[124];
                int le2eCnt = 0;
#endif

                mySock = wfaCreateUDPSock(myProfile->dipaddr, myProfile->dport);
                if(mySock == -1)
                {
                    printf("Error open socket\n");
                    continue;
                }

                if (myProfile->profile == PROF_MCAST)
                {
                    int so = wfaSetSockMcastRecvOpt(mySock, myProfile->dipaddr);
                    if(so < 0)
                    {
                        DPRINT_ERR(WFA_ERR, "Join the multicast group failed\n");
                        wCLOSE(mySock);
                        continue;
                    }
                }

                tgSockfds[myStream->tblidx] = mySock;

#ifdef WFA_VOICE_EXT
                /* only for receive stream needs to create a stats storage */
                tgE2EStats_t *e2esp = NULL;
                int totalE2Cnt = 220 * WFA_G_CODEC_RATE;
                printf("init E2Cnt %i\n", totalE2Cnt);
                if(myProfile->profile == PROF_IPTV)
                {
                    e2esp = malloc(totalE2Cnt * sizeof(tgE2EStats_t));

                    if(e2esp == NULL)
                    {

                    }
                }
#endif

                /* increase the rec queue size */
                getsockopt(mySock, SOL_SOCKET, SO_RCVBUF, (char *)&iOptVal, (socklen_t *)&iOptLen);
                iOptVal = iOptVal * 10;
                setsockopt(mySock, SOL_SOCKET, SO_RCVBUF, (char *)&iOptVal, (socklen_t )iOptLen);

                /* set timeout for blocking receive */
                tmout.tv_sec = 0;
                tmout.tv_usec = 200000;   /* set the receive time out to 200 ms */
                setsockopt(mySock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tmout, (socklen_t) sizeof(tmout));

                wfaSetThreadPrio(myId, TG_WMM_AC_VO);   /* try to raise the receiver higher priority than sender */
                for(;;)
                {
                    nbytes = wfaRecvFile(mySock, myStreamId, (char *)recvBuf);
                    if(nbytes <= 0)
                    {
                        /* due to timeout */
                        if(tgSockfds[myStream->tblidx] >=0 )
                            continue;

                        break;
                    }

#ifdef WFA_VOICE_EXT
                    if(myProfile->profile == PROF_IPTV)
                    {
                        struct timeval ttval, currTimeVal;

                        int sn = bigEndianBuff2Int(&((tgHeader_t *)recvBuf)->hdr[8]);
                        ttval.tv_sec = bigEndianBuff2Int(&((tgHeader_t *)recvBuf)->hdr[12]);
                        ttval.tv_usec = bigEndianBuff2Int(&((tgHeader_t *)recvBuf)->hdr[16]);
                        gettimeofday(&currTimeVal, NULL);

                        /*
                         * take the end2end stats, limit to the max voice pkt number
                         */
                        if(le2eCnt < totalE2Cnt)
                        {
                            tgE2EStats_t *ep = e2esp + le2eCnt++;
                            ep->seqnum = sn;
                            ep->rsec = ttval.tv_sec;
                            ep->rusec = ttval.tv_usec;

                            ep->lsec = currTimeVal.tv_sec;
                            ep->lusec = currTimeVal.tv_usec;

                            if(ep->lusec  < 0)
                            {
                                ep->lsec -=1;
                                ep->lusec += 1000000;
                            }
                            else if(ep->lusec >= 1000000)
                            {
                                ep->lsec += 1;
                                ep->lusec -= 1000000;
                            }
                        }
                    }
#endif /* WFA_VOICE_EXT */
                    wfaSetThreadPrio(myId, TG_WMM_AC_BE); /* put it back down */
                } /* while */

                my_wmm->thr_flag = 0;

#ifdef WFA_VOICE_EXT
                if(myProfile->profile == PROF_IPTV)
                {
                    int j;

                    wGETTIMEOFDAY(&currtime, NULL);
                    sprintf(e2eResults, "/tmp/e2e%u-%i.txt", (unsigned int) currtime.tv_sec, myStreamId);
                    printf("file %s cnt %i\n", e2eResults, le2eCnt);
                    e2eoutp = fopen(e2eResults, "w+");
                    if(e2eoutp != NULL)
                    {
                        fprintf(e2eoutp, "roundtrip delay: %i\n", (int) (1000000*gtgPktRTDelay));
                        for(j = 0; j< le2eCnt; j++)
                        {
                            tgE2EStats_t *ep = e2esp+j;
                            fprintf(e2eoutp, "%i:%i:%i:%i:%i\n", ep->seqnum, ep->lsec, ep->lusec, ep->rsec, ep->rusec);
                        }
                        fclose(e2eoutp);
                    }

                    if(e2esp != NULL)
                        free(e2esp);
                }
#endif
            }
            else if(myProfile->profile == PROF_TRANSC || myProfile->profile == PROF_START_SYNC || myProfile->profile == PROF_CALI_RTD)
            {
                struct timeval tmout;

                mySock = wfaCreateUDPSock(myProfile->sipaddr, myProfile->sport);
                if(mySock < 0)
                {
                    /* return error */
                    my_wmm->thr_flag = 0;
                    continue;
                }

                tgSockfds[myStream->tblidx] = mySock;

                totalTranPkts = 0xFFFFFFF0;
                gtgTransac = myStreamId;

               /* set timeout for blocking receive */
               tmout.tv_sec = 0;
               tmout.tv_usec = 400000;   /* set the receive time out to 400 ms, 200ms is too short */
               setsockopt(mySock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tmout, (socklen_t) sizeof(tmout));

               while(gtgTransac != 0)
               {
                    memset(trafficBuf, 0, sizeof((char*)trafficBuf));

                    if(mySock != -1)
                    {
                        int i = gtgTransac;

                      nbytes = 0;

                      /* check for data as long as we are in a transaction */
                      while ((gtgTransac != 0) && (nbytes <= 0))
                      {
                          nbytes = wfaRecvFile(mySock, i, (char  *)trafficBuf);
                      }
                      /* It is the end of a transaction, go out of the loop */
                      if (gtgTransac == 0) break;
                   }
                    else
                    {
                        break;
                    }

#ifdef WFA_VOICE_EXT
                    /* for a transaction receiver, it just needs to send the local time back */
                    gettimeofday(&lstime, NULL);
                    int2BuffBigEndian(lstime.tv_sec, &((tgHeader_t *)trafficBuf)->hdr[12]);
                    int2BuffBigEndian(lstime.tv_usec, &((tgHeader_t *)trafficBuf)->hdr[16]);
#endif
                    memset(respBuf, 0, WFA_RESP_BUF_SZ);
                    respLen = 0;
                    if(wfaSendShortFile(mySock, gtgTransac, trafficBuf, nbytes, respBuf, &respLen) == DONE)
                    {
                        if(wfaCtrlSend(gxcSockfd, (BYTE *)respBuf, respLen)!=respLen)
                        {
                            DPRINT_WARNING(WFA_WNG, "wfaCtrlSend Error\n");
                        }
                    }
                }

                my_wmm->thr_flag = 0;
               //////////////////// Wifi Alliance Added
               if(mySock != -1)
               {
                   wCLOSE(mySock);
                   mySock = -1;
               }
               //////////////////// Wifi Alliance Added
           }
            break;

        default:
            DPRINT_ERR(WFA_ERR, "Unknown covered case\n");
        }

    }
}