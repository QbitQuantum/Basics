/*
 ÏìÓ¦°ü´¦Àíº¯Êý£¬½«ÏìÓ¦ÄÚÈÝÖ±½ÓÉÏËÍ ÔÚµ÷ÓÃÍê³Éºó»ØÊÕSOCKET
 Èë²Î: thisÖ¸Õë
 ·µ»ØÖµ ³É¹¦ VOS_OK  Ê§°Ü VOS_ERROR
 */
 UINT32 IpappDispatchResponse(PKT_HEAD_S* pThis)
 {
  //Èë²Î¼ì²é
   CHECK_PARAM(pThis);
   
   UINT32 uiRet = VOS_OK;
   map<UINT32, IPAPP_LOCAL_BUF_S>::iterator iter = g_PktMap.find(pThis->uiPktID);
   
  if ( iter != g_PktMap.end())// -->TEST_CODE;
  {
    //ÏÈÍ£Ö¹¶¨Ê±Æ÷
    DeleteTimerQueueTimer(iter->second.hTimerQueue, iter->second.hNewTimer, NULL);
    DeleteTimerQueue(iter->second.hTimerQueue);
    
    if(iter->second.callback_pfn != NULL)
    {
      pfn pfnKey = iter->second.callback_pfn;
      IPAPP_RESPONSE_PACKET_S* pPkt = (IPAPP_RESPONSE_PACKET_S* )(pThis + 1);
      
      /*
       if(FUNCTION_NOT_FOUND == pPkt->uiErrCode) //·þÎñÆ÷¶ËÎ´ÕÒµ½º¯Êý
       {
       no_function();
       return VOS_OK;
       }
       */
       
       size_t szPktLength = sizeof(IPAPP_RESPONSE_PACKET_S) + pPkt->stRetArgs.szLen;
       if(pPkt->stRetArgs.szLen != 0)
       {
        pPkt->stRetArgs.Buf = (char *)pPkt + sizeof(IPAPP_RESPONSE_PACKET_S);
      }
      else
      {
        pPkt->stRetArgs.Buf = NULL;
      }
      
      //µ÷ÓÃ¶ÔÓ¦»Øµ÷º¯Êý
      //uiRet = UPLOADMSG(pMsg);
      CHAR *pArgList = (char *)pPkt->stRetArgs.Buf;
      pfnKey(pPkt->uiErrCode, pArgList, pPkt->stRetArgs.szLen, pPkt->context, (HANDLE)pThis->uiPktID);
    }
    
    IpappClearMap(pThis->uiPktID);
    
    //µ÷ÓÃÍê³É »ØÊÕÌ×½Ó×Ö
    if(SockCloseSocket((SOCKET)pThis->uiPktID))
    {
      printf("RESTORE SOCKET ERROR\n");
    }
    //printf("SOCKET IS ALREADY CLOSED\n");
    
  }
  
  return VOS_OK;
}