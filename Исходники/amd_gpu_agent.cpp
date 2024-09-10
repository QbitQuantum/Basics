void ReleaseApe1(void* addr, size_t size) {
  assert(addr != NULL && size != 0);
  _aligned_free(addr);
}