int SSH2Channel::requestPty(ExceptionSink *xsink, const QoreString &term, const QoreString &modes, int width, int height, int width_px, int height_px, int timeout_ms) {
   AutoLocker al(parent->m);
   if (check_open(xsink))
      return -1;

   BlockingHelper bh(parent);

   int rc;
   while (true) {
      rc = libssh2_channel_request_pty_ex(channel, term.getBuffer(), term.strlen(), modes.strlen() ? modes.getBuffer() : 0, modes.strlen(), width, height, width_px, height_px);
      if (rc == LIBSSH2_ERROR_EAGAIN) {
	 if ((rc = parent->waitSocketUnlocked(xsink, SSH2CHANNEL_TIMEOUT, "SSH2CHANNEL-REQUESTPTY-ERROR", "SSH2Channel::requestPty", timeout_ms)))
	    break;
	 continue;
      }
      if (rc)
	 parent->doSessionErrUnlocked(xsink);
      break;
   }

   return rc;
}