void *
bson_malloc (size_t num_bytes) /* IN */
{
   void *mem = NULL;

   if (BSON_LIKELY (num_bytes)) {
      if (BSON_UNLIKELY (!(mem = gMemVtable.malloc (num_bytes)))) {
         fprintf (stderr, "Failure to allocate memory in bson_malloc(). errno: %d.\n", errno);
         abort ();
      }
   }

   return mem;
}