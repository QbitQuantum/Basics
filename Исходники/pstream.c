static int32_t pvsfreadset_(CSOUND *csound, PVSFREAD *p, int32_t stringname)
{
    PVOCEX_MEMFILE  pp;
    uint32   N;
    char            pvfilnam[MAXNAME];

    if (stringname) strNcpy(pvfilnam, ((STRINGDAT*)p->ifilno)->data, MAXNAME-1);
    else if (csound->ISSTRCOD(*p->ifilno))
      strNcpy(pvfilnam, get_arg_string(csound, *p->ifilno), MAXNAME-1);
    else csound->strarg2name(csound, pvfilnam, p->ifilno, "pvoc.", 0);

    if (UNLIKELY(PVOCEX_LoadFile(csound, pvfilnam, &pp) != 0)) {
      return csound->InitError(csound, Str("Failed to load PVOC-EX file"));
    }
    p->ptr = 0;
    p->overlap = pp.overlap;
    p->winsize = pp.winsize;
    p->fftsize = pp.fftsize;
    p->wintype = pp.wintype;
    p->format  = pp.format;
    p->chans   = pp.chans;
    p->nframes = pp.nframes;
    p->arate   = csound->esr / (MYFLT) pp.overlap;
    p->membase = (float*) pp.data;

    if (UNLIKELY(p->overlap < (int32_t)CS_KSMPS || p->overlap < 10))
      return csound->InitError(csound, Str("Sliding version not yet available"));
    if (UNLIKELY(p->nframes <= 0))
      return csound->InitError(csound, Str("pvsfread: file is empty!\n"));
    /* special case if only one frame - it is an impulse response */
    if (UNLIKELY(p->nframes == 1))
      return csound->InitError(csound, Str("pvsfread: file has only one frame "
                              "(= impulse response).\n"));
    if (UNLIKELY(p->overlap < (int32_t)CS_KSMPS))
      return csound->InitError(csound, Str("pvsfread: analysis frame overlap "
                              "must be >= ksmps\n"));
    p->blockalign = (p->fftsize+2) * p->chans;
    if (UNLIKELY((*p->ichan) >= p->chans))
      return csound->InitError(csound, Str("pvsfread: ichan value exceeds "
                              "file channel count.\n"));
    if (UNLIKELY((int32_t) (*p->ichan) < 0))
      return csound->InitError(csound,
                               Str("pvsfread: ichan cannot be negative.\n"));

    N = p->fftsize;
    /* setup output signal */
    csound->AuxAlloc(csound, (N + 2) * sizeof(float), &p->fout->frame);
    /* init sig with first frame from file,
       regardless (always zero amps, but with bin freqs) */
    p->chanoffset = (int32_t) MYFLT2LRND(*p->ichan) * (N + 2);
    memcpy((float *) p->fout->frame.auxp,               /* RWD MUST be 32bit */
           (float *) pp.data + (int32_t) p->chanoffset,    /* RWD MUST be 32bit */
           (size_t) ((int32_t) (N + 2) * (int32_t) sizeof(float)));
    p->membase += p->blockalign;  /* move to 2nd frame in file, as startpoint */
    p->nframes--;
    p->fout->N           =  N;
    p->fout->overlap = p->overlap;
    p->fout->winsize = p->winsize;
    p->fout->wintype = p->wintype;
    p->fout->format  = p->format;
    p->fout->framecount = 1;
    p->lastframe = 0;
    return OK;
}