static char *tcp_service_name(int port)
{
#ifdef __linux__
    int r;
    struct servent result_buf;
    struct servent *result;
    char buf[2048];

    r = getservbyport_r(htons(port), "tcp", &result_buf,buf, sizeof(buf), &result);

    /* ignore ERANGE - if the result can't fit in 2k, just return unknown */
    if (r != 0 || result == NULL)
        return "unknown";

    return strdup(result_buf.s_name);
#else
    struct servent *result;

    result = getservbyport(htons((unsigned short)port), "tcp");

    if (result == NULL)
        return "unknown";

    return strdup(result->s_name);
#endif
}