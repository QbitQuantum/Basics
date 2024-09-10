static inline unsigned int size_to_bucket(size_t size) {
  if (size < kMinBucketAllocationSize) return kMinBucketAllocationSize;
  return log2(size - 1) + 1 - const_log2(kMinBucketAllocationSize);
}