static void DrawLine(void *data, long x1, long y1, long x2, long y2)
{
  MoveToEx((HDC)data, x1, y1, NULL);
  LineTo((HDC)data,x2,y2);
}