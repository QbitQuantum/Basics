static int add_event(struct acrd_handle *ah, enum acrd_event_type type,
		     struct sd_node *node, void *buf,
		     size_t buf_len)
{
	int idx;
	struct sd_node *n;
	uint64_t *i;
	struct acrd_event ev;

	acrd_lock(ah);

	ev.type = type;
	ev.sender = *node;
	ev.buf_len = buf_len;
	if (buf)
		memcpy(ev.buf, buf, buf_len);

	ev.nr_nodes = get_nodes(ah, ev.nodes, ev.ids);

	switch (type) {
	case EVENT_JOIN_REQUEST:
		ev.nodes[ev.nr_nodes] = *node;
		ev.ids[ev.nr_nodes] = this_id; /* must be local node */
		ev.nr_nodes++;
		break;
	case EVENT_LEAVE:
		n = lfind(node, ev.nodes, &ev.nr_nodes, sizeof(*n),
			  node_id_cmp);
		if (!n)
			goto out;
		idx = n - ev.nodes;
		i = ev.ids + idx;

		ev.nr_nodes--;
		memmove(n, n + 1, sizeof(*n) * (ev.nr_nodes - idx));
		memmove(i, i + 1, sizeof(*i) * (ev.nr_nodes - idx));
		break;
	case EVENT_NOTIFY:
	case EVENT_BLOCK:
		break;
	case EVENT_JOIN_RESPONSE:
		abort();
	}

	acrd_queue_push(ah, &ev);
out:
	acrd_unlock(ah);
	return 0;
}