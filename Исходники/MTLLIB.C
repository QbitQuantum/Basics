/* Функция загрузки материала из файла (*.MTL).
 * АРГУМЕНТЫ:
 *   - имя файла материала:
 *       CHAR *FileName;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (INT) количество загруженных материалов.
 */
INT AK1_MtlLoad( CHAR *FileName )
{
  FILE *F;
  INT cnt = 0, i, j;
  ak1MATERIAL Mtl = AK1_MtlLib[0];
  static CHAR
    Buf[1000], Name[_MAX_PATH],
    path_buffer[_MAX_PATH],
    drive[_MAX_DRIVE],
    dir[_MAX_DIR],
    fname[_MAX_FNAME],
    ext[_MAX_EXT];

  _splitpath(FileName, drive, dir, fname, ext);

  if ((F = fopen(FileName, "r")) == NULL)
    return 0;

  while (fgets(Buf, sizeof(Buf), F) != NULL)
  {
    /* пропускаем лидирующие пробелы */
    i = 0;
    while (Buf[i] != 0 && isspace(Buf[i]))
      i++;

    /* обрабатываем команды материалов */
    if (strncmp(Buf + i, "Ka", 2) == 0)
      sscanf(Buf + i + 3, "%f %f %f", &Mtl.Ka.X, &Mtl.Ka.Y, &Mtl.Ka.Z);
    else if (strncmp(Buf + i, "Kd", 2) == 0)
      sscanf(Buf + i + 3, "%f %f %f", &Mtl.Kd.X, &Mtl.Kd.Y, &Mtl.Kd.Z);
    else if (strncmp(Buf + i, "Ks", 2) == 0)
      sscanf(Buf + i + 3, "%f %f %f", &Mtl.Ks.X, &Mtl.Ks.Y, &Mtl.Ks.Z);
    else if (strncmp(Buf + i, "Ns", 2) == 0)
      sscanf(Buf + i + 3, "%f", &Mtl.Kp);
    else if (Buf[i] == 'D' || Buf[i] == 'd')
      sscanf(Buf + i + 2, "%f", &Mtl.Kt);
    else if (strncmp(Buf + i, "newmtl", 6) == 0)
    {
      /* выделяем в строку остаток массива Buf */
      j = 0;
      i += 7;
      while (j < sizeof(Name) - 1 && Buf[i] != 0 && Buf[i] != '\n')
        Name[j++] = Buf[i++];
      Name[j] = 0;

      /* добавляем материал */
      if (cnt++ != 0)
        AK1_MtlAdd(&Mtl);
      /* создаем материал */
      Mtl = AK1_MtlLib[0];
      strcpy(Mtl.Name, Name);
    }
    else if (strncmp(Buf + i, "map_Kd", 6) == 0)
    {
      /* выделяем в строку остаток массива Buf */
      j = 0;
      i += 7;
      while (j < sizeof(Name) - 1 && Buf[i] != 0 && Buf[i] != '\n')
        Name[j++] = Buf[i++];
      Name[j] = 0;

      /* загружаем текстуру */
      _makepath(path_buffer, drive, dir, Name, "");
      Mtl.TexId = AK1_TextureLoad(path_buffer);
    }
  }
  /* добавляем материал */
  if (cnt != 0)
    AK1_MtlAdd(&Mtl);
  fclose(F);
  return cnt;
} /* End of 'AK1_MtlLoad' function */