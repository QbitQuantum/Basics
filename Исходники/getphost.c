char * 
krb_get_phost(
    char *alias
    )
{
    struct hostent *h;
    char *p;
    /* We keep our own buffer instead of using h->h_name in case someone
       decides to call one of the resolver routines. */
    /* XXX - The buffer is not currently thread-safe */
    /* We cannot simply use __declspec(thread) if our DLL might be
       dynamically loaded with LoadLibrary.  Rather, we must use the
       TLS API.  We wil deal with this later.  Sigh. */
    static char phost[1024]; /* DNS limit is about 975 */

    // INVARIANT: h || return alias at the end of the if-else block below
    h = 0;
    /* Let's add some code to see if someone is passing around an IP address */
    /* note that a DNS name cannot start with a digit */
    if(isdigit(alias[0]))
    {
        unsigned long host_addr;
        host_addr = inet_addr(alias);
        if(host_addr != INADDR_NONE)
            h = GETHOSTBYADDR((char *)&host_addr, sizeof(host_addr), PF_INET);
    } else {
        /* OK, now this will handle the normal case of the application */
        /* passing the machine name rather than the IP address as a string */
        h = GETHOSTBYNAME(alias);
    }
    if (!h)
        return alias;
    if ((strlen(h->h_name) + 1) > sizeof(phost))
        return alias;
    strcpy(phost, h->h_name);
    p = strchr(phost, '.');
    if (p)
        *p = 0;
    p = phost;
    do {
        if (isupper(*p)) *p = tolower(*p);
    } while (*p++);
    return (phost);
}