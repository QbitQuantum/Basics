 /// @brief Verify the blob using the publicKey against the signature.
 static bool
 verifySignature(const Buffer& blob, const Signature& sig, const v1::PublicKey& publicKey)
 {
   return verifySignature(blob.buf(), blob.size(), sig, publicKey);
 }