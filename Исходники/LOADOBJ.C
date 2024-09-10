/* Draw object functioln.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID ObjDraw( HDC hDC, INT H, INT W )
{
  INT i;

  for (i = 0; i < ObjNumOfV; i++)
  {
    /* рисуем точку ObjV[i] */
     
    SelectObject(hDC, GetStockObject(NULL_PEN));
    SelectObject(hDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hDC, RGB(0, 0, 0));  
    Ellipse(hDC, ObjV[i].X + W / 2, ObjV[i].Y + H / 2, ObjV[i].X + W / 2 + 5, ObjV[i].Y + H / 2 + 5);
  }              
} /* End of 'ObjDraw' function */