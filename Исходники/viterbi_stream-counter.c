int viterbi_stream_word_partitioned(DATA_STREAM* dstream, float* opt_res, int thrid)
{
//	if (NTHREADS > 1)		pthread_barrier_wait(&dstream->barrier);

	return 0;

	int L = dstream->L;
	P7_PROFILE* gm = dstream->gm;
	ESL_DSQ** ddsq = dstream->seqs;
	int M = gm->M, i, k, v, t, j;
	const int PARTITION = dstream->partition;
	__m128i** oprmsc = (__m128i**) dstream->rsc_msc;
	__m128i* xmxEv = dstream->xmxE;
	__m128i xmxB, xmxE, xmxC, moveC, Vinf = _mm_set1_epi16(-WORDMAX);

	__m128i dmx[PARTITION];
	__m128i mmx[PARTITION];
	__m128i imx[PARTITION];
	__m128i xmm[24];
	__m128i *mscore[8];
	__m128i overflowlimit, overflows;
	overflowlimit = overflows = Vinf;

	if (thrid == NTHREADS-1) 
	{	overflowlimit = _mm_set1_epi16(WORDMAX-1);
		overflows= _mm_xor_si128(overflows,overflows);	// zero out
	}

	t = ((dstream->Npartitions+thrid)%NTHREADS)*PARTITION;
	tprintf("START viterbiThr %d in %d L %d | Seq %d\n", thrid, t, L, 0); // ccount[thrid]++);

	xmxC  = Vinf;
	moveC = _mm_set1_epi16(discretize(dstream->scale, gm->xsc[p7P_C][p7P_MOVE]));
	xmxB  = _mm_set1_epi16(dstream->wordoffset + discretize(dstream->scale, gm->xsc[p7P_N][p7P_MOVE]));

	for (	; t < M; t += NTHREADS*PARTITION)
	{
		volatile uchar* synchflags1 = dstream->synchflags[t/PARTITION];
		volatile uchar* synchflags2 = dstream->synchflags[t/PARTITION+1];
		int t8 = t/8;

		for (k = 0; k < PARTITION; k++)
			dmx[k] = mmx[k] = imx[k] = Vinf;

		for (i = 1; i <= L; i++)
		{
		//	tprintf("Iter Thr %d t %d: I %d\n", thrid, t, i);
			__m128i sc, dcv, temp, mpv, ipv, dpv;
			__m128i *ttsc = dstream->tsc_all + t*8;
			v = i-1;
			ttsc += 3;

			if (t == 0)
				xmxE = mpv = dpv = ipv = sc = dcv = Vinf;
			else {
				if (NTHREADS > 1)
					 while (!synchflags1[v]) sched_yield();
				xmxE = xmxEv[v];
				dcv = dstream->pdcv[v];
				sc  = dstream->psc[v];
			}

			for (j = 0; j < 8; j++)
				mscore[j] = oprmsc[ddsq[j][i]] + t8;

			for (k = 0; k < PARTITION && t+k < M; )
			{
#if 0
#define EMLOAD(i)	xmm[i+24] = _mm_load_si128(mscore[i]); 
				EMLOAD(0) 	EMLOAD(1) 
				EMLOAD(2) 	EMLOAD(3) 
				EMLOAD(4) 	EMLOAD(5) 
				EMLOAD(6) 	EMLOAD(7) 

#define MIX16(i,r,range)	\
	xmm[r  ] = _mm_unpacklo_epi##range(xmm[24+i], xmm[24+i+1]);	\
	xmm[r+1] = _mm_unpackhi_epi##range(xmm[24+i], xmm[24+i+1]);
				MIX16(0,0,16)	MIX16(2,2,16)
				MIX16(4,4,16)	MIX16(6,6,16)
#else

#define MMLOAD(a,b)		\
	xmm[a] = _mm_unpacklo_epi16(*mscore[a], *mscore[b]);	\
	xmm[b] = _mm_unpackhi_epi16(*mscore[a], *mscore[b]);

				MMLOAD(0,1)	MMLOAD(2,3)
				MMLOAD(4,5)	MMLOAD(6,7)
#endif

#define MIX(i,r,range)	\
	xmm[r  ] = _mm_unpacklo_epi##range(xmm[i], xmm[i+2]);	\
	xmm[r+1] = _mm_unpackhi_epi##range(xmm[i], xmm[i+2]);

				MIX(0, 8,32)	MIX(1,12,32)
				MIX(4,10,32)	MIX(5,14,32)

				MIX( 8,16,64)	MIX( 9,18,64)
				MIX(12,20,64)	MIX(13,22,64)


#define TRIPLETCOMPUTE(k,j)	\
{	/* Calculate new M(k), delay store */	\
	sc = _mm_max_epi16(sc, _mm_adds_epi16(xmxB, *ttsc)); ttsc++;	\
	sc = _mm_adds_epi16(sc,  xmm[j]);		\
	/* Update E */							\
	xmxE = _mm_max_epi16(xmxE, sc);			\
	\
	/* Pre-emptive load of M, D, I */		\
	dpv = dmx[k];	\
	ipv = imx[k];	\
	mpv = mmx[k];	\
	\
	/* Calculate current I(k) */			\
	temp = _mm_adds_epi16(mpv, *ttsc); ttsc++;	\
	imx[k] = _mm_max_epi16(temp, _mm_adds_epi16(ipv, *ttsc)); ttsc++;\
	\
	/* Delayed stores of M and D */			\
	mmx[k] = sc;	\
	dmx[k] = dcv;	\
	\
	/* Calculate next D, D(k+1) */			\
	sc	= _mm_adds_epi16(sc, *ttsc); ttsc++;	\
	dcv = _mm_max_epi16(sc, _mm_adds_epi16(dcv, *ttsc));ttsc++;	\
	\
	/* Pre-emptive partial calculation of M(k+1) */	\
	sc = _mm_adds_epi16(mpv, *ttsc); ttsc++;	\
	sc = _mm_max_epi16(sc, _mm_adds_epi16(ipv, *ttsc)); ttsc++;	\
	sc = _mm_max_epi16(sc, _mm_adds_epi16(dpv, *ttsc)); ttsc++;	\
	k++;			\
}
				TRIPLETCOMPUTE(k,16+0)	TRIPLETCOMPUTE(k,16+1)
				TRIPLETCOMPUTE(k,16+2)	TRIPLETCOMPUTE(k,16+3)
				TRIPLETCOMPUTE(k,16+4)	TRIPLETCOMPUTE(k,16+5)
				TRIPLETCOMPUTE(k,16+6)	TRIPLETCOMPUTE(k,16+7)

				mscore[0]++; mscore[1]++; mscore[2]++; mscore[3]++;
				mscore[4]++; mscore[5]++; mscore[6]++; mscore[7]++;
			}

			if (t+k < M)
			{	v = i-1;
				xmxEv[v] = xmxE;
				dstream->pdcv[v] = dcv;
				dstream->psc [v] = sc;

				if (NTHREADS > 1) synchflags2[v] = 1;
			}
			else	// executed only by main thread (NTHRS-1)
			{
				__m128i overfs = _mm_cmpgt_epi16(xmxE, overflowlimit);
				overflows = _mm_or_si128(overflows, overfs);	// select the overflowed channels
				xmxC	= _mm_max_epi16(xmxC, xmxE);
			}
		}
	}

	xmxC = _mm_adds_epi16(xmxC, moveC);

	if (opt_res != NULL)
	{
		float offset = (float) dstream->wordoffset;
		int16_t res[8] __attribute__ ((aligned (16)));
		int16_t ovs[8] __attribute__ ((aligned (16)));

		memmove(res, &xmxC, sizeof(xmxC));
		memmove(ovs, &overflows, sizeof(overflows));

		for (i = 0; i < 8; i++)
			if (ovs[i])	opt_res[i] = eslINFINITY;	// signal overflow
			else		opt_res[i] = ((float) res[i] - offset) / dstream->scale - 2.0;
												// 2.0 nat approximation, UNILOCAL mode
	}

	tprintf("END viterbi Thr %d - t %d\n", thrid, t);
	return eslOK;
}