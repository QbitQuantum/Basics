__inline
int
getnameinfo (
    IN  const struct sockaddr           *sa,
    IN  socklen_t                       salen,
    OUT char                            *host,
    IN  size_t                          hostlen,
    OUT char                            *serv,
    IN  size_t                          servlen,
    IN  int                             flags)
{
    static WSPIAPI_PGETNAMEINFO     pfGetNameInfo   = NULL;

    if (!pfGetNameInfo)
        pfGetNameInfo   = (WSPIAPI_PGETNAMEINFO) WspiapiLoad(1);
    return ((*pfGetNameInfo)
            (sa, salen, host, hostlen, serv, servlen, flags));
}