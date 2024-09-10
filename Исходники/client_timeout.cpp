int main(int argc, char** argv)
{
    if (argc != 5) {
        printf("usage: %s <pause port> <time out port> <ip> <time out>\n", argv[0]);
        exit(1);
    }

    int result, timeout = atoi(argv[4]);
    string message;
    char line[256];

    printf("Connecting to the paused server...\n");
    TCPConnector* connector = new TCPConnector();
    TCPStream* stream = connector->connect(argv[3], atoi(argv[1]), timeout);
    if (stream == NULL) {
        printf("Timed out connecting to the server\n");
    }

    printf("Connecting to the time out server...\n");
    stream = connector->connect(argv[3], atoi(argv[2]), timeout);
    if (stream) {
        message = "Is there life on Mars?";
        stream->send(message.c_str(), message.size());
        printf("sent - %s\n", message.c_str());
        result = stream->receive(line, sizeof(line), timeout);
        if (result == TCPStream::connectionTimedOut) {
            printf("Timed out waiting for a server response\n");
        }
        delete stream;
    }

    exit(0);
}