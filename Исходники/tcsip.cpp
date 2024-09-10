///////////////////////////////////////////////////
//This function implements the state diagram for
//user inputs
int ProcessUserCommand(char* command, char* result)
{
  if (!(command && result)) return -1;
  memset(result, 0, MAX_STR_LEN);

  int  cmdType = 0;
  char msgExtra[MAX_STR_LEN];
  cmdType = GetCommandType(command, msgExtra);
  if (cmdType < 0)
  {
    strcpy(result,"Please use one of the following commands:\n"
                  "       invite user@host  : To initiate a session with host\n"
                  "       accept            : To accept a request from remote host\n"
                  "       reject            : To reject a request from remote host\n"
                  "       bye               : To terminate an open session\n"
                  "       exit              : To terminate the program\n");
    return -1;
  }

  /* change the mode only if it is none; otherwise leave it as it is */
  if (g_sip_mode==SIP_NONE && cmdType==CMD_INVITE)
      g_sip_mode =SIP_CLIENT;

  /* client */
  if (g_sip_mode == SIP_CLIENT)
  {
    if (g_sip_state==SIP_IDLE)
    {
      if (cmdType==CMD_INVITE)
      { //Client at idle receives invite user@host: createSession;SetRemote sockaddr in oSocSIP, cook buffer and send.
        CreateSessionData(msgExtra);
         
        if (oSocSIP.SetRemoteInfo(g_SessionData.RemoteHost, SIP_PORT)<0)
        {
          strcpy(result, "Invalid host entered");
          return -1;
        }
        sprintf((char*)g___Buffer, INVITE_MSG, g_SessionData.From, (DWORD)lrand48(), (DWORD)lrand48(), g_SessionData.MyHost, g_SessionData.MyHost, SIP_PORT);
        int c_len = strlen((char*)g___Buffer);
        sprintf((char*)g_txBuffer, INVITE_HDR, g_SessionData.ToAdrs, g_SessionData.MyHost, SIP_PORT, g_SessionData.From, g_SessionData.FromAdrs, g_SessionData.To, g_SessionData.ToAdrs, g_SessionData.CallID, ++g_sip_seq, c_len);
        strcat((char*)g_txBuffer, (char*)g___Buffer);
        c_len = strlen((char*)g_txBuffer);
        oSocSIP.SendTo(g_txBuffer, &c_len);

        g_sip_state = SIP_CONX_PENDING;
      }
      else if (cmdType==CMD_ACCEPT)
      {
        strcpy(result, "Nothing to accept");
        return -1;
      }
      else if (cmdType==CMD_REJECT)
      {
        strcpy(result, "Nothing to reject");
        return -1;
      }
      else if (cmdType==CMD_BYE)
      {
        strcpy(result, "No active session to close");
        return -1;
      }
      else if (cmdType==CMD_EXIT)
      {
         g_sip_done = true;  
         //g_run_rtp = false;
         StopAudioThread();
         return 0;
      }
    }
    else if (g_sip_state==SIP_CONX_PENDING)
    {
      if (cmdType==CMD_INVITE)
      {
        strcpy(result, "Connection already in progress. Cannot invite now.");
        return -1;
      }
      else if (cmdType==CMD_ACCEPT)
      {
        strcpy(result, "Nothing to accept");
        return -1;
      }
      else if (cmdType==CMD_REJECT)
      {
        strcpy(result, "Nothing to reject");
        return -1;
      }
      else if (cmdType==CMD_BYE)
      {
        strcpy(result, "Connection in progress. Please try again");
        return -1;
      }
      else if (cmdType==CMD_EXIT)
      {
        strcpy(result, "Connection in progress. Please try again");
        return -1;
      }
    }
    else if (g_sip_state==SIP_CONNECTED)
    {
      if (cmdType==CMD_INVITE)
      {
        strcpy(result, "You are already connected. Please close this session (with bye) first before initiating a new session.");
        return -1;
      }
      else if (cmdType==CMD_ACCEPT)
      {
        strcpy(result, "You are already connected. Nothing to accept");
        return -1;
      }
      else if (cmdType==CMD_REJECT)
      {
        strcpy(result, "You are already connected. Nothing to reject");
        return -1;
      }
      else if (cmdType==CMD_BYE)
      {
        sprintf((char*)g_txBuffer, BYE_HDR, g_SessionData.ToAdrs, g_SessionData.MyHost, SIP_PORT, g_SessionData.From, g_SessionData.FromAdrs,
                                     g_SessionData.To, g_SessionData.ToAdrs, g_SessionData.CallID, ++g_sip_seq);

        int c_len = strlen((char*)g_txBuffer);
        oSocSIP.SendTo(g_txBuffer, &c_len);
        //g_run_rtp = false;
        StopAudioThread();
        //g_au_started = true;
        g_sip_state = SIP_DISCONX_PENDING;
      }
      else if (cmdType==CMD_EXIT)
      {
        strcpy(result, "You are currently connected. Please close this session (with bye) first, and then exit.");
        return -1;
      }
    }
    else if (g_sip_state==SIP_DISCONX_PENDING)
    {
      if (cmdType==CMD_INVITE)
      {
        strcpy(result, "Disconnection in progress. Please try again.");
        return -1;
      }
      else if (cmdType==CMD_ACCEPT)
      {
        strcpy(result, "Disconnection in progress. Nothing to accept.");
        return -1;
      }
      else if (cmdType==CMD_REJECT)
      {
        strcpy(result, "Disconnection in progress. Nothing to reject.");
        return -1;
      }
      else if (cmdType==CMD_BYE)
      {
        strcpy(result, "Disconnection in progress. Please try again.");
        return -1;
      }
      else if (cmdType==CMD_EXIT)
      {
        strcpy(result, "Disconnection in progress. Please try again.");
        return -1;
      }
    }
  }
  else
  /* server mode */
  if (g_sip_mode == SIP_SERVER)
  {
    if (g_sip_state==SIP_IDLE)
    {
      if (cmdType==CMD_INVITE)
      {
        printf("Invalid condition in the state machine!\n");
        return -1;
      }
      else if (cmdType==CMD_ACCEPT)
      {
        strcpy(result, "Nothing to accept");
        return -1;
      }
      else if (cmdType==CMD_REJECT)
      {
        strcpy(result, "Nothing to reject");
        return -1;
      }
      else if (cmdType==CMD_BYE)
      {
        strcpy(result, "No active session to close");
        return -1;
      }
      else if (cmdType==CMD_EXIT)
      {
         g_sip_done = true;  
         //g_run_rtp = false;
         StopAudioThread();
         return 0;
      }
    }
    else if (g_sip_state==SIP_CONX_PENDING)
    {
      if (cmdType==CMD_INVITE)
      {
        strcpy(result, "Connection already in progress. Cannot invite now.");
        return -1;
      }
      else if (cmdType==CMD_ACCEPT)
      {
        sprintf((char*)g_txBuffer, RESPONSE_MSG, 200, "OK", g_SessionData.remoteRestHdr, g_SessionData.remoteRestBdy);
        int c_len = strlen((char*)g_txBuffer);
        oSocSIP.SendTo(g_txBuffer, &c_len);
      }
      else if (cmdType==CMD_REJECT)
      {
        sprintf((char*)g_txBuffer, RESPONSE_MSG, 603, "Decline", g_SessionData.remoteRestHdr, "\0");
        int c_len = strlen((char*)g_txBuffer);
        c_len--;
        oSocSIP.SendTo(g_txBuffer, &c_len);
        g_sip_state = SIP_IDLE;
        g_sip_mode  = SIP_NONE;
      }
      else if (cmdType==CMD_BYE)
      {
        printf("Invalid condition in the state machine!\n");
        return -1;
      }
      else if (cmdType==CMD_EXIT)
      {
        strcpy(result, "Connection in progress. Please try again");
        return -1;
      }
    }
    else if (g_sip_state==SIP_CONNECTED)
    {
      if (cmdType==CMD_INVITE)
      {
        strcpy(result, "You are already connected. Please close this session (with bye) first before initiating a new session.");
        return -1;
      }
      else if (cmdType==CMD_ACCEPT)
      {
        strcpy(result, "You are already connected. Nothing to accept");
        return -1;
      }
      else if (cmdType==CMD_REJECT)
      {
        strcpy(result, "You are already connected. Nothing to reject");
        return -1;
      }
      else if (cmdType==CMD_BYE)
      {
        /*
           This is what i actually need to do. but resorting to short cut @@@@
        sprintf(g_txBuffer, BYE_HDR, g_SessionData.ToAdrs, g_SessionData.MyHost, g_SessionData.From, g_SessionData.FromAdrs,
                                     g_SessionData.To, g_SessionData.ToAdrs, g_SessionData.CallID, ++g_sip_seq);
        */
        sprintf((char*)g_txBuffer, "BYE %s SIP/2.0\n%s\n", g_SessionData.uri, g_SessionData.remoteRestHdr);
        int c_len = strlen((char*)g_txBuffer);
        oSocSIP.SendTo(g_txBuffer, &c_len);
        // g_run_rtp = false;
        StopAudioThread();
        //g_au_started= true;
        g_sip_state = SIP_DISCONX_PENDING;
      }
      else if (cmdType==CMD_EXIT)
      {
        strcpy(result, "You are currently connected. Please close this session (with bye) first, and then exit.");
        return -1;
      }
    }
    else if (g_sip_state==SIP_DISCONX_PENDING)
    {
      if (cmdType==CMD_INVITE)
      {
        strcpy(result, "Disconnection in progress. Please try again.");
        return -1;
      }
      else if (cmdType==CMD_ACCEPT)
      {
        strcpy(result, "Disconnection in progress. Nothing to accept.");
        return -1;
      }
      else if (cmdType==CMD_REJECT)
      {
        strcpy(result, "Disconnection in progress. Nothing to reject.");
        return -1;
      }
      else if (cmdType==CMD_BYE)
      {
        strcpy(result, "Disconnection in progress. Please try again.");
        return -1;
      }
      else if (cmdType==CMD_EXIT)
      {
        strcpy(result, "Disconnection in progress. Please try again.");
        return -1;
      }
    }
  }
  else
  if (g_sip_mode == SIP_NONE)
  {
    if( g_sip_state == SIP_IDLE)
    {
      if (cmdType==CMD_ACCEPT)
      {
        strcpy(result, "Nothing to accept");
        return 0;
      }
      else if (cmdType==CMD_REJECT)
      {
        strcpy(result, "Nothing to accept");
        return 0;
      }
      else if (cmdType==CMD_EXIT)
      {
         g_sip_done = true;  
         //g_run_rtp  = false;
         StopAudioThread();
         return 0;
      }
    }
  }

  return 0;
}