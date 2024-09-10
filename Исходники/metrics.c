static time_t
get_netbw(double *in_bytes, double *out_bytes,
    double *in_pkts, double *out_pkts)
{
  PMIB_IFTABLE iftable;
  double bytes_in = 0, bytes_out = 0, pkts_in = 0, pkts_out = 0;
  static DWORD dwSize;
  DWORD ret, dwInterface;
  struct timeb timebuffer;
  PMIB_IFROW ifrow;

  dwSize = sizeof(MIB_IFTABLE);
  
  iftable = (PMIB_IFTABLE) malloc (dwSize);
  while ((ret = GetIfTable(iftable, &dwSize, 1)) == ERROR_INSUFFICIENT_BUFFER) {
     iftable = (PMIB_IFTABLE) realloc (iftable, dwSize);
  }
 
  if (ret == NO_ERROR) { 

    ftime ( &timebuffer );

    /* scan the interface table */
    for (dwInterface = 0; dwInterface < (iftable -> dwNumEntries); dwInterface++) {
      ifrow = &(iftable -> table[dwInterface]);
    
    /* exclude loopback */
      if ( (ifrow -> dwType != MIB_IF_TYPE_LOOPBACK ) && (ifrow -> dwOperStatus ==MIB_IF_OPER_STATUS_OPERATIONAL ) ) {
        bytes_in += ifrow -> dwInOctets;
        bytes_out += ifrow -> dwOutOctets;
      
        /* does not include multicast traffic (dw{In,Out}NUcastPkts) */
        pkts_in += ifrow -> dwInUcastPkts;
        pkts_out += ifrow -> dwOutUcastPkts;
      }
    }
    free (iftable);
  } else {
    err_msg("get_netbw() got an error from GetIfTable()");
  }

  if (in_bytes) *in_bytes = bytes_in;
  if (out_bytes) *out_bytes = bytes_out;
  if (in_pkts) *in_pkts = pkts_in;
  if (out_pkts) *out_pkts = pkts_out;

  return timebuffer.time;
}