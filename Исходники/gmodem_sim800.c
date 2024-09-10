int gmodem_sim800_wget(gmodem *g,char *url,char *buf,int size) {
int csq = 0;
char ip[20]; buf[0]=0;
gmodem_logf(g,3,"sim800.wget:check GSM coverage");
if (gmodem_csq(g,&csq)<=0) return gmodem_errorf(g,-3,"GSM not connected");
gmodem_logf(g,3,"sim800.wget:check GPRS bearer");
if (gmodem_sim800_getip(g,ip)>0) {
   gmodem_logf(g,3,"sim800.wget: modem has IP address: %s",ip);
   } else {
   char *apn = gmodem_get_default_apn(g);
   if (gmodem_sim800_ip_attach(g,apn )<=0) return 0;
   }
//char buf[300]; int len=sizeof(buf);
gmodem_logf(g,3,"sim800.wget ready for http");
int code = gmodem_sim800_http_connect(g,url,60); if (code<=0) return code; // gmodem_errorf(g,-3,"wget http_connect failed");
int len = size-1;
  if( len > g->http_len) len=g->http_len;
int ok = gmodem_sim800_http_read(g,buf,len); // read one block
if (ok<=0) return -1;
strNcpy(g->out,buf); // copy to state
return 1;
}