// ---------------------------------------------------------------------------
void __fastcall FtpControl::Execute()
{
	DWORD nopwait = 0;
	DWORD nopcmdtm = GetTickCount();
	DWORD secondtm = GetTickCount();
	NameThreadForDebugging("FtpControl");

	fdeb("FtpControl thread %x", GetCurrentThreadId());

	// Priority = tpIdle;

	fce = new TEvent(false);

	while (true)
	{
		Sleep(50);

		if (GetTickCount() - secondtm >= 1000)
		{
			secondtm = GetTickCount();
			call_events(E_SECOND, (LPVOID)rand());
		}
//
//		if (GetTickCount() - nopcmdtm >= nopwait)
//		{
//			nopwait = 23400 + (rand() % 13400);
//
//			if (!FtpSocket || processing_disk_event)
//				continue;
//
//			char *cmds[] =
//			{
//				"NOp", "fEAT", "NooP", "STAT", "HELP", "TYPE", "SYST", "PWD"
//			};
//
//			int num = rand() % 8;
//
//			ftplock();
//
//			ftpcmd(cmds[num], 0, 0);
//
//			char b[11111];
//			ftprl(b, timeoutst, 0);
//
//			while (ftphasdata())
//				ftprl(b, timeoutst, 0);
//
//			ftpunlock();
//
//			// ftpunlock();
//
//			nopcmdtm = GetTickCount();
//		 }

		if (!ccs)
			continue;

		ccs->Enter();

		for (vector<CACHE>::iterator it = cache.begin(); it != cache.end(); it++)
		{

			if (GetTickCount() - (*it).lastaccessed >= 10000)
			{
				try
				{
					if ((SIZE_T)HeapSize(GetProcessHeap(), 0, (*it).buf) != (SIZE_T) - 1)
					{
						// fdeb(E_CACHEMSG, "cache: freeing %7lu bytes (%7lu in records) of '%s' @ %08X",
						// HeapSize(GetProcessHeap(), 0, (*it).buf), (*it).size, (*it).fn, (*it).buf);

						int numcaches = ((int)cache.size()) - 1;
						unsigned long heapsiz;
						heapsiz = (unsigned long)HeapSize(GetProcessHeap(), 0, (*it).buf);

						HeapFree(GetProcessHeap(), 0, (*it).buf);
						it = cache.erase(it);

						call_events(E_CACHEFREED, (LPVOID)(*it).buf, (LPVOID)(*it).fn, (LPVOID)heapsiz,
							(LPVOID)(*it).offset, (LPVOID)numcaches);

						if (it == cache.end())
							break;
					}
					else
					{
						deb(E_FTPCONTROL, "cache block @ %p for '%s' size: %lu is not heap allocated!",
							(*it).buf, (*it).fn, (*it).size);
					}
				}
				catch(...)
				{
					exp;
				}
			}
			//
			// // decrease blocks
			// unsigned long maxcachebufsize = precacheminbytes; // 8 * 1024 * 1024;
			// if ((*it).bufsize > maxcachebufsize)
			// {
			// unsigned long newsiz = maxcachebufsize - 512000;
			// memcpy((*it).buf, (void*)((unsigned long)(*it).buf + (unsigned long)(*it).size -
			// (unsigned long)maxcachebufsize), newsiz);
			//
			// (*it).buf = HeapReAlloc(GetProcessHeap(), 0, (*it).buf, newsiz);
			// cache_list();
			// deb(E_CACHEMSG, "cache block %p truncated from %lu to %lu", (*it).buf, (*it).bufsize,
			// newsiz);
			//
			//
			// (*it).offset += ((*it).bufsize - newsiz);
			// if (!(*it).buf)
			// ds;
			// (*it).size = newsiz;
			// (*it).bufsize = newsiz;
			// }

		}
		ccs->Leave();

		// fdeb(E_CACHEMSG,"check for cache");

		files_sort_diskevent();

		int seqreads;
		seqreads = cache_seq_reads();

		for (vector<FATFILE>::iterator it = files.begin(); it != files.end(); it++)
		{

			if (GetTickCount() - (*it).lastaccessed >= 2000)
			{
				(*it).sequential_reads = 0;

			}

			if ((*it).lastlen && GetTickCount() - (*it).lastdisktime <= 1500)
			{
				// fdeb("checking %s", (*it).fn);
				unsigned long precachesize = 0;
				unsigned long readoffset = 0;
				unsigned long flen = 0;

				unsigned long stofs = 0; // (*it).lastoffset + (*it).lastlen;

				if (!(*it).sequential_reads)
				{
					// fdeb(E_CACHEMSG, "have another %lu bytes @ %lu", (*it).lastlen * 10,
					// stofs - (*it).lastoffset + (*it).lastlen);
					// fdeb( "skip sequential_read");
					continue;

				}
				else
				{
					// fdeb(E_CACHEMSG, "sequential_reads %lu, cache %lu @ %lu", (*it).sequential_reads,
					// (*it).nextcachelen, (*it).nextcacheoffset);

					if (in_cache((*it).dosfn, (*it).lastoffset, (*it).nextcachelen))
					{
						// fdeb("skip precache");
						continue;
					}
				}

				// stofs = highcacheoffset((*it).dosfn);
				// stofs = seqcacheoffset((*it).dosfn);
				stofs = (*it).nextcacheoffset;
				if (stofs <= 65535)
					stofs = 0;
				deb("nextcachelen=%lu", (*it).nextcachelen);
				flen = (*it).nextcachelen;
				if (!flen)
					flen = (*it).nextcachelen ;
				if (!flen)
					flen = 512000;
				(*it).nowcaching = true;
				(*it).nowcachingoffset = stofs;
				(*it).nowcachinglen = flen;
				strcpy(nowcachingdosfn, (*it).dosfn);
				// fdeb(E_CACHEMSG, "seqcacheoffset %lu", stofs);

				if (!ftptrylock())
					continue;

				char curdir[255];
				int code = 250;
				strncpy(curdir, ftpcurdir, sizeof(curdir));
				fdeb("allocating %lu bytes", flen);
				char *buf = (char*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, flen);
				fdeb("flen %lu, buf @ %p %lu", flen, buf, HeapSize(GetProcessHeap(), 0, buf));
				// ftpcs->Enter();
				// fdeb("

				if (strcmpi((*it).ftppath, ftpcurdir) != 0)
				{

					ftpcd("/");
					code = 250;

					if (strlen((*it).ftppath))
						code = ftpcd((*it).ftppath);

					if (code != 250)
					{
						ftpcd("/");
						// ecs->Leave();
						// processing_disk_event = false;
						// ftpcs->Leave();
						ftpunlock();
						continue;
					}

					strcpy(ftpcurdir, (*it).ftppath);
				}

				fdeb("caching %lu '%s' @ %lu  ", flen, (*it).fn, stofs);

				call_events(E_STARTPRECACHE, (LPVOID)(*it).fn, (LPVOID)flen, (LPVOID)stofs);

				fdeb("ftpgetfile(%-15s, %8lu, %8p, %8lu)", (*it).fn, (unsigned long)stofs, buf,
					(unsigned long)flen);

				call_events(E_FTPPREGETFILE, (LPVOID)(*it).ftppath, (LPVOID)(*it).fn, (LPVOID)stofs,
					(LPVOID)buf, (LPVOID)flen);

				DWORD ftpgettm = GetTickCount();

				unsigned long nrd = ftpgetfile((*it).fn, (unsigned long)stofs, (char*)buf, flen,
					(*it).dosfn, 65535, stofs);

				ftpunlock(); // ftpcs->Leave();

				HeapFree(GetProcessHeap(), 0, buf);

				(*it).nowcaching = false;

				ftpgettm = GetTickCount() - ftpgettm;

				// fdeb(E_CACHEMSG, "precacheclstrs [%lu]", (*it).precacheclstrs);
				fdeb("ftpgetfile(%-15s, %8lu, %8p, %8lu) = %lu", (*it).fn, (unsigned long)stofs, buf,
					(unsigned long)flen, nrd);

				call_events(E_FTPGETFILE, (LPVOID)(*it).ftppath, (LPVOID)(*it).fn, (LPVOID)stofs,
					(LPVOID)buf, (LPVOID)flen, (LPVOID)ftpcontroltime, (LPVOID)ftpdatatime,
					(LPVOID)nrd);

				if (nrd > 0)
				{
					// cache_save((*it).ftppath, (*it).dosfn, ((unsigned long)stofs), nrd, buf);

					(*it).nextcacheoffset = stofs + flen;
					// (*it).lastoffset = stofs;

				}
				else
				{
					(*it).lastlen = 0;
					fdeb("zero download %lu @ %lu fsize %lu!", flen, stofs, (*it).size);
					// ds;
				}

				nopcmdtm = GetTickCount();

			}
		}

	}
}