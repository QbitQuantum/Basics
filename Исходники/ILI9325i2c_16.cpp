void ILI9325i2c_16::rotateChar(byte c, int x, int y, int pos, int deg)
{
  byte i, j, ch;
  word temp;
  int newx, newy;
  double radian;
  radian = deg * 0.0175;

  clearBit(CS);

  temp = ((c - cfont.offset) * ((cfont.x_size / 8) * cfont.y_size)) + 4;
  for (j = 0; j < cfont.y_size; j++)
  {
    for (int zz = 0; zz < (cfont.x_size / 8); zz++)
    {
      ch = pgm_read_byte(&cfont.font[temp + zz]);
      for (i = 0; i < 8; i++)
      {
        newx = x + (((i + (zz * 8) + (pos * cfont.x_size)) * cos(radian)) - ((j) * sin(radian)));
        newy = y + (((j) * cos(radian)) + ((i + (zz * 8) + (pos * cfont.x_size)) * sin(radian)));

        setXY(newx, newy, newx + 1, newy + 1);

        if ((ch & (1 << (7 - i))) != 0)
        {
          setPixel(fcolorr, fcolorg, fcolorb);
        }
        else
        {
          setPixel(bcolorr, bcolorg, bcolorb);
        }
      }
    }
    temp += (cfont.x_size / 8);
  }

  setBit(CS);
  clrXY();
}