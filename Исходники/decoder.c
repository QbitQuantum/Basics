void 
Decode(config * conf){
#ifdef ENABLE_PARSEC_HOOKS
    __parsec_roi_begin();
#endif
  RecvBlock(conf);
  Decompress(NULL);
  CheckCache(NULL);
  if (strcmp(conf->outfile, "") == 0)
    Reassemble(NULL);
  else Reassemble(conf->outfile);
#ifdef ENABLE_PARSEC_HOOKS
    __parsec_roi_end();
#endif
}