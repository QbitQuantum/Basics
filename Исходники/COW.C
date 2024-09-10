/* Функция построения объекта анимации.
 * АРГУМЕНТЫ:
 *   - указатель на "себя" - сам объект анимации:
 *       od6UNIT_COW *Unit;
 *   - указатель на контекст анимации:
 *       od6ANIM *Ani;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
static VOID CowUnitRender( od6UNIT_COW *Unit, od6ANIM *Ani )
{
  INT i, N = 0;
  VEC p = {1, 0, 0};
  POINT pt;
  static DBL Delta = 0.1;

  Delta += Ani->JZ * Ani->GlobalDeltaTime;


  OD6_RndMatrView = MatrViewLookAt(VecMulMatr(VecSet(0, 0, Ani->JX * Delta + 15), MatrRotateX(90 * Ani->JY)), VecSet(0, 0, 0), VecSet(0, 1, 0));
  OD6_RndMatrWorld = MatrRotateZ(-Ani->Time);
  OD6_RndMatrWorld = MatrMulMatr(OD6_RndMatrWorld, MatrScale(0.30, 0.30, 0.30));

  SetDCBrushColor(Ani->hDC, RGB(255, 255, 255));
  SetDCPenColor(Ani->hDC, RGB(255, 255, 255));

  srand(30);
  for (i = 0; i < N; i++)
  {
    p.X = 2.0 * rand() / RAND_MAX - 1 ;
    p.Y = 2.0 * rand() / RAND_MAX - 1 ;
    p.Z = 2.0 * rand() / RAND_MAX - 1 ;
    pt = OD6_RndWorldToScreen(p);
    if (i == 0)
      MoveToEx(Ani->hDC, pt.x , pt.y, NULL);
    else
      LineTo(Ani->hDC, pt.x , pt.y);
  }
  OD6_RndGObjDraw(&Unit->Cow, Ani->hDC);
 /*
  OD6_RndMatrWorld = MatrRotateZ(-Ani->GlobalTime / 60);
  OD6_RndMatrWorld = MatrMulMatr(OD6_RndMatrWorld, MatrScale(0.30, 0.30, 0.30));

  SetDCBrushColor(Ani->hDC, RGB(0, 255, 255));
  SetDCPenColor(Ani->hDC, RGB(0, 255, 255));

  OD6_RndGObjDraw(&Unit->Cow, Ani->hDC);

  OD6_RndMatrWorld = MatrRotateZ(-Ani->GlobalTime / 60 / 60);
  OD6_RndMatrWorld = MatrMulMatr(OD6_RndMatrWorld, MatrScale(0.30, 0.30, 0.30));

  SetDCBrushColor(Ani->hDC, RGB(255, 255, 0));
  SetDCPenColor(Ani->hDC, RGB(255, 255, 0));

  OD6_RndGObjDraw(&Unit->Cow, Ani->hDC);

  OD6_RndMatrWorld = MatrRotateY(Ani->Time * 30);

  OD6_RndMatrWorld = MatrMulMatr(OD6_RndMatrWorld, MatrScale(0.30, 0.30, 0.30));
  OD6_RndMatrWorld = MatrMulMatr(MatrTranslate(0.0, 0.0, 3 * 3.30), OD6_RndMatrWorld);
  OD6_RndGObjDraw(&Unit->Cow, Ani->hDC); */  
} /* End of 'CowUnitRender' function */