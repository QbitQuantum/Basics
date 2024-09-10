// draw a rectangle
void SSD1306::drawrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
		      uint8_t color) {
  // stupidest version - just pixels - but fast with internal buffer!
  for (uint8_t i=x; i<x+w; i++) {
    setpixel(i, y, color);
    setpixel(i, y+h-1, color);
  }
  for (uint8_t i=y; i<y+h; i++) {
    setpixel(x, i, color);
    setpixel(x+w-1, i, color);
  } 
}