/* handle Telnet better */
int FTP_Socket::recvSocket(char *message)
{
    Uint32 result;

    /* get the string buffer over the socket */
    result = SDLNet_TCP_Recv(controlSocket, message, 8192);
    // TCP Connection is broken. (because of error or closure)
    if(result <= 0)
    {
        onExit();
        return -1;
    }
    /* return the new buffer */
    return result;
}