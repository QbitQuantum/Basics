static int32_t ctrl7a_set(CSOUND *csound, CTRL7a *p)
{
    int32_t ctlno, chan;
    MYFLT   cutoff, b;


    if ((ctlno = (int32_t) *p->ictlno) < 0 || ctlno > 127)
      return csound->InitError(csound, Str("illegal controller number"));
    else if ((chan=(int32_t) *p->ichan-1) < 0 || chan > 15)
      return csound->InitError(csound, Str("illegal midi channel"));
    else p->ctlno = ctlno;

    if (*p->ifn > 0) {
      if (UNLIKELY(((p->ftp = csound->FTnp2Find(csound, p->ifn)) == NULL)))
        p->flag = 0;  /* invalid ftable */
      else p->flag= 1;
    }
    else p->flag= 0;

    p->yt1 = FL(0.0);
    if (*p->icutoff <= 0) cutoff = 5;
    else cutoff = *p->icutoff;

    b = FL(2.0) - COS(cutoff * csound->tpidsr * CS_KSMPS);
    p->c2 = b - SQRT(b * b - 1.0);
    p->c1 = FL(1.0) - p->c2;
    p->prev = 0;
    return OK;
}