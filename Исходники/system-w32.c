/* Return true if HD refers to a socket.  */
static int
is_socket (HANDLE hd)
{
    /* We need to figure out whether we are working on a socket or on a
       handle.  A trivial way would be to check for the return code of
       recv and see if it is WSAENOTSOCK.  However the recv may block
       after the server process died and thus the destroy_reader will
       hang.  Another option is to use getsockopt to test whether it is
       a socket.  The bug here is that once a socket with a certain
       values has been opened, closed and later a CreatePipe returned
       the same value (i.e. handle), getsockopt still believes it is a
       socket.  What we do now is to use a combination of GetFileType
       and GetNamedPipeInfo.  The specs say that the latter may be used
       on anonymous pipes as well.  Note that there are claims that
       since winsocket version 2 ReadFile may be used on a socket but
       only if it is supported by the service provider.  Tests on a
       stock XP using a local TCP socket show that it does not work.  */
    DWORD dummyflags, dummyoutsize, dummyinsize, dummyinst;
    if (GetFileType (hd) == FILE_TYPE_PIPE
            && !GetNamedPipeInfo (hd, &dummyflags, &dummyoutsize,
                                  &dummyinsize, &dummyinst))
        return 1; /* Function failed; thus we assume it is a socket.  */
    else
        return 0; /* Success; this is not a socket.  */
}