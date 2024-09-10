static DWORD WINAPI handle_output_threadfunc(void *param)
{
    struct handle_output *ctx = (struct handle_output *) param;
    OVERLAPPED ovl, *povl;
    HANDLE oev;
    int writeret;

    if (ctx->flags & HANDLE_FLAG_OVERLAPPED) {
	povl = &ovl;
	oev = CreateEvent(NULL, TRUE, FALSE, NULL);
    } else {
	povl = NULL;
    }

    while (1) {
	WaitForSingleObject(ctx->ev_from_main, INFINITE);
	if (ctx->done) {
            /*
             * The main thread has asked us to shut down. Send back an
             * event indicating that we've done so. Hereafter we must
             * not touch ctx at all, because the main thread might
             * have freed it.
             */
	    SetEvent(ctx->ev_to_main);
	    break;
	}
	if (povl) {
	    memset(povl, 0, sizeof(OVERLAPPED));
	    povl->hEvent = oev;
	}

	writeret = WriteFile(ctx->h, ctx->buffer, ctx->len,
			     &ctx->lenwritten, povl);
	if (!writeret)
	    ctx->writeerr = GetLastError();
	else
	    ctx->writeerr = 0;
	if (povl && !writeret && GetLastError() == ERROR_IO_PENDING) {
	    writeret = GetOverlappedResult(ctx->h, povl,
					   &ctx->lenwritten, TRUE);
	    if (!writeret)
		ctx->writeerr = GetLastError();
	    else
		ctx->writeerr = 0;
	}

	SetEvent(ctx->ev_to_main);
	if (!writeret) {
            /*
             * The write operation has suffered an error. Telling that
             * to the main thread will cause it to set its 'defunct'
             * flag and dispose of the handle structure at the next
             * opportunity, so we must not touch ctx at all after
             * this.
             */
	    break;
        }
    }

    if (povl)
	CloseHandle(oev);

    return 0;
}