GMPErr
ClearKeyDecryptionManager::Decrypt(std::vector<uint8_t>& aBuffer,
                                   const CryptoMetaData& aMetadata)
{
  return Decrypt(&aBuffer[0], aBuffer.size(), aMetadata);
}