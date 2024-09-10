void loop() { 
  uint32_t t;
  double r;

  Serial.println("Type any character to start");
  while (!Serial.available()) SPARK_WLAN_Loop();
  while (Serial.available()) Serial.read();

  // open or create file - truncate existing file.
  if (!file.open(&root, "BENCH.DAT", O_CREAT | O_TRUNC | O_RDWR)) {
    error("open failed");
  }
  // fill buf with known data
  for (uint16_t i = 0; i < (BUF_SIZE-2); i++) {
    buf[i] = 'A' + (i % 26);
  }
  buf[BUF_SIZE-2] = '\r';
  buf[BUF_SIZE-1] = '\n';
  Serial.print("File size ");
  Serial.print(FILE_SIZE_MB);
  Serial.println(" MB");
  uint32_t n = FILE_SIZE/sizeof(buf);
  Serial.println("Starting write test.  Please wait up to a minute");
  // do write test
  t = millis();
  for (uint32_t i = 0; i < n; i++) {
    if (file.write(buf, sizeof(buf)) != sizeof(buf)) {
      error("write failed");
    }
  }
  t = millis() - t;
  file.sync();
  r = (double)file.fileSize()/t;
  Serial.print("Write ");
  Serial.print(r);
  Serial.println(" kB/sec");
  Serial.println();
  Serial.println("Starting read test.  Please wait up to a minute");
  // do read test
  file.rewind();
  t = millis();
  for (uint32_t i = 0; i < n; i++) {
    if (file.read(buf, sizeof(buf)) != sizeof(buf)) {
      error("read failed");
    }
  }
  t = millis() - t;
  r = (double)file.fileSize()/t;
  Serial.print("Read ");
  Serial.print(r);
  Serial.println(" kB/sec");
  Serial.println("Done");
  file.close();
}