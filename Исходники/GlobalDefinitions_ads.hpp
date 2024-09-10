inline unsigned int _rotl(unsigned int x, unsigned int y) {
  return _rotr(x, 32 - y);
}