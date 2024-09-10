int
MAMessenger::logMsg (MHL7Msg& message, const MString& event, char* hl7Type)
{
  int logdirLen = mLogDir.size() + 1;
  int eventLen = event.size() + 1;
  char logdir[logdirLen];
  char eventstr[eventLen];
  event.safeExport(eventstr, eventLen);
  mLogDir.safeExport(logdir, logdirLen);

  sprintf (mStream, "%s/msg%d_%s.%s", logdir, ++gMsgNumber, eventstr, hl7Type);
  ofstream msgFile (mStream, ios::out | ios::trunc | ios::binary);
  {
    MLogClient logClient;
    char x[512];
    sprintf(x, "Log %s message to: %s", hl7Type, mStream);
    logClient.log(MLogClient::MLOG_VERBOSE, "<no peer>",
		  "MAMessenter::logMsg", __LINE__, x);
  }

  int length=0;
  message.exportToWire (mStream, mStreamSize, length);
  msgFile << mStream << endl;  
  
  return 0;
}