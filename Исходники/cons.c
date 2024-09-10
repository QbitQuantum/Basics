static int init_buffer(HANDLE b)
{
  /* Set console size */
  COORD newSize = {W*2, H+1};
  SetConsoleScreenBufferSize(b, newSize);

  SMALL_RECT newWinSize;
  newWinSize.Left = 0;
  newWinSize.Top = 0;
  newWinSize.Right = W*2-1;
  newWinSize.Bottom = H;
  return SetConsoleWindowInfo(b, TRUE, &newWinSize);
}