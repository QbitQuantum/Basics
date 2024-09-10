/* \brief Send 32bit unsigned integer as SUMP meta data */
static void SUMP_sendmeta_uint32(char type, unsigned int i) {
  PutChar(type);
  PutChar((i >> 24) & 0xff);
  PutChar((i >> 16) & 0xff);
  PutChar((i >> 8) & 0xff);
  PutChar(i & 0xff);
}