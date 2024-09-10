/*******************************************************************
 return the DNS name of the client 
 ******************************************************************/
char *
client_name (int fd)
{
    struct sockaddr sa;
    struct sockaddr_in *sockin = (struct sockaddr_in *) (&sa);
    unsigned int length = sizeof (sa);
    static pstring name_buf;
    struct hostent *hp;
    static int last_fd = -1;

    if (global_client_name_done && last_fd == fd)
        return name_buf;

    last_fd = fd;
    global_client_name_done = False;

    pstrcpy (name_buf, "UNKNOWN");

    if (fd == -1)
    {
        return name_buf;
    }

    if (getpeername (fd, &sa, &length) < 0)
    {
        DEBUG (0, ("getpeername failed. Error was %s\n", unix_error_string (errno)));
        return name_buf;
    }

    /* Look up the remote host name. */
    if ((hp = gethostbyaddr ((char *) &sockin->sin_addr, sizeof (sockin->sin_addr), AF_INET)) == 0)
    {
        DEBUG (1, ("Gethostbyaddr failed for %s\n", client_addr (fd)));
        StrnCpy (name_buf, client_addr (fd), sizeof (name_buf) - 1);
    }
    else
    {
        StrnCpy (name_buf, (char *) hp->h_name, sizeof (name_buf) - 1);
        if (!matchname (name_buf, sockin->sin_addr))
        {
            DEBUG (0, ("Matchname failed on %s %s\n", name_buf, client_addr (fd)));
            pstrcpy (name_buf, "UNKNOWN");
        }
    }
    global_client_name_done = True;
    return name_buf;
}