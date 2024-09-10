ICMP_CHAT *icmp_chat_create(ACL_AIO* aio, int check_tid)
{
	ICMP_CHAT *chat;

	chat = (ICMP_CHAT*) acl_mycalloc(1, sizeof(ICMP_CHAT));
	chat->aio = aio;
	acl_ring_init(&chat->host_head);
	chat->is = icmp_stream_open(aio);
	chat->seq_no = 0;
	chat->count = 0;
#ifdef ACL_UNIX
	chat->pid = getpid();
#elif defined(ACL_WINDOWS)
	chat->pid = _getpid();
#endif
	chat->tid = (unsigned long) acl_pthread_self();
	chat->check_tid = check_tid;

	if (aio != NULL)
		icmp_chat_aio_init(chat, aio);
	else
		icmp_chat_sio_init(chat);

	return (chat);
}