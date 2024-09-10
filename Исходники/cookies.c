/*
 * Flush cookies to disk and free all the memory allocated.
 */
static void Cookies_save_and_free()
{
   int i, fd, saved = 0;
   DomainNode *node;
   CookieData_t *cookie;
   time_t now;

#ifndef HAVE_LOCKF
   struct flock lck;
#endif

   if (disabled)
      return;

   now = time(NULL);

   rewind(file_stream);
   fd = fileno(file_stream);
   if (ftruncate(fd, 0) == -1)
      MSG("Cookies: Truncate file stream failed: %s\n", dStrerror(errno));
   fprintf(file_stream, "%s", cookies_txt_header_str);

   /* Iterate cookies per domain, saving and freeing */
   while ((node = dList_nth_data(domains, 0))) {
      for (i = 0; (cookie = dList_nth_data(node->cookies, i)); ++i) {
         if (!cookie->session_only && difftime(cookie->expires_at, now) > 0) {
            int len;
            char buf[LINE_MAXLEN];

            len = snprintf(buf, LINE_MAXLEN, "%s\t%s\t%s\t%s\t%ld\t%s\t%s\n",
                           cookie->domain,
                           cookie->host_only ? "FALSE" : "TRUE",
                           cookie->path,
                           cookie->secure ? "TRUE" : "FALSE",
                           (long) difftime(cookie->expires_at,
                                           cookies_epoch_time),
                           cookie->name,
                           cookie->value);
            if (len < LINE_MAXLEN) {
               fprintf(file_stream, "%s", buf);
               saved++;
            } else {
               MSG("Not saving overly long cookie for %s.\n", cookie->domain);
            }
         }
         Cookies_free_cookie(cookie);
      }
      Cookies_delete_node(node);
   }
   dList_free(domains);
   dList_free(all_cookies);

#ifdef HAVE_LOCKF
   lockf(fd, F_ULOCK, 0);
#else  /* POSIX file lock */
   lck.l_start = 0; /* start at beginning of file */
   lck.l_len = 0;  /* lock entire file */
   lck.l_type = F_UNLCK;
   lck.l_whence = SEEK_SET;  /* absolute offset */

   fcntl(fileno(file_stream), F_SETLKW, &lck);
#endif
   fclose(file_stream);

   MSG("Cookies saved: %d.\n", saved);
}