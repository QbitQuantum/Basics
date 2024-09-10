void TListViewer::draw() {
   int i, j, item;
   ushort normalColor, selectedColor, focusedColor, color;
   short colWidth, curCol, indent;
   TDrawBuffer b;
   uchar scOff;

   if ((state&(sfSelected | sfActive)) == (sfSelected | sfActive)) {
      normalColor = getColor(1);
      focusedColor = getColor(3);
      selectedColor = getColor(4);
   } else {
      normalColor = getColor(2);
      selectedColor = getColor(4);
   }

   if (hScrollBar != 0)
      indent = hScrollBar->value;
   else
      indent = 0;

   colWidth = size.x / numCols + 1;
   for (i = 0; i < size.y; i++) {
      for (j = 0; j < numCols; j++) {
         item =  j * size.y + i + topItem;
         curCol = j * colWidth;
         if ((state & (sfSelected | sfActive)) == (sfSelected | sfActive) &&
             focused == item &&
             range > 0) {
            color = focusedColor;
            setCursor(curCol + 1, i);
            scOff = 0;
         } else if (item < range && isSelected(item)) {
            color = selectedColor;
            scOff = 2;
         } else {
            color = normalColor;
            scOff = 4;
         }

         b.moveChar(curCol, ' ', color, colWidth);
         if (item < range) {
            char text[MAXSTR];
            getText(text, item, colWidth + indent);
            char buf[MAXSTR];
            buf[0] = '\0';
            if (strlen(text) > indent) {
               memcpy(buf, text+indent, colWidth);
               buf[colWidth] = EOS;
            }
            b.moveStr(curCol+1, buf, color);
            if (showMarkers) {
               b.putChar(curCol, specialChars[scOff]);
               b.putChar(curCol+colWidth-2, specialChars[scOff+1]);
            }
         } else if (i == 0 && j == 0)
            b.moveStr(curCol+1, emptyText, getColor(1));

         b.moveChar(curCol+colWidth-1, 179, getColor(5), 1);
      }
      writeLine(0, i, size.x, 1, b);
   }
}