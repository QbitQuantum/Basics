/*
 * Function: socket_connection
 *
 * Purpose: Opens the network connection with the mail host, without
 * 	doing any sort of I/O with it or anything.
 *
 * Arguments:
 * 	host	The host to which to connect.
 *	flags	Option flags.
 *
 * Return value: A file descriptor indicating the connection, or -1
 * 	indicating failure, in which case an error has been copied
 * 	into pop_error.
 */
static int
socket_connection (char *host, int flags)
{
#ifdef HAVE_GETADDRINFO
  struct addrinfo *res, *it;
  struct addrinfo hints;
  int ret;
#else /* !HAVE_GETADDRINFO */
  struct hostent *hostent;
#endif
  struct servent *servent;
  struct sockaddr_in addr;
  char found_port = 0;
  const char *service;
  int sock;
  char *realhost;
#ifdef KERBEROS
#ifdef KERBEROS5
  krb5_error_code rem;
  krb5_context kcontext = 0;
  krb5_auth_context auth_context = 0;
  krb5_ccache ccdef;
  krb5_principal client, server;
  krb5_error *err_ret;
  register char *cp;
#else
  KTEXT ticket;
  MSG_DAT msg_data;
  CREDENTIALS cred;
  Key_schedule schedule;
  int rem;
#endif /* KERBEROS5 */
#endif /* KERBEROS */

  int try_count = 0;
  int connect_ok;

#ifdef WINDOWSNT
  {
    WSADATA winsockData;
    if (WSAStartup (0x101, &winsockData) == 0)
      have_winsock = 1;
  }
#endif

  memset (&addr, 0, sizeof (addr));
  addr.sin_family = AF_INET;

  /** "kpop" service is  never used: look for 20060515 to see why **/
#ifdef KERBEROS
  service = (flags & POP_NO_KERBEROS) ? POP_SERVICE : KPOP_SERVICE;
#else
  service = POP_SERVICE;
#endif

#ifdef HESIOD
  if (! (flags & POP_NO_HESIOD))
    {
      servent = hes_getservbyname (service, "tcp");
      if (servent)
	{
	  addr.sin_port = servent->s_port;
	  found_port = 1;
	}
    }
#endif
  if (! found_port)
    {
      servent = getservbyname (service, "tcp");
      if (servent)
	{
	  addr.sin_port = servent->s_port;
	}
      else
	{
  /** "kpop" service is  never used: look for 20060515 to see why **/
#ifdef KERBEROS
	  addr.sin_port = htons ((flags & POP_NO_KERBEROS) ?
				POP_PORT : KPOP_PORT);
#else
	  addr.sin_port = htons (POP_PORT);
#endif
	}
    }

#define POP_SOCKET_ERROR "Could not create socket for POP connection: "

  sock = socket (PF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    {
      snprintf (pop_error, ERROR_MAX, "%s%s",
		POP_SOCKET_ERROR, strerror (errno));
      return (-1);

    }

#ifdef HAVE_GETADDRINFO
  memset (&hints, 0, sizeof (hints));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_CANONNAME;
  hints.ai_family = AF_INET;
  do
    {
      ret = getaddrinfo (host, service, &hints, &res);
      try_count++;
      if (ret != 0 && (ret != EAI_AGAIN || try_count == 5))
	{
	  strcpy (pop_error, "Could not determine POP server's address");
	  return (-1);
	}
    } while (ret != 0);

  if (ret == 0)
    {
      it = res;
      while (it)
        {
          if (it->ai_addrlen == sizeof (addr))
            {
              struct sockaddr_in *in_a = (struct sockaddr_in *) it->ai_addr;
              memcpy (&addr.sin_addr, &in_a->sin_addr, sizeof (addr.sin_addr));
              if (! connect (sock, (struct sockaddr *) &addr, sizeof (addr)))
                break;
            }
          it = it->ai_next;
        }
      connect_ok = it != NULL;
      if (connect_ok)
        {
          realhost = alloca (strlen (it->ai_canonname) + 1);
          strcpy (realhost, it->ai_canonname);
        }
      freeaddrinfo (res);
    }
#else /* !HAVE_GETADDRINFO */
  do
    {
      hostent = gethostbyname (host);
      try_count++;
      if ((! hostent) && ((h_errno != TRY_AGAIN) || (try_count == 5)))
	{
	  strcpy (pop_error, "Could not determine POP server's address");
	  return (-1);
	}
    } while (! hostent);

  while (*hostent->h_addr_list)
    {
      memcpy (&addr.sin_addr, *hostent->h_addr_list, hostent->h_length);
      if (! connect (sock, (struct sockaddr *) &addr, sizeof (addr)))
	break;
      hostent->h_addr_list++;
    }
  connect_ok = *hostent->h_addr_list != NULL;
  if (! connect_ok)
    {
      realhost = alloca (strlen (hostent->h_name) + 1);
      strcpy (realhost, hostent->h_name);
    }

#endif /* !HAVE_GETADDRINFO */

#define CONNECT_ERROR "Could not connect to POP server: "

  if (! connect_ok)
    {
      CLOSESOCKET (sock);
      snprintf (pop_error, ERROR_MAX, "%s%s", CONNECT_ERROR, strerror (errno));
      return (-1);

    }

#ifdef KERBEROS

#define KRB_ERROR "Kerberos error connecting to POP server: "
  if (! (flags & POP_NO_KERBEROS))
    {
#ifdef KERBEROS5
      if ((rem = krb5_init_context (&kcontext)))
	{
	krb5error:
	  if (auth_context)
	    krb5_auth_con_free (kcontext, auth_context);
	  if (kcontext)
	    krb5_free_context (kcontext);
	  snprintf (pop_error, ERROR_MAX, "%s%s",
		    KRB_ERROR, error_message (rem));
	  CLOSESOCKET (sock);
	  return (-1);
	}

      if ((rem = krb5_auth_con_init (kcontext, &auth_context)))
	goto krb5error;

      if (rem = krb5_cc_default (kcontext, &ccdef))
	goto krb5error;

      if (rem = krb5_cc_get_principal (kcontext, ccdef, &client))
	goto krb5error;

      for (cp = realhost; *cp; cp++)
	{
	  if (isupper (*cp))
	    {
	      *cp = tolower (*cp);
	    }
	}

      if (rem = krb5_sname_to_principal (kcontext, realhost,
					 POP_SERVICE, FALSE, &server))
	goto krb5error;

      rem = krb5_sendauth (kcontext, &auth_context,
			   (krb5_pointer) &sock, "KPOPV1.0", client, server,
			  AP_OPTS_MUTUAL_REQUIRED,
			  0,	/* no checksum */
			  0,	/* no creds, use ccache instead */
			  ccdef,
			  &err_ret,
			  0,	/* don't need subsession key */
			  0);	/* don't need reply */
      krb5_free_principal (kcontext, server);
      if (rem)
	{
	  int pop_error_len = snprintf (pop_error, ERROR_MAX, "%s%s",
					KRB_ERROR, error_message (rem));
#if defined HAVE_KRB5_ERROR_TEXT
	  if (err_ret && err_ret->text.length)
	    {
	      int errlen = err_ret->text.length;
	      snprintf (pop_error + pop_error_len, ERROR_MAX - pop_error_len,
			" [server says '.*%s']", errlen, err_ret->text.data);
	    }
#elif defined HAVE_KRB5_ERROR_E_TEXT
	  if (err_ret && err_ret->e_text && **err_ret->e_text)
	    snprintf (pop_error + pop_error_len, ERRMAX - pop_error_len,
		      " [server says '%s']", *err_ret->e_text);
#endif
	  if (err_ret)
	    krb5_free_error (kcontext, err_ret);
	  krb5_auth_con_free (kcontext, auth_context);
	  krb5_free_context (kcontext);

	  CLOSESOCKET (sock);
	  return (-1);
	}
#else  /* ! KERBEROS5 */
      ticket = (KTEXT) malloc (sizeof (KTEXT_ST));
      rem = krb_sendauth (0L, sock, ticket, "pop", realhost,
			  (char *) krb_realmofhost (realhost),
			  (unsigned long) 0, &msg_data, &cred, schedule,
			  (struct sockaddr_in *) 0,
			  (struct sockaddr_in *) 0,
			  "KPOPV0.1");
      free ((char *) ticket);
      if (rem != KSUCCESS)
	{
	  snprintf (pop_error, ERROR_MAX, "%s%s", KRB_ERROR, krb_err_txt[rem]);
	  CLOSESOCKET (sock);
	  return (-1);
	}
#endif /* KERBEROS5 */
    }
#endif /* KERBEROS */

  return (sock);
} /* socket_connection */