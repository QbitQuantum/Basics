void setup() {
  Serial.begin(SERIAL_BAUD);          //  setup serial
  Serial.println("starting");
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
#ifdef IS_RFM69HW
  radio.setHighPower(); //uncomment only for RFM69HW!
#endif
  radio.encrypt(ENCRYPTKEY);
  char buff[50];
  sprintf(buff, "\nTransmitting at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  Serial.println(buff);
  theData.nodeID = NODEID;  //this node id should be the same for all devices in this node 
  theData.deviceID = GASDEVICEID;
  pinMode(REDPIN, OUTPUT);
  pinMode(PIEZOPIN, OUTPUT); 
}