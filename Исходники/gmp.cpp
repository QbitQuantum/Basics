DWORD WINAPI CGMP::udtRcvHandler(LPVOID s)
#endif
{
   CGMP* self = (CGMP*)s;

   Transport t;
   sockaddr_in addr;
   int namelen = sizeof(sockaddr_in);

   int32_t header[4];

   while (!self->m_bClosed)
   {
      if (self->m_UDTSocket.accept(t, (sockaddr*)&addr, &namelen) < 0)
         continue;

      int port;
      if (t.recv((char*)&port, 4) < 0)
      {
         t.close();
         continue;
      }

      // recv "header" information
      if (t.recv((char*)header, 16) < 0)
      {
         t.close();
         continue;
      }

      CMsgRecord* rec = new CMsgRecord;

      char tmp[64]="";
      udt_inet_ntop(AF_INET, &(addr.sin_addr), tmp, 64);

      rec->m_strIP = tmp;
      rec->m_iPort = port;
      rec->m_pMsg = new CGMPMessage;
      //rec->m_pMsg->m_iType = type;
      rec->m_pMsg->m_iSession = header[1];
      rec->m_pMsg->m_iID = header[2];
      rec->m_pMsg->m_iInfo = header[3];

      // recv parameter size
      if (t.recv((char*)&(rec->m_pMsg->m_iLength), 4) < 0)
      {
         t.close();
         delete rec->m_pMsg;
         delete rec;
         continue;
      }

      rec->m_pMsg->m_pcData = new char[rec->m_pMsg->m_iLength];

      if (t.recv(rec->m_pMsg->m_pcData, rec->m_pMsg->m_iLength) < 0)
      {
         t.close();
         delete rec->m_pMsg;
         delete rec;
         continue;
      }

      t.close();

      if (self->m_PeerHistory.hit(rec->m_strIP, rec->m_iPort, rec->m_pMsg->m_iSession, rec->m_pMsg->m_iID))
         continue;

      self->m_PeerHistory.insert(rec->m_strIP, rec->m_iPort, rec->m_pMsg->m_iSession, rec->m_pMsg->m_iID);

      if (0 == header[3])
      {
          {
              CMutexGuard guard (self->m_RcvQueueLock);
              self->m_qRcvQueue.push(rec);
          }
         #ifndef WIN32
            pthread_cond_signal(&self->m_RcvQueueCond);
         #else
            SetEvent(self->m_RcvQueueCond);
         #endif
      }
      else
      {
          {
              CMutexGuard guard (self->m_ResQueueLock);
              self->m_mResQueue[header[3]] = rec;
          }
         #ifndef WIN32
            pthread_cond_signal(&self->m_ResQueueCond);
         #else
            SetEvent(self->m_ResQueueCond);
         #endif
      }
   }

   #ifndef WIN32
      pthread_cond_signal(&self->m_RcvQueueCond);
      pthread_cond_signal(&self->m_ResQueueCond);
   #else
      SetEvent(self->m_RcvQueueCond);
      SetEvent(self->m_ResQueueCond);
   #endif

   return NULL;
}