void debugWifiState () {
  char buf[32];
  Serial.print(F("MAC: "));
  Serial.println(wifly.getMAC(buf, sizeof(buf)));
  Serial.print(F("IP: "));
  Serial.println(wifly.getIP(buf, sizeof(buf)));
  Serial.print(F("Netmask: "));
  Serial.println(wifly.getNetmask(buf, sizeof(buf)));
  Serial.print(F("Gateway: "));
  Serial.println(wifly.getGateway(buf, sizeof(buf)));
  Serial.print(F("DeviceID: "));
  Serial.println(wifly.getDeviceID(buf, sizeof(buf)));
}