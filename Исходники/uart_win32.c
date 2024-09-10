static int open_device(uart_ctx_t* ctx, char* name)
{
    ctx->fh = CreateFile(name,
			 GENERIC_READ | GENERIC_WRITE, 
			 0, 
			 0, 
			 OPEN_EXISTING,
			 FILE_FLAG_OVERLAPPED,
			 0);
    if (ctx->fh == INVALID_HANDLE_VALUE) {
	DEBUG_ERROR("CreateFile: invalid handle: error %d", GetLastError());
	goto error;
    }

    if (!(ctx->in.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL))) {
	DEBUG_ERROR("CreateEvent: 1: error %d", GetLastError());
	goto error;
    }

    if (!(ctx->out.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL))) {
	DEBUG_ERROR("CreateEvent: 1: error %d", GetLastError());
	goto error;
    }

    if (!(ctx->stat.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL))) {
	DEBUG_ERROR("CreateEvent: 1: error %d", GetLastError());
	goto error;
    }

    // SetCommMask(wd->fh, EV_RXCHAR);
    WaitCommEvent(ctx->fh, &ctx->statm, &ctx->stat);
    return 0;

error:
    if (ctx->fh != INVALID_HANDLE_VALUE) CloseHandle(ctx->fh);
    if (ctx->in.hEvent) CloseHandle(ctx->in.hEvent);
    if (ctx->out.hEvent) CloseHandle(ctx->out.hEvent);
    if (ctx->stat.hEvent) CloseHandle(ctx->stat.hEvent);
    return -1;
}