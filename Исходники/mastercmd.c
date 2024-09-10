TMasterCmdReq * TMasterCmdFactory_GetMasterCmd( TMasterCmdType cmd )
{
   TMasterCmdReq * mc= NULL;
   usedcmd++;
   os_thread_MutexLock(&unusedMasterCmdList.Mutex);
   if (!ISLISTEMPTY( &unusedMasterCmdList ))
   {
      //get it from list...
      mc = (TMasterCmdReq *)GETFIRST(&unusedMasterCmdList);
      REMOVE(&mc->Node);
      
      //reinit the command
      TMasterCmd_Init(mc, cmd);
   }
   os_thread_MutexUnlock(&unusedMasterCmdList.Mutex);
   
   if (mc) return mc;
   
   //nothing free, create an new one...
   return TMasterCmd_Constructor( cmd );
}