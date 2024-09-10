void StringHelper::toString(int n, Pool& pool, LogString& s) {
  char* fmt = pool.itoa(n);
  Transcoder::decode(fmt, s);
}