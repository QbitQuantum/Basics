int32_t kreads(CSOUND *csound, KREADS *p)
{
    if (--p->countdown <= 0) {
      p->countdown = p->timcount;
      if (UNLIKELY(fgets(p->lasts, INITSIZE-1,  p->f)==NULL)) {
        csound->PerfError(csound, &(p->h), Str("Read failure in readks"));
      }
    }
    strNcpy((char*) p->str->data, p->lasts, INITSIZE);
    return OK;
}