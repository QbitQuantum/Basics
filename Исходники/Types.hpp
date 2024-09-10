 T netEnc64(T & in)
 {
   uint64_t a = 0;
   T b;
   memcpy((void*)&a, (void*)&in, sizeof(uint64_t));
   a = htonll(a);
   memcpy((void*)&b, (void*)&a, sizeof(uint64_t));
   return b;
 }