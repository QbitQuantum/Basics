static int 
_csngen_adjust_local_time (CSNGen *gen, time_t cur_time)
{
    extern int config_get_ignore_time_skew(void);
    int ignore_time_skew = config_get_ignore_time_skew();
    time_t time_diff = cur_time - gen->state.sampled_time;

    if (time_diff == 0) {
        /* This is a no op - _csngen_adjust_local_time should never be called
           in this case, because there is nothing to adjust - but just return
           here to protect ourselves
        */
        return CSN_SUCCESS;
    }
    else if (time_diff > 0)
    {
        time_t ts_before = CSN_CALC_TSTAMP(gen);
        time_t ts_after = 0;
        if (slapi_is_loglevel_set(SLAPI_LOG_REPL)) {
            time_t new_time = CSN_CALC_TSTAMP(gen);
            slapi_log_err(SLAPI_LOG_REPL, "_csngen_adjust_local_time",
                             "gen state before %08lx%04x:%ld:%ld:%ld\n",
                             new_time, gen->state.seq_num,
                             gen->state.sampled_time,
                             gen->state.local_offset,
                             gen->state.remote_offset);
        }

        gen->state.sampled_time = cur_time;
        if (time_diff > gen->state.local_offset)
            gen->state.local_offset = 0;
        else
            gen->state.local_offset = gen->state.local_offset - time_diff;

        /* only reset the seq_num if the new timestamp part of the CSN
           is going to be greater than the old one - if they are the
           same after the above adjustment (which can happen if
           csngen_adjust_time has to store the offset in the
           local_offset field) we must not allow the CSN to regress or
           generate duplicate numbers */
        ts_after = CSN_CALC_TSTAMP(gen);
        if (ts_after > ts_before) {
            gen->state.seq_num = 0; /* only reset if new time > old time */
        }

        if (slapi_is_loglevel_set(SLAPI_LOG_REPL)) {
            time_t new_time = CSN_CALC_TSTAMP(gen);
            slapi_log_err(SLAPI_LOG_REPL, "_csngen_adjust_local_time",
                             "gen state after %08lx%04x:%ld:%ld:%ld\n",
                             new_time, gen->state.seq_num,
                             gen->state.sampled_time,
                             gen->state.local_offset,
                             gen->state.remote_offset);
        }
        return CSN_SUCCESS;
    }
    else   /* time was turned back */
    {
        if (slapi_is_loglevel_set(SLAPI_LOG_REPL)) {
            time_t new_time = CSN_CALC_TSTAMP(gen);
            slapi_log_err(SLAPI_LOG_REPL, "_csngen_adjust_local_time",
                             "gen state back before %08lx%04x:%ld:%ld:%ld\n",
                             new_time, gen->state.seq_num,
                             gen->state.sampled_time,
                             gen->state.local_offset,
                             gen->state.remote_offset);
        }

        if (!ignore_time_skew && (labs (time_diff) > CSN_MAX_TIME_ADJUST))
        {
            slapi_log_err(SLAPI_LOG_ERR, "_csngen_adjust_local_time",
                             "Adjustment limit exceeded; value - %ld, limit - %d\n",
                             labs (time_diff), CSN_MAX_TIME_ADJUST);
            return CSN_LIMIT_EXCEEDED;
        }    

        gen->state.sampled_time = cur_time;
        gen->state.local_offset = MAX_VAL (gen->state.local_offset, labs (time_diff));
        gen->state.seq_num = 0;

        if (slapi_is_loglevel_set(SLAPI_LOG_REPL)) {
            time_t new_time = CSN_CALC_TSTAMP(gen);
            slapi_log_err(SLAPI_LOG_REPL, "_csngen_adjust_local_time",
                             "gen state back after %08lx%04x:%ld:%ld:%ld\n",
                             new_time, gen->state.seq_num,
                             gen->state.sampled_time,
                             gen->state.local_offset,
                             gen->state.remote_offset);
        }

        return CSN_SUCCESS;
    }
}