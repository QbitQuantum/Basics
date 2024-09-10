/* extProcCommand: process command message */
EXPORT void extProcCommand(MMDAgent *mmdagent, const char *type, const char *args)
{
   if(enable == true) {
      if(MMDAgent_strequal(type, MMDAGENT_COMMAND_PLUGINDISABLE) == true) {
         if(MMDAgent_strequal(args, PLUGINWINDOWCONTROLLER_NAME)) {
            enable = false;
            mmdagent->sendEventMessage(MMDAGENT_EVENT_PLUGINDISABLE, PLUGINWINDOWCONTROLLER_NAME);
         }
      } else if(MMDAgent_strequal(type, PLUGINWINDOWCONTROLLER_EXECUTE) == true) {
         if(MMDAgent_strlen(args) > 0)
            ShellExecuteA(NULL, NULL, args, NULL, NULL, SW_SHOWNORMAL);
      } else if(MMDAgent_strequal(type, PLUGINWINDOWCONTROLLER_KEYPOST) == true) {
         postKeyMessage(args);
      }
   } else {
      if(MMDAgent_strequal(type, MMDAGENT_COMMAND_PLUGINENABLE) == true) {
         if(MMDAgent_strequal(args, PLUGINWINDOWCONTROLLER_NAME) == true) {
            enable = true;
            mmdagent->sendEventMessage(MMDAGENT_EVENT_PLUGINENABLE, PLUGINWINDOWCONTROLLER_NAME);
         }
      }
   }
}