void Glowprobe::setColumn(uint8_t fb, uint8_t lr, uint8_t r, uint8_t g, uint8_t b) {
  setPixel(fb, lr, 0, r, g, b);
  setPixel(fb, lr, 1, r, g, b);
  setPixel(fb, lr, 2, r, g, b);
  setPixel(fb, lr, 3, r, g, b);
  setPixel(fb, lr, 4, r, g, b);
  setPixel(fb, lr, 5, r, g, b);
}