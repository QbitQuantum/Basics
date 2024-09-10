int vibraphnset(CSOUND *csound, VIBRAPHN *p)
{
    Modal4      *m = &(p->m4);
    MYFLT       temp;
    FUNC        *ftp;

    if (LIKELY((ftp = csound->FTnp2Find(csound, p->ifn)) != NULL))
      p->m4.wave = ftp;         /* Expect an impulslything */
    else {
      return csound->InitError(csound, Str("No table for Vibraphone strike"));
    }

    if (UNLIKELY(make_Modal4(csound, m, p->ivfn, *p->vibAmt, *p->vibFreq)==NOTOK))
      return NOTOK;

    p->m4.w_phaseOffset = FL(0.0);
/*     p->m4.w_rate = 13.33; */
    OnePole_setPole(&p->m4.onepole, FL(0.2));
    Modal4_setRatioAndReson(csound, m, 0, FL(1.0), FL(0.99995)); /*  Set         */
    Modal4_setRatioAndReson(csound, m, 1, FL(2.01),FL(0.99991)); /*  our         */
    Modal4_setRatioAndReson(csound, m, 2, FL(3.9), FL(0.99992)); /*  resonance   */
    Modal4_setRatioAndReson(csound, m, 3,FL(14.37),FL(0.99990)); /*  values here */
    Modal4_setFiltGain(m, 0, FL(0.025));
    Modal4_setFiltGain(m, 1, FL(0.015));
    Modal4_setFiltGain(m, 2, FL(0.015));
    Modal4_setFiltGain(m, 3, FL(0.015));
    p->m4.directGain = FL(0.0);
/*     vibrGain = 0.2; */
    p->m4.w_rate = FL(2.0) + (FL(22.66) * *p->hardness);
    p->m4.masterGain = FL(0.2) + (*p->hardness * FL(1.6));
                                /* Set Strike position */
    temp = (p->strikePosition = *p->spos) * PI_F;
    BiQuad_setGain(p->m4.filters[0], FL(0.025) * SIN(temp));
    BiQuad_setGain(p->m4.filters[1], FL(0.015) *
                   SIN(FL(0.1) + (FL(2.01) * temp)));
    BiQuad_setGain(p->m4.filters[2], FL(0.015) * SIN(FL(3.95) * temp));
                                /* Strike */
    Modal4_strike(csound, m, *p->amplitude * AMP_RSCALE);
    Modal4_setFreq(csound, m, *p->frequency);
    p->first = 1;
    return OK;
}