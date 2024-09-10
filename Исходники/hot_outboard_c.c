static int tcp_send(int s, void *buf_void, int len) {
  int result, ofs;
  char *buf = buf_void ;

  trace("tcpsend: %d 0x%x %d",s,buf,len);
  for (ofs=0 ; ofs < len ; ofs += result) {
    result = send(s, buf+ofs, len-ofs, 0);
    if (result == -1) {
#ifdef EINTR
      if (errno == EINTR) continue ;
#endif
      Perror("send");
      hot_sys_Panic("lost connection to outboard") ;
    }
  }
  return len;
}