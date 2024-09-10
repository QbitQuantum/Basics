/**
 * Stores in the bits buffer a sequence of nbits pseudo-random bits.
 * Overwrites the bits generated using binsource_cache_gen.
 */
int binsource_generate(binsource_t* q, char *bits, int nbits) {

  if (gen_seq_buff(q,DIV(nbits,32))) {
    return -1;
  }
  int_2_bits(q->seq_buff,bits,nbits);
  return 0;
}