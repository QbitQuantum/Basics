void
MLDispatchOrderFillerJapanese::logHL7Stream(const char* txt, int len)
{
  if (mAnalysisMode) {
    char storageDir[1024];
    char storageFile[1024];
    mStorageDir.safeExport(storageDir, sizeof(storageDir));
    sprintf(storageFile, "%s/%d.hl7", storageDir, ++gMsgNumber);
    {
      MLogClient logClient;
      char x[512];
      sprintf(x, "Writing input HL7 Stream of length %d to: %s",
		len, storageFile);
      logClient.log(MLogClient::MLOG_VERBOSE,
		    "peer",
		    "MLDispatchOrderFillerJapanese::logHL7Stream", __LINE__, x);
    }
    ofstream f(storageFile, ios::out | ios::binary);
    f.write(txt, len);
  }
}