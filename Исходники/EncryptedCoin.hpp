 Coin<FIELD> decrypt(const AddrPair<FIELD>& addr) const {
     return decrypt(addr.secretAddr(), addr.publicAddr());
 }