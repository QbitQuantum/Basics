/* Socket create(destination, port[, buffering]) */
static AValue SocketCreate(AThread *t, AValue *frame)
{
    char addressStr[MAX_ADDRESS_LEN];
    int handle;
    struct sockaddr_in address;
    int port;

    /* Get host name. */
    AGetStr(t, frame[1], addressStr, MAX_ADDRESS_LEN);

    /* Get port number. */
    port = AGetInt(t, frame[2]);

    /* Get buffering mode. */
    if (AIsDefault(frame[3]))
        frame[1] = AGlobalByNum(AUnbufferedNum);
    else if (frame[3] == AGlobalByNum(AUnbufferedNum) ||
             frame[3] == AGlobalByNum(ALineBufferedNum) ||
             frame[3] == AGlobalByNum(ABufferedNum))
        frame[1] = frame[3];
    else
        return ARaiseValueError(t, "Invalid arguments");

    frame[2] = AGlobalByNum(AInputNum);
    frame[3] = AGlobalByNum(AOutputNum);
    frame[4] = AGlobalByNum(ANarrowNum);

    if (AIsError(AStreamCreate(t, frame)))
        return AError;

    /* Initialize address structure. */
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    /* GetHostByName can handle both numeric IP addresses and host names. */
    if (!GetHostByName(t, addressStr, &address.sin_addr))
        return AError;

    /* Create socket. */
    handle = socket(AF_INET, SOCK_STREAM, 0);
    if (handle < 0)
        return RaiseSocketError(t);

    /* Create connection. */
    for (;;) {
        int status;

        AAllowBlocking();
        status = connect(handle, (struct sockaddr *)&address,
                         sizeof(address));
        AEndBlocking();

        if (status < 0) {
            if (errno == EINTR) {
                if (AIsInterrupt && AHandleInterrupt(t))
                    return AError;
                else
                    continue;
            } else {
                RaiseSocketError(t);
                close(handle);
                return AError;
            }
        }
        break;
    }

    frame[1] = AMakeInt(t, handle);
    ASetMemberDirect(t, frame[0], A_FILE_ID, frame[1]);

    return frame[0];
}