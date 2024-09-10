static int posix_memalign(void **p, size_t align, size_t size) { 
   void *buf = _aligned_malloc(size, align);
   if (buf == NULL) return errno;
   *p = buf;
   return 0;
}