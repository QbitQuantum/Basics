int aio_socket_sendto_v(aio_socket_t socket, const struct sockaddr *addr, socklen_t addrlen, socket_bufvec_t* vec, int n, aio_onsend proc, void* param)
{
	struct aio_context *ctx = (struct aio_context*)socket;
	struct aio_context_action *aio;
	
	aio = util_alloc(ctx);
	aio->action = iocp_send;
	aio->send.proc = proc;
	aio->send.param = param;

	assert(0 == (AIO_WRITE & InterlockedOr(&ctx->flags, AIO_WRITE)));
	if(SOCKET_ERROR == WSASendTo(ctx->socket, vec, (DWORD)n, NULL/*&dwBytes*/, 0, addr, addrlen, &aio->overlapped, NULL))
	{
		return aio_socket_result(aio, AIO_WRITE);
	}
	return 0;
}