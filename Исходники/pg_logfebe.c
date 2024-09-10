/*
 * Useful for HUP triggered reassignment: invalidate the socket, which will
 * cause path information to be evaluated when reconnection and identification
 * to be re-exchanged.
 */
static void
gucOnAssignCloseInvalidate(const char *newval, void *extra)
{
	closeSocket(&outSockFd);
}