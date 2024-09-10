/*
 * Generate a mirroring data stream from the specific source over the
 * entire key range, but restricted to the specified transaction range.
 *
 * The HAMMER VFS does most of the work, we add a few new mrecord
 * types to negotiate the TID ranges and verify that the entire
 * stream made it to the destination.
 *
 * streaming will be 0 for mirror-read, 1 for mirror-stream.  The code will
 * set up a fake value of -1 when running the histogram for mirror-read.
 */
void
hammer_cmd_mirror_read(char **av, int ac, int streaming)
{
	struct hammer_ioc_mirror_rw mirror;
	struct hammer_ioc_pseudofs_rw pfs;
	union hammer_ioc_mrecord_any mrec_tmp;
	struct hammer_ioc_mrecord_head pickup;
	hammer_ioc_mrecord_any_t mrec;
	hammer_tid_t sync_tid;
	histogram_t histogram_ary;
	const char *filesystem;
	char *buf = malloc(SERIALBUF_SIZE);
	int interrupted = 0;
	int error;
	int fd;
	int n;
	int didwork;
	int histogram;
	int histindex;
	int histmax;
	int repeat = 0;
	int sameline;
	int64_t total_bytes;
	time_t base_t = time(NULL);
	struct timeval bwtv;
	uint64_t bwcount;
	uint64_t estbytes;

	if (ac == 0 || ac > 2)
		mirror_usage(1);
	filesystem = av[0];
	hammer_check_restrict(filesystem);

	pickup.signature = 0;
	pickup.type = 0;
	histogram = 0;
	histindex = 0;
	histmax = 0;
	histogram_ary = NULL;
	sameline = 0;

again:
	bzero(&mirror, sizeof(mirror));
	hammer_key_beg_init(&mirror.key_beg);
	hammer_key_end_init(&mirror.key_end);

	fd = getpfs(&pfs, filesystem);

	if (streaming >= 0)
		score_printf(LINE1, "Running");

	if (streaming >= 0 && VerboseOpt && VerboseOpt < 2) {
		fprintf(stderr, "%cRunning  \b\b", (sameline ? '\r' : '\n'));
		fflush(stderr);
		sameline = 1;
	}
	sameline = 1;
	total_bytes = 0;
	gettimeofday(&bwtv, NULL);
	bwcount = 0;

	/*
	 * Send initial header for the purpose of determining the
	 * shared-uuid.
	 */
	generate_mrec_header(fd, pfs.pfs_id, &mrec_tmp);
	write_mrecord(1, HAMMER_MREC_TYPE_PFSD,
		      &mrec_tmp, sizeof(mrec_tmp.pfs));

	/*
	 * In 2-way mode the target will send us a PFS info packet
	 * first.  Use the target's current snapshot TID as our default
	 * begin TID.
	 */
	if (TwoWayPipeOpt) {
		mirror.tid_beg = 0;
		n = validate_mrec_header(fd, 0, 0, pfs.pfs_id, &pickup,
					 NULL, &mirror.tid_beg);
		if (n < 0) {	/* got TERM record */
			relpfs(fd, &pfs);
			free(buf);
			free(histogram_ary);
			return;
		}
		++mirror.tid_beg;
	} else if (streaming && histogram) {
		mirror.tid_beg = histogram_ary[histindex].tid + 1;
	} else {
		mirror.tid_beg = 0;
	}

	/*
	 * Write out the PFS header, tid_beg will be updated if our PFS
	 * has a larger begin sync.  tid_end is set to the latest source
	 * TID whos flush cycle has completed.
	 */
	generate_mrec_header(fd, pfs.pfs_id, &mrec_tmp);
	if (mirror.tid_beg < mrec_tmp.pfs.pfsd.sync_beg_tid)
		mirror.tid_beg = mrec_tmp.pfs.pfsd.sync_beg_tid;
	mirror.tid_end = mrec_tmp.pfs.pfsd.sync_end_tid;
	mirror.ubuf = buf;
	mirror.size = SERIALBUF_SIZE;
	mirror.pfs_id = pfs.pfs_id;
	mirror.shared_uuid = pfs.ondisk->shared_uuid;

	/*
	 * XXX If the histogram is exhausted and the TID delta is large
	 *     the stream might have been offline for a while and is
	 *     now picking it up again.  Do another histogram.
	 */
#if 0
	if (streaming && histogram && histindex == histend) {
		if (mirror.tid_end - mirror.tid_beg > BULK_MINIMUM)
			histogram = 0;
	}
#endif

	/*
	 * Initial bulk startup control, try to do some incremental
	 * mirroring in order to allow the stream to be killed and
	 * restarted without having to start over.
	 */
	if (histogram == 0 && BulkOpt == 0) {
		if (VerboseOpt && repeat == 0) {
			fprintf(stderr, "\n");
			sameline = 0;
		}
		histmax = generate_histogram(fd, filesystem,
					     &histogram_ary, &mirror,
					     &repeat);
		histindex = 0;
		histogram = 1;

		/*
		 * Just stream the histogram, then stop
		 */
		if (streaming == 0)
			streaming = -1;
	}

	if (streaming && histogram) {
		++histindex;
		mirror.tid_end = histogram_ary[histindex].tid;
		estbytes = histogram_ary[histindex-1].bytes;
		mrec_tmp.pfs.pfsd.sync_end_tid = mirror.tid_end;
	} else {
		estbytes = 0;
	}

	write_mrecord(1, HAMMER_MREC_TYPE_PFSD,
		      &mrec_tmp, sizeof(mrec_tmp.pfs));

	/*
	 * A cycle file overrides the beginning TID only if we are
	 * not operating in two-way or histogram mode.
	 */
	if (TwoWayPipeOpt == 0 && histogram == 0) {
		hammer_get_cycle(&mirror.key_beg, &mirror.tid_beg);
	}

	/*
	 * An additional argument overrides the beginning TID regardless
	 * of what mode we are in.  This is not recommending if operating
	 * in two-way mode.
	 */
	if (ac == 2)
		mirror.tid_beg = strtoull(av[1], NULL, 0);

	if (streaming == 0 || VerboseOpt >= 2) {
		fprintf(stderr,
			"Mirror-read: Mirror %016jx to %016jx",
			(uintmax_t)mirror.tid_beg, (uintmax_t)mirror.tid_end);
		if (histogram)
			fprintf(stderr, " (bulk= %ju)", (uintmax_t)estbytes);
		fprintf(stderr, "\n");
		fflush(stderr);
	}
	if (mirror.key_beg.obj_id != (int64_t)HAMMER_MIN_OBJID) {
		fprintf(stderr, "Mirror-read: Resuming at object %016jx\n",
			(uintmax_t)mirror.key_beg.obj_id);
	}

	/*
	 * Nothing to do if begin equals end.
	 */
	if (mirror.tid_beg >= mirror.tid_end) {
		if (streaming == 0 || VerboseOpt >= 2)
			fprintf(stderr, "Mirror-read: No work to do\n");
		sleep(DelayOpt);
		didwork = 0;
		histogram = 0;
		goto done;
	}
	didwork = 1;

	/*
	 * Write out bulk records
	 */
	mirror.ubuf = buf;
	mirror.size = SERIALBUF_SIZE;

	do {
		mirror.count = 0;
		mirror.pfs_id = pfs.pfs_id;
		mirror.shared_uuid = pfs.ondisk->shared_uuid;
		if (ioctl(fd, HAMMERIOC_MIRROR_READ, &mirror) < 0) {
			score_printf(LINE3, "Mirror-read %s failed: %s",
				     filesystem, strerror(errno));
			fprintf(stderr, "Mirror-read %s failed: %s\n",
				filesystem, strerror(errno));
			exit(1);
		}
		if (mirror.head.flags & HAMMER_IOC_HEAD_ERROR) {
			score_printf(LINE3, "Mirror-read %s fatal error %d",
				     filesystem, mirror.head.error);
			fprintf(stderr,
				"Mirror-read %s fatal error %d\n",
				filesystem, mirror.head.error);
			exit(1);
		}
		if (mirror.count) {
			if (BandwidthOpt) {
				n = writebw(1, mirror.ubuf, mirror.count,
					    &bwcount, &bwtv);
			} else {
				n = write(1, mirror.ubuf, mirror.count);
			}
			if (n != mirror.count) {
				score_printf(LINE3,
					     "Mirror-read %s failed: "
					     "short write",
					     filesystem);
				fprintf(stderr,
					"Mirror-read %s failed: "
					"short write\n",
				filesystem);
				exit(1);
			}
		}
		total_bytes += mirror.count;
		if (streaming && VerboseOpt) {
			fprintf(stderr,
				"\rscan obj=%016jx tids=%016jx:%016jx %11jd",
				(uintmax_t)mirror.key_cur.obj_id,
				(uintmax_t)mirror.tid_beg,
				(uintmax_t)mirror.tid_end,
				(intmax_t)total_bytes);
			fflush(stderr);
			sameline = 0;
		} else if (streaming) {
			score_printf(LINE2,
				"obj=%016jx tids=%016jx:%016jx %11jd",
				(uintmax_t)mirror.key_cur.obj_id,
				(uintmax_t)mirror.tid_beg,
				(uintmax_t)mirror.tid_end,
				(intmax_t)total_bytes);
		}
		mirror.key_beg = mirror.key_cur;

		/*
		 * Deal with time limit option
		 */
		if (TimeoutOpt &&
		    (unsigned)(time(NULL) - base_t) > (unsigned)TimeoutOpt) {
			score_printf(LINE3,
				"Mirror-read %s interrupted by timer at"
				" %016jx",
				filesystem,
				(uintmax_t)mirror.key_cur.obj_id);
			fprintf(stderr,
				"Mirror-read %s interrupted by timer at"
				" %016jx\n",
				filesystem,
				(uintmax_t)mirror.key_cur.obj_id);
			interrupted = 1;
			break;
		}
	} while (mirror.count != 0);

done:
	if (streaming && VerboseOpt && sameline == 0) {
		fprintf(stderr, "\n");
		fflush(stderr);
		sameline = 1;
	}

	/*
	 * Write out the termination sync record - only if not interrupted
	 */
	if (interrupted == 0) {
		if (didwork) {
			write_mrecord(1, HAMMER_MREC_TYPE_SYNC,
				      &mrec_tmp, sizeof(mrec_tmp.sync));
		} else {
			write_mrecord(1, HAMMER_MREC_TYPE_IDLE,
				      &mrec_tmp, sizeof(mrec_tmp.sync));
		}
	}

	/*
	 * If the -2 option was given (automatic when doing mirror-copy),
	 * a two-way pipe is assumed and we expect a response mrec from
	 * the target.
	 */
	if (TwoWayPipeOpt) {
		mrec = read_mrecord(0, &error, &pickup);
		if (mrec == NULL ||
		    mrec->head.type != HAMMER_MREC_TYPE_UPDATE ||
		    mrec->head.rec_size != sizeof(mrec->update)) {
			fprintf(stderr, "mirror_read: Did not get final "
					"acknowledgement packet from target\n");
			exit(1);
		}
		if (interrupted) {
			if (CyclePath) {
				hammer_set_cycle(&mirror.key_cur,
						 mirror.tid_beg);
				fprintf(stderr, "Cyclefile %s updated for "
					"continuation\n", CyclePath);
			}
		} else {
			sync_tid = mrec->update.tid;
			if (CyclePath) {
				hammer_key_beg_init(&mirror.key_beg);
				hammer_set_cycle(&mirror.key_beg, sync_tid);
				fprintf(stderr,
					"Cyclefile %s updated to 0x%016jx\n",
					CyclePath, (uintmax_t)sync_tid);
			}
		}
		free(mrec);
	} else if (CyclePath) {
		/* NOTE! mirror.tid_beg cannot be updated */
		fprintf(stderr, "Warning: cycle file (-c option) cannot be "
				"fully updated unless you use mirror-copy\n");
		hammer_set_cycle(&mirror.key_beg, mirror.tid_beg);
	}
	if (streaming && interrupted == 0) {
		time_t t1 = time(NULL);
		time_t t2;

		/*
		 * Try to break down large bulk transfers into smaller ones
		 * so it can sync the transaction id on the slave.  This
		 * way if we get interrupted a restart doesn't have to
		 * start from scratch.
		 */
		if (streaming && histogram) {
			if (histindex != histmax) {
				if (VerboseOpt && VerboseOpt < 2 &&
				    streaming >= 0) {
					fprintf(stderr, " (bulk incremental)");
				}
				relpfs(fd, &pfs);
				goto again;
			}
		}

		if (VerboseOpt && streaming >= 0) {
			fprintf(stderr, " W");
			fflush(stderr);
		} else if (streaming >= 0) {
			score_printf(LINE1, "Waiting");
		}
		pfs.ondisk->sync_end_tid = mirror.tid_end;
		if (streaming < 0) {
			/*
			 * Fake streaming mode when using a histogram to
			 * break up a mirror-read, do not wait on source.
			 */
			streaming = 0;
		} else if (ioctl(fd, HAMMERIOC_WAI_PSEUDOFS, &pfs) < 0) {
			score_printf(LINE3,
				     "Mirror-read %s: cannot stream: %s\n",
				     filesystem, strerror(errno));
			fprintf(stderr,
				"Mirror-read %s: cannot stream: %s\n",
				filesystem, strerror(errno));
		} else {
			t2 = time(NULL) - t1;
			if (t2 >= 0 && t2 < DelayOpt) {
				if (VerboseOpt) {
					fprintf(stderr, "\bD");
					fflush(stderr);
				}
				sleep(DelayOpt - t2);
			}
			if (VerboseOpt) {
				fprintf(stderr, "\b ");
				fflush(stderr);
			}
			relpfs(fd, &pfs);
			goto again;
		}
	}
	write_mrecord(1, HAMMER_MREC_TYPE_TERM,
		      &mrec_tmp, sizeof(mrec_tmp.sync));
	relpfs(fd, &pfs);
	free(buf);
	free(histogram_ary);
	fprintf(stderr, "Mirror-read %s succeeded\n", filesystem);
}