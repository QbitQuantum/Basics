void ixion::drawing_functions::drawEllipse(Target &target,int x,int y,int r_x,int r_y) {
  int const fix_digits = 10;

  if (r_x > r_y) {
    int counter = r_x;
    int xcount = 0;
    int ycount = r_x;
    int factor = (r_y << fix_digits) / r_x;
  
    target.setPixel(x + r_x,y); // S
    target.setPixel(x - r_x,y); // N
    target.setPixel(x,y - r_y); // W
    target.setPixel(x,y + r_y); // E
    
    int lastline_ycount = ycount;
    int last_xcount_scaled = (xcount * factor) >> fix_digits;
    counter -= xcount + xcount + 1;
    xcount++;
    
    while(xcount < ycount) {
      if (counter < 0) {
        ycount--;
        counter += ycount + ycount;
        }
      
      int ycount_scaled = (ycount * factor) >> fix_digits;
      
      target.setPixel(x + xcount,y - ycount_scaled); // 1
      target.setPixel(x - xcount,y - ycount_scaled); // 8
      target.setPixel(x + xcount,y + ycount_scaled); // 4
      target.setPixel(x - xcount,y + ycount_scaled); // 5

      int xcount_scaled = (xcount * factor) >> fix_digits;
      
      if (xcount_scaled != last_xcount_scaled) {
        if (lastline_ycount == ycount) {
          target.setPixel(x + ycount,y + xcount_scaled);
          target.setPixel(x - ycount,y + xcount_scaled);
          target.setPixel(x + ycount,y - xcount_scaled);
          target.setPixel(x - ycount,y - xcount_scaled);
	  }
        else {
          target.drawHLine(x + ycount,y + xcount_scaled,x + lastline_ycount);
          target.drawHLine(x - lastline_ycount + 1,y + xcount_scaled,x - ycount + 1); 
          target.drawHLine(x + ycount,y - xcount_scaled,x + lastline_ycount);
          target.drawHLine(x - lastline_ycount + 1,y - xcount_scaled,x - ycount + 1); 
	  }

        last_xcount_scaled = xcount_scaled;
        lastline_ycount = ycount;
        }
      
      counter -= xcount + xcount + 1;
      xcount++;
      }
    }