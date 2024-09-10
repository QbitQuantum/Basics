bool
_mongoc_crypto_cng_hmac_or_hash (BCRYPT_ALG_HANDLE algorithm,
                                 void *key,
                                 size_t key_length,
                                 void *data,
                                 size_t data_length,
                                 void *output)
{
   char *hash_object_buffer = 0;
   ULONG hash_object_length = 0;
   BCRYPT_HASH_HANDLE hash = 0;
   ULONG mac_length = 0;
   NTSTATUS status = STATUS_UNSUCCESSFUL;
   bool retval = false;
   ULONG noop = 0;

   status = BCryptGetProperty (algorithm,
                               BCRYPT_OBJECT_LENGTH,
                               (char *) &hash_object_length,
                               sizeof hash_object_length,
                               &noop,
                               0);

   if (!NT_SUCCESS (status)) {
      MONGOC_ERROR ("BCryptGetProperty(): OBJECT_LENGTH %x", status);
      return false;
   }

   status = BCryptGetProperty (algorithm,
                               BCRYPT_HASH_LENGTH,
                               (char *) &mac_length,
                               sizeof mac_length,
                               &noop,
                               0);

   if (!NT_SUCCESS (status)) {
      MONGOC_ERROR ("BCryptGetProperty(): HASH_LENGTH %x", status);
      return false;
   }

   hash_object_buffer = bson_malloc (hash_object_length);

   status = BCryptCreateHash (algorithm,
                              &hash,
                              hash_object_buffer,
                              hash_object_length,
                              key,
                              (ULONG) key_length,
                              0);

   if (!NT_SUCCESS (status)) {
      MONGOC_ERROR ("BCryptCreateHash(): %x", status);
      goto cleanup;
   }

   status = BCryptHashData (hash, data, (ULONG) data_length, 0);
   if (!NT_SUCCESS (status)) {
      MONGOC_ERROR ("BCryptHashData(): %x", status);
      goto cleanup;
   }

   status = BCryptFinishHash (hash, output, mac_length, 0);
   if (!NT_SUCCESS (status)) {
      MONGOC_ERROR ("BCryptFinishHash(): %x", status);
      goto cleanup;
   }

   retval = true;

cleanup:
   if (hash) {
      (void) BCryptDestroyHash (hash);
   }

   bson_free (hash_object_buffer);
   return retval;
}