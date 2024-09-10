int NetworkMuninNodePlugin::GetValues(char *buffer, int len) { 
  int ret = 0;
  MIB_TCPSTATS tcpStats;
  MIB_UDPSTATS udpStats;

  ret = GetTcpStatistics(&tcpStats);
  ret = GetUdpStatistics(&udpStats);
  _snprintf(buffer, len, "down.value %u\nup.value %u\n.\n", 
    tcpStats.dwInSegs + udpStats.dwInDatagrams,
    tcpStats.dwOutSegs + udpStats.dwOutDatagrams);

  return 0;
};