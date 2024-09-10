int sdbtest(int argc, char* argv[]) {
    AWSConnectionFactory* lFactory = AWSConnectionFactory::getInstance();

    std::cout << "Testing libaws version " << lFactory->getVersion() << std::endl;

    char* lAccessKeyId = getenv("AWS_ACCESS_KEY");
    char* lSecretAccessKey = getenv("AWS_SECRET_ACCESS_KEY");
    if (lAccessKeyId == 0 || lSecretAccessKey == 0) {
        std::cerr
                << "Environment variables (i.e. AWS_ACCESS_KEY or AWS_SECRET_ACCESS_KEY) not set"
                << std::endl;
        return 1;
    }

    SDBConnectionPtr lConSmart = lFactory->createSDBConnection(lAccessKeyId,
                                 lSecretAccessKey);
    SDBConnection* lCon = lConSmart.get();

    try {
        if (createDomain(lCon) != 0) {
            return 1;
        }
        if (listDomains(lCon) != 0) {
            return 1;
        }
        if (putAttributes(lCon) != 0) {
            return 1;
        }
        if (getAttributes(lCon) != 0) {
            return 1;
        }
        if (deleteAttributes(lCon) != 0) {
            return 1;
        }
        if (getAttributes(lCon) != 0) {
            return 1;
        }
        if (query(lCon) != 0) {
            return 1;
        }
        if (queryWithAttributes(lCon) != 0) {
            return 1;
        }
        if (deleteDomain(lCon) != 0) {
            return 1;
        }
    }
    catch (AWSConnectionException& e) {
        std::cerr << e.what() << std::endl;
        return 2;
    }

    lFactory->shutdown();

    return 0;
}