// Read the state, returns -1 on failure
int8_t OwRelay::rawRead(uint64_t addr) {
  OneWire ds = os->getOneWire();
  byte data[12];
  ds.reset();
  ds.select((uint8_t *)&addr);
  uint8_t value = ds.read_bit() ^ 1; // read the switch value

#if DEBUG
  Serial.print(F("OWR: Good data for "));
  printAddr(&Serial, addr);
  Serial.print("->");
  Serial.print(value);
  Serial.println();
#endif

  return value;
}