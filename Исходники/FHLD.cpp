void show(Ctxt ctxt, EncryptedArray ea, const FHESecKey secretKey) {
  PlaintextArray p(ea);
  ea.decrypt(ctxt, secretKey, p);

  printVoteFull(p);
}