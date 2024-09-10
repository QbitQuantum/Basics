static int Comp_TimeF(void)                                  //Сравнение времени создания файлов
{
   SYSTEMTIME sysTime;
   FILETIME fTime, flTime;
   TimeFileCopy(&sysTime);                                   //Время нового файла
   SystemTimeToFileTime(&sysTime, &flTime);                  //Преобразовали время
   LocalFileTimeToFileTime(&flTime, &fTime);
   return (CompareFileTime(&DataF.ftLastWriteTime, &fTime) == -1) ? IDOK : IDC_SCIP; //Действие в зависимости от времени записи файла
}