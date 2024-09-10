/* Функция построения объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       ak1UNIT_BALL *Uni;
 *   - указатель на контекст анимации:
 *       ak1ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID AK1_AnimCowRender( ak1UNIT_COW *Uni, ak1ANIM *Ani )
{
  int i, l = -1;
  DBL X1 = Ani->PosX;
  AK1_RndMatrWorld = MatrMulMatr(MatrMulMatr(MatrRotateX(Ani->AngleX), MatrRotateY(Ani->AngleY)), MatrScale(10, 10, 10));
  AK1_RndMatrView = MatrView(VecSet(8, 8, 8), VecSet(0, 0, 0), VecSet(0, 1, 0));
  SetDCPenColor(Ani->hDC, RGB(255, 255, 255));
//  AK1_RndGObjDraw(&Uni->Model);
  for (i = 0; i < 3; i++)
  {
    Ani->PosX = X1 + (i + l) * 600;
    AK1_RndGObjDraw(&Uni->Model);
  }
  Ani->PosX = X1;
} /* End of 'ak1_AnimUnitRender' function */