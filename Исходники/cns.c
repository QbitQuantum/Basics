/*
 * This routine is called to cancel a blocking hook call within
 * the Kerberos library.  The need for this routine arises due
 * to bugs which exist in existing WINSOCK implementations.  We
 * blocking gethostbyname with WSAASyncGetHostByName.  In order
 * to cancel such an operation, this routine must be called.
 * Applications may call this routine in addition to calls to
 * WSACancelBlockingCall to get any sucy Async calls canceled.
 * Return values are as they would be for WSACancelAsyncRequest.
 */
int
krb_cancel_blocking_call(void)
{
  if (htaskasync == NULL)
    return 0;
  iscompleted = TRUE;

  return WSACancelAsyncRequest(htask);
}