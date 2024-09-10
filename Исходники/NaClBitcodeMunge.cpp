bool NaClCompressMunger::runTest(const uint64_t Munges[], size_t MungesSize) {
  bool AddHeader = true;
  if (!setupTest(Munges, MungesSize, AddHeader))
    return cleanupTest();

  NaClBitcodeCompressor Compressor;
  if (!Compressor.compress(MungedInput.get(), getDumpStream()))
    Error() << "Unable to compress\n";
  return cleanupTest();
}