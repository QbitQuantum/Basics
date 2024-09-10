void
pubnub_sync_wait(struct pubnub *p, void *ctx_data)
{
	struct pubnub_sync *sync = (struct pubnub_sync *)ctx_data;
	while (!sync->stop) {
		DBGMSG("=polling= for %d (timeout %p)\n", sync->n, sync->timeout_cb);

		long timeout;
		if (sync->timeout_cb) {
			struct timespec now;
			GET_CLOCK_NOW
			timeout = (sync->timeout_at.tv_sec - now.tv_sec) * 1000;
			timeout += (sync->timeout_at.tv_nsec - now.tv_nsec) / 1000000;
			DBGMSG("timeout in %ld ms\n", timeout);
			if (timeout < 0) {
				/* If we missed the timeout moment, just
				 * spin poll() quickly until we are clear
				 * to call the timeout handler. */
				timeout = 0;
			}
		} else {
			timeout = -1;
		}

#ifdef _MSC_VER
		int n = (sync->n ? WSAPoll(sync->fdset, sync->n, timeout) : 0);
#else
		int n = poll(sync->fdset, sync->n, timeout);
#endif

		if (n < 0) {
			/* poll() errors are ignored, it's not clear what
			 * we should do. Most likely, we have just received
			 * a signal and will spin around and restart poll(). */
#ifdef _MSC_VER
			DBGMSG("WSAPoll error: %d\n", WSAGetLastError());
#else
			DBGMSG("poll(): %s\n", strerror(errno));
#endif
			continue;
		}

		if (n == 0) {
			/* Time out, call the handler and reset
			 * timeout. */
			DBGMSG("Timeout, callback and reset\n");
			/* First, we reset sync->timeout_cb, then we
			 * call the timeout handler - likely, that will
			 * cause it to set timeout_cb again, so resetting
			 * timeout_cb only after the call is bad idea. */
			void (*timeout_cb)(struct pubnub *p, void *cb_data) = sync->timeout_cb;
			sync->timeout_cb = NULL;
			if (timeout_cb) {
				timeout_cb(p, sync->timeout_cb_data);
			}
			continue;
		}

		for (int i = 0; i < sync->n; i++) {
			short revents = sync->fdset[i].revents;
			if (!revents)
				continue;
			DBGMSG("event: fd %d ev %d rev %d\n", sync->fdset[i].fd, sync->fdset[i].events, sync->fdset[i].revents);
			int mode = (revents & POLLIN ? 1 : 0) | (revents & POLLOUT ? 2 : 0) | (revents & POLLERR ? 4 : 0);
			sync->cbset[i].cb(p, sync->fdset[i].fd, mode, sync->cbset[i].cb_data);
		}
	}
	sync->stop = false;
}