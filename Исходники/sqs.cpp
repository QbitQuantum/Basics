int
main (int argc, char** argv) {
    char* lAction = 0;
    char* lQueueName = 0;
    char* lPrefix = 0;
    int   lMaxNbMessages = -1;
    char* lMessage = 0;
    int   lVisibilityTimeOut = -1;
    char* lAccessKeyId = 0;
    char* lSecretAccessKey = 0;
    char* lReceiptHandle = 0;
    char* lHost = 0;
    bool lBase64 = true;

    int c;
    opterr = 0;

    AWSConnectionFactory* lFactory = AWSConnectionFactory::getInstance();

    while ( (c = getopt (argc, argv, "hbi:s:a:n:p:x:m:r:")) != -1)
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
        case 'o':
            lHost = optarg;
            break;
        case 'n':
            lQueueName = optarg;
            break;
        case 'p':
            lPrefix = optarg;
            break;
        case 'x':
            lMaxNbMessages = atoi (optarg);
            break;
        case 'm':
            lMessage = optarg;
            break;
        case 'v':
            lVisibilityTimeOut = atoi (optarg);
            break;
        case 'r':
            lReceiptHandle = optarg;
            break;
        case 'h': {
            std::cout << "libaws version " << lFactory->getVersion() << std::endl;
            std::cout << "Usage: sqs <options>" << std::endl;
            std::cout << "  -i: AWS Access Key Id"  << std::endl;
            std::cout << "  -s: AWS Secret Access Key"  << std::endl;
            std::cout << "  -a action: Action to perform" << std::endl;
            std::cout << "             list-queues: List all queues" << std::endl;
            std::cout << "             create-queue: Create a queue" << std::endl;
            std::cout << "             delete-queue: Delete a queue" << std::endl;
            std::cout << "             delete-all-queues: Delete all queues" << std::endl;
            std::cout << "             send-message: Send a message" << std::endl;
            std::cout << "             list-message: Receive messages" << std::endl;
            std::cout << "             delete-message: Delete messages" << std::endl;
            std::cout << "             delete-all-messages: Delete all messages retrieved" << std::endl;
            std::cout << "  -o host name"  << std::endl;
            std::cout << "  -n name: A Queue Name/URL"  << std::endl;
            std::cout << "  -p prefix: Prefix for listing queues"  << std::endl;
            std::cout << "  -x #messages: Number of messages to return"  << std::endl;
            std::cout << "  -m message: the message to send" << std::endl;
            std::cout << "  -v visibility timeout: the visibility timeout" << std::endl;
            std::cout << "  -r receipt-handle: the receipt-handle" << std::endl;
            std::cout << "  -b base64-handle: do not encode/decode message bodies to/from base64" << std::endl;
            std::cout << "  -h help: display help" << std::endl;
            exit (1);
        }
        case 'b':
            lBase64 = false;
            break;
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

    if (!lHost) {
        lHost = getenv ("SQS_HOST");
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

    SQSConnectionPtr lSQSRest;
    if (!lHost) {
        lSQSRest = lFactory->createSQSConnection (lAccessKeyId, lSecretAccessKey);
    }
    else {
        // aPort = -1 -> we have specified our own
        // aIsSecure = false -> we would like http instead of https
        lSQSRest = lFactory->createSQSConnection(lAccessKeyId, lSecretAccessKey, lHost, -1, false);
    }

    if (!lAction) {
        std::cerr << "No Action parameter specified." << std::endl;
        std::cerr << "Use -a as a command line argument" << std::endl;
        exit (1);
    }
    std::string lActionString (lAction);

    if (lActionString.compare ("list-queues") == 0) {
        listQueues (lSQSRest, lPrefix == 0 ? "" : lPrefix);
    } else if (lActionString.compare ("create-queue") == 0) {
        if (!lQueueName) {
            std::cerr << "No queue name parameter specified." << std::endl;
            std::cerr << "Use -n as a command line argument" << std::endl;
            exit (1);
        }
        createQueue (lSQSRest, lQueueName, lVisibilityTimeOut);
    } else if (lActionString.compare ("delete-queue") == 0) {
        if (!lQueueName) {
            std::cerr << "No queue name parameter specified." << std::endl;
            std::cerr << "Use -n as a command line argument" << std::endl;
            exit (1);
        }
        deleteQueue (lSQSRest, lQueueName);
    } else if (lActionString.compare ("delete-all-queues") == 0) {
        deleteAllQueues (lSQSRest);
    } else if (lActionString.compare ("send-message") == 0) {
        if (!lQueueName) {
            std::cerr << "No queue name parameter specified." << std::endl;
            std::cerr << "Use -n as a command line argument" << std::endl;
            exit (1);
        }
        if (!lMessage) {
            std::cerr << "No message parameter specified." << std::endl;
            std::cerr << "Use -m as a command line argument" << std::endl;
            exit (1);
        }
        sendMessage (lSQSRest, lQueueName, lMessage, lBase64);
    } else if (lActionString.compare ("list-messages") == 0 || lActionString.compare ("list-message") == 0) {
        if (!lQueueName) {
            std::cerr << "No queue name parameter specified." << std::endl;
            std::cerr << "Use -n as a command line argument" << std::endl;
            exit (1);
        }
        receiveMessage (lSQSRest, lQueueName, lMaxNbMessages, lVisibilityTimeOut, lBase64);
    } else if (lActionString.compare ("delete-message") == 0) {
        if (!lQueueName) {
            std::cerr << "No queue name parameter specified." << std::endl;
            std::cerr << "Use -n as a command line argument" << std::endl;
            exit (1);
        }
        if (!lReceiptHandle) {
            std::cerr << "No receipt handle parameter specified." << std::endl;
            std::cerr << "Use -r as a command line argument" << std::endl;
            exit (1);
        }
        deleteMessage (lSQSRest, lQueueName, lReceiptHandle);
    } else if (lActionString.compare ("delete-all-messages") == 0) {
        if (!lQueueName) {
            std::cerr << "No queue name parameter specified." << std::endl;
            std::cerr << "Use -n as a command line argument" << std::endl;
            exit (1);
        }
        deleteAllMessages (lSQSRest, lQueueName);
    } else {
        std::cerr << "Command not recognized." << std::endl;
        exit(1);
    }

}