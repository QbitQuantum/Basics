int
MLXferAgent::xmitVectorOfImages(const MString& sourceAE,
	const MString& destAE,
	const MString& host,
	const MString& port)
{
  MStorageAgent agent;
  U16 result = 0;
  MString rtnMessage;
  int status;
  MLogClient logClient;

  logClient.log(MLogClient::MLOG_CONVERSATION,
	destAE,
	"MLXferAgent::xmitVectorOfImages",
	__LINE__,
	MString("About to export images to ") + host + MString(":") + port);

  MStringVector::iterator it = mFileNameVector.begin();
  for (; it != mFileNameVector.end(); it++) {
    status = agent.storeInstance(sourceAE, destAE,
		host, port.intData(),
		*it,
		result,
		rtnMessage);
    if (status != 0) {
      cout << "Unable to xfer: " << *it << endl;
      return 1;
    }
  }
  return 0;
}