/* pkt is null-terminated */
void 
debug_exec(struct gdbcontext *ctx, const char *pkt) 
{
	char *cs;  /* start of the checksum */
	int i;
	int check = 0, scheck;

#ifdef SHOW_PACKETS
	msg("Got packet %s", pkt);
#endif

	if (pkt[0] != '$') {
		return;
	}

	cs = strchr(pkt, '#');
	if (cs == NULL) {
		return;
	}
	*cs = 0;
	cs++;

	for (i=1; pkt[i]; i++) {
		check += pkt[i];
	}

	scheck = strtoul(cs, NULL, 16);
	if (scheck != check % 256) {
		write(ctx->myfd, "-", 1);
		return;
	} else {
		write(ctx->myfd, "+", 1);
	}

	switch (pkt[1]) {
	    case '!':
		/*
		 * Enable extended mode -- extended mode is apparently
		 * where gdb can ask to rerun the program. We can't do
		 * that... although it could probably be arranged.
		 *
		 * Reply with "OK" if extended mode is enabled.
		 */
		debug_notsupp(ctx);
		break;
	    case '?':
		/* Report why the target stopped. */
		debug_send_stopinfo(ctx);
		break;
	    case 'A':
		/*
		 * Set argv[]. We can't do this, although it might make
		 * sense if we grow support for reloading the kernel.
		 */
		debug_notsupp(ctx);
		break;
	    case 'b':
		if (pkt[2] == 0) {
			/* Set serial bit rate; deprecated. */
			debug_notsupp(ctx);
			break;
		}
		else if (pkt[2] == 'c') {
			/* Backward continue - resume executing, backwards */
		}
		else if (pkt[2] == 's') {
			/* Backward single step - execute one insn backwards */
		}
		else {
			/* ? */
		}
		debug_notsupp(ctx);
		break;
	    case 'B':
		/* Set or clear breakpoint; old, deprecated. */
		debug_notsupp(ctx);
		break;
	    case 'c':
		/*
		 * Continue. If an address follows the 'c', continue
		 * from that address. debug_restart() does that.
		 */
		debug_restart(ctx, pkt + 2);
		unset_breakcond();
		break;
	    case 'C':
		/*
		 * Continue with signal. A signal number in hex
		 * follows the C; that may be followed with a
		 * semicolon and an address to continue at. We don't
		 * have signals per se; in theory we could fake up
		 * some mapping of signals to hardware traps, but that
		 * would be difficult to arrange and not serve much
		 * purpose.
		 */
		debug_notsupp(ctx);
		break;
	    case 'd':
		/* Toggle debug flag (whatever that means); deprecated. */
		debug_notsupp(ctx);
		break;
	    case 'D':
		/*
		 * Detach. With a process-id, detach only one process,
		 * if the multiprocess extension is in use.
		 */
		debug_send(ctx, "OK");
		unset_breakcond();
		break;
	    case 'F':
		/*
		 * File I/O extension reply; for now at least we have
		 * no use for this.
		 */
		debug_notsupp(ctx);
		break;
	    case 'g':
		/* Read general-purpose registers */
		debug_register_print(ctx);
		break;
	    case 'G':
		/*
		 * Write general-purpose registers. The G is followed
		 * by a register dump in the same format as the 'g'
		 * reply.
		 */
		// XXX gcc docs say this is required
		debug_notsupp(ctx);
		break;
	    case 'H':
		/*
		 * Hc followed by a thread ID sets the thread that
		 * step and continue operations should affect; Hg
		 * followed by a thread ID sets the thread that
		 * other operations should affect.
		 */
		if (pkt[2] == 'c') {
			debug_notsupp(ctx);
		}
		else if (pkt[2] == 'g') {
			unsigned cpunum;

			cpunum = getthreadid(pkt+3);
			if (cpunum >= cpu_numcpus()) {
				debug_send(ctx, "E00");
				break;
			}
			debug_cpu = cpunum;
			debug_send(ctx, "OK");
		}
		else {
			debug_send(ctx, "OK");
		}
		break;
	    case 'i':
		/* Step by cycle count */
		debug_notsupp(ctx);
		break;
	    case 'I':
		/* Step by cycle count with signal (apparently) */
		debug_notsupp(ctx);
		break;
	    case 'k':
		/* Kill the target */
		// don't do this - debugger hangs up and we get SIGPIPE
		//debug_send(ctx, "OK");
		msg("Debugger requested kill");
		reqdie();
		// To continue running instead of dying, do this instead
		//unset_breakcond();
		break;
	    case 'm':
		/* Read target memory */
		debug_read_mem(ctx, pkt + 2);
		break;
	    case 'M':
		/* Write target memory */
		debug_write_mem(ctx, pkt + 2);
		break;
	    case 'p':
		/* read one register */
		debug_notsupp(ctx);
		break;
	    case 'P':
		/* write one register */
		debug_notsupp(ctx);
		break;
	    case 'q':
		/* General query */
		if (strcmp(pkt + 2, "C") == 0) {
			/* Return current thread id */
			debug_sendf(ctx,"QC%x", mkthreadid(debug_cpu));
		}
		else if (!strcmp(pkt+2, "fThreadInfo")) {
			char buf[128];
			unsigned i;

			strcpy(buf, "m");
			for (i=0; i<cpu_numcpus(); i++) {
				if (!cpu_enabled(i)) {
					continue;
				}
				if (i > 0) {
					strcat(buf, ",");
				}
				printbyte(buf, sizeof(buf), mkthreadid(i));
			}
			debug_send(ctx, buf);
		}
		else if (!strcmp(pkt+2, "sThreadInfo")) {
			debug_send(ctx, "l");
		}
		else if (strcmp(pkt+2, "Offsets") == 0) {
			/* Return info about load-time relocations */ 
			debug_notsupp(ctx);
		}
		else if (strcmp(pkt+2, "Supported") == 0) {
			/* Features handshake */
			debug_notsupp(ctx);
		}
		else if (!strncmp(pkt+2, "ThreadExtraInfo,", 16)) {
			debug_getthreadinfo(ctx, pkt+2+16);
		}
		else {
			debug_notsupp(ctx);
		}
		break;
	    case 'Q':
		/* General set mode (I think) */
		debug_notsupp(ctx);
		break;
	    case 'r':
		/* Reset target - deprecated */
		debug_notsupp(ctx);
		break;
	    case 'R':
		/*
		 * Restart target (only with extended mode enabled).
		 * Do not reply.
		 */
		break;
	    case 's':
		/* Single step */
		debug_restart(ctx, pkt + 2);
		onecycle();
		debug_send_stopinfo(ctx);
		break;
	    case 'S':
		/* Single step with signal */
		debug_notsupp(ctx);
		break;
	    case 't':
		/* search memory for a pattern (underdocumented) */
		debug_notsupp(ctx);
		break;
	    case 'T':
		/* check if a thread is alive (OK - yes; E.. - no) */
		debug_checkthread(ctx, pkt + 2);
		break;
	    case 'v':
		/* various longer commands */
		debug_notsupp(ctx);
		break;
	    case 'X':
		/* Write target memory with a more efficient encoding */
		debug_notsupp(ctx);
		break;
	    case 'z':
	    case 'Z':
		/* insert (Z) or remove (z) one of the following: */
		switch (pkt[2]) {
		    case '0':
			/* set or clear memory breakpoint */
			debug_notsupp(ctx);
			break;
		    case '1':
			/* set or clear hardware breakpoint */
			debug_notsupp(ctx);
			break;
		    case '2':
			/* set or clear write watchpoint */
			debug_notsupp(ctx);
			break;
		    case '3':
			/* set or clear read watchpoint */
			debug_notsupp(ctx);
			break;
		    case '4':
			/* set or clear access watchpoint */
			debug_notsupp(ctx);
			break;
		    default:
			/* ? */
			debug_notsupp(ctx);
			break;
		}
		break;
	    default:
		debug_notsupp(ctx);
		break;
	}
}