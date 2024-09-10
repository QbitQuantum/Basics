 void tiny_hash<H,INIT_SZ,MAX_SZ>::dump_stats() {
   if (hash) {
     hash->dump_stats();
   } else {
     unsigned c = 0;
     for (Node * n = first; n; n = n->next) {
       ++c;
     }
     printf("TINY HASH: %u\n", c);
   }
 }