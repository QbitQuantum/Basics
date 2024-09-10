static int
proto (int sock, const char *service)
{
    struct sockaddr_storage remote, local;
    socklen_t addrlen;
    krb5_address remote_addr, local_addr;
    krb5_ccache ccache;
    krb5_auth_context auth_context;
    krb5_error_code status;
    krb5_data packet;
    krb5_data data;
    krb5_data client_name;
    krb5_creds in_creds, *out_creds;

    addrlen = sizeof(local);
    if (getsockname (sock, (struct sockaddr *)&local, &addrlen) < 0
	|| addrlen > sizeof(local))
	err (1, "getsockname)");

    addrlen = sizeof(remote);
    if (getpeername (sock, (struct sockaddr *)&remote, &addrlen) < 0
	|| addrlen > sizeof(remote))
	err (1, "getpeername");

    status = krb5_auth_con_init (context, &auth_context);
    if (status)
	krb5_err(context, 1, status, "krb5_auth_con_init");

    status = krb5_sockaddr2address (context, (struct sockaddr *)&local, &local_addr);
    if (status)
	krb5_err(context, 1, status, "krb5_sockaddr2address(local)");
    status = krb5_sockaddr2address (context, (struct sockaddr *)&remote, &remote_addr);
    if (status)
	krb5_err(context, 1, status, "krb5_sockaddr2address(remote)");

    status = krb5_auth_con_setaddrs (context,
				     auth_context,
				     &local_addr,
				     &remote_addr);
    if (status)
	krb5_err(context, 1, status, "krb5_auth_con_setaddr");

    status = krb5_read_message(context, &sock, &client_name);
    if(status)
	krb5_err(context, 1, status, "krb5_read_message");

    memset(&in_creds, 0, sizeof(in_creds));
    status = krb5_cc_default(context, &ccache);
    if(status)
	krb5_err(context, 1, status, "krb5_cc_default");
    status = krb5_cc_get_principal(context, ccache, &in_creds.client);
    if(status)
	krb5_err(context, 1, status, "krb5_cc_get_principal");

    status = krb5_read_message(context, &sock, &in_creds.second_ticket);
    if(status)
	krb5_err(context, 1, status, "krb5_read_message");

    status = krb5_parse_name(context, client_name.data, &in_creds.server);
    if(status)
	krb5_err(context, 1, status, "krb5_parse_name");

    status = krb5_get_credentials(context, KRB5_GC_USER_USER, ccache,
				  &in_creds, &out_creds);
    if(status)
	krb5_err(context, 1, status, "krb5_get_credentials");

    status = krb5_cc_default(context, &ccache);
    if(status)
	krb5_err(context, 1, status, "krb5_cc_default");

    status = krb5_sendauth(context,
			   &auth_context,
			   &sock,
			   VERSION,
			   in_creds.client,
			   in_creds.server,
			   AP_OPTS_USE_SESSION_KEY,
			   NULL,
			   out_creds,
			   ccache,
			   NULL,
			   NULL,
			   NULL);

    if (status)
	krb5_err(context, 1, status, "krb5_sendauth");

    {
	char *str;
	krb5_unparse_name(context, in_creds.server, &str);
	printf ("User is `%s'\n", str);
	free(str);
	krb5_unparse_name(context, in_creds.client, &str);
	printf ("Server is `%s'\n", str);
	free(str);
    }

    krb5_data_zero (&data);
    krb5_data_zero (&packet);

    status = krb5_read_message(context, &sock, &packet);
    if(status)
	krb5_err(context, 1, status, "krb5_read_message");

    status = krb5_rd_safe (context,
			   auth_context,
			   &packet,
			   &data,
			   NULL);
    if (status)
	krb5_err(context, 1, status, "krb5_rd_safe");

    printf ("safe packet: %.*s\n", (int)data.length,
	    (char *)data.data);

    status = krb5_read_message(context, &sock, &packet);
    if(status)
	krb5_err(context, 1, status, "krb5_read_message");

    status = krb5_rd_priv (context,
			   auth_context,
			   &packet,
			   &data,
			   NULL);
    if (status)
	krb5_err(context, 1, status, "krb5_rd_priv");

    printf ("priv packet: %.*s\n", (int)data.length,
	    (char *)data.data);

    return 0;
}