/*@
   bwritev - writev

   Parameters:
+  int bfd - bsocket
.  B_VECTOR *pIOVec - iovec structure
-  int n - length of iovec

   Notes:
@*/
int bwritev(int bfd, B_VECTOR *pIOVec, int n)
{
#ifdef HAVE_WINSOCK2_H
#ifdef DBG_BWRITEV
    int i;
#endif
    DWORD dwNumSent = 0;
    if (n == 0)
	return 0;
#ifdef DBG_BWRITEV
    printf("(bwritev");
    for (i=0; i<n; i++)
	printf(":%d", pIOVec[i].B_VECTOR_LEN);
#endif
    if (WSASend(bfd, pIOVec, n, &dwNumSent, 0, NULL/*overlapped*/, NULL/*completion routine*/) == SOCKET_ERROR)
    {
	if (WSAGetLastError() != WSAEWOULDBLOCK)
	{
	    return SOCKET_ERROR;
	}
    }
    DBG_BWRITEV_PRINT(("->%d)", dwNumSent));
    return dwNumSent;
#else
    return writev(bfd, pIOVec, n);
#endif
}