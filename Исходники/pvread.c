int32_t pvreadset_(CSOUND *csound, PVREAD *p, int32_t stringname)
{
    char      pvfilnam[256];

    if (stringname==0){
      if (csound->ISSTRCOD(*p->ifilno))
        strNcpy(pvfilnam,get_arg_string(csound, *p->ifilno), MAXNAME);
      else csound->strarg2name(csound, pvfilnam, p->ifilno, "pvoc.",0);
    }
    else strNcpy(pvfilnam, ((STRINGDAT *)p->ifilno)->data, MAXNAME);

    if (pvocex_loadfile(csound, pvfilnam, p) == OK) {
      p->prFlg = 1;
      p->mybin = MYFLT2LRND(*p->ibin);
      return OK;
    }
    return NOTOK;
}