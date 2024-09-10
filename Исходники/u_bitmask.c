/**
 * Resize the bitmask if necessary 
 */
static inline boolean
util_bitmask_resize(struct util_bitmask *bm,
                    unsigned minimum_index)
{
   unsigned minimum_size = minimum_index + 1;
   unsigned new_size;
   util_bitmask_word *new_words;

   /* Check integer overflow */
   if(!minimum_size)
      return FALSE;
      
   if(bm->size >= minimum_size)
      return TRUE;

   assert(bm->size % UTIL_BITMASK_BITS_PER_WORD == 0);
   new_size = bm->size;
   while(new_size < minimum_size) {
      new_size *= 2;
      /* Check integer overflow */
      if(new_size < bm->size)
         return FALSE;
   }
   assert(new_size);
   assert(new_size % UTIL_BITMASK_BITS_PER_WORD == 0);
   
   new_words = (util_bitmask_word *)REALLOC((void *)bm->words,
                                            bm->size / UTIL_BITMASK_BITS_PER_BYTE,
                                            new_size / UTIL_BITMASK_BITS_PER_BYTE);
   if (!new_words)
      return FALSE;
   
   memset(new_words + bm->size/UTIL_BITMASK_BITS_PER_WORD, 
          0, 
          (new_size - bm->size)/UTIL_BITMASK_BITS_PER_BYTE);
   
   bm->size = new_size;
   bm->words = new_words;
   
   return TRUE;
}