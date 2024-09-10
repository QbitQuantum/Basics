char *
bson_strerror_r (int err_code,  /* IN */
                 char *buf,     /* IN */
                 size_t buflen) /* IN */
{
   static const char *unknown_msg = "Unknown error";
   char *ret = NULL;

#if defined(_WIN32)
   if (strerror_s (buf, buflen, err_code) != 0) {
      ret = buf;
   }
#elif defined(__GNUC__) && defined(_GNU_SOURCE)
   ret = strerror_r (err_code, buf, buflen);
#else /* XSI strerror_r */
   if (strerror_r (err_code, buf, buflen) == 0) {
      ret = buf;
   }
#endif

   if (!ret) {
      bson_strncpy (buf, unknown_msg, buflen);
      ret = buf;
   }

   return ret;
}