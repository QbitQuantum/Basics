int
s3objecttest(int argc, char** argv) 
{
	
	AWSConnectionFactory* lFactory = AWSConnectionFactory::getInstance();

  std::cout << "Testing libaws version " << lFactory->getVersion() << std::endl;

  char* lAccessKeyId = getenv("AWS_ACCESS_KEY");
  char* lSecretAccessKey = getenv("AWS_SECRET_ACCESS_KEY");

  if (lAccessKeyId == 0 || lSecretAccessKey == 0) {
    std::cerr << "Environment variables (i.e. AWS_ACCESS_KEY or AWS_SECRET_ACCESS_KEY) not set" 
              << std::endl;
    return 1;
  }
	
  S3ConnectionPtr lS3Rest = lFactory->createS3Connection(lAccessKeyId, lSecretAccessKey);

  int lReturnCode;
  try {
    lReturnCode = createbucket(lS3Rest.get());
    if (lReturnCode != 0)
      return lReturnCode;

    lReturnCode = put(lS3Rest.get());
    if (lReturnCode != 0)
      return lReturnCode;

    lReturnCode = listbucket(lS3Rest.get());
    if (lReturnCode != 0)
      return lReturnCode;

    lReturnCode = getobject(lS3Rest.get());
    if (lReturnCode != 0)
      return lReturnCode;

    lReturnCode = deleteobject(lS3Rest.get());
    if (lReturnCode != 0)
      return lReturnCode;

    lReturnCode = deletebucket(lS3Rest.get());
    if (lReturnCode != 0)
      return lReturnCode;

  } catch (AWSConnectionException& e) {
    std::cerr << e.what() << std::endl;
    return 2;
  }

  lFactory->shutdown();

  return 0;
}