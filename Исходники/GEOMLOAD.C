/* Функция загрузки геометрического объекта.
 * АРГУМЕНТЫ:
 *   - геометрический объект:
 *       as4GEOM *G;
 *   - имя файла материалов:
 *       CHAR *FileName;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (BOOL) TRUE при успехе.
 */
BOOL AS4_GeomLoad( as4GEOM *G, CHAR *FileName )
{
  INT vn = 0, vtn = 0, vnn = 0, fn = 0, pn = 0, size, i, p;
  FILE *F;
  /* читаемые данные */
  VEC *ReadV, *ReadN;
  as4UV *ReadUV;
  INT (*ReadF)[3];
  /* хранение примитивов */
  struct
  {
    INT
      First, Last, /* первый и последний номера вершин примитива */
      Mtl;         /* материал примитива */
  } *PrimInfo;

  memset(G, 0, sizeof(as4GEOM));
  /* разбиваем имя на части и открываем файл */
  _splitpath(FileName, ModelDrive, ModelDir, ModelFileName, ModelFileExt);
  if ((F = fopen(FileName, "rt")) == NULL)
    return FALSE;

  /* считаем количества */
  while (fgets(Buf, sizeof(Buf), F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      vn++;
    else if (Buf[0] == 'v' && Buf[1] == 't')
      vtn++;
    else if (Buf[0] == 'v' && Buf[1] == 'n')
      vnn++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
      fn += Split() - 3;
    else if (strncmp(Buf, "usemtl", 6) == 0)
      pn++;

  if (pn == 0)
    pn = 1; /* материалы не использовались */

  /* загружаем:
   *   вершины                        vn
   *   нормали                        vvn
   *   текстурные координаты          vtn
   *   треугольники                   fn
   *   примитивы                      pn
   * дополнительно:
   *   индексы (Vv, Vn, Vt) <- новые номера вершин  ? (vn + vt + vnn) * ???
   *   начальные индексы              vn
   */

  /* выделяем память под вспомогательные данные */
  size = 
    sizeof(VEC) * vn +                        /*   вершины               vn */
    sizeof(VEC) * vnn +                       /*   нормали               vnn */
    sizeof(as4UV) * vtn +                     /*   текстурные координаты vtn */
    sizeof(INT [3]) * fn +                    /*   треугольники          fn */
    sizeof(PrimInfo[0]) * pn +                /*   примитивы             pn */
    sizeof(VertexRefs[0]) * (vn + vtn + vnn) + /*   индексы (Vv, Vn, Vt)  (vn + vt + vnn) */
    sizeof(INT) * vn;                         /*   начальные индексы     vn */
  if ((ReadV = malloc(size)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  memset(ReadV, 0, size);

  /* расставляем указатели */
  ReadN = ReadV + vn;
  ReadUV = (as4UV *)(ReadN + vnn);
  ReadF = (INT (*)[3])(ReadUV + vtn);
  VertexRefsStart = (INT *)(ReadF + fn);
  PrimInfo = (VOID *)(VertexRefsStart + vn);
  VertexRefs = (VOID *)(PrimInfo + pn);
  NumOfAllocedVertexRefs = vn + vtn + vnn;
  NumOfVertexRefs = 0;
  /* начала списка индексов вершин ==> -1 */
  memset(VertexRefsStart, 0xFF, sizeof(INT) * vn);
  memset(VertexRefs, 0xFF, sizeof(VertexRefs[0]) * NumOfAllocedVertexRefs);

  /* второй проход - читаем геометрию */
  rewind(F);
  vn = 0;
  vtn = 0;
  vnn = 0;
  fn = 0;
  pn = 0;
  PrimInfo[0].First = 0;

  /* считаем количества */
  while (fgets(Buf, sizeof(Buf), F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      FLT x = 0, y = 0, z = 0;

      sscanf(Buf + 2, "%f%f%f", &x, &y, &z);
      ReadV[vn++] = VecSet(x, y, z);
    }
    else if (Buf[0] == 'v' && Buf[1] == 't')
    {
      FLT u = 0, v = 0;

      sscanf(Buf + 3, "%f%f", &u, &v);
      ReadUV[vtn++] = AS4_UVSet(u, v);
    }
    else if (Buf[0] == 'v' && Buf[1] == 'n')
    {
      FLT nx = 0, ny = 0, nz = 0;

      sscanf(Buf + 3, "%f%f%f", &nx, &ny, &nz);
      ReadN[vnn++] = VecNormalize(VecSet(nx, ny, nz));
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n0[3], n1[3], n[3], r0, r1, r;

      Split();
      SCANF3(Parts[1], n0);
      r0 = GetVertexNo(n0[0], n0[1], n0[2]);

      SCANF3(Parts[2], n1);
      r1 = GetVertexNo(n1[0], n1[1], n1[2]);

      for (i = 3; i < NumOfParts; i++)
      {
        SCANF3(Parts[i], n);
        r = GetVertexNo(n[0], n[1], n[2]);

        ReadF[fn][0] = r0;
        ReadF[fn][1] = r1;
        ReadF[fn][2] = r;
        r1 = r;
        fn++;
      }
    }
    else if (strncmp(Buf, "usemtl", 6) == 0)
    {
      Split();

      /* запоминаем номер последней грани */
      if (pn != 0)
        PrimInfo[pn - 1].Last = fn - 1;

      /* ищем материал */
      for (i = 0; i < G->NumOfMtls; i++)
        if (strcmp(Parts[1], G->Mtls[i].Name) == 0)
          break;
      if (i == G->NumOfMtls)
        PrimInfo[pn].Mtl = -1;
      else
        PrimInfo[pn].Mtl = i;
      PrimInfo[pn].First = fn;
      pn++;
    }
    else if (strncmp(Buf, "mtllib ", 7) == 0)
    {
      Split();
      LoadMaterials(G, Parts[1]);
    }

  /* у последнего примитива запоминаем номер последней грани */
  if (pn == 0)
  {
    PrimInfo[0].Last = fn - 1;
    PrimInfo[0].Mtl = -1;
  }
  else
    PrimInfo[pn - 1].Last = fn - 1;
  fclose(F);

  /* Формируем примитивы из прочитанных данных */
  AS4_DefaultColor = ColorSet(1, 1, 1);
  for (p = 0; p < pn; p++)
  {
    INT minv, maxv, j;
    as4PRIM prim;
    BOOL is_need_normal = FALSE;

    minv = maxv = ReadF[PrimInfo[p].First][0];
    for (i = PrimInfo[p].First; i <= PrimInfo[p].Last; i++)
      for (j = 0; j < 3; j++)
      {
        if (minv > ReadF[i][j])
          minv = ReadF[i][j];
        if (maxv < ReadF[i][j])
          maxv = ReadF[i][j];
      }
    vn = maxv - minv + 1;
    fn = PrimInfo[p].Last - PrimInfo[p].First + 1;
    AS4_PrimCreate(&prim, AS4_PRIM_TRIMESH, vn, fn * 3);

    /* копируем вершины */
    for (i = 0; i < vn; i++)
    {
      INT n;

      prim.V[i].P = ReadV[VertexRefs[minv + i].Nv];
      if ((n = VertexRefs[minv + i].Nn) != -1)
        prim.V[i].N = ReadN[n];
      else
        is_need_normal = TRUE;
      if ((n = VertexRefs[minv + i].Nt) != -1)
        prim.V[i].T = ReadUV[n];
    }
    /* копируем грани */
    for (i = 0; i < fn; i++)
      for (j = 0; j < 3; j++)
        prim.I[i * 3 + j] = ReadF[PrimInfo[p].First + i][j] - minv;
    if (is_need_normal)
        AS4_PrimAutoNormals(&prim);
    prim.Mtl = PrimInfo[p].Mtl;
    AS4_GeomAddPrim(G, &prim);
  }
  /* освобождаем память из-под прочитанных данных */
  free(ReadV);
  return TRUE;
} /* End of 'AS4_GeomLoad' function */