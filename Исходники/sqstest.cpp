int
sqstest(int argc, char** argv)
{

  AWSConnectionFactory* lFactory = AWSConnectionFactory::getInstance();
  //logging::LoggerManager::logmanager()->setLoggerConfig("|1|logging.log");
  //logging::LoggerManager::logmanager()->setFileName ( "", "logging.log" );
  std::cout << "Testing libaws version " << lFactory->getVersion() << std::endl;

  char* lAccessKeyId = getenv("AWS_ACCESS_KEY");
  char* lSecretAccessKey = getenv("AWS_SECRET_ACCESS_KEY");
  if (lAccessKeyId == 0 || lSecretAccessKey == 0) {
    std::cerr << "Environment variables (i.e. AWS_ACCESS_KEY or AWS_SECRET_ACCESS_KEY) not set"
        << std::endl;
    return 1;
  }

  SQSConnectionPtr lS3Rest;
  char* lHost = getenv("SQS_HOST");
  if (lHost == 0) {
  	lS3Rest = lFactory->createSQSConnection(lAccessKeyId, lSecretAccessKey);
  }
  else {
    // aPort = -1 -> we have specified our own
    // aIsSecure = false -> we would like http instead of https
  	lS3Rest = lFactory->createSQSConnection(lAccessKeyId, lSecretAccessKey, lHost, -1, false);
  }

  int lReturnCode;
  try {
   // lReturnCode = testQueues(lS3Rest.get());
   // if (lReturnCode != 0)
   //		return lReturnCode;

    lReturnCode = testMessages(lS3Rest.get());
    if (lReturnCode != 0)
      return lReturnCode;


  } catch (AWSConnectionException& e) {
    std::cerr << e.what() << std::endl;
    return 2;
  }

  lFactory->shutdown();

  return 0;
}