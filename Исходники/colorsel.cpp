void TColorSelector::draw() {
   TDrawBuffer b;
   b.moveChar(0, ' ', 0x70, size.x);
   for (int i = 0; i <= size.y; i++) {
      if (i < 4) {
         for (int j = 0; j < 4; j++) {
            int c = i * 4 + j;
            b.moveChar(j * 3, icon, c, 3);
            if (c == color) {
               b.putChar(j * 3 + 1, 8);
               if (c == 0)
                  b.putAttribute(j * 3 + 1, 0x70);
            }
         }
      }
      writeLine(0, i, size.x, 1, b);
   }
}