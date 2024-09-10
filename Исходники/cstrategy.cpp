void BehaviourPatterns::cStrategy() {
  Compressor* c = new Compressor( new ZIP_Compression() );
  c->compress("file.txt");

  delete c;
}