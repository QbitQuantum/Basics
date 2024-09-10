void fmat_rev(fmat_t *s) {
  uint_t i,j;
  for (i=0; i< s->height; i++) {
    for (j=0; j< FLOOR(s->length/2); j++) {
      ELEM_SWAP(s->data[i][j], s->data[i][s->length-1-j]);
    }
  }
}