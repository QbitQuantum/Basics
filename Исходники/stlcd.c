// draw a rectangle
void drawrect(unsigned char *buff, unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char color) {
  // stupidest version - just pixels - but fast with internal buffer!
  for (uint8_t i=x; i<x+w; i++) {
    setpixel(buff, i, y, color);
    setpixel(buff, i, y+h-1, color);
  }
  for (uint8_t i=y; i<y+h; i++) {
    setpixel(buff, x, i, color);
    setpixel(buff, x+w-1, i, color);
  } 
}