Nrrd *
_baneGkmsDonNew(int invert) {
  char me[]="_baneGkmsDonNew", err[BIFF_STRLEN];
  Nrrd *ret;
  float *data;

  if (nrrdMaybeAlloc_va(ret=nrrdNew(), nrrdTypeFloat, 2,
                        AIR_CAST(size_t, 4), AIR_CAST(size_t, 23))) {
    sprintf(err, "%s: can't create output", me);
    biffAdd(BANE, err); return NULL;
  }
  data = (float *)ret->data;
  memcpy(data, _baneGkmsDonData, 4*23*sizeof(float));
  data[0 + 4*0] = AIR_NEG_INF;
  data[0 + 4*1] = AIR_NAN;
  data[0 + 4*2] = AIR_POS_INF;
  if (invert) {
    INVERT(data, 0);
    INVERT(data, 1);
    INVERT(data, 2);
    INVERT(data, 12);
    INVERT(data, 13);
  }
  return ret;
}