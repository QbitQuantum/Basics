/* called when RecvPacket timed out */
void transfer_timeout(int signum) {
 if (otries++>=NUM_TRIES) {
  fprintf(stderr,"No reply from terminal ! Assuming dead, hence aborting\n");
  transfer_abort(RET_EPROTO);
 }
 SEND(obuf,osize);
 alarm(1);
}