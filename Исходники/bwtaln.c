void bwa_cal_sa_reg_gap(int tid, bwt_t * const bwt[2], int n_seqs,
		bwa_seq_t *seqs, const gap_opt_t *opt) {
	int i, max_l = 0, max_len;
	gap_stack_t *stack;
	bwt_width_t *w[2], *seed_w[2];
	const ubyte_t *seq[2];
	gap_opt_t local_opt = *opt;

	// initiate priority stack
	for (i = max_len = 0; i != n_seqs; ++i)
		if (seqs[i].len > max_len)
			max_len = seqs[i].len;
	if (opt->fnr > 0.0)
		local_opt.max_diff = bwa_cal_maxdiff(max_len, BWA_AVG_ERR, opt->fnr);
	if (local_opt.max_diff < local_opt.max_gapo)
		local_opt.max_gapo = local_opt.max_diff;
	stack = gap_init_stack(local_opt.max_diff, local_opt.max_gapo,
			local_opt.max_gape, &local_opt);

	seed_w[0] = (bwt_width_t*) calloc(opt->seed_len + 1, sizeof(bwt_width_t));
	seed_w[1] = (bwt_width_t*) calloc(opt->seed_len + 1, sizeof(bwt_width_t));
	w[0] = w[1] = 0;
	for (i = 0; i != n_seqs; ++i) {
		bwa_seq_t *p = seqs + i;
#ifdef HAVE_PTHREAD
		if (opt->n_threads > 1) {
			pthread_mutex_lock(&g_seq_lock);
			if (p->tid < 0) { // unassigned
				int j;
				for (j = i; j < n_seqs && j < i + THREAD_BLOCK_SIZE; ++j)
					seqs[j].tid = tid;
			} else if (p->tid != tid) {
				pthread_mutex_unlock(&g_seq_lock);
				continue;
			}
			pthread_mutex_unlock(&g_seq_lock);
		}
#endif
		p->sa = 0;
		p->type = BWA_TYPE_NO_MATCH;
		p->c1 = p->c2 = 0;
		p->n_aln = 0;
		p->aln = 0;
		seq[0] = p->seq;
		seq[1] = p->rseq;
		if (max_l < p->len) {
			max_l = p->len;
			w[0] = (bwt_width_t*) realloc(w[0], (max_l + 1)
					* sizeof(bwt_width_t));
			w[1] = (bwt_width_t*) realloc(w[1], (max_l + 1)
					* sizeof(bwt_width_t));
			memset(w[0], 0, (max_l + 1) * sizeof(bwt_width_t));
			memset(w[1], 0, (max_l + 1) * sizeof(bwt_width_t));
		}
		bwt_cal_width(bwt[0], p->len, seq[0], w[0]);
		bwt_cal_width(bwt[1], p->len, seq[1], w[1]);
		if (opt->fnr > 0.0)
			local_opt.max_diff = bwa_cal_maxdiff(p->len, BWA_AVG_ERR, opt->fnr);
		local_opt.seed_len = opt->seed_len < p->len ? opt->seed_len
				: 0x7fffffff;
		if (p->len > opt->seed_len) {
			bwt_cal_width(bwt[0], opt->seed_len, seq[0] + (p->len
					- opt->seed_len), seed_w[0]);
			bwt_cal_width(bwt[1], opt->seed_len, seq[1] + (p->len
					- opt->seed_len), seed_w[1]);
		}
		// core function
		p->aln = bwt_match_gap(bwt, p->len, seq, w, p->len <= opt->seed_len ? 0
				: seed_w, &local_opt, &p->n_aln, stack);
		// store the alignment
		free(p->name);
		free(p->seq);
		free(p->rseq);
		free(p->qual);
		p->name = 0;
		p->seq = p->rseq = p->qual = 0;
	}
	free(seed_w[0]);
	free(seed_w[1]);
	free(w[0]);
	free(w[1]);
	gap_destroy_stack(stack);
}