SPAN_DECLARE(int) dtmf_rx(dtmf_rx_state_t *s, const int16_t amp[], int samples)
{
#if defined(SPANDSP_USE_FIXED_POINT)
    int32_t row_energy[4];
    int32_t col_energy[4];
    int16_t xamp;
    float famp;
#else
    float row_energy[4];
    float col_energy[4];
    float xamp;
    float famp;
#endif
    float v1;
    int i;
    int j;
    int sample;
    int best_row;
    int best_col;
    int limit;
    uint8_t hit;

    hit = 0;
    for (sample = 0;  sample < samples;  sample = limit)
    {
        /* The block length is optimised to meet the DTMF specs. */
        if ((samples - sample) >= (DTMF_SAMPLES_PER_BLOCK - s->current_sample))
            limit = sample + (DTMF_SAMPLES_PER_BLOCK - s->current_sample);
        else
            limit = samples;
        /* The following unrolled loop takes only 35% (rough estimate) of the 
           time of a rolled loop on the machine on which it was developed */
        for (j = sample;  j < limit;  j++)
        {
            xamp = amp[j];
            if (s->filter_dialtone)
            {
                famp = xamp;
                /* Sharp notches applied at 350Hz and 440Hz - the two common dialtone frequencies.
                   These are rather high Q, to achieve the required narrowness, without using lots of
                   sections. */
                v1 = 0.98356f*famp + 1.8954426f*s->z350[0] - 0.9691396f*s->z350[1];
                famp = v1 - 1.9251480f*s->z350[0] + s->z350[1];
                s->z350[1] = s->z350[0];
                s->z350[0] = v1;

                v1 = 0.98456f*famp + 1.8529543f*s->z440[0] - 0.9691396f*s->z440[1];
                famp = v1 - 1.8819938f*s->z440[0] + s->z440[1];
                s->z440[1] = s->z440[0];
                s->z440[0] = v1;
                xamp = famp;
            }
            xamp = goertzel_preadjust_amp(xamp);
#if defined(SPANDSP_USE_FIXED_POINT)
            s->energy += ((int32_t) xamp*xamp);
#else
            s->energy += xamp*xamp;
#endif
            goertzel_samplex(&s->row_out[0], xamp);
            goertzel_samplex(&s->col_out[0], xamp);
            goertzel_samplex(&s->row_out[1], xamp);
            goertzel_samplex(&s->col_out[1], xamp);
            goertzel_samplex(&s->row_out[2], xamp);
            goertzel_samplex(&s->col_out[2], xamp);
            goertzel_samplex(&s->row_out[3], xamp);
            goertzel_samplex(&s->col_out[3], xamp);
        }
        if (s->duration < INT_MAX - (limit - sample))
            s->duration += (limit - sample);
        s->current_sample += (limit - sample);
        if (s->current_sample < DTMF_SAMPLES_PER_BLOCK)
            continue;

        /* We are at the end of a DTMF detection block */
        /* Find the peak row and the peak column */
        row_energy[0] = goertzel_result(&s->row_out[0]);
        best_row = 0;
        col_energy[0] = goertzel_result(&s->col_out[0]);
        best_col = 0;
        for (i = 1;  i < 4;  i++)
        {
            row_energy[i] = goertzel_result(&s->row_out[i]);
            if (row_energy[i] > row_energy[best_row])
                best_row = i;
            col_energy[i] = goertzel_result(&s->col_out[i]);
            if (col_energy[i] > col_energy[best_col])
                best_col = i;
        }
        hit = 0;
        /* Basic signal level test and the twist test */
        if (row_energy[best_row] >= s->threshold
            &&
            col_energy[best_col] >= s->threshold)
        {
            if (col_energy[best_col] < row_energy[best_row]*s->reverse_twist
                &&
                col_energy[best_col]*s->normal_twist > row_energy[best_row])
            {
                /* Relative peak test ... */
                for (i = 0;  i < 4;  i++)
                {
                    if ((i != best_col  &&  col_energy[i]*DTMF_RELATIVE_PEAK_COL > col_energy[best_col])
                        ||
                        (i != best_row  &&  row_energy[i]*DTMF_RELATIVE_PEAK_ROW > row_energy[best_row]))
                    {
                        break;
                    }
                }
                /* ... and fraction of total energy test */
                if (i >= 4
                    &&
                    (row_energy[best_row] + col_energy[best_col]) > DTMF_TO_TOTAL_ENERGY*s->energy)
                {
                    /* Got a hit */
                    hit = dtmf_positions[(best_row << 2) + best_col];
                }
            }
            if (span_log_test(&s->logging, SPAN_LOG_FLOW))
            {
                /* Log information about the quality of the signal, to aid analysis of detection problems */
                /* Logging at this point filters the total no-hoper frames out of the log, and leaves
                   anything which might feasibly be a DTMF digit. The log will then contain a list of the
                   total, row and coloumn power levels for detailed analysis of detection problems. */
                span_log(&s->logging,
                         SPAN_LOG_FLOW,
                         "Potentially '%c' - total %.2fdB, row %.2fdB, col %.2fdB - %s\n",
                         dtmf_positions[(best_row << 2) + best_col],
                         log10f(s->energy)*10.0f - DTMF_POWER_OFFSET + DBM0_MAX_POWER,
                         log10f(row_energy[best_row]/DTMF_TO_TOTAL_ENERGY)*10.0f - DTMF_POWER_OFFSET + DBM0_MAX_POWER,
                         log10f(col_energy[best_col]/DTMF_TO_TOTAL_ENERGY)*10.0f - DTMF_POWER_OFFSET + DBM0_MAX_POWER,
                         (hit)  ?  "hit"  :  "miss");
            }
        }
        /* The logic in the next test should ensure the following for different successive hit patterns:
                -----ABB = start of digit B.
                ----B-BB = start of digit B
                ----A-BB = start of digit B
                BBBBBABB = still in digit B.
                BBBBBB-- = end of digit B
                BBBBBBC- = end of digit B
                BBBBACBB = B ends, then B starts again.
                BBBBBBCC = B ends, then C starts.
                BBBBBCDD = B ends, then D starts.
           This can work with:
                - Back to back differing digits. Back-to-back digits should
                  not happen. The spec. says there should be a gap between digits.
                  However, many real phones do not impose a gap, and rolling across
                  the keypad can produce little or no gap.
                - It tolerates nasty phones that give a very wobbly start to a digit.
                - VoIP can give sample slips. The phase jumps that produces will cause
                  the block it is in to give no detection. This logic will ride over a
                  single missed block, and not falsely declare a second digit. If the
                  hiccup happens in the wrong place on a minimum length digit, however
                  we would still fail to detect that digit. Could anything be done to
                  deal with that? Packet loss is clearly a no-go zone.
                  Note this is only relevant to VoIP using A-law, u-law or similar.
                  Low bit rate codecs scramble DTMF too much for it to be recognised,
                  and often slip in units larger than a sample. */
        if (hit != s->in_digit)
        {
            if (s->last_hit != s->in_digit)
            {
                /* We have two successive indications that something has changed. */
                /* To declare digit on, the hits must agree. Otherwise we declare tone off. */
                hit = (hit  &&  hit == s->last_hit)  ?  hit   :  0;
                if (s->realtime_callback)
                {
                    /* Avoid reporting multiple no digit conditions on flaky hits */
                    if (s->in_digit  ||  hit)
                    {
                        i = (s->in_digit  &&  !hit)  ?  -99  :  lfastrintf(log10f(s->energy)*10.0f - DTMF_POWER_OFFSET + DBM0_MAX_POWER);
                        s->realtime_callback(s->realtime_callback_data, hit, i, s->duration);
                        s->duration = 0;
                    }
                }
                else
                {
                    if (hit)
                    {
                        if (s->current_digits < MAX_DTMF_DIGITS)
                        {
                            s->digits[s->current_digits++] = (char) hit;
                            s->digits[s->current_digits] = '\0';
                            if (s->digits_callback)
                            {
                                s->digits_callback(s->digits_callback_data, s->digits, s->current_digits);
                                s->current_digits = 0;
                            }
                        }
                        else
                        {
                            s->lost_digits++;
                        }
                    }
                }
                s->in_digit = hit;
            }
        }
        s->last_hit = hit;
#if defined(SPANDSP_USE_FIXED_POINT)
        s->energy = 0;
#else
        s->energy = 0.0f;
#endif
        s->current_sample = 0;
    }
    if (s->current_digits  &&  s->digits_callback)
    {
        s->digits_callback(s->digits_callback_data, s->digits, s->current_digits);
        s->digits[0] = '\0';
        s->current_digits = 0;
    }
    return 0;
}