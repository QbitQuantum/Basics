int lfoset(CSOUND *csound, LFO *p)
{
  /* Types: 0:  sine
            1:  triangles
            2:  square (biplar)
            3:  square (unipolar)
            4:  saw-tooth
            5:  saw-tooth(down)
            */
    int type = (int)*p->type;
    if (type == 0) {            /* Sine wave so need to create */
      int i;
      if (p->auxd.auxp==NULL) {
        csound->AuxAlloc(csound, sizeof(MYFLT)*4097L, &p->auxd);
        p->sine = (MYFLT*)p->auxd.auxp;
      }
      for (i=0; i<4096; i++)
        p->sine[i] = SIN(TWOPI_F*(MYFLT)i/FL(4096.0));
/*        csound->Message(csound,"Table set up (max is %d)\n", MAXPHASE>>10); */
    }
    else if (UNLIKELY(type>5 || type<0)) {
      return csound->InitError(csound, Str("LFO: unknown oscilator type %d"),
                                       type);
    }
    p->lasttype = type;
    p->phs = 0;
    return OK;
}