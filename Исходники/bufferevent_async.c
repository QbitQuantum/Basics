/* GetQueuedCompletionStatus doesn't reliably yield WSA error codes, so
 * we use WSAGetOverlappedResult to translate. */
static void
bev_async_set_wsa_error(struct bufferevent *bev, struct event_overlapped *eo)
{
	DWORD bytes, flags;
	evutil_socket_t fd;

	fd = _evbuffer_overlapped_get_fd(bev->input);
	WSAGetOverlappedResult(fd, &eo->overlapped, &bytes, FALSE, &flags);
}