PIPECLINETHANDLE NamedPipeClientConnect(char * pName, unsigned long commID, PPIPERECVCB pPipeRecvCB)
{
   PIPECLINETHANDLE pipeClientHandle = NULL;
   BOOL bFlag = FALSE;
   if(pName == NULL || commID <= 0) return pipeClientHandle;
   if(!WaitNamedPipe(pName, NMPWAIT_WAIT_FOREVER)) return pipeClientHandle;
   {
      pipeClientHandle = (PIPECLINETHANDLE)malloc(sizeof(NAMEDPIPECLIENT));
      memset(pipeClientHandle, 0, sizeof(NAMEDPIPECLIENT));
      pipeClientHandle->pPipeRecvCB = pPipeRecvCB;
      pipeClientHandle->commID = commID;
      pipeClientHandle->pipeRecvThreadRun = TRUE;
      pipeClientHandle->pipeRecvThreadHandle = CreateThread(NULL, 0, PipeClientRecvThreadStart,pipeClientHandle, 0, NULL);
      if(!pipeClientHandle->pipeRecvThreadHandle)
      {
         pipeClientHandle->pipeRecvThreadRun = FALSE;
         goto done;
      }

      pipeClientHandle->hPipe = CreateFile(pName, GENERIC_READ |GENERIC_WRITE,
         0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      if(INVALID_HANDLE_VALUE == pipeClientHandle->hPipe)
      {
         pipeClientHandle->isConnected = FALSE;
         goto done;
      }

      {
         DWORD dwMode = PIPE_READMODE_MESSAGE | PIPE_NOWAIT;
         SetNamedPipeHandleState(pipeClientHandle->hPipe, &dwMode, NULL, NULL);
      }

      pipeClientHandle->isConnected = TRUE;

      {
         IPCINTERMSG ipcInterMsg;
         ipcInterMsg.interCmdKey = IPC_CONNECT;
         ipcInterMsg.interParams.commID = commID;
         bFlag = NamedPipeClientGNSend(pipeClientHandle, INTER_MSG, (char *)&ipcInterMsg, sizeof(IPCINTERMSG));
         if(!bFlag) goto done;
      }

      bFlag =TRUE;
   }
   
done:
   if(!bFlag && pipeClientHandle)
   {
      NamedPipeClientDisconnect(pipeClientHandle);
     /* free(pipeClientHandle);*/
      pipeClientHandle = NULL;
   }
   return pipeClientHandle;
}