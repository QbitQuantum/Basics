static void compute_block(CSOUND *csound, PAULSTRETCH *p)
{
    uint32_t istart_pos = floor(p->start_pos);
    uint32_t pos;
    uint32_t i;
    uint32_t windowsize = p->windowsize;
    uint32_t half_windowsize = p->half_windowsize;
    MYFLT *hinv_buf = p->hinv_buf;
    MYFLT *old_windowed_buf= p->old_windowed_buf;
    MYFLT *tbl = p->ft->ftable;
    MYFLT *window = p->window;
    MYFLT *output= p->output;
    MYFLT *tmp = p->tmp;
    for (i = 0; i < windowsize; i++) {
      pos = istart_pos + i;
      if (pos < p->ft->flen) {
        tmp[i] = tbl[pos] * window[i];
      } else {
        tmp[i] = 0;
      }
    }
    /* re-order bins and take FFT */
    tmp[p->windowsize] = tmp[1];
    tmp[p->windowsize + 1] = 0.0;
    csoundRealFFTnp2(csound, tmp, p->windowsize);

    /* randomize phase */
    for (i = 0; i < windowsize + 2; i += 2) {
      MYFLT mag = HYPOT(tmp[i], tmp[i + 1]);
      // Android 5.1 does not seem to have cexpf ...
      // complex ph = cexpf(I * ((MYFLT)rand() / RAND_MAX) * 2 * M_PI);
      // so ...
      MYFLT  x = (((MYFLT)rand() / RAND_MAX) * 2 * M_PI);
      complex ph =  cos(x) + I*sin(x);
      tmp[i] = mag * (MYFLT)crealf(ph);
      tmp[i + 1] = mag * (MYFLT)cimagf(ph);
    }

    /* re-order bins and take inverse FFT */
    tmp[1] = tmp[p->windowsize];
    csoundInverseRealFFTnp2(csound, tmp, p->windowsize);

    /* apply window and overlap */
    for (i = 0; i < windowsize; i++) {
      tmp[i] *= window[i];
      if (i < half_windowsize) {
        output[i] = (MYFLT)(tmp[i] + old_windowed_buf[half_windowsize + i]);
        output[i] *= hinv_buf[i];
      }
      old_windowed_buf[i] = tmp[i];
    }
    p->start_pos += p->displace_pos;
}