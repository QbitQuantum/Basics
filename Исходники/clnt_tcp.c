CLIENT *
clnttcp_create (struct sockaddr_in *raddr, u_long prog, u_long vers,
		int *sockp, u_int sendsz, u_int recvsz)
{
  CLIENT *h;
  struct ct_data *ct;
  struct rpc_msg call_msg;

  h = (CLIENT *) mem_alloc (sizeof (*h));
  ct = (struct ct_data *) mem_alloc (sizeof (*ct));
  if (h == NULL || ct == NULL)
    {
      struct rpc_createerr *ce = &get_rpc_createerr ();
#ifdef USE_IN_LIBIO
      if (_IO_fwide (stderr, 0) > 0)
	(void) fwprintf (stderr, L"%s",
			   _("clnttcp_create: out of memory\n"));
      else
#endif
	(void) fputs (_("clnttcp_create: out of memory\n"), stderr);
      ce->cf_stat = RPC_SYSTEMERROR;
      ce->cf_error.re_errno = ENOMEM;
      goto fooy;
    }

  /*
   * If no port number given ask the pmap for one
   */
  if (raddr->sin_port == 0)
    {
      u_short port;
      if ((port = pmap_getport (raddr, prog, vers, IPPROTO_TCP)) == 0)
	{
	  mem_free ((caddr_t) ct, sizeof (struct ct_data));
	  mem_free ((caddr_t) h, sizeof (CLIENT));
	  return ((CLIENT *) NULL);
	}
      raddr->sin_port = htons (port);
    }

  /*
   * If no socket given, open one
   */
  if (*sockp < 0)
    {
      *sockp = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
      (void) bindresvport (*sockp, (struct sockaddr_in *) 0);
      if ((*sockp < 0)
	  || (connect (*sockp, (struct sockaddr *) raddr,
			 sizeof (*raddr)) < 0))
	{
	  struct rpc_createerr *ce = &get_rpc_createerr ();
	  ce->cf_stat = RPC_SYSTEMERROR;
	  ce->cf_error.re_errno = errno;
	  if (*sockp >= 0)
	    (void) close (*sockp);
	  goto fooy;
	}
      ct->ct_closeit = TRUE;
    }
  else
    {
      ct->ct_closeit = FALSE;
    }

  /*
   * Set up private data struct
   */
  ct->ct_sock = *sockp;
  ct->ct_wait.tv_usec = 0;
  ct->ct_waitset = FALSE;
  ct->ct_addr = *raddr;

  /*
   * Initialize call message
   */
  call_msg.rm_xid = _create_xid ();
  call_msg.rm_direction = CALL;
  call_msg.rm_call.cb_rpcvers = RPC_MSG_VERSION;
  call_msg.rm_call.cb_prog = prog;
  call_msg.rm_call.cb_vers = vers;

  /*
   * pre-serialize the static part of the call msg and stash it away
   */
  xdrmem_create (&(ct->ct_xdrs), ct->ct_mcall, MCALL_MSG_SIZE,
		 XDR_ENCODE);
  if (!xdr_callhdr (&(ct->ct_xdrs), &call_msg))
    {
      if (ct->ct_closeit)
	{
	  (void) close (*sockp);
	}
      goto fooy;
    }
  ct->ct_mpos = XDR_GETPOS (&(ct->ct_xdrs));
  XDR_DESTROY (&(ct->ct_xdrs));

  /*
   * Create a client handle which uses xdrrec for serialization
   * and authnone for authentication.
   */
  xdrrec_create (&(ct->ct_xdrs), sendsz, recvsz,
		 (caddr_t) ct, readtcp, writetcp);
  h->cl_ops = &tcp_ops;
  h->cl_private = (caddr_t) ct;
  h->cl_auth = authnone_create ();
  return h;

fooy:
  /*
   * Something goofed, free stuff and barf
   */
  mem_free ((caddr_t) ct, sizeof (struct ct_data));
  mem_free ((caddr_t) h, sizeof (CLIENT));
  return ((CLIENT *) NULL);
}