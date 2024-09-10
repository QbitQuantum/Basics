void
padsynth_oscillator(unsigned long sample_count, y_sosc_t *sosc,
                    y_voice_t *voice, struct vosc *vosc, int index, float w0)
{
    unsigned long sample;
    float w, w_delta,
          level_a, level_a_delta,
          level_b, level_b_delta;
    float f;
    int   i, ready;

    i = y_voice_mod_index(sosc->pitch_mod_src);
    f = *(sosc->pitch_mod_amt);
    w = 1.0f + f * voice->mod[i].value;
    w_delta = w + f * voice->mod[i].delta * (float)sample_count;
    w_delta *= w0;
    w       *= w0;
    w_delta = (w_delta - w) / (float)sample_count;
    /* -FIX- condition to [0, 0.5)? */

    i = y_voice_mod_index(sosc->amp_mod_src);
    f = *(sosc->amp_mod_amt);
    if (f > 0.0f)
        level_a = 1.0f - f + f * voice->mod[i].value;
    else
        level_a = 1.0f + f * voice->mod[i].value;
    level_a_delta = volume_cv_to_amplitude(level_a + f * voice->mod[i].delta * (float)sample_count);
    level_a       = volume_cv_to_amplitude(level_a);
    level_a       /= 32767.0f;
    level_a_delta /= 32767.0f;
    level_b       = level_a       * *(sosc->level_b);
    level_b_delta = level_a_delta * *(sosc->level_b);
    level_a       *= *(sosc->level_a);
    level_a_delta *= *(sosc->level_a);
    level_a_delta = (level_a_delta - level_a) / (float)sample_count;
    level_b_delta = (level_b_delta - level_b) / (float)sample_count;
    /* -FIX- condition to [0, 1]? */

    if (sosc->sampleset && sosc->sampleset->set_up) {

        i = voice->key + lrintf(*(sosc->pitch));
        if (vosc->mode     != vosc->last_mode ||
            vosc->waveform != vosc->last_waveform ||
            i              != vosc->wave_select_key) {

            /* get sample indices and crossfade from sampleset */
            sample_select(sosc, vosc, i);
            vosc->last_waveform = vosc->waveform;
            /* try to avoid reseting pos0 except when necessary to avoid causing clocks in mono
             * mode with portamento -- but basically it's going to click if it's not the same
             * sample.... */
            if (vosc->mode != vosc->last_mode) {
                vosc->last_mode = vosc->mode;
                if (sosc->sampleset->sample[vosc->i0])
                    vosc->pos0 = vosc->pos1 = (double)random_float(0.0f,
                                                  (float)sosc->sampleset->sample[vosc->i0]->length);
                else
                    vosc->pos0 = vosc->pos1 = 0.0;
            }
        }
        if (sosc->sampleset->sample[vosc->i0] &&
            sosc->sampleset->sample[vosc->i1])
            ready = 1;
        else
            ready = 0;
    } else {
        if (vosc->mode != vosc->last_mode) {
            vosc->last_mode = vosc->mode;
            vosc->pos0 = vosc->pos1 = 0.0;
        }
        vosc->last_waveform = -1;
        ready = 0;
    }

    if (!ready) {
        /* sampleset not ready, render a sine instead */
        float pos = (float)vosc->pos0;

        if (pos > 1.0f) pos = 0.0f;
        level_a       *= 16383.5f; /* scale for sine_wave (float) instead of sample->data (16-bit fixed) */
        level_a_delta *= 16383.5f;
        level_b       *= 16383.5f;
        level_b_delta *= 16383.5f;

        for (sample = 0; sample < sample_count; sample++) {

            pos += w;
            if (pos >= 1.0f) pos -= 1.0f;

            f = pos * (float)SINETABLE_POINTS;
            i = lrintf(f - 0.5f);
            f -= (float)i;
            f = sine_wave[i + 4] + (sine_wave[i + 5] - sine_wave[i + 4]) * f;
            voice->osc_bus_a[index]   += level_a * f;
            voice->osc_bus_b[index++] += level_b * f;

            w       += w_delta;
            level_a += level_a_delta;
            level_b += level_b_delta;
        }

        vosc->pos0 = (double)pos;
        return;
    }

    if (sosc->sampleset->param3 & 1) {  /* mono */
      if (vosc->i0 == vosc->i1) { /* no crossfade */

        /* mono without crossfade */
        y_sample_t *s = (y_sample_t *)sosc->sampleset->sample[vosc->i0];
        signed short *data = s->data;
        double pos = vosc->pos0;
        double length = (double)s->length;
        float period = s->period;

        if (pos >= length) pos = 0.0;

        for (sample = 0; sample < sample_count; sample++) {

            i = lrint(pos - 0.5);
            f = (float)(pos - (double)i);
            f = bspline_interp(f, (float)data[i - 1], (float)data[i],
                                  (float)data[i + 1], (float)data[i + 2]);
            voice->osc_bus_a[index]   += level_a * f;
            voice->osc_bus_b[index++] += level_b * f;

            w       += w_delta;
            level_a += level_a_delta;
            level_b += level_b_delta;

            pos += w * period;
            if (pos >= length) pos -= length;
            /* sampleset oscillators do not export sync */
        }

        vosc->pos0 = pos;

      } else {

        /* mono with crossfade */
        y_sample_t *s0 = (y_sample_t *)sosc->sampleset->sample[vosc->i0],
                   *s1 = (y_sample_t *)sosc->sampleset->sample[vosc->i1];
        signed short *data0 = s0->data,
                     *data1 = s1->data;
        double pos0 = vosc->pos0,
               pos1 = vosc->pos1;
        double length0 = (double)s0->length,
               length1 = (double)s1->length;
        float period0 = s0->period,
              period1 = s1->period;
        float a,
              wavemix0 = vosc->wavemix0,
              wavemix1 = vosc->wavemix1;

        if (pos0 >= length0) pos0 = 0.0;
        if (pos1 >= length1) pos1 = 0.0;

        for (sample = 0; sample < sample_count; sample++) {

            i = lrint(pos0 - 0.5);
            f = (float)(pos0 - (double)i);
            a = bspline_interp(f, (float)data0[i - 1], (float)data0[i],
                                  (float)data0[i + 1], (float)data0[i + 2]) * wavemix0;

            i = lrint(pos1 - 0.5);
            f = (float)(pos1 - (double)i);
            a += bspline_interp(f, (float)data1[i - 1], (float)data1[i],
                                  (float)data1[i + 1], (float)data1[i + 2]) * wavemix1;

            voice->osc_bus_a[index]   += level_a * a;
            voice->osc_bus_b[index++] += level_b * a;

            w       += w_delta;
            level_a += level_a_delta;
            level_b += level_b_delta;

            pos0 += w * period0;
            pos1 += w * period1;
            if (pos0 >= length0) pos0 -= length0;
            if (pos1 >= length1) pos1 -= length1;
            /* sampleset oscillators do not export sync */
        }

        vosc->pos0 = pos0;
        vosc->pos1 = pos1;
      }

    } else {

      if (vosc->i0 == vosc->i1) {

        /* stereo without crossfade */
        y_sample_t *s = (y_sample_t *)sosc->sampleset->sample[vosc->i0];
        signed short *data = s->data;
        double posl = vosc->pos0,
               posr,
               length = (double)s->length;
        float period = s->period;

        if (posl >= length) posl = 0.0;
        /* delay the right channel by about one-half the table length, but make
         * it an multiple of the period length to minimize phase cancellation
         * when summed to mono */
        posr = posl + rint(length / 2.0 / (double)period) * (double)period;
        if (posr >= length) posr -= length;

        for (sample = 0; sample < sample_count; sample++) {

            i = lrint(posl - 0.5);
            f = (float)(posl - (double)i);
            f = bspline_interp(f, (float)data[i - 1], (float)data[i],
                                  (float)data[i + 1], (float)data[i + 2]);
            voice->osc_bus_a[index]   += level_a * f;

            i = lrint(posr - 0.5);
            f = (float)(posr - (double)i);
            f = bspline_interp(f, (float)data[i - 1], (float)data[i],
                                  (float)data[i + 1], (float)data[i + 2]);
            voice->osc_bus_b[index++] += level_b * f;

            w       += w_delta;
            level_a += level_a_delta;
            level_b += level_b_delta;

            posl += w * period;
            if (posl >= length) posl -= length;
            posr += w * period;
            if (posr >= length) posr -= length;
            /* sampleset oscillators do not export sync */
        }

        vosc->pos0 = posl;

      } else {

        /* stereo with crossfade */
        y_sample_t *s0 = (y_sample_t *)sosc->sampleset->sample[vosc->i0],
                   *s1 = (y_sample_t *)sosc->sampleset->sample[vosc->i1];
        signed short *data0 = s0->data,
                     *data1 = s1->data;
        double posl0 = vosc->pos0,
               posl1 = vosc->pos1,
               posr0, posr1;
        double length0 = (double)s0->length,
               length1 = (double)s1->length;
        float period0 = s0->period,
              period1 = s1->period;
        float a,
              wavemix0 = vosc->wavemix0,
              wavemix1 = vosc->wavemix1;

        if (posl0 >= length0) posl0 = 0.0;
        if (posl1 >= length1) posl1 = 0.0;
        posr0 = posl0 + rint(length0 / 2.0 / (double)period0) * (double)period0;
        posr1 = posl1 + rint(length1 / 2.0 / (double)period1) * (double)period1;
        if (posr0 >= length0) posr0 -= length0;
        if (posr1 >= length1) posr1 -= length1;

        for (sample = 0; sample < sample_count; sample++) {

            i = lrint(posl0 - 0.5);
            f = (float)(posl0 - (double)i);
            a = bspline_interp(f, (float)data0[i - 1], (float)data0[i],
                                  (float)data0[i + 1], (float)data0[i + 2]) * wavemix0;
            i = lrint(posl1 - 0.5);
            f = (float)(posl1 - (double)i);
            a += bspline_interp(f, (float)data1[i - 1], (float)data1[i],
                                  (float)data1[i + 1], (float)data1[i + 2]) * wavemix1;
            voice->osc_bus_a[index]   += level_a * a;

            i = lrint(posr0 - 0.5);
            f = (float)(posr0 - (double)i);
            a = bspline_interp(f, (float)data0[i - 1], (float)data0[i],
                                  (float)data0[i + 1], (float)data0[i + 2]) * wavemix0;
            i = lrint(posr1 - 0.5);
            f = (float)(posr1 - (double)i);
            a += bspline_interp(f, (float)data1[i - 1], (float)data1[i],
                                  (float)data1[i + 1], (float)data1[i + 2]) * wavemix1;
            voice->osc_bus_b[index++] += level_b * a;

            w       += w_delta;
            level_a += level_a_delta;
            level_b += level_b_delta;

            posl0 += w * period0;
            posr0 += w * period0;
            posl1 += w * period1;
            posr1 += w * period1;
            if (posl0 >= length0) posl0 -= length0;
            if (posr0 >= length0) posr0 -= length0;
            if (posl1 >= length1) posl1 -= length1;
            if (posr1 >= length1) posr1 -= length1;
            /* sampleset oscillators do not export sync */
        }

        vosc->pos0 = posl0;
        vosc->pos1 = posl1;
      }
    }
}