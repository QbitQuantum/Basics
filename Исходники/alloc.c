void* mpeg2_malloc(size_t size, mpeg2_alloc_t reason)
{
 return _aligned_malloc(size,64);
}