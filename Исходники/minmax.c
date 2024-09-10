/* Absolute value versions of the above */
static int32_t MaxAbsAccumulate(CSOUND *csound, MINMAXACCUM *p)
{
    IGN(csound);
    uint32_t offset = p->h.insdshead->ksmps_offset;
    uint32_t early  = p->h.insdshead->ksmps_no_end;
    uint32_t n, nsmps = CS_KSMPS;
    MYFLT   *out = p->accum;
    MYFLT   *in = p->ain;
    MYFLT   inabs;

    if (UNLIKELY(offset)) memset(out, '\0', offset*sizeof(MYFLT));
    if (UNLIKELY(early)) {
      nsmps -= early;
      memset(&out[nsmps], '\0', early*sizeof(MYFLT));
    }
    for (n=offset; n<nsmps; n++) {
      inabs = FABS(in[n]);
      if (UNLIKELY(inabs > out[n]))
        out[n] = inabs;
    }

    return OK;
}