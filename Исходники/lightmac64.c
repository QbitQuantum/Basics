void lightmac_tag(const void *msg, uint32_t msglen, 
    void *tag, void* mkey) 
{
  uint8_t  *data=(uint8_t*)msg;
  uint8_t  *key=(uint8_t*)mkey;
  uint32_t idx, ctr, i;
  bc_blk   m;
  bc_blk   *t=(bc_blk*)tag;
  
  // zero initialize T
  t->q = 0;

  // set counter + index to zero
  ctr = 0; idx = 0;
  
  // while we have msg data
  while (msglen) {
    // add byte to M
    m.b[COUNTER_LENGTH + idx++] = *data++;
    // M filled?
    if (idx == (BLOCK_LENGTH - COUNTER_LENGTH)) {
      // add S counter in big endian format
      m.ctr = SWAP32(++ctr);
      // encrypt M with E using K1
      ENCRYPT(key, &m);
      // update T
      t->q ^= m.q;
      // reset index      
      idx = 0;
    }
    // decrease length
    msglen--;
  }
  // add the end bit
  m.b[COUNTER_LENGTH + idx++] = 0x80;  
  // update T with anything remaining
  for (i=0; i<idx; i++) {
    t->b[i] ^= m.b[COUNTER_LENGTH + i];
  }
  // advance key to K2
  key += BC_KEY_LENGTH;
  // encrypt T with E using K2
  ENCRYPT(key, t);
}