void DataProvider::printCharTable() {
  char mbs[16];
  int nBytes;
  for (auto it = char2int_.begin(); it != char2int_.end(); ++it) {
    nBytes = wctomb(mbs, it->first);
    printf("%lc : %x : %d : ", it->first, it->first, it->second);
    for (int i=0; i<nBytes; i++) {
      printf("%x ", 0xff & mbs[i]);
    }
    printf("\n");
  }
}