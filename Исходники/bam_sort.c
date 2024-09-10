/*!
  @abstract    Merge multiple sorted BAM.
  @param  is_by_qname whether to sort by query name
  @param  out  output BAM file name
  @param  headers  name of SAM file from which to copy '@' header lines,
                   or NULL to copy them from the first file to be merged
  @param  n    number of files to be merged
  @param  fn   names of files to be merged

  @discussion Padding information may NOT correctly maintained. This
  function is NOT thread safe.
 */
int bam_merge_core2(int by_qname, const char *out, const char *headers, int n, char * const *fn, int flag, const char *reg, int n_threads, int level)
{
	bamFile fpout, *fp;
	heap1_t *heap;
	bam_header_t *hout = 0;
	bam_header_t *hheaders = NULL;
	int i, j, *RG_len = 0;
	uint64_t idx = 0;
	char **RG = 0, mode[8];
	bam_iter_t *iter = 0;

	if (headers) {
		tamFile fpheaders = sam_open(headers);
		if (fpheaders == 0) {
			const char *message = strerror(errno);
			fprintf(stderr, "[bam_merge_core] cannot open '%s': %s\n", headers, message);
			return -1;
		}
		hheaders = sam_header_read(fpheaders);
		sam_close(fpheaders);
	}

	g_is_by_qname = by_qname;
	fp = (bamFile*)calloc(n, sizeof(bamFile));
	heap = (heap1_t*)calloc(n, sizeof(heap1_t));
	iter = (bam_iter_t*)calloc(n, sizeof(bam_iter_t));
	// prepare RG tag
	if (flag & MERGE_RG) {
		RG = (char**)calloc(n, sizeof(void*));
		RG_len = (int*)calloc(n, sizeof(int));
		for (i = 0; i != n; ++i) {
			int l = strlen(fn[i]);
			const char *s = fn[i];
			if (l > 4 && strcmp(s + l - 4, ".bam") == 0) l -= 4;
			for (j = l - 1; j >= 0; --j) if (s[j] == '/') break;
			++j; l -= j;
			RG[i] = calloc(l + 1, 1);
			RG_len[i] = l;
			strncpy(RG[i], s + j, l);
		}
	}
	// read the first
	for (i = 0; i != n; ++i) {
		bam_header_t *hin;
		fp[i] = bam_open(fn[i], "r");
		if (fp[i] == 0) {
			int j;
			fprintf(stderr, "[bam_merge_core] fail to open file %s\n", fn[i]);
			for (j = 0; j < i; ++j) bam_close(fp[j]);
			free(fp); free(heap);
			// FIXME: possible memory leak
			return -1;
		}
		hin = bam_header_read(fp[i]);
		if (i == 0) { // the first BAM
			hout = hin;
		} else { // validate multiple baf
			int min_n_targets = hout->n_targets;
			if (hin->n_targets < min_n_targets) min_n_targets = hin->n_targets;

			for (j = 0; j < min_n_targets; ++j)
				if (strcmp(hout->target_name[j], hin->target_name[j]) != 0) {
					fprintf(stderr, "[bam_merge_core] different target sequence name: '%s' != '%s' in file '%s'\n",
							hout->target_name[j], hin->target_name[j], fn[i]);
					return -1;
				}

			// If this input file has additional target reference sequences,
			// add them to the headers to be output
			if (hin->n_targets > hout->n_targets) {
				swap_header_targets(hout, hin);
				// FIXME Possibly we should also create @SQ text headers
				// for the newly added reference sequences
			}

			bam_header_destroy(hin);
		}
	}

	if (hheaders) {
		// If the text headers to be swapped in include any @SQ headers,
		// check that they are consistent with the existing binary list
		// of reference information.
		if (hheaders->n_targets > 0) {
			if (hout->n_targets != hheaders->n_targets) {
				fprintf(stderr, "[bam_merge_core] number of @SQ headers in '%s' differs from number of target sequences\n", headers);
				if (!reg) return -1;
			}
			for (j = 0; j < hout->n_targets; ++j)
				if (strcmp(hout->target_name[j], hheaders->target_name[j]) != 0) {
					fprintf(stderr, "[bam_merge_core] @SQ header '%s' in '%s' differs from target sequence\n", hheaders->target_name[j], headers);
					if (!reg) return -1;
				}
		}

		swap_header_text(hout, hheaders);
		bam_header_destroy(hheaders);
	}

	if (reg) {
		int tid, beg, end;
		if (bam_parse_region(hout, reg, &tid, &beg, &end) < 0) {
			fprintf(stderr, "[%s] Malformated region string or undefined reference name\n", __func__);
			return -1;
		}
		for (i = 0; i < n; ++i) {
			bam_index_t *idx;
			idx = bam_index_load(fn[i]);
			iter[i] = bam_iter_query(idx, tid, beg, end);
			bam_index_destroy(idx);
		}
	}

	for (i = 0; i < n; ++i) {
		heap1_t *h = heap + i;
		h->i = i;
		h->b = (bam1_t*)calloc(1, sizeof(bam1_t));
		if (bam_iter_read(fp[i], iter[i], h->b) >= 0) {
			h->pos = ((uint64_t)h->b->core.tid<<32) | (uint32_t)((int32_t)h->b->core.pos+1)<<1 | bam1_strand(h->b);
			h->idx = idx++;
		}
		else h->pos = HEAP_EMPTY;
	}
	if (flag & MERGE_UNCOMP) level = 0;
	else if (flag & MERGE_LEVEL1) level = 1;
	strcpy(mode, "w");
	if (level >= 0) sprintf(mode + 1, "%d", level < 9? level : 9);
	if ((fpout = strcmp(out, "-")? bam_open(out, "w") : bam_dopen(fileno(stdout), "w")) == 0) {
		fprintf(stderr, "[%s] fail to create the output file.\n", __func__);
		return -1;
	}
	bam_header_write(fpout, hout);
	bam_header_destroy(hout);
	if (!(flag & MERGE_UNCOMP)) bgzf_mt(fpout, n_threads, 256);

	ks_heapmake(heap, n, heap);
	while (heap->pos != HEAP_EMPTY) {
		bam1_t *b = heap->b;
		if (flag & MERGE_RG) {
			uint8_t *rg = bam_aux_get(b, "RG");
			if (rg) bam_aux_del(b, rg);
			bam_aux_append(b, "RG", 'Z', RG_len[heap->i] + 1, (uint8_t*)RG[heap->i]);
		}
		bam_write1_core(fpout, &b->core, b->data_len, b->data);
		if ((j = bam_iter_read(fp[heap->i], iter[heap->i], b)) >= 0) {
			heap->pos = ((uint64_t)b->core.tid<<32) | (uint32_t)((int)b->core.pos+1)<<1 | bam1_strand(b);
			heap->idx = idx++;
		} else if (j == -1) {
			heap->pos = HEAP_EMPTY;
			free(heap->b->data); free(heap->b);
			heap->b = 0;
		} else fprintf(stderr, "[bam_merge_core] '%s' is truncated. Continue anyway.\n", fn[heap->i]);
		ks_heapadjust(heap, 0, n, heap);
	}

	if (flag & MERGE_RG) {
		for (i = 0; i != n; ++i) free(RG[i]);
		free(RG); free(RG_len);
	}
	for (i = 0; i != n; ++i) {
		bam_iter_destroy(iter[i]);
		bam_close(fp[i]);
	}
	bam_close(fpout);
	free(fp); free(heap); free(iter);
	return 0;
}