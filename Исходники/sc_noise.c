static int32_t gausstrig_process_krate(CSOUND* csound, GAUSSTRIG *p)
{
    MYFLT frq, dev;
    p->frq0 = *p->kfrq;
    frq = (*p->kfrq > FL(0.001) ? *p->kfrq : FL(0.001));
    dev = *p->kdev;
    if (p->first > 0) {
      /* values less than FL(0.0) could be used in later versions
         as an offset in samples */
      int32_t     nextsamps;
      MYFLT   nextcount, r1, r2;
      /* this very line of k-time fix. Changed GetSt to GetKr */
      nextsamps = (int32_t)(csound->GetKr(csound) / frq);
      p->rand = csoundRand31(&p->rand);
      r1 = (MYFLT)p->rand * dv2_31;
      p->rand = csoundRand31(&p->rand);
      r2 = (MYFLT)p->rand * dv2_31;
      nextcount = SQRT(FL(-2.0) * LOG(r1)) * SIN(r2 * TWOPI_F);
      if (nextcount < FL(-1.0)) {
        MYFLT diff = FL(-1.0) - nextcount;
        nextcount  = (FL(1.0) < FL(-1.0) + diff ? FL(1.0) : FL(-1.0) + diff);
      }
      else if (nextcount > FL(1.0)) {
        MYFLT diff = nextcount - FL(1.0);
        nextcount  = (FL(-1.0) > FL(1.0) - diff ? FL(-1.0) : FL(1.0) - diff);
      }
      p->count = (int32_t)(nextsamps + nextcount * dev * nextsamps);
      p->first = 0;
    }
    if (p->count <= 0) {
      int32_t     nextsamps;
      MYFLT   nextcount, r1, r2;
/* this very line of k-time fix. Changed GetSt to GetKr */
      nextsamps = (int32_t)(csound->GetKr(csound) / frq);
      p->rand = csoundRand31(&p->rand);
      r1 = (MYFLT)p->rand * dv2_31;
      p->rand = csoundRand31(&p->rand);
      r2 = (MYFLT)p->rand * dv2_31;
      nextcount = SQRT(FL(-2.0) * LOG(r1)) * SIN(r2 * TWOPI_F);
      if (nextcount < FL(-1.0)) {
        MYFLT diff = FL(-1.0) - nextcount;
        nextcount  = (FL(1.0) < FL(-1.0) + diff ? FL(1.0) : FL(-1.0) + diff);
      }
      else if (nextcount > FL(1.0)) {
        MYFLT diff = nextcount - FL(1.0);
        nextcount  = (FL(-1.0) > FL(1.0) - diff ? FL(-1.0) : FL(1.0) - diff);
      }
      p->count = (int32_t)(nextsamps + nextcount * dev * nextsamps);
      *p->out = *p->kamp;
    }
    else {
      if (p->mmode && *p->kfrq != p->frq0)
        p->count = 0;
      *p->out = FL(0.0);
    }
    p->count--;
    return OK;
}