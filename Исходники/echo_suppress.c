/*
 * Update EC state
 */
static void echo_supp_update(echo_supp *ec, pj_int16_t *rec_frm,
			     const pj_int16_t *play_frm)
{
    int prev_index;
    unsigned i, j, frm_level, sum_play_level, ulaw;
    pj_uint16_t old_rec_frm_level, old_play_frm_level;
    float play_corr;

    ++ec->update_cnt;
    if (ec->update_cnt > 0x7FFFFFFF)
	ec->update_cnt = 0x7FFFFFFF; /* Detect overflow */

    /* Calculate current play frame level */
    frm_level = pjmedia_calc_avg_signal(play_frm, ec->samples_per_segment);
    ++frm_level; /* to avoid division by zero */

    /* Save the oldest frame level for later */
    old_play_frm_level = ec->play_hist[0];

    /* Push current frame level to the back of the play history */
    pj_array_erase(ec->play_hist, sizeof(pj_uint16_t), ec->play_hist_cnt, 0);
    ec->play_hist[ec->play_hist_cnt-1] = (pj_uint16_t) frm_level;

    /* Calculate level of current mic frame */
    frm_level = pjmedia_calc_avg_signal(rec_frm, ec->samples_per_segment);
    ++frm_level; /* to avoid division by zero */

    /* Save the oldest frame level for later */
    old_rec_frm_level = ec->rec_hist[0];

    /* Push to the back of the rec history */
    pj_array_erase(ec->rec_hist, sizeof(pj_uint16_t), ec->templ_cnt, 0);
    ec->rec_hist[ec->templ_cnt-1] = (pj_uint16_t) frm_level;


    /* Can't do the calc until the play history is full. */
    if (ec->update_cnt < ec->play_hist_cnt)
	return;

    /* Skip if learning is done */
    if (!ec->learning)
	return;


    /* Calculate rec signal pattern */
    if (ec->sum_rec_level == 0) {
	/* Buffer has just been filled up, do full calculation */
	ec->rec_corr = 0;
	ec->sum_rec_level = 0;
	for (i=0; i < ec->templ_cnt-1; ++i) {
	    float corr;
	    corr = (float)ec->rec_hist[i+1] / ec->rec_hist[i];
	    ec->rec_corr += corr;
	    ec->sum_rec_level += ec->rec_hist[i];
	}
	ec->sum_rec_level += ec->rec_hist[i];
    } else {
	/* Update from previous calculation */
	ec->sum_rec_level = ec->sum_rec_level - old_rec_frm_level + 
			    ec->rec_hist[ec->templ_cnt-1];
	ec->rec_corr = ec->rec_corr - ((float)ec->rec_hist[0] / 
					      old_rec_frm_level) +
		       ((float)ec->rec_hist[ec->templ_cnt-1] /
			       ec->rec_hist[ec->templ_cnt-2]);
    }

    /* Iterate through the play history and calculate the signal correlation
     * for every tail position in the play_hist. Save the result in temporary
     * array since we may bail out early if the conversation state is not good
     * to detect echo.
     */
    /* 
     * First phase: do full calculation for the first position 
     */
    if (ec->sum_play_level0 == 0) {
	/* Buffer has just been filled up, do full calculation */
	sum_play_level = 0;
	play_corr = 0;
	for (j=0; j<ec->templ_cnt-1; ++j) {
	    float corr;
	    corr = (float)ec->play_hist[j+1] / ec->play_hist[j];
	    play_corr += corr;
	    sum_play_level += ec->play_hist[j];
	}
	sum_play_level += ec->play_hist[j];
	ec->sum_play_level0 = sum_play_level;
	ec->play_corr0 = play_corr;
    } else {
	/* Update from previous calculation */
	ec->sum_play_level0 = ec->sum_play_level0 - old_play_frm_level + 
			      ec->play_hist[ec->templ_cnt-1];
	ec->play_corr0 = ec->play_corr0 - ((float)ec->play_hist[0] / 
					          old_play_frm_level) +
		         ((float)ec->play_hist[ec->templ_cnt-1] /
			         ec->play_hist[ec->templ_cnt-2]);
	sum_play_level = ec->sum_play_level0;
	play_corr = ec->play_corr0;
    }
    ec->tmp_corr[0] = FABS(play_corr - ec->rec_corr);
    ec->tmp_factor[0] = (float)ec->sum_rec_level / sum_play_level;

    /* Bail out if remote isn't talking */
    ulaw = pjmedia_linear2ulaw(sum_play_level/ec->templ_cnt) ^ 0xFF;
    if (ulaw < MIN_SIGNAL_ULAW) {
	echo_supp_set_state(ec, ST_REM_SILENT, ulaw);
	return;
    }
    /* Bail out if local user is talking */
    if (ec->sum_rec_level >= sum_play_level) {
	echo_supp_set_state(ec, ST_LOCAL_TALK, ulaw);
	return;
    }

    /*
     * Second phase: do incremental calculation for the rest of positions
     */
    for (i=1; i < ec->tail_cnt; ++i) {
	unsigned end;

	end = i + ec->templ_cnt;

	sum_play_level = sum_play_level - ec->play_hist[i-1] +
			 ec->play_hist[end-1];
	play_corr = play_corr - ((float)ec->play_hist[i]/ec->play_hist[i-1]) +
		    ((float)ec->play_hist[end-1]/ec->play_hist[end-2]);

	/* Bail out if remote isn't talking */
	ulaw = pjmedia_linear2ulaw(sum_play_level/ec->templ_cnt) ^ 0xFF;
	if (ulaw < MIN_SIGNAL_ULAW) {
	    echo_supp_set_state(ec, ST_REM_SILENT, ulaw);
	    return;
	}

	/* Bail out if local user is talking */
	if (ec->sum_rec_level >= sum_play_level) {
	    echo_supp_set_state(ec, ST_LOCAL_TALK, ulaw);
	    return;
	}

#if 0
	// disabled: not a good idea if mic throws out loud echo
	/* Also bail out if we suspect there's a doubletalk */
	ulaw = pjmedia_linear2ulaw(ec->sum_rec_level/ec->templ_cnt) ^ 0xFF;
	if (ulaw > MIN_SIGNAL_ULAW) {
	    echo_supp_set_state(ec, ST_DOUBLETALK, ulaw);
	    return;
	}
#endif

	/* Calculate correlation and save to temporary array */
	ec->tmp_corr[i] = FABS(play_corr - ec->rec_corr);

	/* Also calculate the gain factor between mic and speaker level */
	ec->tmp_factor[i] = (float)ec->sum_rec_level / sum_play_level;
	pj_assert(ec->tmp_factor[i] < 1);
    }

    /* We seem to have good signal, we can update the EC state */
    echo_supp_set_state(ec, ST_REM_TALK, MIN_SIGNAL_ULAW);

    /* Accummulate the correlation value to the history and at the same
     * time find the tail index of the best correlation.
     */
    prev_index = ec->tail_index;
    for (i=1; i<ec->tail_cnt-1; ++i) {
	float *p = &ec->corr_sum[i], sum;

	/* Accummulate correlation value  for this tail position */
	ec->corr_sum[i] += ec->tmp_corr[i];

	/* Update the min and avg gain factor for this tail position */
	if (ec->tmp_factor[i] < ec->min_factor[i])
	    ec->min_factor[i] = ec->tmp_factor[i];
	ec->avg_factor[i] = ((ec->avg_factor[i] * ec->tail_cnt) + 
				    ec->tmp_factor[i]) /
			    (ec->tail_cnt + 1);

	/* To get the best correlation, also include the correlation
	 * value of the neighbouring tail locations.
	 */
	sum = *(p-1) + (*p)*2 + *(p+1);
	//sum = *p;

	/* See if we have better correlation value */
	if (sum < ec->best_corr) {
	    ec->tail_index = i;
	    ec->best_corr = sum;
	}
    }

    if (ec->tail_index != prev_index) {
	unsigned duration;
	int imin, iavg;

	duration = ec->update_cnt * SEGMENT_PTIME;
	imin = (int)(ec->min_factor[ec->tail_index] * 1000);
	iavg = (int)(ec->avg_factor[ec->tail_index] * 1000);

	PJ_LOG(4,(THIS_FILE, 
		  "Echo suppressor updated at t=%03d.%03ds, echo tail=%d msec"
		  ", factor min/avg=%d.%03d/%d.%03d",
		  (duration/1000), (duration%1000),
		  (ec->tail_cnt-ec->tail_index) * SEGMENT_PTIME,
		  imin/1000, imin%1000,
		  iavg/1000, iavg%1000));

    }

    ++ec->calc_cnt;

    if (ec->calc_cnt > ec->max_calc) {
	unsigned duration;
	int imin, iavg;


	ec->learning = PJ_FALSE;
	ec->running_cnt = 0;

	duration = ec->update_cnt * SEGMENT_PTIME;
	imin = (int)(ec->min_factor[ec->tail_index] * 1000);
	iavg = (int)(ec->avg_factor[ec->tail_index] * 1000);

	PJ_LOG(4,(THIS_FILE, 
	          "Echo suppressor learning done at t=%03d.%03ds, tail=%d ms"
		  ", factor min/avg=%d.%03d/%d.%03d",
		  (duration/1000), (duration%1000),
		  (ec->tail_cnt-ec->tail_index) * SEGMENT_PTIME,
		  imin/1000, imin%1000,
		  iavg/1000, iavg%1000));
    }

}