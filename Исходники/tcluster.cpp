void TCluster::drawMultiBox(const char *icon, const char *marker) {
   TDrawBuffer b;
   ushort color;
   int i, j, cur;

   ushort cNorm = getColor(0x0301);
   ushort cSel = getColor(0x0402);
   ushort cDis = getColor(0x0505);
   for (i = 0; i <= size.y; i++) {
      b.moveChar(0, ' ', (uchar)cNorm, size.x);
      for (j = 0; j <= (strings->getCount() - 1) / size.y + 1; j++) {
         cur = j * size.y + i;
         if (cur < strings->getCount()) {
            int col = column(cur);

            if (((col + strlen((const char *)strings->at(cur)) + 5) <
                  (sizeof(b) / sizeof(ushort))) && (col < size.x)) {
               if (!buttonState(cur))
                  color = cDis;
               else if ((cur == sel) && (state & sfSelected) != 0)
                  color = cSel;
               else
                  color = cNorm;
               b.moveChar(col, ' ', color, size.x - col);
               b.moveCStr(col, icon, color);

               b.putChar(col + 2, marker[multiMark(cur)]);
               b.moveCStr(col + 5, (char *)(strings->at(cur)), color);
               if (showMarkers && ((state & sfSelected) != 0) && cur == sel) {
                  b.putChar(col, specialChars[0]);
                  b.putChar(column(cur + size.y) - 1, specialChars[1]);
               }

            }
         }
      }
      writeBuf(0, i, size.x, 1, b);
   }
   setCursor(column(sel) + 2, row(sel));
}