MPEG2TransportStreamIndexFile
::MPEG2TransportStreamIndexFile(UsageEnvironment& env, char const* indexFileName)
  : Medium(env),
    fFileName(strDup(indexFileName)), fFid(NULL), fMPEGVersion(0), fCurrentIndexRecordNum(0),
    fCachedPCR(0.0f), fCachedTSPacketNumber(0), fNumIndexRecords(0) {
  // Get the file size, to determine how many index records it contains:
  u_int64_t indexFileSize = GetFileSize(indexFileName, NULL);
  if (indexFileSize % INDEX_RECORD_SIZE != 0) {
    env << "Warning: Size of the index file \"" << indexFileName
 	<< "\" (" << (unsigned)indexFileSize
	<< ") is not a multiple of the index record size ("
	<< INDEX_RECORD_SIZE << ")\n";
  }
  fNumIndexRecords = (unsigned long)(indexFileSize/INDEX_RECORD_SIZE);
}