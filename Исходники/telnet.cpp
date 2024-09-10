BOOL CTelnetServer::ProcessPendingAccept(void)
{
   //create new client socket, and add to list
   CTelnetServerSession* pSocket = (CTelnetServerSession*)m_pSessionRuntimeClass->CreateObject();
   ASSERT_KINDOF(CTelnetServerSession, pSocket);
	BOOL bOK = (NULL != pSocket);
	if(bOK)
   {
      pSocket->m_pParent = this;
      bOK = Accept(*pSocket);
      if (bOK)
	   {
		   bOK = pSocket->Init();
	   }
   }

	if(!bOK)
   {
		delete pSocket;
   }
   return bOK;
}