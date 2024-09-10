/* this only sends one packet a time */
int wfaSendShortFile(int mySockfd, int streamid, BYTE *sendBuf, int pksize, BYTE *aRespBuf, int *aRespLen)
{
   BYTE *packBuf = sendBuf; 
   struct sockaddr_in toAddr;
   tgProfile_t *theProf;
   tgStream_t *myStream;
   int packLen, bytesSent=-1;
   dutCmdResponse_t sendResp;

   if(mySockfd == -1)
   {
      /* stop */ 
      gtgTransac = 0;
      //gtimeOut = 0; 
      gtgRecv = 0;
      gtgSend = 0;
      printf("stop short traffic\n");

      myStream = findStreamProfile(streamid);
      if(myStream != NULL)
      {
          sendResp.status = STATUS_COMPLETE;
          sendResp.streamId = streamid;
          wMEMCPY(&sendResp.cmdru.stats, &myStream->stats, sizeof(tgStats_t)); 
    
          wfaEncodeTLV(WFA_TRAFFIC_AGENT_SEND_RESP_TLV, sizeof(dutCmdResponse_t), (BYTE *)&sendResp, aRespBuf);

          *aRespLen = WFA_TLV_HDR_LEN + sizeof(dutCmdResponse_t);
      }

      return DONE;
   }

   /* find the profile */
   myStream = findStreamProfile(streamid);

   if(myStream == NULL)
   {
        return FALSE;
   }

   theProf = &myStream->profile;
   if(theProf == NULL)
   {
        return FALSE;
   }

   if(pksize == 0)
      packLen = theProf->pksize;
   else
      packLen = pksize;

   wMEMSET(&toAddr, 0, sizeof(toAddr));
   toAddr.sin_family = AF_INET;
   toAddr.sin_addr.s_addr = inet_addr(theProf->sipaddr);
   toAddr.sin_port = htons(theProf->sport); 

   if(gtgRecv && gtgTransac)
   {
//      printf("mySock %i sipaddr %s sport %i\n", mySockfd, theProf->sipaddr, theProf->sport); 
      toAddr.sin_addr.s_addr = inet_addr(theProf->sipaddr);
      toAddr.sin_port = htons(theProf->sport); 
   }
   else if(gtgSend && gtgTransac)
   {
//      printf("mySock %i dipaddr %s dport %i\n", mySockfd, theProf->dipaddr, theProf->dport); 
      toAddr.sin_addr.s_addr = inet_addr(theProf->dipaddr);
      toAddr.sin_port = htons(theProf->dport); 
   }

   int2BuffBigEndian(myStream->stats.txFrames, &((tgHeader_t *)packBuf)->hdr[8]);

   if(mySockfd != -1)
      bytesSent = wfaTrafficSendTo(mySockfd, (char *)packBuf, packLen, (struct sockaddr *)&toAddr);

   if(bytesSent != -1)
   {
      myStream->stats.txFrames++;
      myStream->stats.txPayloadBytes += bytesSent;
   }
   else
   {
      int errsv = errno;
      switch(errsv)
      {
          case EAGAIN:
          case ENOBUFS:
             DPRINT_ERR(WFA_ERR, "send error\n");
             wUSLEEP(1000);             /* hold for 1 ms */
             myStream->stats.txFrames--;
	  break;
	  default:
              ;;
             //perror("sendto: ");
      }
   }

   sentTranPkts++;

   return TRUE;
}