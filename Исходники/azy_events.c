Eina_Bool
azy_events_header_parse(Azy_Net       *net,
                        unsigned char *event_data,
                        size_t         event_len,
                        int            offset)
{
   unsigned char *r = NULL, *p = NULL, *start = NULL, *buf_start = NULL;
   unsigned char *data = (event_data) ? event_data + offset : NULL;
   int64_t len = (event_len) ? event_len - offset : 0;
   const char *s = NULL;
   unsigned char slen = 0;
   unsigned char sep[5];
   int line_len = 0;
   int64_t prev_size = 0;

   DBG("(net=%p, event_data=%p, len=%zu, offset=%i)", net, event_data, event_len, offset);
   if (!AZY_MAGIC_CHECK(net, AZY_MAGIC_NET))
     {
        AZY_MAGIC_FAIL(net, AZY_MAGIC_NET);
        return EINA_FALSE;
     }
   if (net->headers_read)
     return EINA_TRUE;
   EINA_SAFETY_ON_TRUE_RETURN_VAL((!net->buffer) && (!data), EINA_FALSE);

   if (net->size && net->buffer)
     {
        if (event_data && (azy_rpc_log_dom >= 0))
          {
             char buf[64];
             snprintf(buf, sizeof(buf), "STORED:\n<<<<<<<<<<<<<\n%%.%"PRIi64"s\n<<<<<<<<<<<<<", net->size);
             RPC_INFO(buf, net->buffer);
             snprintf(buf, sizeof(buf), "RECEIVED:\n<<<<<<<<<<<<<\n%%.%"PRIi64"s\n<<<<<<<<<<<<<", len - offset);
             RPC_INFO(buf, data);
          }
        /* previous buffer */
        /* alloca should be safe here because ecore_con reads at most 64k
         * and even if no headers were found previously, the entire
         * buffer would not be copied
         */
        buf_start = alloca(len + net->size - offset);
        /* grab and combine buffers */
        if (event_data)
          {
             memcpy(buf_start, net->buffer + offset, net->size - offset);
             memcpy(buf_start + net->size, event_data, len);
          }
        else
          memcpy(buf_start, net->buffer + offset, net->size - offset);

        free(net->buffer);
        net->buffer = NULL;
        len += net->size - offset;

        prev_size = net->size;
        net->size = 0;
        start = buf_start;
        AZY_SKIP_BLANK(start);
     }
   else
   /* only current buffer plus possible net->overflow */
     {
        /* copy pointer */
         start = data;
         /* skip all spaces/newlines/etc and decrement len */
         AZY_SKIP_BLANK(start);
     }

   if ((!len) && (event_len - offset > 0)) /* only blanks were passed, assume http separator */
     {
        net->headers_read = EINA_TRUE;
        return EINA_TRUE;
     }
   /* apparently this can happen? */
   EINA_SAFETY_ON_NULL_RETURN_VAL(start, EINA_FALSE);
   /* find a header or append to buffer */
   if ((!(r = memchr(start, '\r', len)) && !(r = memchr(start, '\n', len)))) /* append to a buffer and use net->overflow */
     {
        unsigned char *tmp;

        if (net->size)
          {
             tmp = realloc(net->buffer, net->size + len);
             EINA_SAFETY_ON_NULL_RETURN_VAL(tmp, EINA_FALSE);

             net->buffer = tmp;
             memcpy(net->buffer + net->size, start, len);
             net->size += len;
          }
        else
          {
             tmp = realloc(net->buffer, len);
             EINA_SAFETY_ON_NULL_RETURN_VAL(tmp, EINA_FALSE);

             net->buffer = tmp;
             memcpy(net->buffer, start, len);
             net->size = len;
          }
        return EINA_TRUE;
     }

   if (*r == '\r')
     {
        unsigned char *x;
        if ((x = memchr(start, '\n', len)))
          {
             if ((x - r) > 0)
               s = "\r\n";
             else
               { /* we currently have \n\r: b64 encoding can leave a trailing \n
                  * so we have to check for an extra \n
                  */
                   if ((x - r < 0) && ((unsigned int)(r + 1 - start) < len) && (r[1] == '\n')) /* \n\r\n */
                     {
                        if (((unsigned int)(r + 2 - start) < len) && (r[2] == '\r')) /* \n\r\n\r */
                          {
                             if (((unsigned int)(r + 3 - start) < len) && (r[3] == '\n'))
                               /* \n\r\n\r\n oh hey I'm gonna stop here before it gets too insane */
                               s = "\r\n";
                             else
                               s = "\n\r";
                          }
                        else
                          s = "\r\n";
                     }
                   else
                     s = "\n\r";
               }
          }
        else
          s = "\r";
     }
   else
     s = "\n";

   slen = strlen(s);
   snprintf((char *)sep, sizeof(sep), "%s%s", s, s);

   p = start;
   line_len = r - p;
   while (len && r)
     {
        unsigned char *ptr, *semi = p;

        if (line_len > MAX_HEADER_SIZE)
          {
             WARN("Ignoring unreasonably large header starting with:\n %.32s\n", p);
             goto skip_header;
          }
        semi += (line_len - _azy_events_valid_header_name((const char *)p, line_len));
        if (semi == p) goto skip_header;

        ptr = semi + 1;
        while ((isspace(*ptr)) && (ptr - p < line_len))
          ptr++;

        if (_azy_events_valid_header_value((const char *)ptr, line_len - (ptr - p)))
          {
             const char *key, *value;

             p[semi - p] = 0;
             ptr[line_len - (ptr - p)] = 0;
             key = (const char *)p;
             value = (const char *)ptr;
             INFO("Found header: key='%s'", key);
             INFO("Found header: value='%s'", value);
             azy_net_header_set(net, key, value);
             if (!strcasecmp(key, "content-length"))
               net->http.content_length = strtol((const char *)value, NULL, 10);
          }

skip_header:
        len -= line_len + slen;
        if (len < slen)
          break;
        p = r + slen;
        /* double separator: STOP */
        if (!strncmp((char*)p, s, slen))
          {
             net->headers_read = EINA_TRUE;
             break;
          }
        r = azy_memstr(p, (const unsigned char *)s, len, slen);
        line_len = r - p;
        /* FIXME: to be fully 1.1 compliant, lines without a colon
         * be filtered and checked to see if is a continuing header
         * from the previous line
         */
     }

   AZY_SKIP_BLANK(p);

   if (!net->headers_read)
     return EINA_TRUE;

   if (!net->http.content_length) net->http.content_length = -1;
   if (len)
     {
        int64_t rlen;
        /* if we get here, we need to append to the buffers */

        if (net->http.content_length > 0)
          {
             if (len > net->http.content_length)
               {
                  rlen = net->http.content_length;
                  net->overflow_length = len - rlen;
                  WARN("Extra content length of %"PRIi64"!", net->overflow_length);
                  net->overflow = malloc(net->overflow_length);
     /* FIXME: uhhhh f**k? */
                  EINA_SAFETY_ON_NULL_RETURN_VAL(net->overflow, EINA_FALSE);
                  memcpy(net->overflow, p + rlen, net->overflow_length);
#ifdef ISCOMFITOR
                if (azy_rpc_log_dom >= 0)
                  {
                     int64_t x;
                     RPC_INFO("OVERFLOW:\n<<<<<<<<<<<<<");
                     for (x = 0; x < net->overflow_length; x++)
                       putc(net->overflow[x], stdout);
                     fflush(stdout);
                  }
#endif
               }
             else
               rlen = len;
          }
        else
          /* this shouldn't be possible unless someone is violating spec */
          rlen = len;

        INFO("Set recv size to %"PRIi64" (previous %"PRIi64")", rlen, prev_size);
        net->size = rlen;
        net->buffer = malloc(rlen);
        /* FIXME: cleanup */
        EINA_SAFETY_ON_NULL_RETURN_VAL(net->buffer, EINA_FALSE);

        memcpy(net->buffer, p, rlen);
     }

   return EINA_TRUE;
}