int
main (int argc, char** argv) {
  char* lAccessKeyId = 0;
  char* lSecretAccessKey = 0;
  char* lAction = 0;
  char* lDomain = 0;
  int   lMaxItems = 0;
  std::string lNextToken = "";
  char lEmpty[] = { '\0' };
  char* lNextTokenTmp = lEmpty;
  char* lAttrName = 0;
  char* lAttrValue = 0;
  char* lItem = 0;
  char* lQuery = 0;
  bool  lReplace = false;

  int c;
  opterr = 0;

  AWSConnectionFactory* lFactory = AWSConnectionFactory::getInstance();

  while ( (c = getopt (argc, argv, "hi:s:a:d:x:c:t:k:v:q:r")) != -1)
    switch (c) {
      case 'i':
        lAccessKeyId = optarg;
        break;
      case 's':
        lSecretAccessKey = optarg;
        break;
      case 'a':
        lAction = optarg;
        break;
      case 'd':
        lDomain = optarg;
        break;
      case 'x':
        lMaxItems = atoi (optarg);
        break;
      case 'c':
        lItem = optarg;
        break;
      case 't':
        lNextToken = optarg;
        break;
      case 'k':
        lAttrName = optarg;
        break;
      case 'v':
        lAttrValue = optarg;
        break;
      case 'q':
        lQuery = optarg;
        break;
      case 'r':
        lReplace = true;
        break;
      case 'h': {
          std::cout << "libaws version " << lFactory->getVersion() << std::endl;
          std::cout << "Usage: sdb <options>" << std::endl;
          std::cout << "  -i: AWS Access Key Id"  << std::endl;
          std::cout << "  -s: AWS Secret Access Key"  << std::endl;
          std::cout << "  -a action: Action to perform" << std::endl;
          std::cout << "             create-domain" << std::endl;
          std::cout << "             delete-domain" << std::endl;
          std::cout << "             domain-metadata" << std::endl;
          std::cout << "             delete-all-domains" << std::endl;
          std::cout << "             list-domains" << std::endl;
          std::cout << "             put-attribute" << std::endl;
          std::cout << "             delete-attribute" << std::endl;
          std::cout << "             get-attribute" << std::endl;
          std::cout << "             query" << std::endl;
          std::cout << "             list-all" << std::endl;
          std::cout << "  -d domain: A Domain Name"  << std::endl;
          std::cout << "  -c item/content: The item"  << std::endl;
          std::cout << "  -x #items: Max number of items/domains"  << std::endl;
          std::cout << "  -t next token: The next token" << std::endl;
          std::cout << "  -k key/attributes: An attribute" << std::endl;
          std::cout << "  -v value: An attribute value" << std::endl;
          std::cout << "  -q query: Replace Attribue" << std::endl;
          std::cout << "  -r replace: Replace Attribue" << std::endl;
          std::cout << "  -h help: display help" << std::endl;
          exit (1);
        }
      case '?':
        if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        exit (1);
      default:
        exit (1);
      }

  if (!lAccessKeyId) {
      lAccessKeyId = getenv ("AWS_ACCESS_KEY");
    }

  if (!lSecretAccessKey) {
      lSecretAccessKey = getenv ("AWS_SECRET_ACCESS_KEY");
    }

  if (!lAccessKeyId) {
      std::cerr << "No Access Key given" << std::endl;
      std::cerr << "Either use -i as a command line argument or set AWS_ACCESS_KEY as an environmental variable" << std::endl;
      exit (1);
    }

  if (!lSecretAccessKey) {
      std::cerr << "No Secret Access Key given" << std::endl;
      std::cerr << "Either use -s as a command line argument or set AWS_SECRET_ACCESS_KEY as an environmental variable" << std::endl;
      exit (1);
    }

  SDBConnectionPtr lSDBRest;
  lSDBRest = lFactory->createSDBConnection (lAccessKeyId, lSecretAccessKey);

  if (!lAction) {
      std::cerr << "No Action parameter specified." << std::endl;
      std::cerr << "Use -a as a command line argument" << std::endl;
      exit (1);
    }
  std::string lActionString (lAction);

  if (lActionString.compare ("list-domains") == 0) {
    listDomains (lSDBRest, lMaxItems, lNextTokenTmp);
      exit (0);
    }
  if (lActionString.compare ("delete-all-domains") == 0) {
      deleteAllDomains (lSDBRest, lQuery==0?"":lQuery);
      exit (0);
    }
    if (lActionString.compare ("list-all") == 0) {
      listAll (lSDBRest);
      exit (0);
    }

  if (!lDomain) {
      std::cerr << "No domain provided." << std::endl;
      exit (1);
    }

  if (lActionString.compare ("create-domain") == 0) {
      createDomain (lSDBRest, lDomain);
      exit (0);
    }

  if (lActionString.compare ("delete-domain") == 0) {
      deleteDomain (lSDBRest, lDomain);
      exit (0);
    }

  if (lActionString.compare ("domain-metadata") == 0) {
      domainMetadata (lSDBRest, lDomain);
      exit (0);
    }
    
    if (lActionString.compare ("query") == 0) {
      query (lSDBRest, lDomain, lQuery==0?"":lQuery, lMaxItems, lNextTokenTmp);
      exit(0);
    } 

  if (!lItem) {
      std::cerr << "No item provided." << std::endl;
      exit (1);
    }

  if (lActionString.compare ("get-attribute") == 0) {
      if (lAttrName) {
          getAttribute (lSDBRest, lDomain, lItem, lAttrName);
        } else {
          getAttribute (lSDBRest, lDomain, lItem);
        }
    }

  if (!lAttrName) {
      std::cerr << "No attribute name provided." << std::endl;
      exit (1);
    }

  if (!lAttrValue) {
      std::cerr << "No attribute value provided." << std::endl;
      exit (1);
    }

  if (lActionString.compare ("put-attribute") == 0) {
      putAttribute (lSDBRest, lDomain, lItem, lAttrName, lAttrValue, lReplace);
    } else if (lActionString.compare ("delete-attribute") == 0) {
      deleteAttribute (lSDBRest, lDomain, lItem, lAttrName, lAttrValue);
    } else {
      std::cerr << "Command not recognized." << std::endl;
      exit (1);
    }

}