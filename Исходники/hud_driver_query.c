static boolean
batch_query_add(struct hud_batch_query_context **pbq,
                struct pipe_context *pipe, unsigned query_type,
                unsigned *result_index)
{
   struct hud_batch_query_context *bq = *pbq;
   unsigned i;

   if (!bq) {
      bq = CALLOC_STRUCT(hud_batch_query_context);
      if (!bq)
         return false;
      bq->pipe = pipe;
      *pbq = bq;
   }

   for (i = 0; i < bq->num_query_types; ++i) {
      if (bq->query_types[i] == query_type) {
         *result_index = i;
         return true;
      }
   }

   if (bq->num_query_types == bq->allocated_query_types) {
      unsigned new_alloc = MAX2(16, bq->allocated_query_types * 2);
      unsigned *new_query_types
         = REALLOC(bq->query_types,
                   bq->allocated_query_types * sizeof(unsigned),
                   new_alloc * sizeof(unsigned));
      if (!new_query_types)
         return false;
      bq->query_types = new_query_types;
      bq->allocated_query_types = new_alloc;
   }

   bq->query_types[bq->num_query_types] = query_type;
   *result_index = bq->num_query_types++;
   return true;
}