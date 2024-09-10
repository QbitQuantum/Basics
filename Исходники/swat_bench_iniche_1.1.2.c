void
swat_udp_rx_data(STREAM_CXT_t * pStreamCxt)
{
    A_INT32 recvBytes = 0;
    A_INT32 fromSize = 0;
    A_UINT32 sumBytes = 0;
    A_UINT8 *pDataBuffer = NULL;
    struct sockaddr_in fromAddr;
    q_fd_set sockSet;
    struct timeval tmo;
    A_INT32 fdAct = 0;
    A_UINT32 isFirst = 1;
    A_UINT32 clientIp = 0;
    A_UINT16 clientPort = 0;
    A_UINT32 totalInterval = 0;
    A_UINT32 sendBytes = 0;
    STAT_PACKET_t StatPacket;

    A_INT32 sendTerminalCount = 0;

    SWAT_PTR_NULL_CHK(pStreamCxt);

    /* Initial Calc & Time */
    pStreamCxt->calc.firstTime.milliseconds = CALC_TIME_DEF;
    pStreamCxt->calc.lastTime.milliseconds = CALC_TIME_DEF;
    pStreamCxt->calc.bytes = CALC_BYTES_DEF;
    pStreamCxt->calc.kbytes = CALC_KBYTES_DEF;

    /* Initial Bench Value */
    swat_bench_quit_init();

    /* Malloc Packet Buffer Size */
    pDataBuffer = swat_mem_malloc(pStreamCxt->param.pktSize);
    if (NULL == pDataBuffer) {
        SWAT_PTF("UDP RX data buffer malloc error\r\n");
        return;
    }
    pStreamCxt->param.pktBuff = pDataBuffer;

    memset(&StatPacket, 0, sizeof (StatPacket));

    /* Prepare IP address & port */
    memset(&fromAddr, 0, sizeof (struct sockaddr_in));
    fromSize = sizeof (struct sockaddr_in);

    /* Init fd_set */
    swat_fd_zero(&sockSet);
    swat_fd_set(pStreamCxt->socketLocal, &sockSet);
    pStreamCxt->pfd_set = (void *) &sockSet;
    tmo.tv_sec = 300;
    tmo.tv_usec = 0;

    /* Get First Time */
    swat_get_first_time(pStreamCxt);

    while (1) {
        if (swat_bench_quit()) {
            /* Get Last Time For Pressure */
            //SWAT_PTF("Bench quit!!\r\n");
            swat_get_last_time(pStreamCxt);

            //swat_bytes_calc(pStreamCxt, sumBytes);
            break;
        }

        /* Wait for Input */
        fdAct = swat_select(pStreamCxt->socketLocal + 1, &sockSet, NULL, NULL, &tmo);   //k_select()
        if (0 != fdAct) {
            if (swat_fd_isset(pStreamCxt->socketLocal, &sockSet)) {
                recvBytes = swat_recvfrom(pStreamCxt->socketLocal, (char*) pDataBuffer,
                                          pStreamCxt->param.pktSize, 0,
                                          (struct sockaddr *) &fromAddr, &fromSize);
                if (recvBytes <= 0) {
                    SWAT_PTF("UDP Socket receive is error %d, sumBytes = %d\r\n", recvBytes,
                             sumBytes);
                    break;
                }

                if (recvBytes >= sizeof (EOT_PACKET_t)) {
                    if (isFirst) {
                        if (recvBytes > sizeof (EOT_PACKET_t)) {
                            clientIp = NTOHL(fromAddr.sin_addr.s_addr);
                            clientPort = NTOHS(fromAddr.sin_port);

                            SWAT_PTF("UDP receving from %d.%d.%d.%d port:%d \r\n",
                                     (clientIp) >> 24 & 0xFF, (clientIp) >> 16 & 0xFF,
                                     (clientIp) >> 8 & 0xFF, (clientIp) & 0xFF, clientPort);
                            isFirst = 0;
                            swat_get_first_time(pStreamCxt);
                        }
                        swat_bytes_calc(pStreamCxt, recvBytes);
                    } else {

                    	/*End packet is not count*/
                    	if (recvBytes > sizeof (EOT_PACKET_t)) {
							swat_bytes_calc(pStreamCxt, recvBytes);
                    	}
						else {

							/* Update Port */
							fromAddr.sin_port = HTONS(pStreamCxt->param.port);
							fromAddr.sin_family = AF_INET;	/* End Of Transfer */

                            swat_get_last_time(pStreamCxt);

                            totalInterval =
                                (pStreamCxt->calc.lastTime.milliseconds -
                                 pStreamCxt->calc.firstTime.milliseconds);
                            StatPacket.kbytes = pStreamCxt->calc.kbytes;
                            StatPacket.bytes = pStreamCxt->calc.bytes;
                            StatPacket.msec = totalInterval;
                            /* Tell ath_console TX received end mark AABBCCDD with throughput value */
                            while (sendTerminalCount <= 10) {
                                /* Wait for Output */
                                fdAct = swat_select(pStreamCxt->socketLocal + 1, NULL, &sockSet, NULL, &tmo);   //k_select()
                                if (0 != fdAct) {
                                    if (swat_fd_isset(pStreamCxt->socketLocal, &sockSet)) {
                                        sendBytes = swat_sendto(pStreamCxt->socketLocal,
                                                                (char *) (&StatPacket),
                                                                sizeof (STAT_PACKET_t), 0,
                                                                (struct sockaddr *) &fromAddr,
                                                                sizeof (struct sockaddr_in));
                                        if (sendBytes < 0) {
                                            SWAT_PTF
                                                ("UDP send throughput info packet error %d , retry %d \r\n",
                                                 sendBytes, sendTerminalCount);
                                            qcom_thread_msleep(100);
                                        } else {
                                            /* Clean */
                                            tmo.tv_sec = 2;
                                            tmo.tv_usec = 0;
                                            while (recvBytes == sizeof (EOT_PACKET_t)) {
                                                fdAct = swat_select(pStreamCxt->socketLocal + 1, &sockSet, NULL, NULL, &tmo);   //k_select()
                                                if (0 == fdAct) {
                                                    SWAT_PTF("UDP break\n");
                                                    break;
                                                }

                                                if (swat_fd_isset(pStreamCxt->socketLocal, &sockSet)) {
                                                    recvBytes = swat_recvfrom(pStreamCxt->socketLocal, (char*) pDataBuffer,
                                                                              pStreamCxt->param.pktSize, 0,
                                                                              (struct sockaddr *) &fromAddr, &fromSize);
                                                }
                                            }
                                            break;
                                        }
                                    }
                                }
                                sendTerminalCount++;
                            }
                            break;
                        }
                    }
                }
            }