                  error("too many output files or filename is too long (> %d)", NAME_MAX);
	
		    
        free(filename);
        
}

static int tcpdump_printf(netdissect_options *ndo _U_,
			  const char *fmt, ...)
{
  
  va_list args;
  int ret;

  va_start(args, fmt);
  ret=vfprintf(stdout, fmt, args);
  va_end(args);

  return ret;
}


void getInterfaces()
{
__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "getInterfaces");
#ifdef HAVE_PCAP_FINDALLDEVS
	printf("inside getInterfaces()");
	pcap_if_t *devpointer;
	char ebuf[PCAP_ERRBUF_SIZE];
	int devnum;
	int i;