static void *uaenet_trap_thread (void *arg)
{
	struct uaenetdatawin32 *sd = arg;
	HANDLE handles[4];
	int cnt, towrite;
	int readactive, writeactive;
	DWORD actual;

	uae_set_thread_priority (NULL, 2);
	sd->threadactive = 1;
	uae_sem_post (&sd->sync_sem);
	readactive = 0;
	writeactive = 0;
	while (sd->threadactive == 1) {
		int donotwait = 0;

		uae_sem_wait (&sd->change_sem);

		if (readactive) {
			if (GetOverlappedResult (sd->hCom, &sd->olr, &actual, FALSE)) {
				readactive = 0;
				uaenet_gotdata (sd->user, sd->readbuffer, actual);
				donotwait = 1;
			}
		}
		if (writeactive) {
			if (GetOverlappedResult (sd->hCom, &sd->olw, &actual, FALSE)) {
				writeactive = 0;
				donotwait = 1;
			}
		}

		if (!readactive) {
			if (!ReadFile (sd->hCom, sd->readbuffer, sd->mtu, &actual, &sd->olr)) {
				DWORD err = GetLastError();
				if (err == ERROR_IO_PENDING)
					readactive = 1;
			} else {
				uaenet_gotdata (sd->user, sd->readbuffer, actual);
				donotwait = 1;
			}
		}

		towrite = 0;
		if (!writeactive && uaenet_getdata (sd->user, sd->writebuffer, &towrite)) {
			donotwait = 1;
			if (!WriteFile (sd->hCom, sd->writebuffer, towrite, &actual, &sd->olw)) {
				DWORD err = GetLastError();
				if (err == ERROR_IO_PENDING)
					writeactive = 1;
			}
		}

		uae_sem_post (&sd->change_sem);

		if (!donotwait) {
			cnt = 0;
			handles[cnt++] = sd->evtt;
			if (readactive)
				handles[cnt++] = sd->olr.hEvent;
			if (writeactive)
				handles[cnt++] = sd->olw.hEvent;
			WaitForMultipleObjects(cnt, handles, FALSE, INFINITE);
		}


	}
	sd->threadactive = 0;
	uae_sem_post (&sd->sync_sem);
	return 0;
}