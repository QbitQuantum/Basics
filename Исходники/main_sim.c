int main(int argc, char **argv)
{
	int trace = 0;
	char buf[512], cryptdata[128];
	mf_t trace_mf;
	dpa_t *dpa = NULL;
	uint8_t hypotheses[1024], key[16], plain[16];
	int hypos = 16;
	correl_t *results = NULL;
	time_t start = 0, runtime;
	int res, cnt;
	int last_cnt = 0;
	FILE *fl_align, *fl_iod;
	float signif;
	int best_keybyte = 0;
	float max_correl = 0;
	hypo_template_t *hypo_templates;
	int trace_ofs = (372*12*280)/16; // 78k
	int trace_len = 100000;

	assert(argc>=3);

	fl_iod = fopen(argv[1], "r");
	assert(fl_iod);
	
	fl_align = fopen(argv[2],"r");
	assert(fl_align);

	while (fgets(buf, 512, fl_iod)) {
		uint8_t rand[16];
		uint8_t sres_kc[12];
		char *p = parse_hex(buf+9, rand, 16);
		assert(p == buf+9+32);
		p = parse_hex(buf+9+32+1, sres_kc, 12);
		assert(p == buf+9+32+1+24);
		int ofs;
		float diff;

		res = fscanf(fl_align, "%s %i %f",buf,&ofs,&diff);
		assert(res == 3);

		res = open_trace(&trace_mf, buf);
		assert(!res);

		for(cnt=0; cnt<16; cnt++) {
			hypotheses[cnt] = hamming_weight(rand[cnt]);
		}

		if (!dpa) {
			dpa = dpa_init(hypos, trace_len);
			assert((results =
				malloc(sizeof(correl_t) * (dpa->tracelen))));
			start = time(NULL);
		}

		assert(ofs <= trace_ofs);
		dpa_add(dpa, trace_mf.ptr + trace_ofs - ofs, hypotheses);

		trace++;
		last_cnt = trace;

		if(!(trace%32))
			printf("%d\n",trace);

	}

	fclose(fl_iod);
	fclose(fl_align);

	runtime = time(NULL);
	runtime -= start;

	dpa_speedinfo(dpa, runtime);

	signif = 1.3 * (4 / sqrt((float)trace));
	printf("signif: %f\n", signif);

	for (cnt = 0; cnt < hypos; cnt++) {
		float max;
		FILE *res_fl;
		int i;

		dpa_get_results(dpa, cnt, results, &max);

		sprintf(buf,"dpa-%d.txt",cnt);
		res_fl = fopen(buf,"w");
		assert(res_fl);

		for(i=0;i<dpa->tracelen;i++)
			fprintf(res_fl,"%d %f\n",i+trace_ofs,results[i]);
		
		fclose(res_fl);
	}

	free(results);

	dpa_destroy(&dpa);

	return 0;
}