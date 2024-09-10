int collision_detect(BITMAP *sprite1, int xmin1, int ymin1, BITMAP *sprite2, int xmin2, int ymin2)
{
  int xmax1, ymax1, xmax2, ymax2;
  xmin1 -= sprite1->w/2; ymin1 -= sprite1->h/2;
  xmin2 -= sprite2->w/2; ymin2 -= sprite2->h/2;
  xmax1 = xmin1 + sprite1->w; ymax1 = ymin1 + sprite1->h;
  xmax2 = xmin2 + sprite2->w; ymax2 = ymin2 + sprite2->h;
  
  int xmin = max(xmin1, xmin2);
  int ymin = max(ymin1, ymin2);
  int xmax = min(xmax1, xmax2);
  int ymax = min(ymax1, ymax2);
  
  if (!(xmin1 <= xmax2 && xmax1 >= xmin2 && ymin1 <= ymax2 && ymax1 >= ymin2)) return 0; 

  for (int y = ymin; y < ymax; y++) 
  {
    for (int x = xmin; x < xmax; x++) 
    {
      int x1 = x - xmin1, y1 = y - ymin1;
      int x2 = x - xmin2, y2 = y - ymin2;
      int color1 = getpixel(sprite1, x1, y1);
      int color2 = getpixel(sprite2, x2, y2);
      if (color1 != TRANSPARENT && color2 != TRANSPARENT) { return 1; }
    }
  }
  return 0;
}