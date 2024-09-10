SOCKET
open_ifs_socket(int af, int type, int protocol)
{
    dTHX;
    char *s;
    unsigned long proto_buffers_len = 0;
    int error_code;
    SOCKET out = INVALID_SOCKET;

    if ((s = PerlEnv_getenv("PERL_ALLOW_NON_IFS_LSP")) && atoi(s))
        return WSASocket(af, type, protocol, NULL, 0, 0);

    if (WSCEnumProtocols(NULL, NULL, &proto_buffers_len, &error_code) == SOCKET_ERROR
        && error_code == WSAENOBUFS)
    {
	WSAPROTOCOL_INFOW *proto_buffers;
        int protocols_available = 0;       
 
        Newx(proto_buffers, proto_buffers_len / sizeof(WSAPROTOCOL_INFOW),
            WSAPROTOCOL_INFOW);

        if ((protocols_available = WSCEnumProtocols(NULL, proto_buffers, 
            &proto_buffers_len, &error_code)) != SOCKET_ERROR)
        {
            int i;
            for (i = 0; i < protocols_available; i++)
            {
                WSAPROTOCOL_INFOA proto_info;

                if ((af != AF_UNSPEC && af != proto_buffers[i].iAddressFamily)
                    || (type != proto_buffers[i].iSocketType)
                    || (protocol != 0 && proto_buffers[i].iProtocol != 0 &&
                        protocol != proto_buffers[i].iProtocol))
                    continue;

                if ((proto_buffers[i].dwServiceFlags1 & XP1_IFS_HANDLES) == 0)
                    continue;

                convert_proto_info_w2a(&(proto_buffers[i]), &proto_info);

                out = WSASocket(af, type, protocol, &proto_info, 0, 0);
                break;
            }
        }

        Safefree(proto_buffers);
    }

    return out;
}