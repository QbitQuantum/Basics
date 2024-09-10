CassDriver::CassDriver() {
  InitLogLevelMap();
  CreateCluster();
  ConnectSession();
  PrepareQuery();
}