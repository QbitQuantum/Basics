static void sensorQueryWorker() {
  char com1Name[] = IOSERVERCOM1_NAME;
  int com1 = WhoIs(com1Name);

  int parent = MyParentsTid();

  for (;;) {
    SensorMsg msg;
    msg.type = QUERY_WORKER;
    Send(parent, (char *)&msg, sizeof(SensorMsg), (char *)NULL, 0);
    Putc(com1, 133);
  }
}