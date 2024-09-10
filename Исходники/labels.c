SLABELS *CreateSLabels(void){
  uint32_t n;
  SLABELS *SL = (SLABELS *) Calloc(1, sizeof(SLABELS));
  SL->idx     = 0;
  SL->maxV    = SLCACHE;
  SL->maxH    = SLMAXSTR;
  SL->names   = (uint8_t **) Calloc(SL->maxV, sizeof(uint8_t *));
  for(n = 0 ; n < SL->maxV ; ++n)
    SL->names[n] = (uint8_t *) Calloc(SL->maxH+1, sizeof(uint8_t));
  return SL;
  }