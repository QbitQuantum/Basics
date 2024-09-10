static void *do_resolve(void *hostname)
{

	slogi("do_resolve hostname[%s]",hostname);
	#if 0
	/*
[/home/st/toffaletti/armhf/key.c_114__st_thread_cleanup]key [110876]  key_max[0]
do_resolve hostname[www.baidu.com]
after strcpy  strcpy(host,hostname)[www.baidu.com] hostname[www.baidu.com]
[/home/st/toffaletti/armhf/event.c_421__st_select_fd_new]_st_select_fd_new osfd[7] ok
[/home/st/toffaletti/armhf/io.c_749_st_sendto]sendto get n [31]
[/home/st/toffaletti/armhf/io.c_730_st_recvfrom]recvfrom get n [90]
[/home/st/toffaletti/armhf/examples/res.c_278_dns_getaddr]query_domain return 0
[/home/st/toffaletti/armhf/io.c_212_st_netfd_close]JUST TEST st_netfd_close

Program received signal SIGSEGV, Segmentation fault.
0x00000000 in ?? ()
(gdb) bt
#0  0x00000000 in ?? ()
#1  0x0000b06e in dns_getaddr (
    host=<error reading variable: Cannot access memory at address 0xc>,
    addr=<error reading variable: Cannot access memory at address 0x8>,
    timeout=<error reading variable: Cannot access memory at address 0x0>)
    at /home/st/toffaletti/armhf/examples/res.c:281
Backtrace stopped: previous frame inner to this frame (corrupt stack?)
(gdb)
	*/
	char host[128];
	memset(host,0,128);
	//strcpy(host,hostname);
	slogi("after strcpy  strcpy(host,hostname)[%s] hostname[%s]",strcpy(host,hostname),hostname);
	#else
	char *host=malloc(128);
	memset(host,0,128);
	slogi("sizeof(hostname)[%d] strlen(hostname)[%d]",sizeof(hostname),strlen(hostname));
	memcpy(host,hostname,strlen(hostname)+1);
	slogi("host is [%s]",host);
	#endif

  struct in_addr addr;

#if 1
  /* Use dns_getaddr() instead of gethostbyname(3) to get IP address */
  #if 1
    int ret=-99;
     dns_getaddr(host, &addr, TIMEOUT);
    LOGD("dns_getaddr RET");
    if ( ret< 0) {
  #else
    if ( dns_getaddr(host, &addr, TIMEOUT)< 0) {
  #endif
// #endif
  	/*PCÉÏ»áÊä³öÐ¡ÓÚ0£¬tvboxÉÏÉ¶¶¼Ã»ÓÐÊä³ö°¡*/
    fprintf(stderr, "dns_getaddr: can't resolve %s: ", (char *)host);
    if (h_errno == NETDB_INTERNAL)
      perror("");
    else
      herror("");
  } else /*ÕâÖÖÇé¿ö¾ÍÊÇÕÒµ½ÁË*/
      printf("%-40s %s\n", (char *)host, inet_ntoa(addr));
#else //Ö±½Ó²âÊÔÏß³Ìº¯Êý
/* http://m.blog.chinaunix.net/uid-28595538-id-4923606.html
inet_ntoa º¯Êý API ÃèÊö
#include
#include
char * inet_ntoa( struct in_addr_in ) ;

²ÎÊý£º
   in : ¸Ã²ÎÊý´æ·ÅÓÃÀ´×ª»»µÄ16½øÖÆÍøÂçË³ÐòµÄIPµØÖ·½á¹¹Ìå
·µ»ØÖµ£º
   Èç¹ûº¯Êý Inet_ntoa ³É¹¦½« 16½øÖÆÍøÂçË³ÐòµÄ IPµØÖ·×ª»»Îª×Ö·û´®ÀàÐÍµÄµã·ÖIP µØÖ·£¬
   Ôò½«¸Ã×Ö·û´®×÷Îª·µ»ØÖµ·µ»Ø£¬×ª»»Ê§°Ü£¬·µ»Ø NULL

*/
	int count=20;
	while(count--)
    {
		LOGD("just for test thread func ....");
		//ÕâÀïÊä³öµÄaddrÊÇ´íÎóµÄ
		printf("%-40s %s\n", (char *)host, inet_ntoa(addr));
	}
#endif
//20150923
   free(host);
  return NULL;
}


/*
 * Asynchronous DNS host name resolution. This program creates one
 * ST thread for each host name (specified as command line arguments).
 * All threads do host name resolution concurrently.
 */
int main(int argc, char *argv[])
{
	slogi("argc[%d]",argc);
  int i;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <hostname1> [<hostname2>] ...\n", argv[0]);
    exit(1);
  }

  if (st_init() < 0) {
    perror("st_init");
    exit(1);
  }

	slogi("---before for--argc[%d]",argc);
  for (i = 1; i < argc; i++) {
  	slogi("====%d=[%s]=",i,argv[i]);
    /* Create a separate thread for each host name */
    if (st_thread_create(do_resolve, argv[i], 0, 0) == NULL) {
      perror("st_thread_create");
      exit(1);
    }
  }

  st_thread_exit(NULL); //ÔõÃ´Ö±½Óµ½ÁËÕâÀïÄØ

  /* NOTREACHED ÍøÂç²»¿É´ïå */
  return 1; //Ã²ËÆÕâÀïÊÇ³É¹¦?
}