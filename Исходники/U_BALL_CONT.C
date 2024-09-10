/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       al5UNIT_BALL *Uni;
 *   - animation context:
 *       al5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AL5_UnitRender( al5UNIT_BALL_CONT *Uni, al5ANIM *Ani )
{
  VEC p = VecAddVec(Uni->Pos, Uni->Shift);
  
  SetDCBrushColor(Ani->hDC, Uni->Color);
  Ellipse(Ani->hDC, p.X - 20, p.Y - 20, p.X + 20, p.Y + 20);
} /* End of 'AL5_UnitRender' function */