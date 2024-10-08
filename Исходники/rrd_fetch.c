int rrd_fetch_fn(
    const char *filename,   /* name of the rrd */
    enum cf_en cf_idx,  /* which consolidation function ? */
    time_t *start,
    time_t *end,        /* which time frame do you want ?
                         * will be changed to represent reality */
    unsigned long *step,    /* which stepsize do you want? 
                             * will be changed to represent reality */
    unsigned long *ds_cnt,  /* number of data sources in file */
    char ***ds_namv,    /* names of data_sources */
    rrd_value_t **data)
{                       /* two dimensional array containing the data */
    long      i, ii;
    time_t    cal_start, cal_end, rra_start_time, rra_end_time;
    long      best_full_rra = 0, best_part_rra = 0, chosen_rra =
        0, rra_pointer = 0;
    long      best_full_step_diff = 0, best_part_step_diff =
        0, tmp_step_diff = 0, tmp_match = 0, best_match = 0;
    long      full_match, rra_base;
    off_t     start_offset, end_offset;
    int       first_full = 1;
    int       first_part = 1;
    rrd_t     rrd;
    rrd_file_t *rrd_file;
    rrd_value_t *data_ptr;
    unsigned long rows;

#ifdef DEBUG
    fprintf(stderr, "Entered rrd_fetch_fn() searching for the best match\n");
    fprintf(stderr, "Looking for: start %10lu end %10lu step %5lu\n",
            *start, *end, *step);
#endif

#ifdef HAVE_LIBDBI
    /* handle libdbi datasources */
    if (strncmp("sql//",filename,5)==0) {
	return rrd_fetch_fn_libdbi(filename,cf_idx,start,end,step,ds_cnt,ds_namv,data);
    }
#endif

    rrd_init(&rrd);
    rrd_file = rrd_open(filename, &rrd, RRD_READONLY);
    if (rrd_file == NULL)
        goto err_free;

    /* when was the really last update of this file ? */

    if (((*ds_namv) =
         (char **) malloc(rrd.stat_head->ds_cnt * sizeof(char *))) == NULL) {
        rrd_set_error("malloc fetch ds_namv array");
        goto err_close;
    }

    for (i = 0; (unsigned long) i < rrd.stat_head->ds_cnt; i++) {
        if ((((*ds_namv)[i]) = (char*)malloc(sizeof(char) * DS_NAM_SIZE)) == NULL) {
            rrd_set_error("malloc fetch ds_namv entry");
            goto err_free_ds_namv;
        }
        strncpy((*ds_namv)[i], rrd.ds_def[i].ds_nam, DS_NAM_SIZE - 1);
        (*ds_namv)[i][DS_NAM_SIZE - 1] = '\0';

    }

    /* find the rra which best matches the requirements */
    for (i = 0; (unsigned) i < rrd.stat_head->rra_cnt; i++) {
        if (cf_conv(rrd.rra_def[i].cf_nam) == cf_idx) {

            cal_end = (rrd.live_head->last_up - (rrd.live_head->last_up
                                                 % (rrd.rra_def[i].pdp_cnt
                                                    *
                                                    rrd.stat_head->
                                                    pdp_step)));
            cal_start =
                (cal_end -
                 (rrd.rra_def[i].pdp_cnt * rrd.rra_def[i].row_cnt *
                  rrd.stat_head->pdp_step));

            full_match = *end - *start;
#ifdef DEBUG
            fprintf(stderr, "Considering: start %10lu end %10lu step %5lu ",
                    cal_start, cal_end,
                    rrd.stat_head->pdp_step * rrd.rra_def[i].pdp_cnt);
#endif
            /* we need step difference in either full or partial case */
            tmp_step_diff = labs(*step - (rrd.stat_head->pdp_step
                                          * rrd.rra_def[i].pdp_cnt));
            /* best full match */
            if (cal_start <= *start) {
                if (first_full || (tmp_step_diff < best_full_step_diff)) {
                    first_full = 0;
                    best_full_step_diff = tmp_step_diff;
                    best_full_rra = i;
#ifdef DEBUG
                    fprintf(stderr, "best full match so far\n");
                } else {
                    fprintf(stderr, "full match, not best\n");
#endif
                }

            } else {
                /* best partial match */
                tmp_match = full_match;
                if (cal_start > *start)
                    tmp_match -= (cal_start - *start);
                if (first_part ||
                    (best_match < tmp_match) ||
                    (best_match == tmp_match &&
                     tmp_step_diff < best_part_step_diff)) {
#ifdef DEBUG
                    fprintf(stderr, "best partial so far\n");
#endif
                    first_part = 0;
                    best_match = tmp_match;
                    best_part_step_diff = tmp_step_diff;
                    best_part_rra = i;
                } else {
#ifdef DEBUG
                    fprintf(stderr, "partial match, not best\n");
#endif
                }
            }
        }
    }

    /* lets see how the matching went. */
    if (first_full == 0)
        chosen_rra = best_full_rra;
    else if (first_part == 0)
        chosen_rra = best_part_rra;
    else {
        rrd_set_error
            ("the RRD does not contain an RRA matching the chosen CF");
        goto err_free_all_ds_namv;
    }

    /* set the wish parameters to their real values */
    *step = rrd.stat_head->pdp_step * rrd.rra_def[chosen_rra].pdp_cnt;
    *start -= (*start % *step);
    *end += (*step - *end % *step);
    rows = (*end - *start) / *step + 1;

#ifdef DEBUG
    fprintf(stderr,
            "We found:    start %10lu end %10lu step %5lu rows  %lu\n",
            *start, *end, *step, rows);
#endif

/* Start and end are now multiples of the step size.  The amount of
** steps we want is (end-start)/step and *not* an extra one.
** Reasoning:  if step is s and we want to graph from t to t+s,
** we need exactly ((t+s)-t)/s rows.  The row to collect from the
** database is the one with time stamp (t+s) which means t to t+s.
*/
    *ds_cnt = rrd.stat_head->ds_cnt;
    if (((*data) = (rrd_value_t*)malloc(*ds_cnt * rows * sizeof(rrd_value_t))) == NULL) {
        rrd_set_error("malloc fetch data area");
        goto err_free_all_ds_namv;
    }

    data_ptr = (*data);

    /* find base address of rra */
    rra_base = rrd_file->header_len;
    for (i = 0; i < chosen_rra; i++)
        rra_base += (*ds_cnt * rrd.rra_def[i].row_cnt * sizeof(rrd_value_t));

    /* find start and end offset */
    rra_end_time = (rrd.live_head->last_up
                    - (rrd.live_head->last_up % *step));
    rra_start_time = (rra_end_time
                      - (*step * (rrd.rra_def[chosen_rra].row_cnt - 1)));
    /* here's an error by one if we don't be careful */
    start_offset = ((long long) *start + (long long)*step - (long long)rra_start_time) / (long long) *step;
    end_offset = ((long long) rra_end_time - (long long)*end) / (long long) *step;
#ifdef DEBUG
    fprintf(stderr,
            "rra_start %lu, rra_end %lu, start_off %li, end_off %li\n",
            rra_start_time, rra_end_time, start_offset, end_offset);
#endif
    /* only seek if the start time is before the end time */
    if (*start <= rra_end_time && *end >= rra_start_time - (off_t)*step ){
        if (start_offset <= 0)
            rra_pointer = rrd.rra_ptr[chosen_rra].cur_row + 1;
        else
            rra_pointer = rrd.rra_ptr[chosen_rra].cur_row + 1 + start_offset;

        rra_pointer = rra_pointer % (signed) rrd.rra_def[chosen_rra].row_cnt;
         
        if (rrd_seek(rrd_file, (rra_base + (rra_pointer * (*ds_cnt)
                                        * sizeof(rrd_value_t))),
                 SEEK_SET) != 0) {
            rrd_set_error("seek error in RRA");
            goto err_free_data;
        }
#ifdef DEBUG
        fprintf(stderr, "First Seek: rra_base %lu rra_pointer %lu\n",
                rra_base, rra_pointer);
#endif
    }
    
    /* step trough the array */

    for (i = start_offset;
         i < (signed) rrd.rra_def[chosen_rra].row_cnt - end_offset; i++) {
        /* no valid data yet */
        if (i < 0) {
#ifdef DEBUG
            fprintf(stderr, "pre fetch %li -- ", i);
#endif
            for (ii = 0; (unsigned) ii < *ds_cnt; ii++) {
                *(data_ptr++) = DNAN;
#ifdef DEBUG
                fprintf(stderr, "%10.2f ", *(data_ptr - 1));
#endif
            }
        }
        /* past the valid data area */
        else if (i >= (signed) rrd.rra_def[chosen_rra].row_cnt) {
#ifdef DEBUG
            fprintf(stderr, "past fetch %li -- ", i);
#endif
            for (ii = 0; (unsigned) ii < *ds_cnt; ii++) {
                *(data_ptr++) = DNAN;
#ifdef DEBUG
                fprintf(stderr, "%10.2f ", *(data_ptr - 1));
#endif
            }
        } else {
            /* OK we are inside the valid area but the pointer has to 
             * be wrapped*/
            if (rra_pointer >= (signed) rrd.rra_def[chosen_rra].row_cnt) {
                rra_pointer -= rrd.rra_def[chosen_rra].row_cnt;
                if (rrd_seek(rrd_file, (rra_base + rra_pointer * (*ds_cnt)
                                        * sizeof(rrd_value_t)),
                             SEEK_SET) != 0) {
                    rrd_set_error("wrap seek in RRA did fail");
                    goto err_free_data;
                }
#ifdef DEBUG
                fprintf(stderr, "wrap seek ...\n");
#endif
            }

            if (rrd_read(rrd_file, data_ptr, sizeof(rrd_value_t) * (*ds_cnt))
                != (ssize_t) (sizeof(rrd_value_t) * (*ds_cnt))) {
                rrd_set_error("fetching cdp from rra");
                goto err_free_data;
            }
#ifdef DEBUG
            fprintf(stderr, "post fetch %li -- ", i);
            for (ii = 0; ii < *ds_cnt; ii++)
                fprintf(stderr, "%10.2f ", *(data_ptr + ii));
#endif
            data_ptr += *ds_cnt;
            rra_pointer++;
        }
#ifdef DEBUG
        fprintf(stderr, "\n");
#endif

    }

    rrd_close(rrd_file);
    rrd_free(&rrd);
    return (0);
  err_free_data:
    free(*data);
    *data = NULL;
  err_free_all_ds_namv:
    for (i = 0; (unsigned long) i < rrd.stat_head->ds_cnt; ++i)
        free((*ds_namv)[i]);
  err_free_ds_namv:
    free(*ds_namv);
  err_close:
    rrd_close(rrd_file);
  err_free:
    rrd_free(&rrd);
    return (-1);
}