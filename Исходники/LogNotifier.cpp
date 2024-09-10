OsStatus LogNotifier::handleAlarm(
      const OsTime alarmTime,
      const UtlString& callingHost,
      const cAlarmData* alarmData,
      const UtlString& alarmMsg)
{
   OsStatus retval = OS_SUCCESS;
   OsSysLog::add(alarmData->getComponent().data(), 0, FAC_ALARM, alarmData->getSeverity(),
         "%s: %s", alarmData->getCode().data(), alarmMsg.data());

   OsDateTime logTime(alarmTime);
   UtlString   strTime ;
   logTime.getIsoTimeStringZus(strTime);

   char tempMsg[500 + alarmMsg.length()];
   snprintf(tempMsg, sizeof(tempMsg), "\"%s\":%zd:%s:%s:%s:%s::%s:\"%s\"",
             strTime.data(),
             ++mEventCount,
             OsSysLog::sFacilityNames[FAC_ALARM],
             OsSysLog::priorityName(alarmData->getSeverity()),
             callingHost.data(),
             alarmData->getComponent().data(),
             alarmData->getCode().data(),
             escape(alarmMsg).data());
   tempMsg[sizeof(tempMsg)-2]='"';
   tempMsg[sizeof(tempMsg)-1]=0;

   char* szPtr = strdup(tempMsg);
   OsSysLogMsg msg(OsSysLogMsg::LOG, szPtr);
   mpOsSysLogTask->postMessage(msg);

   return retval;
}