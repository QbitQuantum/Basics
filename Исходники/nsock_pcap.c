char *nsock_pcap_set_filter(pcap_t *pt, const char *device, const char *bpf) {
  struct bpf_program fcode;
  static char errorbuf[128];

  /* log_write(LOG_STDOUT, "Packet capture filter (device %s): %s\n", device, buf); */

  if (pcap_compile(pt, &fcode, (char*)bpf, 1, 0) < 0) {
    Snprintf(errorbuf, sizeof(errorbuf), "Error compiling our pcap filter: %s\n", pcap_geterr(pt));
    return errorbuf;
  }

  if (pcap_setfilter(pt, &fcode) < 0 ) {
    Snprintf(errorbuf, sizeof(errorbuf),"Failed to set the pcap filter: %s\n", pcap_geterr(pt));
    return errorbuf;
  }

  pcap_freecode(&fcode);
  return NULL;
}