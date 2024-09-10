/* Функция построения объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       pd6UNIT_BALL *Uni;
 *   - указатель на контекст анимации:
 *       pd6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID PD6_RectUnitRender( pd6UNIT_RECT *Uni, pd6ANIM *Ani )
{
  DBL shift = fabs(sin(Uni->PhaseShift + (DBL)clock() / CLOCKS_PER_SEC * 3)) * 30;

  SetDCBrushColor(Ani->hDC, Uni->Color);
  Rectangle(Ani->hDC, Uni->Pos.X - 5 - shift, Uni->Pos.Y - 5, Uni->Pos.X + 5, Uni->Pos.Y + 5 - shift);
} /* End of 'PD6_AnimUnitRender' function */