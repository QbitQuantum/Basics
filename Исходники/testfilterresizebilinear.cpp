void PLTestFilterResizeBilinear::createBmp(PLBmp& Bmp)
{
  Bmp.Create (8, 8, PLPixelFormat::X8R8G8B8);

  int x,y;
  for (y=0; y<4; y++)
    for (x=0; x<4; x++)
      Bmp.SetPixel (x,y, PLPixel32 (255,0,0,0));

  for (y=0; y<4; y++)
    for (x=4; x<8; x++)
      Bmp.SetPixel (x,y, PLPixel32 (0,255,0,0));

  for (y=4; y<8; y++)
    for (x=0; x<4; x++)
      Bmp.SetPixel (x,y, PLPixel32 (0,0,255,0));

  for (y=4; y<8; y++)
    for (x=4; x<8; x++)
      Bmp.SetPixel (x,y, PLPixel32 (255,255,255,0));
}