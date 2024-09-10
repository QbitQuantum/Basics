int initLog(char* rootPathStoreLog, int secondsSwitchLog, int kbSwitchLog)
{
   if((NULL == rootPathStoreLog) ||
         (secondsSwitchLog <= 0) ||
         (kbSwitchLog <= 0))
   {
      return LOG_INVALID_INPUT_PARA;
   }
   memcpy((void*)_rootPathStoreLog, (void*)rootPathStoreLog, strlen(rootPathStoreLog));
   if(_rootPathStoreLog[strlen(_rootPathStoreLog)-1] == '/') {
      _rootPathStoreLog[strlen(_rootPathStoreLog)-1] = 0;
   }
   _secondsSwitchLog = secondsSwitchLog;
   _kbSwitchLog = kbSwitchLog;

   createLogFile();
   return LOG_SUCCESS;
}