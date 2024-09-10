// draw a circle
void fillcircle(struct drawdata *d,
	      uint8_t x0, uint8_t y0, uint8_t r,
	      uint8_t color) {
  int8_t f = 1 - r;
  int8_t ddF_x = 1;
  int8_t ddF_y = -2 * r;
  int8_t x = 0;
  int8_t y = r;


  for (uint8_t i=y0-r; i<=y0+r; i++) {
    setpixel(d, x0, i, color);
  }
//  uint8_t xg = x;
  while (x<y) {
    if (f >= 0) {
#if 0
      fillrect(d, x0+xg, y0-y,(x-xg)+1,y*2+1, color);
      fillrect(d, x0-x,  y0-y,(x-xg)+1,y*2+1, color);
      fillrect(d, x0+y,  y0-x,
#endif
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    for (uint8_t i=y0-y; i<=y0+y; i++) {
      setpixel(d, x0+x, i, color);
      setpixel(d, x0-x, i, color);
    }
    for (uint8_t i=y0-x; i<=y0+x; i++) {
      setpixel(d, x0+y, i, color);
      setpixel(d, x0-y, i, color);
    }
  }