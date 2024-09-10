void
MLMessenger::logHL7Stream(const char* txt, int len)
{
  if (mAnalysisMode) {
    char storageDir[1024];
    char logFile[1024];
    mStorageDir.safeExport(storageDir, sizeof(storageDir));
    sprintf(logFile, "%s/%d.hl7", storageDir, ++gMsgNumber);
    {
      MLogClient logClient;
      char x[512];
      sprintf(x, "Writing input HL7 Stream of length %d to: %s",
		len, logFile);
      logClient.log(MLogClient::MLOG_CONVERSATION,
		    this->mHandler->getPeerName(),
		    "MLMessenger::logHL7Stream", __LINE__, x);
    }
    ofstream f(logFile, ios::out | ios::binary);
    f.write(txt, len);
  }
}