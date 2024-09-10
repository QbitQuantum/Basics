void CompressionVarintTest::runSimpleTest(const DataHolder& dh) {
  auto original = IOBuf::wrapBuffer(dh.data(uncompressedLength_));
  auto compressed = codec_->compress(original.get());
  auto breakPoint =
      1UL +
      Random::rand64(std::max(9UL, oneBasedMsbPos(uncompressedLength_)) / 9UL);
  auto tinyBuf = IOBuf::copyBuffer(compressed->data(),
                                   std::min(compressed->length(), breakPoint));
  compressed->trimStart(breakPoint);
  tinyBuf->prependChain(std::move(compressed));
  compressed = std::move(tinyBuf);

  auto uncompressed = codec_->uncompress(compressed.get());

  EXPECT_EQ(uncompressedLength_, uncompressed->computeChainDataLength());
  EXPECT_EQ(dh.hash(uncompressedLength_), hashIOBuf(uncompressed.get()));
}