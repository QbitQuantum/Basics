static void RequestThread(void *vParam)
{
	while (!g_shutDown) {
		EnterCriticalSection(&cs);

		if (queue.getCount() == 0) {
			// No items, so suspend thread
			LeaveCriticalSection(&cs);
			mir_sleep(POOL_DELAY);
			continue;
		}

		// Take a look at first item
		QueueItem& qi = queue[queue.getCount() - 1];
		if (qi.check_time > GetTickCount()) {
			// Not time to request yet, wait...
			LeaveCriticalSection(&cs);
			mir_sleep(POOL_DELAY);
			continue;
		}

		// Will request this item
		MCONTACT hContact = qi.hContact;
		queue.remove(queue.getCount() - 1);
		QueueRemove(hContact);
		LeaveCriticalSection(&cs);

		if (FetchAvatarFor(hContact) == GAIR_WAITFOR) {
			// Mark to not request this contact avatar for more 30 min
				{
					mir_cslock lock(cs);
					QueueRemove(hContact);
					QueueAdd(hContact, REQUEST_WAITFOR_WAIT_TIME);
				}

			// Wait a little until requesting again
			mir_sleep(REQUEST_DELAY);
		}
	}
}