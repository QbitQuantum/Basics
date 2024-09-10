/* Unit clock render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT_CLOCK *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID VG4_UnitRender( vg4UNIT_CLOCK *Uni, vg4ANIM *Ani )
{
  DBL a, r;
  SYSTEMTIME t;

  GetLocalTime(&t);

  a = (t.wSecond) * 2 * 3.1415926535 / 60;
  r = Ani->W / 2.2;

  if (Ani->JBut[0])
    SetDCPenColor(Ani->hDC, RGB(255, 0, 0));
  else
    SetDCPenColor(Ani->hDC, RGB(0, 0, 0));

  MoveToEx(Ani->hDC, Ani->W / 2 + Ani->JX * 30, Ani->H / 2 + Ani->JY * 30, NULL);
  LineTo(Ani->hDC, Ani->W / 2 + Ani->JX * 30 + sin(a) * r, Ani->H / 2 + Ani->JY * 30 - cos(a) * r);
} /* End of 'VG4_UnitRender' function */