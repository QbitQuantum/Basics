void MI0283QT9::drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	int16_t dx, dy, dx2, dy2, err, stepx, stepy;

  if(x0 >= lcd_width)
  {
    x0 = lcd_width-1;
  }
  if(x1 >= lcd_width)
  {
    x1 = lcd_width-1;
  }
  if(y0 >= lcd_height)
  {
    y0 = lcd_height-1;
  }
  if(y1 >= lcd_height)
  {
    y1 = lcd_height-1;
  }

  if((x0 == x1) ||
     (y0 == y1)) //horizontal or vertical line
  {
    fillRect(x0, y0, x1, y1, color);
  }
  else
  {
    //calculate direction
    dx = x1 - x0;
    dy = y1 - y0;
    if(dx < 0) { dx = -dx; stepx = -1; } else { stepx = +1; }
    if(dy < 0) { dy = -dy; stepy = -1; } else { stepy = +1; }
    dx2 = dx << 1;
    dy2 = dy << 1;
    //draw line
    setArea(0, 0, lcd_width-1, lcd_height-1);
    drawPixel(x0, y0, color);
    if(dx > dy)
    {
      err = dy2 - dx;
      while(x0 != x1)
      {
        if(err >= 0)
        {
          y0  += stepy;
          err -= dx2;
        }
        x0  += stepx;
        err += dy2;
        drawPixel(x0, y0, color);
      }
    }
    else
    {
      err = dx2 - dy;
      while(y0 != y1)
      {
        if(err >= 0)
        {
          x0  += stepx;
          err -= dy2;
        }
        y0  += stepy;
        err += dx2;
        drawPixel(x0, y0, color);
      }
    }
  }

  return;
}