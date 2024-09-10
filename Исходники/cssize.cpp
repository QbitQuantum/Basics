 Statement* Cssize::flatten(Statement* s)
 {
   Block* bb = s->block();
   Block* result = SASS_MEMORY_NEW(ctx.mem, Block, bb->pstate(), 0, bb->is_root());
   for (size_t i = 0, L = bb->length(); i < L; ++i) {
     Statement* ss = (*bb)[i];
     if (ss->block()) {
       ss = flatten(ss);
       for (size_t j = 0, K = ss->block()->length(); j < K; ++j) {
         *result << (*ss->block())[j];
       }
     }
     else {
       *result << ss;
     }
   }
   return result;
 }