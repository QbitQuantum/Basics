static int
_bson_json_read_string (void                *_ctx, /* IN */
                        const unsigned char *val,  /* IN */
                        size_t               vlen) /* IN */
{
   bson_json_read_state_t rs;
   bson_json_read_bson_state_t bs;

   BASIC_YAJL_CB_PREAMBLE;

   rs = bson->read_state;
   bs = bson->bson_state;

   if (rs == BSON_JSON_REGULAR) {
      bson_append_utf8 (STACK_BSON_CHILD, key, (int)len, (const char *)val, (int)vlen);
   } else if (rs == BSON_JSON_IN_BSON_TYPE || rs ==
              BSON_JSON_IN_BSON_TYPE_TIMESTAMP_VALUES) {
      const char *val_w_null;
      _bson_json_buf_set (&bson->bson_type_buf[2], val, vlen, true);
      val_w_null = (const char *)bson->bson_type_buf[2].buf;

      switch (bs) {
      case BSON_JSON_LF_REGEX:
         bson->bson_type_data.regex.has_regex = true;
         _bson_json_buf_set (&bson->bson_type_buf[0], val, vlen, true);
         break;
      case BSON_JSON_LF_OPTIONS:
         bson->bson_type_data.regex.has_options = true;
         _bson_json_buf_set (&bson->bson_type_buf[1], val, vlen, true);
         break;
      case BSON_JSON_LF_OID:

         if (vlen != 24) {
            goto BAD_PARSE;
         }

         bson->bson_type_data.oid.has_oid = true;
         bson_oid_init_from_string (&bson->bson_type_data.oid.oid, val_w_null);
         break;
      case BSON_JSON_LF_TYPE:
         bson->bson_type_data.binary.has_subtype = true;

#ifdef _WIN32
# define SSCANF sscanf_s
#else
# define SSCANF sscanf
#endif

         if (SSCANF (val_w_null, "%02x",
                     &bson->bson_type_data.binary.type) != 1) {
            goto BAD_PARSE;
         }

#undef SSCANF

         break;
      case BSON_JSON_LF_BINARY: {
            /* TODO: error handling for pton */
            int binary_len;
            bson->bson_type_data.binary.has_binary = true;
            binary_len = b64_pton (val_w_null, NULL, 0);
            _bson_json_buf_ensure (&bson->bson_type_buf[0], binary_len + 1);
            b64_pton ((char *)bson->bson_type_buf[2].buf,
                      bson->bson_type_buf[0].buf, binary_len + 1);
            bson->bson_type_buf[0].len = binary_len;
            break;
         }
      case BSON_JSON_LF_REF:
         bson->bson_type_data.ref.has_ref = true;
         _bson_json_buf_set (&bson->bson_type_buf[0], val, vlen, true);
         break;
      case BSON_JSON_LF_ID:

         if (vlen != 24) {
            goto BAD_PARSE;
         }

         bson->bson_type_data.ref.has_id = true;
         bson_oid_init_from_string (&bson->bson_type_data.ref.id, val_w_null);
         break;
      case BSON_JSON_LF_INT64:
         {
            int64_t v64;
            char *endptr = NULL;

            errno = 0;
            v64 = bson_ascii_strtoll ((const char *)val, &endptr, 10);

            if (((v64 == INT64_MIN) || (v64 == INT64_MAX)) && (errno == ERANGE)) {
               goto BAD_PARSE;
            }

            if (endptr != ((const char *)val + vlen)) {
               goto BAD_PARSE;
            }

            bson_append_int64 (STACK_BSON_CHILD, key, (int)len, v64);
         }
         break;
      case BSON_JSON_LF_DATE:
      case BSON_JSON_LF_TIMESTAMP_T:
      case BSON_JSON_LF_TIMESTAMP_I:
      case BSON_JSON_LF_UNDEFINED:
      case BSON_JSON_LF_MINKEY:
      case BSON_JSON_LF_MAXKEY:
      default:
         goto BAD_PARSE;
      }

      return 1;

   BAD_PARSE:
      _bson_json_read_set_error (reader,
                                 "Invalid input string %s, looking for %d",
                                 val_w_null, bs);
      return 0;
   } else {
      _bson_json_read_set_error (reader, "Invalid state to look for string %d",
                                 rs);
      return 0;
   }

   return 1;
}