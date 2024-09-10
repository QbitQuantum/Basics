void Adafruit_SSD1351::fillScreen(uint16_t fillcolor) {
  fillRect(0, 0, SSD1351WIDTH, SSD1351HEIGHT, fillcolor);
}