 void * xxmalloc (size_t sz) {
   TheCustomHeapType * h = getCustomHeap();
   void * ptr = h->malloc (sz);
   return ptr;
 }