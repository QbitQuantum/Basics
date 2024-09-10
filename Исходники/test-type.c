static void
test_bson_type (bson_t *scenario, test_bson_type_valid_cb valid)
{
   bson_iter_t iter;
   bson_iter_t inner_iter;
   BSON_ASSERT (scenario);

   if (bson_iter_init_find (&iter, scenario, "valid")) {
      const char *expected = NULL;
      bson_t json;
      bson_t bson_input = BSON_INITIALIZER;

      bson_iter_recurse (&iter, &inner_iter);
      while (bson_iter_next (&inner_iter)) {
         bson_iter_t test;
         uint8_t       *bson_str;
         uint32_t       bson_str_len;
         const uint8_t *extjson_str;
         uint32_t       extjson_str_len;
         const uint8_t *canonical_extjson_str;
         uint32_t       canonical_extjson_str_len;
         bool           lossy = false;
         bool           have_extjson = false;
         bool           have_canonical_extjson = false;

         bson_iter_recurse (&inner_iter, &test);
         _test_bson_type_print_description (&test);
         while (bson_iter_next (&test)) {
            const char *key = bson_iter_key (&test);

            if (!strcmp (key, "bson") && BSON_ITER_HOLDS_UTF8 (&test)) {
               const char *input = NULL;
               unsigned int byte;
               uint32_t tmp;
               int x = 0;
               int i = 0;

               input = bson_iter_utf8 (&test, &tmp);
               bson_str_len = tmp / 2;
               bson_str = bson_malloc (bson_str_len);
               while (SSCANF (&input[i], "%2x", &byte) == 1) {
                  bson_str[x++] = (uint8_t) byte;
                  i += 2;
               }
            }

            if (!strcmp (key, "extjson") && BSON_ITER_HOLDS_UTF8 (&test)) {
               extjson_str = (const uint8_t *)bson_iter_utf8 (&test, &extjson_str_len);
               have_extjson = true;
            }

            if (!strcmp (key, "canonical_extjson") && BSON_ITER_HOLDS_UTF8 (&test)) {
               canonical_extjson_str = (const uint8_t *)bson_iter_utf8 (&test, &canonical_extjson_str_len);
               have_canonical_extjson = true;
            }
            if (!strcmp (key, "canonical_extjson") && BSON_ITER_HOLDS_BOOL (&test)) {
               lossy = bson_iter_bool (&test);
            }
         }

         valid (bson_str,
                bson_str_len,
                bson_str,
                bson_str_len,
                have_extjson ? extjson_str : NULL,
                have_extjson ?  extjson_str_len : 0,
                have_canonical_extjson ? canonical_extjson_str : extjson_str,
                have_canonical_extjson ? canonical_extjson_str_len : extjson_str_len,
                lossy);
         bson_free (bson_str);
      }
   }

   if (bson_iter_init_find (&iter, scenario, "parseErrors")) {
      bson_iter_recurse (&iter, &inner_iter);
      while (bson_iter_next (&inner_iter)) {
         bson_iter_t test;

         bson_iter_recurse (&inner_iter, &test);
         _test_bson_type_print_description (&test);

         if (bson_iter_find (&test, "string") && BSON_ITER_HOLDS_UTF8 (&test)) {
            bson_decimal128_t d;
            uint32_t tmp;
            const char *input = bson_iter_utf8 (&test, &tmp);

            ASSERT (!bson_decimal128_from_string (input, &d));
            ASSERT (IS_NAN (d));
         }
      }
   }
}