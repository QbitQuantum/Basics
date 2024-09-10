VOID
main(
    int argc,
    char *argv[]
    )
{
    DWORD i;
    NET_API_STATUS status;
#ifdef UNICODE
    LPWSTR ToName;
    LPWSTR Message;
#else
    LPSTR ToName;
    LPSTR Message;
#endif

    if (argc != 3) {
        printf("Usage: wstsend <recipient> <message>.\n");
        return;
    }

#ifdef UNICODE
    ToName = NetpAllocWStrFromStr(_strupr(argv[1]));

    if (ToName == NULL) {
        printf("Could not convert the receipient name.\n");
        return;
    }

    Message = NetpAllocWStrFromStr(argv[2]);

    if (ToName == NULL) {
        printf("Could not convert the message.\n");
        NetApiBufferFree(ToName);
        return;
    }
#else
    ToName = _strupr(argv[1]);
    Message = argv[2];
#endif


    if ((status = NetMessageBufferSend(
                     NULL,
                     ToName,             // To
                     NULL,
                     Message,            // Message to send
                     STRLEN(Message) * sizeof(TCHAR)
                     )) != NERR_Success) {

        printf("Failed in sending message to %s %lu\n", argv[1], status);
        printf("Message is %s\n", argv[2]);
    }
    else {
        printf("Message sent successfully\n");
    }

#ifdef UNICODE
    NetApiBufferFree(ToName);
    NetApiBufferFree(Message);
#endif
}