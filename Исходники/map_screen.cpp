 void unmask(uint32_t x, uint32_t y) {
   if (x < (uint32_t) bitmap.getWidth() && y < (uint32_t) bitmap.getHeight()) {
     bitmap.setPixel(x, y, 0);
   }
 }