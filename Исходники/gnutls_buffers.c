static ssize_t
_gnutls_dgram_read (gnutls_session_t session, mbuffer_st **bufel,
		    gnutls_pull_func pull_func)
{
  ssize_t i, ret;
  char *ptr;
  size_t max_size = _gnutls_get_max_decrypted_data(session);
  size_t recv_size = MAX_RECV_SIZE(session);
  gnutls_transport_ptr_t fd = session->internals.transport_recv_ptr;

  if (recv_size > max_size)
    recv_size = max_size;

  *bufel = _mbuffer_alloc (0, max_size);
  if (*bufel == NULL)
    return gnutls_assert_val(GNUTLS_E_MEMORY_ERROR);

  ptr = (*bufel)->msg.data;

  session->internals.direction = 0;

  reset_errno (session);
  i = pull_func (fd, ptr, recv_size);

  if (i < 0)
    {
      int err = get_errno (session);

      _gnutls_read_log ("READ: %d returned from %p, errno=%d gerrno=%d\n",
			(int) i, fd, errno, session->internals.errnum);

      if (err == EAGAIN)
        {
          ret = GNUTLS_E_AGAIN;
          goto cleanup;
        }
      else if (err == EINTR)
        {
          ret = GNUTLS_E_INTERRUPTED;
          goto cleanup;
        }
      else
        {
          gnutls_assert ();
          ret = GNUTLS_E_PULL_ERROR;
          goto cleanup;
        }
    }
  else
    {
      _gnutls_read_log ("READ: Got %d bytes from %p\n", (int) i, fd);
      if (i == 0) 
        {
          /* If we get here, we likely have a stream socket.
           * FIXME: this probably breaks DCCP. */
          gnutls_assert ();
          ret = 0;
          goto cleanup;
        }

      _mbuffer_set_udata_size (*bufel, i);
    }

  _gnutls_read_log ("READ: read %d bytes from %p\n", (int) i, fd);
  
  return i;
  
cleanup:
  _mbuffer_xfree(bufel);
  return ret;
}