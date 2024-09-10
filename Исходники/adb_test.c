static void
lookup_callback(isc_task_t *task, isc_event_t *ev) {
	client_t *client;

	client = ev->ev_arg;
	INSIST(client->find == ev->ev_sender);

	printf("NAME %s:\n\tTask %p got event %p type %08x from %p, client %p\n\terr4: %s  err6: %s\n",
	       client->target,
	       task, ev, ev->ev_type, client->find, client,
	       isc_result_totext(client->find->result_v4),
	       isc_result_totext(client->find->result_v6));

	isc_event_free(&ev);
	ev = NULL;

	CLOCK();

	dns_adb_dumpfind(client->find, stderr);
	dns_adb_destroyfind(&client->find);

	ISC_LIST_UNLINK(clients, client, link);
	free_client(&client);

	CUNLOCK();
}