void sfcloseout(CSOUND *csound)
{
    OPARMS  *O = csound->oparms;
    int     nb;

    alloc_globals(csound);
    if (!STA(osfopen))
      return;
    if ((nb = (O->outbufsamps - STA(outbufrem)) * sizeof(MYFLT)) > 0) {
      /* flush outbuffer */
      csound->nrecs++;
      csound->audtran(csound, STA(outbuf), nb);
    }
    if (STA(pipdevout) == 2 && (!STA(isfopen) || STA(pipdevin) != 2)) {
      /* close only if not open for input too */
      csound->rtclose_callback(csound);
    }
    if (STA(pipdevout) == 2)
      goto report;
    if (STA(outfile) != NULL) {
      if (!STA(pipdevout) && O->outformat != AE_VORBIS)
        sf_command(STA(outfile), SFC_UPDATE_HEADER_NOW, NULL, 0);
      sf_close(STA(outfile));
      STA(outfile) = NULL;
    }
#ifdef PIPES
    if (STA(pout) != NULL) {
      _pclose(STA(pout));
      STA(pout) = NULL;
    }
#endif

 report:
    if (STA(pipdevout) == 2) {
      csound->Message(csound,
                      "%"PRIi32" %d %s%lu%s%s\n",
                      csound->nrecs, O->outbufsamps, Str("sample blks of "),
                      (unsigned long)sizeof(MYFLT)*8,Str("-bit floats written to "),
                      STA(sfoutname));
    }
    else {
      csound->Message(csound, Str("%"PRIi32" %d sample blks of %s written to %s"),
                      O->outbufsamps, O->outbufsamps * O->sfsampsize,
                      getstrformat(O->outformat), STA(sfoutname));
      if (O->sfheader == 0)
        csound->Message(csound, Str(" (raw)\n"));
      else
        csound->Message(csound, " (%s)\n", type2string(O->filetyp));
    }
    STA(osfopen) = 0;
}