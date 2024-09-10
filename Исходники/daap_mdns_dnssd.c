static void
browse_reply (DNSServiceRef client,
              DNSServiceFlags flags,
              uint32_t ifIndex,
              DNSServiceErrorType errorCode,
              const char *replyName,
              const char *replyType,
              const char *replyDomain,
              void *context)
{
	DNSServiceErrorType err;
	GMDNSServer *server;
	GMDNSUserData *ud = context;
	GMDNSUserData *ud2;
	gboolean remove = (flags & kDNSServiceFlagsAdd) ? FALSE : TRUE;

	if (!remove) {
		server = g_new0 (GMDNSServer, 1);
		server->mdnsname = g_strdup (replyName);
		ud2 = g_new0 (GMDNSUserData, 1);
		err = DNSServiceResolve (&ud2->client, 0, kDNSServiceInterfaceIndexAny,
		                         server->mdnsname,
		                         "_daap._tcp", "local",
		                         resolve_reply, ud2);

		if (err != kDNSServiceErr_NoError) {
			g_warning ("Couldn't do ServiceResolv");
			g_free (server->mdnsname);
			g_free (server);
			return;
		}

		ud2->server = server;

		g_mdns_poll_add (ud->mdns, ud2, ud2->client);
	} else {
		GSList *n, *nxt;
		g_mutex_lock (ud->mdns->mutex);
		for (n = ud->mdns->service_list; n; n = nxt) {
			nxt = g_slist_next (n);
			GMDNSServer *server = n->data;
			if (strcmp (server->mdnsname, replyName) == 0) {
				n = ud->mdns->service_list = g_slist_remove (ud->mdns->service_list, server);
				g_mutex_unlock (ud->mdns->mutex);
				if (ud->mdns->callback)
					ud->mdns->callback (ud->mdns, G_MDNS_SERVER_REMOVE, server, ud->mdns->user_data);
				g_mdns_server_destroy (server);
				g_mutex_lock (ud->mdns->mutex);
			}
		}
		g_mutex_unlock (ud->mdns->mutex);
	}

}