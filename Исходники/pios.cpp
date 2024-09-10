void PIOS::do_one_run(void *data)
{
	ThreadLocalData *tld = (ThreadLocalData *) data;
	run_arg *args = (run_arg *)tld->v;
	
	switch (tld->state) {
	case pios_RunOneStartState: {
		int i;

		args->startime = Event::Clock();
		Print(NOW "Start run: T %lu N %llu C %llu S %llu O %llu\n",
			args->startime, args->threadcount, args->regioncount,
			args->chunksize, args->regionsize, args->offset);

		/* Setup stream */
		args->streams = new pios_stream [args->regioncount];
		for (i = 0; i < args->regioncount; i++) {
			if (args->fpp) {
				args->streams[i].fid = i;
				args->streams[i].offset = args->offset;
				args->streams[i].max_offset = args->offset + args->regionsize;
				args->num_open_files++;
			} else {
				args->streams[i].fid = 0;
				args->streams[i].offset = args->offset * i;
				args->streams[i].max_offset = args->offset * i + args->regionsize;
			}
			args->streams[i].iotime = 0;
		}

		/* Setup pios thread data */
		args->ptds = new pios_thdata [args->threadcount];
		args->tlds = new ThreadLocalData [args->threadcount];

		memset(args->ptds, 0, sizeof(pios_thdata) * args->threadcount);
		memset(args->tlds, 0, sizeof(ThreadLocalData) * args->threadcount);
		for (i = 0; i < args->threadcount; i++) {
			Thread *t;

			t = new Thread;

			args->ptds[i].parent = tld->t;
			args->ptds[i].args = args;
			args->ptds[i].io.cmd = WRITE;
			args->ptds[i].io.count = 0;
			args->ptds[i].io.fid = 0;
			args->ptds[i].io.off = 0;
			args->ptds[i].io.waiter = t;
			args->ptds[i].io.left = 0;
			args->ptds[i].io.parent = NULL;
			args->ptds[i].io.ref = 0;

			args->tlds[i].t = t;
			args->tlds[i].id = i;
			args->tlds[i].f = do_one_thread;
			args->tlds[i].v = &args->ptds[i];
			args->tlds[i].flags |= TLD_CTX_SWITCH;
			t->CreateThread(do_one_thread, &args->tlds[i]);

			t->RunAfter(/*Event::Rand(args->threadcount * 10)*/1);
		}
		tld->state = pios_RunOneAllFinishState;
		break;
	}
	case pios_RunOneAllFinishState:
		args->iotime = Event::Clock() - args->startime;
		print_stats(args);
	case pios_RunOneLastState:
		/* cleanup all resource. */
		delete [] args->streams;
		delete [] args->ptds;
		delete [] args->tlds;
		break;
	}
}