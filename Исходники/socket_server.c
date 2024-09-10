/*
 * Connection request. We accept connections either from the
 * Director, Storage Daemon or a Client (File daemon).
 *
 * Note, we are running as a seperate thread of the Storage daemon.
 *
 * Basic tasks done here:
 *  - If it was a connection from the FD, call handle_filed_connection()
 *  - If it was a connection from another SD, call handle_stored_connection()
 *  - Otherwise it was a connection from the DIR, call handle_director_connection()
 */
static void *handle_connection_request(void *arg)
{
   BSOCK *bs = (BSOCK *)arg;
   char name[MAX_NAME_LENGTH];
   char tbuf[MAX_TIME_LENGTH];

   if (bs->recv() <= 0) {
      Emsg1(M_ERROR, 0, _("Connection request from %s failed.\n"), bs->who());
      bmicrosleep(5, 0);   /* make user wait 5 seconds */
      bs->close();
      return NULL;
   }

   /*
    * Do a sanity check on the message received
    */
   if (bs->msglen < MIN_MSG_LEN || bs->msglen > MAX_MSG_LEN) {
      Dmsg1(000, "<filed: %s", bs->msg);
      Emsg2(M_ERROR, 0, _("Invalid connection from %s. Len=%d\n"), bs->who(), bs->msglen);
      bmicrosleep(5, 0);   /* make user wait 5 seconds */
      bs->close();
      return NULL;
   }

   Dmsg1(110, "Conn: %s", bs->msg);

   /*
    * See if this is a File daemon connection. If so call FD handler.
    */
   if (sscanf(bs->msg, "Hello Start Job %127s", name) == 1) {
      Dmsg1(110, "Got a FD connection at %s\n", bstrftimes(tbuf, sizeof(tbuf), (utime_t)time(NULL)));
      return handle_filed_connection(bs, name);
   }

   /*
    * See if this is a Storage daemon connection. If so call SD handler.
    */
   if (sscanf(bs->msg, "Hello Start Storage Job %127s", name) == 1) {
      Dmsg1(110, "Got a SD connection at %s\n", bstrftimes(tbuf, sizeof(tbuf), (utime_t)time(NULL)));
      return handle_stored_connection(bs, name);
   }

   Dmsg1(110, "Got a DIR connection at %s\n", bstrftimes(tbuf, sizeof(tbuf), (utime_t)time(NULL)));

   return handle_director_connection(bs);
}