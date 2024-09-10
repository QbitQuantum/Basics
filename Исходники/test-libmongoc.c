static void
set_mongoc_test_host(void)
{
#ifdef _MSC_VER
   size_t buflen;

   if (0 != getenv_s (&buflen, MONGOC_TEST_HOST, sizeof MONGOC_TEST_HOST, "MONGOC_TEST_HOST")) {
      bson_strncpy (MONGOC_TEST_HOST, "localhost", sizeof MONGOC_TEST_HOST);
   }
#else
   if (getenv("MONGOC_TEST_HOST")) {
      bson_strncpy (MONGOC_TEST_HOST, getenv("MONGOC_TEST_HOST"), sizeof MONGOC_TEST_HOST);
   } else {
      bson_strncpy (MONGOC_TEST_HOST, "localhost", sizeof MONGOC_TEST_HOST);
   }
#endif
}