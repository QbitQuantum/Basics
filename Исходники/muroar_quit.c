// Close a control connection by sending QUIT command.
int muroar_quit   (muroar_t fh) {
 char quit[] = "\0\6\0\0\0\0\0\0\0\0"; // QUIT command
 int ret = 0;

 if ( fh == MUROAR_HANDLE_INVALID ) {
  _SET_ERRNO(EBADF);
  return -1;
 }

 if ( muroar_write(fh, quit, 10) != 10 )
  ret = -1;

 // read in case the server response
 // ignore errors as the server do not necessary
 // response to our request.
 muroar_read(fh, quit, 10);

 if ( muroar_close(fh) == -1 )
  ret = -1;

 return ret;
}