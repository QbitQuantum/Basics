int
_mongoc_rand_bytes (uint8_t *buf, int num)
{
   static BCRYPT_ALG_HANDLE algorithm = 0;
   NTSTATUS status = 0;

   if (!algorithm) {
      status = BCryptOpenAlgorithmProvider (
         &algorithm, BCRYPT_RNG_ALGORITHM, NULL, 0);
      if (!NT_SUCCESS (status)) {
         MONGOC_ERROR ("BCryptOpenAlgorithmProvider(): %d", status);
         return 0;
      }
   }

   status = BCryptGenRandom (algorithm, buf, num, 0);
   if (NT_SUCCESS (status)) {
      return 1;
   }

   MONGOC_ERROR ("BCryptGenRandom(): %d", status);
   return 0;
}